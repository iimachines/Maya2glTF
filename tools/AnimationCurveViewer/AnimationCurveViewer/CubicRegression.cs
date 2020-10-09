using System;
using System.Collections.Generic;
using System.Windows;

namespace iim.AnimationCurveViewer
{
    public static class CubicRegression
    {
        private struct State
        {
            /// <summary>
            /// Sjk = sum of u[i]^j * v[i]^k where (u[i],v[i]) are the coordinates of sample#i relative to the segment's FirstSample
            /// </summary>
            public double S60;
            public double S50;
            public double S40;
            public double S30;
            public double S20;
            public double S10;
            public double S00;
            public double S31;
            public double S21;
            public double S11;
            public double S01;

            public CubicSegment Segment;

            public readonly int SegmentIndex;

            public readonly double FixedC;


            /// <summary>
            /// HACK: This point is both the current sample and the origin point (in the accumulator)
            /// </summary>
            public readonly Point Point;

            public State(Point point, int segmentIndex, double fixedC) : this()
            {
                Point = point;
                S00 = 1;
                SegmentIndex = segmentIndex;
                FixedC = fixedC;
            }

            public void Compute(Point origin)
            {
                S10 = Point.X - origin.X;
                S01 = Point.Y - origin.Y;

                S20 = S10 * S10;
                S30 = S20 * S10;
                S40 = S20 * S20;
                S50 = S20 * S30;
                S60 = S30 * S30;

                S11 = S10 * S01;
                S21 = S20 * S01;
                S31 = S30 * S01;
            }

            public CubicSegment GetNextCubicSegment(State current, double epsilon)
            {
                current.Compute(Point);

                S60 += current.S60;
                S50 += current.S50;
                S40 += current.S40;
                S30 += current.S30;
                S20 += current.S20;
                S10 += current.S10;
                S00 += current.S00;
                S31 += current.S31;
                S21 += current.S21;
                S11 += current.S11;
                S01 += current.S01;

                // Need at least 4 points
                if (S00 < 4)
                    return null;

                // Our cubic segment has the equation f(u) = a*u^3 + b*u^2 + c*u + d
                // Each segment is defined relative to an origin close to its first sample point, to improve floating point precision
                //
                // So 0 <= u < width of segment
                //
                // So to evaluate the absolute y-value at absolute x-position, we compute f(x-x0)+y0,
                // where (x0,y0) is the origin of the segment 
                //
                // In general, to fit a cubic curve to a set of samples, we must fit the solutions of 
                // df/da = 0, df/db = 0, df/dc = 0, df/dd = 0
                // where f = ∑(u,v) (a*u^3 + b*u^2 + c*u + d - v)^2
                // and (u,v) are the relative coordinates of the samples
                //
                // These partial derivative equations are (see Brainstorm.wxmx for wxMaxima)
                // df/da = 0 <=> 0 = 2*a*S60 + 2*b*S50 + 2*c*S40 - 2*S31 + 2*d*S30
                // df/db = 0 <=> 0 = 2*a*S50 + 2*b*S40 + 2*c*S30 - 2*S21 + 2*d*S20
                // df/dc = 0 <=> 0 = 2*a*S40 + 2*b*S30 + 2*c*S20 - 2*S11 + 2*d*S10
                // df/dd = 0 <=> 0 = 2*a*S30 + 2*b*S20 + 2*c*S10 - 2*S01 + 2*d
                //
                // where Sjk = ∑(u,v) u^j * v^k 
                //
                // This simplifies to
                // a*S60 + b*S50 + c*S40 + d*S30 = S31 
                // a*S50 + b*S40 + c*S30 + d*S20 = S21 
                // a*S40 + b*S30 + c*S20 + d*S10 = S11 
                // a*S30 + b*S20 + c*S10 + d	 = S01
                // <=>
                // [S60,S50,S40,S30] [a]   [S31]
                // [S50,S40,S30,S20] [b]   [S21]
                // [S40,S30,S20,S10] [c] = [S11]
                // [S30,S20,S10,  1] [d]   [S01]

                Mat4D A = new Mat4D(
                    S60, S50, S40, S30,
                    S50, S40, S30, S20,
                    S40, S30, S20, S10,
                    S30, S20, S10, 1);

                double det = A.Determinant();
                if (Math.Abs(det) < epsilon)
                    return null;

                Mat4D M;
                A.Adjoints(out M);

                Vec4D V = new Vec4D(S31 / det, S21 / det, S11 / det, S01 / det);

                Vec4D abcd;
                M.Product(ref V, out abcd);

                return new CubicSegment(abcd.X, abcd.Y, abcd.Z, abcd.W, SegmentIndex, Point, current.Point, Segment);
            }
        }

        public static IEnumerable<CubicSegment> FitCubics(this Point[] points, double maxError, double epsilon = float.Epsilon)
        {
            State accum = default;

            for (var index = 0; index < points.Length; index++)
            {
                var p = points[index];
                var current = new State(p, 0, 0);
                if (index == 0)
                {
                    accum = current;
                    continue;
                }

                var fitting = accum;

                var segment = accum.GetNextCubicSegment(current, epsilon);

                if (segment != null)
                {
                    if (segment.Error > maxError)
                    {
                        yield return fitting.Segment;

                        // Started over at half the segment.
                        double fixedC = fitting.Segment.AbsDerivative(fitting.Segment.LastPoint.X);
                        accum = new State(fitting.Segment.LastPoint, fitting.SegmentIndex + 1, fixedC);
                        accum.GetNextCubicSegment(current, epsilon);
                    }
                    else
                    {
                        // The segment still fits, replace the previous segment
                        accum.Segment = segment;
                    }
                }
            }

            if (accum.S00 >= 4)
            {
                yield return accum.Segment;
            }
        }
    }
}