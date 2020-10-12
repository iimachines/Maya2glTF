using System;
using System.Buffers;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace iim.AnimationCurveViewer
{
    public static class Solvers
    {
        public static (double x1, double x2, int count) SolveQuadratic(double a, double b, double c, double epsilon = float.Epsilon)
        {
            double bb4ac = b * b - 4 * a * c;

            if (bb4ac < 0)
                return (double.NaN, double.NaN, 0);

            var sqrt = Math.Sqrt(bb4ac);
            var t1 = (-b + sqrt) / (2 * a);
            var t2 = (-b - sqrt) / (2 * a);
            var x1 = Math.Min(t1, t2);
            var x2 = Math.Max(t1, t2);
            return (x1, x2, Math.Abs(x1 - x2) < epsilon ? 1 : 2);
        }

        public static (IList<int> knotIndices, double largestError) FitAkimaSplines(Point[][] samplesPerAxis, int pointCount, int dimension, double[] maxErrors)
        {
            // Brute force algorithm, randomly tries knots, then splits each interval at largest error.

            var random = new Random(0x76543210);

            // TODO: Preprocess to find discontinuities! 
            // TODO: Research Adaptive spline fitting with particle swarm optimization
            // https://arxiv.org/pdf/1907.12160.pdf
            // Matlab code: https://github.com/mohanty-sd/SHAPES
            var result = Enumerable
                .Range(0, 100)
                .Select(n => Enumerable
                    .Range(0, n / 10)
                    .Select(_ => random.Next(1, pointCount - 1))
                    .Distinct()
                    .OrderBy(r => r)
                    .ToArray())
                .Concat(new[]
                {
                    new[] { pointCount / 2 },
                    new[] { 1 * pointCount / 3, 2 * pointCount / 3 }
                })
                .AsParallel()
                .Select(middleKnotIndices =>
                {
                    // Start with 3 points
                    var knotIndices = middleKnotIndices.Prepend(0).Append(pointCount - 1).ToList();

                    var splines = new alglib.spline1dinterpolant[dimension];

                    var knotXs = new double[pointCount];
                    var knotYs = new double[pointCount];

                    for (; ; )
                    {
                        // Build splines.
                        for (int axis = 0; axis < dimension; axis++)
                        {
                            splines[axis]?.Dispose();

                            var points = samplesPerAxis[axis];
                            for (var ki = 0; ki < knotIndices.Count; ki++)
                            {
                                var p = points[knotIndices[ki]];
                                knotXs[ki] = p.X;
                                knotYs[ki] = p.Y;
                            }

                            alglib.spline1dbuildakima(knotXs, knotYs, knotIndices.Count, out splines[axis]);
                        }

                        // Split at highest error of any curve.
                        var knotCount = knotIndices.Count;
                        var splitIndices = new List<int>(knotCount * 2);

                        double largestError = 0D;

                        for (int i = 0; i < knotCount - 1; i++)
                        {
                            var iStart = knotIndices[i];
                            var iEnd = knotIndices[i + 1];

                            splitIndices.Add(iStart);

                            int splitIndex = -1;
                            double splitError = 0;

                            for (int j = iStart; j < iEnd; ++j)
                            {
                                for (int axis = 0; axis < dimension; axis++)
                                {
                                    var p = samplesPerAxis[axis][j];
                                    var z = alglib.spline1dcalc(splines[axis], p.X);

                                    var error = Math.Abs(p.Y - z);

                                    largestError = Math.Max(largestError, error);

                                    if (error > maxErrors[axis] && error > splitError)
                                    {
                                        splitError = error;
                                        splitIndex = j;
                                    }
                                }
                            }

                            if (splitIndex >= 0)
                            {
                                splitIndices.Add(splitIndex);
                            }
                        }

                        splitIndices.Add(knotIndices.Last());

                        if (splitIndices.Count == knotIndices.Count)
                        {
                            // Console.WriteLine($"{name} #start={middleKnotIndices.Length} #knots={knotIndices.Count}, error={largestError}");
                            return (knotIndices, largestError);
                        }

                        knotIndices = splitIndices;
                    }
                })
                .AsSequential()
                .OrderBy(pair => pair.knotIndices.Count)
                .ThenBy(pair => pair.largestError)
                .First();

            return result;
        }

        public static (IList<int> knotIndices, sbyte[] quantErrors) FitAkimaSpline(Point[] quantizedSamples, int quantErrorBits)
        {
            int pointCount = quantizedSamples.Length;

            // Brute force algorithm, randomly tries knots, then splits each interval at largest error.
            var qMin = -(1 << (quantErrorBits - 1));
            var qMax = (1 << (quantErrorBits - 1)) - 1;

            var random = new Random(0x76543210);

            // TODO: Preprocess to find discontinuities! 
            // TODO: Research Adaptive spline fitting with particle swarm optimization
            // https://arxiv.org/pdf/1907.12160.pdf
            // Matlab code: https://github.com/mohanty-sd/SHAPES
            var result = Enumerable
#if DEBUG
                .Range(0, 0)
#else
                .Range(0, 100)
#endif
                .Select(n => Enumerable
                    .Range(0, n / 10)
                    .Select(_ => random.Next(1, pointCount - 1))
                    .Distinct()
                    .OrderBy(r => r)
                    .ToArray())
                .Concat(new[]
                {
                    new[] { pointCount / 2 },
                    new[] { 1 * pointCount / 3, 2 * pointCount / 3 }
                })
#if !DEBUG
                .AsParallel()
#endif
                .Select(middleKnotIndices =>
                {
                    // Start with 3 points
                    var knotIndices = middleKnotIndices.Prepend(0).Append(pointCount - 1).ToList();

                    var knotXs = new double[pointCount];
                    var knotYs = new double[pointCount];

                    alglib.spline1dinterpolant spline = null;

                    for (; ; )
                    {
                        // Build spline.
                        spline?.Dispose();

                        for (var ki = 0; ki < knotIndices.Count; ki++)
                        {
                            var p = quantizedSamples[knotIndices[ki]];
                            knotXs[ki] = p.X;
                            knotYs[ki] = p.Y;
                        }

                        alglib.spline1dbuildakima(knotXs, knotYs, knotIndices.Count, out spline);

                        // Split at highest error.
                        var knotCount = knotIndices.Count;
                        var splitIndices = new List<int>(knotCount * 2);

                        var quantBuffer = ArrayPool<sbyte>.Shared.Rent(pointCount);
                        var quantIndex = 0;

                        for (int i = 0; i < knotCount - 1; i++)
                        {
                            var iStart = knotIndices[i];
                            var iEnd = knotIndices[i + 1];

                            splitIndices.Add(iStart);

                            bool shouldSplit = false;
                            int splitIndex = -1;
                            double splitError = 0;

                            for (int j = iStart; j < iEnd; ++j)
                            {
                                var p = quantizedSamples[j];
                                var y = p.Y;
                                var z = Math.Round(alglib.spline1dcalc(spline, p.X));

                                var d = y - z;
                                var error = Math.Abs(d);

                                quantBuffer[j] = (sbyte)d;

                                shouldSplit |= d < qMin || d > qMax;

                                if (error > splitError)
                                {
                                    splitError = error;
                                    splitIndex = j;
                                }
                            }

                            if (shouldSplit)
                            {
                                splitIndices.Add(splitIndex);
                            }
                        }

                        splitIndices.Add(knotIndices.Last());

                        if (splitIndices.Count == knotIndices.Count)
                        {
                            var quantErrors = quantBuffer.Take(pointCount).ToArray();
                            ArrayPool<sbyte>.Shared.Return(quantBuffer);
                            return (knotIndices, quantErrors);
                        }

                        ArrayPool<sbyte>.Shared.Return(quantBuffer);
                        knotIndices = splitIndices;
                    }
                })
#if !DEBUG
                .AsSequential()
#endif
                .OrderBy(pair => pair.knotIndices.Count)
                .First();

            return result;
        }

        public static IList<(int stop, alglib.barycentricinterpolant)> FitBestPolynomial(Point[] samples, double maxError)
        {
            var polys = new List<(int, alglib.barycentricinterpolant)>();

            var xArray = new Span<double>(samples.Select(p => p.X).ToArray());
            var yArray = new Span<double>(samples.Select(p => p.Y).ToArray());
            var count = samples.Length;

            int index = 0;

            while (index < count)
            {
                var xSlice = xArray.Slice(index).ToArray();
                var ySlice = yArray.Slice(index).ToArray();

                int start = index;

                var best = Enumerable
                    .Range(1, 10)
                    .AsParallel()
                    .Select(m =>
                    {
                        int n;

                        alglib.barycentricinterpolant poly = null;

                        for (n = Math.Min(m, count - start); start + n <= count; ++n)
                        {
                            alglib.polynomialfit(xSlice, ySlice, n, m, out var info, out var candidate, out var rep);

                            if (Math.Abs(rep.maxerror) > maxError)
                                break;

                            poly = candidate;
                        }

                        return (poly, m, n);
                    })
                    .AsSequential()
                    // Check if this polygon compresses better.
                    // 1 byte to store the degree, 1 byte to store the offset, 4 bytes per float for the coefficients.
                    .OrderBy(entry => (2 + 4D * entry.m) / (4 * entry.n))
                    .First();

                index += best.n;

                Debug.Assert(best.poly != null);

                polys.Add((index - 1, best.poly));
            }

            return polys;
        }

        public static IList<int> FitAkimaSpline(Point[] points, double maxError)
        {
            int pointCount = points.Length;

            // Brute force algorithm, randomly tries knots, then splits each interval at largest error.
            var random = new Random(0x76543210);

            // TODO: Preprocess to find discontinuities! 
            // TODO: Research Adaptive spline fitting with particle swarm optimization
            // https://arxiv.org/pdf/1907.12160.pdf
            // Matlab code: https://github.com/mohanty-sd/SHAPES
            var result = Enumerable
#if DEBUG
                .Range(0, 0)
#else
                .Range(0, 100)
#endif
                .Select(n => Enumerable
                    .Range(0, n / 10)
                    .Select(_ => random.Next(1, pointCount - 1))
                    .Distinct()
                    .OrderBy(r => r)
                    .ToArray())
                .Concat(new[]
                {
                    new[] { pointCount / 2 },
                    new[] { 1 * pointCount / 3, 2 * pointCount / 3 }
                })
#if !DEBUG
                .AsParallel()
#endif
                .Select(middleKnotIndices =>
                {
                    // Start with 3 points
                    var knotIndices = middleKnotIndices.Prepend(0).Append(pointCount - 1).ToList();

                    var knotXs = new double[pointCount];
                    var knotYs = new double[pointCount];

                    alglib.spline1dinterpolant spline = null;

                    for (; ; )
                    {
                        // Build spline.
                        spline?.Dispose();

                        for (var ki = 0; ki < knotIndices.Count; ki++)
                        {
                            var p = points[knotIndices[ki]];
                            knotXs[ki] = p.X;
                            knotYs[ki] = p.Y;
                        }

                        alglib.spline1dbuildakima(knotXs, knotYs, knotIndices.Count, out spline);

                        // Split at highest error.
                        var knotCount = knotIndices.Count;
                        var splitIndices = new List<int>(knotCount * 2);

                        for (int i = 0; i < knotCount - 1; i++)
                        {
                            var iStart = knotIndices[i];
                            var iEnd = knotIndices[i + 1];

                            splitIndices.Add(iStart);

                            bool shouldSplit = false;
                            int splitIndex = -1;
                            double splitError = 0;

                            for (int j = iStart; j < iEnd; ++j)
                            {
                                var p = points[j];
                                var y = p.Y;
                                var z = alglib.spline1dcalc(spline, p.X);

                                var error = Math.Abs(y - z);

                                shouldSplit |= error > maxError;

                                if (error > splitError)
                                {
                                    splitError = error;
                                    splitIndex = j;
                                }
                            }

                            if (shouldSplit)
                            {
                                splitIndices.Add(splitIndex);
                            }
                        }

                        splitIndices.Add(knotIndices.Last());

                        if (splitIndices.Count == knotIndices.Count)
                            return knotIndices;

                        knotIndices = splitIndices;
                    }
                })
#if !DEBUG
                .AsSequential()
#endif
                .OrderBy(knotIndices => knotIndices.Count)
                .First();

            return result;
        }
    }
}