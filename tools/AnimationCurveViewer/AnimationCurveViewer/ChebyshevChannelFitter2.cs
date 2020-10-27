using System;
using System.Dynamic;
using System.IO;
using System.Linq;
using System.Numerics;
using glTFLoader.Schema;

namespace iim.AnimationCurveViewer
{
    public class ChebyshevChannelFitter2
    {
        private readonly BinaryWriter _chevyStream;
        private readonly BinaryWriter _errorStream;

        public int InputByteCount;
        public int OutputByteCount;

        public ChebyshevChannelFitter2(Stream chevyStream, Stream errorStream)
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

            const int bucketLength = 256;

            var xPoints = new double[bucketLength];
            var yPoints = new double[bucketLength];

            var absMaxError = pathKind switch
            {
                AnimationChannelTarget.PathEnum.translation => 1,
                AnimationChannelTarget.PathEnum.rotation => 0.1,
                AnimationChannelTarget.PathEnum.scale => 0.1,
                AnimationChannelTarget.PathEnum.weights => 0.01,
                _ => throw new ArgumentOutOfRangeException()
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
                    var chebyFloats = dblCheby.Coefficients.Select(d => (float)d).ToArray();

                    Chebyshev bestCheby = new Chebyshev(chebyFloats, dblCheby.MinX, dblCheby.MaxX);

                    // Selectively zero smallest coefficient, until error is too large.
                    for (; ; )
                    {
                        bool fits = true;

                        var fltCheby = new Chebyshev(chebyFloats, dblCheby.MinX, dblCheby.MaxX);

                        for (int i = 0; i < pointCount; ++i)
                        {
                            var py = fltCheby.Evaluate(xPoints[i]);
                            var dy = yPoints[i] - py;
                            if (Math.Abs(dy) > absMaxError)
                            {
                                fits = false;
                                break;
                            }
                        }

                        if (!fits)
                            break;

                        bestCheby = fltCheby;

                        var smallestIndices = chebyFloats
                            .Select((f, i) => (f, i))
                            .Where(pair => pair.f != 0)
                            .OrderBy(pair => Math.Abs(pair.f))
                            .Select(pair => pair.i)
                            .ToArray();

                        if (smallestIndices.Length == 0)
                        {
                            // All floats are zero. 
                            break;
                        }

                        chebyFloats[smallestIndices[0]] = 0;
                    }

                    int count = chebyFloats.Count(f => f != 0);

                    OutputByteCount += 4 * (count + 1);
                    InputByteCount += 4 * pointCount;

                    Console.WriteLine($"{axis} -> {count}");

                    for (int i = 0; i < count; ++i)
                    {
                        _chevyStream.Write(chebyFloats[i]);
                    }

                    for (int i = 0; i < pointCount; ++i)
                    {
                        var j = (pointStart + i) * dimension + axis;
                        var py = bestCheby.Evaluate(xPoints[i]);
                        values[j] = (float)py;
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