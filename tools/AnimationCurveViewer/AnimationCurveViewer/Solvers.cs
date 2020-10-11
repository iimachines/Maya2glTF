using System;
using System.Collections.Generic;
using System.Linq;
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

        public static int[] FitAkimaSpline(Point[] inputPoints, double maxError)
        {
            var n = inputPoints.Length;

            // Start with 4 points
            var knotIndices = new List<int> { 0, (n - 1) / 3, 2 * n / 3, n - 1 };

            for (;;)
            {
                var knotPoints = knotIndices.Select(i => inputPoints[i]).ToArray();
                var knotXs = knotPoints.Select(p => p.X).ToArray();
                var knotYs = knotPoints.Select(p => p.Y).ToArray();

                alglib.spline1dbuildakima(knotXs, knotYs, out var spline);

                // Check each internal for error, and split if needed.
                var knotCount = knotIndices.Count;
                var splitIndices = new List<int>(knotCount * 2);

                for (int i = 0; i < knotCount - 1; i++)
                {
                    var iStart = knotIndices[i];
                    var iEnd = knotIndices[i + 1];

                    splitIndices.Add(iStart);

                    int iSplit = -1;
                    double eSplit = 0;

                    for (int j = iStart; j < iEnd; ++j)
                    {
                        var p = inputPoints[j];
                        var z = alglib.spline1dcalc(spline, p.X);

                        var error = Math.Abs(p.Y - z);

                        if (error > maxError && error > eSplit)
                        {
                            eSplit = error;
                            iSplit = j;
                        }
                    }

                    if (iSplit >= 0)
                    {
                        splitIndices.Add(iSplit);
                    }
                }

                splitIndices.Add(knotIndices.Last());

                if (splitIndices.Count == knotIndices.Count)
                    return knotIndices.ToArray();

                knotIndices = splitIndices;
            }
        }
    }
}