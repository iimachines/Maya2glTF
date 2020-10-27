using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Runtime.ExceptionServices;
using glTFLoader.Schema;

namespace iim.AnimationCurveViewer
{
    public class ChebyshevChannelFitter3
    {
        private readonly BinaryWriter _chevyStream;
        private readonly BinaryWriter _countStream;

        public int InputByteCount;
        public int OutputByteCount;

        public ChebyshevChannelFitter3(Stream chevyStream, Stream errorStream)
        {
            _chevyStream = new BinaryWriter(chevyStream);
            _countStream = new BinaryWriter(errorStream);
        }

        public void Process(Gltf gltf,
            Animation animation, AnimationChannel channel,
            Span<float> times, Span<float> inputValues, bool isRoot)
        {
            var pathKind = channel.Target.Path;

            var accessor = gltf.GetChannelOutputAccessor(animation, channel);
            var dimension = accessor.GetComponentDimension();

            var sampleCount = times.Length;

            var values = inputValues;

            if (channel.Target.Path == AnimationChannelTarget.PathEnum.rotation)
            {
                // Convert to log of quaternion, assuming quaternions are unit length
                dimension = 3;

                // 4 -> 3
                InputByteCount += 4 * sampleCount;

                values = new float[sampleCount * 3];

                for (int i = 0; i < sampleCount; ++i)
                {
                    var qx = inputValues[i * 4 + 0];
                    var qy = inputValues[i * 4 + 1];
                    var qz = inputValues[i * 4 + 2];
                    var qw = inputValues[i * 4 + 3];

                    var q1 = new Quaternion(qx, qy, qz, qw);
                    var v = q1.Log();

                    values[i * 3 + 0] = v.X;
                    values[i * 3 + 1] = v.Y;
                    values[i * 3 + 2] = v.Z;
                }
            }

            var bucketLength = 256;

            var xPoints = new double[bucketLength];
            var yPoints = new double[bucketLength];

            var absMaxError = pathKind switch
            {
                AnimationChannelTarget.PathEnum.translation => 0.1,
                AnimationChannelTarget.PathEnum.rotation => 1D / 1024,
                AnimationChannelTarget.PathEnum.scale => 0.01,
                AnimationChannelTarget.PathEnum.weights => 0.01,
                _ => throw new ArgumentOutOfRangeException()
            };

            var coefScales = Enumerable.Range(0, 100).Select(i => Math.Exp(i) / absMaxError).ToArray();

            const int bytesPerCoef = 2;

            for (int axis = 0; axis < dimension; ++axis)
            {
                for (int pointStart = 0; pointStart < sampleCount; pointStart += bucketLength)
                {
                    var pointCount = Math.Min(bucketLength, sampleCount - pointStart);

                    if (pointCount < 2)
                    {
                        // Not enough points in bucket to do compression.
                        OutputByteCount += 1 + 4 * pointCount;
                        InputByteCount += 4 * pointCount;
                        continue;
                    }

                    for (int i = 0; i < pointCount; ++i)
                    {
                        var j = (pointStart + i) * dimension + axis;
                        var t = times[pointStart + i];
                        var v = values[j];
                        xPoints[i] = t;
                        yPoints[i] = v;
                    }

                    // Build a spline through all the points
                    alglib.spline1dbuildakima(xPoints, yPoints, pointCount, out var spline);

                    (int bestCheby, int bestEnd, double bestCompression)[] FitChevy(int startIndex, int maxChebyCount)
                    {
                        var fits = Enumerable.Range(1, maxChebyCount + 1).AsParallelInRelease().Select(chebyCount =>
                          {
                              var pickChebyCount = 1;
                              var pickCompression = 0.0;
                              var pickEnd = startIndex;

                              for (int end = pointCount - startIndex < maxChebyCount ? pointCount - 1 : startIndex + 1; end < pointCount; ++end)
                              {
                                  var cheby = new ChebyshevF(x => alglib.spline1dcalc(spline, x),
                                      xPoints[startIndex], xPoints[end], chebyCount, coefScales);

                                  // See if the curve fits.
                                  bool fits = true;

                                  for (int i = startIndex + 1; i <= end; ++i)
                                  {
                                      var py = cheby.Evaluate(xPoints[i], chebyCount);
                                      var dy = yPoints[i] - py;
                                      if (Math.Abs(dy) > absMaxError)
                                      {
                                          fits = false;
                                          break;
                                      }
                                  }

                                  if (!fits)
                                      break;

                                  double inputByteLength = (end - startIndex + 1) * 4;
                                  double outputByteLength = 1 + 1 + chebyCount * bytesPerCoef;
                                  double compression = inputByteLength / outputByteLength;

                                  if (pickCompression <= compression)
                                  {
                                      pickCompression = compression;
                                      pickChebyCount = chebyCount;
                                      pickEnd = end;
                                  }
                              }

                              return (pickChebyCount, pickEnd, pickCompression);
                          })
                        .AsSequentialInRelease()
                        .OrderByDescending(pair => pair.pickCompression)
                        .ToArray();

                        return fits;
                    }

#if DEBUG
                    IEnumerable<int> chebyCounts = new[] { 8 };
#else
                    IEnumerable<int> chebyCounts = new[] { 4, 8, 16, 24, 32 };
#endif

                    var trials = chebyCounts
                        .AsParallelInRelease()
                        .Select(maxChebyCount =>
                        {
                            int start = 0;
                            int inputByteCount = 0;
                            int outputByteCount = 0;

                            var entries = new List<(int chebyCount, int start, int end, double compression)>();

                            while (start < pointCount - 2)
                            {
                                // Find the best fitting Chebyshev polynomial 
                                var fits = FitChevy(start, maxChebyCount);

                                var (chebyCount, end, compression) = fits.First();

                                entries.Add((chebyCount, start, end, compression));

                                inputByteCount += (end - start + 1) * 4;

                                // 1 byte for Cheby #coefficients, 1 byte for #samples
                                outputByteCount += 1 + 1 + chebyCount * bytesPerCoef;

                                start = end + 1;
                            }

                            return (inputByteCount, outputByteCount, entries);
                        })
                        .AsSequentialInRelease()
                        .ToArray();

                    var bestTrial = trials.OrderBy(trial => trial.outputByteCount).First();

                    InputByteCount += bestTrial.inputByteCount;
                    OutputByteCount += bestTrial.outputByteCount;

                    foreach (var (chebyCount, start, end, _) in bestTrial.entries)
                    {
                        var cheby = new ChebyshevF(x => alglib.spline1dcalc(spline, x),
                            xPoints[start], xPoints[end], chebyCount, coefScales);

                        _countStream.Write((byte)cheby.Count);
                        _countStream.Write((byte)(start - end + 1));
                        foreach (var coef in cheby.FixedPoints)
                        {
                            _chevyStream.Write(coef);
                        }

                        for (int i = start; i <= end; ++i)
                        {
                            var j = (pointStart + i) * dimension + axis;
                            var py = cheby.Evaluate(xPoints[i], chebyCount);
                            values[j] = (float)py;
                        }
                    }
                }
            }

            if (channel.Target.Path == AnimationChannelTarget.PathEnum.rotation)
            {
                // Convert back to quaternions
                for (int i = 0; i < sampleCount; ++i)
                {
                    var nx = values[i * 3 + 0];
                    var ny = values[i * 3 + 1];
                    var nz = values[i * 3 + 2];

                    var q = new Vector3(nx, ny, nz).Exp();

                    inputValues[i * 4 + 0] = q.X;
                    inputValues[i * 4 + 1] = q.Y;
                    inputValues[i * 4 + 2] = q.Z;
                    inputValues[i * 4 + 3] = q.W;
                }
            }
        }
    }
}