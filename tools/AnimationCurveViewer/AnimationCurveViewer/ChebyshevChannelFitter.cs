using System;
using System.IO;
using System.Linq;
using System.Numerics;
using glTFLoader.Schema;

namespace iim.AnimationCurveViewer
{
    public class ChebyshevChannelFitter
    {
        private readonly BinaryWriter _chevyStream;
        private readonly BinaryWriter _errorStream;

        public int InputByteCount;
        public int OutputByteCount;

        public ChebyshevChannelFitter(Stream chevyStream, Stream errorStream)
        {
            _chevyStream = new BinaryWriter(chevyStream);
            _errorStream = new BinaryWriter(errorStream);
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
                AnimationChannelTarget.PathEnum.rotation => 1D/1024,
                AnimationChannelTarget.PathEnum.scale => 0.01,
                AnimationChannelTarget.PathEnum.weights => 0.01,
                _ => throw new ArgumentOutOfRangeException()
            };

            var bits = new int[]
            {
                0,
                2,
                4,
                8
            };

            for (int axis = 0; axis < dimension; ++axis)
            {
                for (int pointStart = 0; pointStart < sampleCount; pointStart += bucketLength)
                {
                    var pointCount = Math.Min(bucketLength, sampleCount - pointStart);

                    if (pointCount <= 4)
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

                    // Fit Chebyshev polynomial to the spline, using all points
                    var dblCheby = new Chebyshev(x => alglib.spline1dcalc(spline, x), xPoints[0], xPoints[pointCount - 1], pointCount);

                    // We store the coefficients using floats.
                    var chebyFloats = dblCheby.Coefficients.Select(d => (double)(float)d).ToArray();
                    var fltCheby = new Chebyshev(chebyFloats, dblCheby.MinX, dblCheby.MaxX);

                    var bestChebyCount = 1;
                    var bestChebyError = 0.0;
                    var bestErrorBits = 0;
                    var bestByteLength = int.MaxValue;
                    var bestFound = false;

                    foreach (var qBits in bits)
                    {
                        double qMid = Math.Pow(2, qBits - 1) - 0.5;
                        var maxError = absMaxError * Math.Max(qMid, 1);

                        // Find the truncated polygon that results in the smallest bitsize.
                        var qChebyCount = pointCount;
                        var qChebyError = 0.0;
                        var qChebyFound = false;

                        for (var chebyCount = 1; chebyCount <= pointCount; ++chebyCount)
                        {
                            var found = true;
                            var error = 0.0;

                            for (int i = 0; i < pointCount; ++i)
                            {
                                var py = fltCheby.Evaluate(xPoints[i], chebyCount);
                                var dy = yPoints[i] - py;
                                error = Math.Max(error, Math.Abs(dy));
                                if (error > maxError)
                                {
                                    found = false;
                                    break;
                                }
                            }

                            if (found)
                            {
                                qChebyCount = chebyCount;
                                qChebyError = error;
                                qChebyFound = true;
                                break;
                            }
                        }

                        // if (!qChebyFound)
                        // {
                        //     for (int i = 0; i < pointCount; ++i)
                        //     {
                        //         var py = fltCheby.Evaluate(xPoints[i]);
                        //         var dy = Math.Abs(yPoints[i] - py);
                        //         if (dy >= maxError)
                        //         {
                        //             Console.WriteLine($"{i} -> {dy:0.0000}");
                        //         }
                        //     }
                        //     Console.WriteLine();
                        // }

                        var isPerfect = qBits == 0 || qChebyError < 1e-6;
                        var errorByteCount = (isPerfect ? 0 : pointCount * qBits + 7) / 8;
                        var qByteLength = 1 + qChebyCount * 4 + errorByteCount;

                        if (bestByteLength > qByteLength)
                        {
                            bestByteLength = qByteLength;
                            bestChebyError = qChebyError;
                            bestChebyCount = qChebyCount;
                            bestErrorBits = qBits;
                        }
                    }

                    // Found best bits.
                    {

                        OutputByteCount += bestByteLength;
                        InputByteCount += 4 * pointCount;

                        var isPerfect = bestErrorBits == 0 || bestChebyError < 1e-6;

                        Console.WriteLine($"{axis} -> {bestChebyCount} #{bestErrorBits}");

                        for (int i = 0; i < bestChebyCount; ++i)
                        {
                            _chevyStream.Write((float)fltCheby.Coefficients[i]);
                        }

                        // Re-evaluate 
                        double qMax = Math.Pow(2, bestErrorBits) - 1;
                        double qMid = Math.Pow(2, bestErrorBits - 1) - 0.5;
                        var maxError = absMaxError * qMid;

                        for (int i = 0; i < pointCount; ++i)
                        {
                            var j = (pointStart + i) * dimension + axis;
                            var py = fltCheby.Evaluate(xPoints[i], bestChebyCount);
                            if (isPerfect)
                            {
                                values[j] = (float)py;
                            }
                            else
                            {
                                var dy = yPoints[i] - py;
                                var qy = Math.Round(qMid * (dy / maxError) + qMid);
                                if (qy < 0 || qy > qMax)
                                    throw new Exception();
                                _errorStream.Write((byte) qy);
                                var fy = (qy - qMid) / qMid * maxError;
                                if (!double.IsFinite(fy))
                                    throw new Exception();
                                values[j] = (float)(py + fy);
                            }
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