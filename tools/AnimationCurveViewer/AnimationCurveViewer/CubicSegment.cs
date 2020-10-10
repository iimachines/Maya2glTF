using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Media;

namespace iim.AnimationCurveViewer
{
    public sealed class CubicSegment
    {
        public readonly double A, B, C, D;

        public readonly Point FirstPoint;
        public Point LastPoint;

        public CubicSegment(double a, double b, double c, double d, Point firstPoint, Point lastPoint)
        {
            A = a;
            B = b;
            C = c;
            D = d;
            FirstPoint = firstPoint;
            LastPoint = lastPoint;
        }

        public override string ToString()
        {
            return $"{A:0.00}x^3 + {B:0.00}x^2 + {C:0.00}x + {D:0.00}, first:{FirstPoint}, last:{LastPoint:0.00}";
        }

        public IEnumerable<Point> Sample(double dist)
        {
            var x1 = FirstPoint.X;
            var x2 = LastPoint.X;
            var cx = (int)Math.Ceiling((x2 - x1) / dist);
            var ps = Enumerable.Range(0, cx + 1)
                .Select(i => x1 + i * (x2 - x1) / cx)
                .Select(x => new Point(x, AbsEvaluate(x)));
            return ps;
        }

        public double RelEvaluate(double u)
        {
            return ((A * u + B) * u + C) * u + D;
        }

        public double RelDerivative(double u)
        {
            return (3 * A * u + 2 * B) * u + C;
        }

        public (double u1, double u2, int count) ZeroRelDerivatives => Solvers.SolveQuadratic(3 * A, 2 * B, C);
        
        public (double x1, double x2, int count) ZeroAbsDerivatives
        {
            get
            {
                var (u1, u2, count) = ZeroRelDerivatives;
                var x1 = u1 + FirstPoint.X;
                var x2 = u2 + FirstPoint.X;
                return (x1, x2, count);
            }
        }

        public double RelSecondDerivative(double u)
        {
            return 6 * A * u + 2 * B;
        }

        public double ZeroSecondRelDerivative =>
            // 6 * A * u + 2 * B = 0
            // <=>
            // u = -B/3A
            -B / (3 * A);

        public double ZeroSecondAbsDerivative => ZeroSecondRelDerivative + FirstPoint.X;

        public double AbsEvaluate(double x)
        {
            return RelEvaluate(x - FirstPoint.X) + FirstPoint.Y;
        }

        public double AbsDerivative(double x)
        {
            return RelDerivative(x - FirstPoint.X);
        }

        public static IEnumerable<Point> GetPoints(IList<CubicSegment> segments)
        {
            CubicSegment segment = null;
            for (var index = 0; index < segments.Count; index++)
            {
                segment = segments[index];
                yield return segment.FirstPoint;
            }

            if (segment != null)
            {
                yield return segment.LastPoint;
            }
        }


        public static StreamGeometry GetGeometry(IList<CubicSegment> segments)
        {
            var geometry = new StreamGeometry();

            using (var sgc = geometry.Open())
            {
                for (var index = 0; index < segments.Count; index++)
                {
                    var segment = segments[index];
                    if (index == 0)
                    {
                        sgc.BeginFigure(segment.FirstPoint, false, false);
                    }

                    var cp = segment.GetControlPoints();
                    sgc.BezierTo(cp[1], cp[2], cp[3], true, true);
                }
            }

            geometry.Freeze();
            return geometry;
        }

        public Point[] GetControlPoints()
        {
            var p1 = FirstPoint;
            var p4 = LastPoint;

            var xDiff = p4.X - p1.X;
            var x1 = p1.X + xDiff / 3.0;
            var x2 = p1.X + 2.0 * xDiff / 3.0;

            var y1 = AbsEvaluate(x1);
            var y2 = AbsEvaluate(x2);

            var f1 = 0.296296296296296296296; // (1-1/3)^3
            var f2 = 0.037037037037037037037; // (1-2/3)^3
            var f3 = 0.296296296296296296296; // (2/3)^3

            var b1 = y1 - p1.Y * f1 - p4.Y / 27.0;
            var b2 = y2 - p1.Y * f2 - f3 * p4.Y;

            var c1 = (-2 * b1 + b2) / -0.666666666666666666;
            var c2 = (b2 - 0.2222222222222 * c1) / 0.44444444444444444;

            var p2 = new Point(x1, c1);
            var p3 = new Point(x2, c2);
            return new[] { p1, p2, p3, p4 };
        }
    }
}