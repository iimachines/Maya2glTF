using System;

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
    }
}