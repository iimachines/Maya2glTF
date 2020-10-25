using System;
using System.Diagnostics;
using System.Linq;
using System.Windows;
using glTFLoader.Schema;

namespace iim.AnimationCurveViewer
{
    public class ChebyshevChannelFitter
    {
        public int InputByteCount;
        public int OutputByteCount;

        public void Process(Gltf gltf,
            Animation animation, AnimationChannel channel,
            Span<float> times, Span<float> values, bool isRoot)
        {
            var pathKind = channel.Target.Path;

            var accessor = gltf.GetChannelOutputAccessor(animation, channel);
            var dimension = accessor.GetComponentDimension();

            var sampleCount = times.Length;

            var bucketLength = 32;

            var xPoints = new double[bucketLength];
            var yPoints = new double[bucketLength];

            // var maxError = pathKind switch
            // {
            //     AnimationChannelTarget.PathEnum.translation => 0.05,
            //     AnimationChannelTarget.PathEnum.rotation => 0.005,
            //     AnimationChannelTarget.PathEnum.scale => 0.005,
            //     AnimationChannelTarget.PathEnum.weights => 0.01,
            //     _ => throw new ArgumentOutOfRangeException()
            // };

            // The maximum error so that we can encode the difference in 4 bits
            var absMaxError = pathKind switch
            {
                AnimationChannelTarget.PathEnum.translation => 0.01,
                AnimationChannelTarget.PathEnum.rotation => 0.001,
                AnimationChannelTarget.PathEnum.scale => 0.001,
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

                        byte[] errors = new byte[pointCount];

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
                                errors[i] = (byte)qy;
                                var fy = (qy - qMid) / qMid * maxError;
                                if (!double.IsFinite(fy))
                                    throw new Exception();
                                values[j] = (float)(py + fy);
                            }
                        }
                    }
                }
            }
        }
    }
}