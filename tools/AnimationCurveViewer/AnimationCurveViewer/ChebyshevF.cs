using System;
using System.Collections.Generic;
using System.Linq;

namespace iim.AnimationCurveViewer
{
    public class ChebyshevF
    {
        public readonly int Count;
        public readonly double[] Coefficients;
        public readonly short[] FixedPoints;
        public readonly double MinX;
        public readonly double MaxX;

        public ChebyshevF(Func<double, double> func, double minX, double maxX, int count, double[] scales)
        {
            Count = count;
            Coefficients = new double[count];
            FixedPoints = new short[count];
            MinX = minX;
            MaxX = maxX;

            int k, j;
            double y;
            double[] f = new double[Count];
            var bma = 0.5 * (MaxX - MinX);
            var bpa = 0.5 * (MaxX + MinX);
            for (k = 0; k < Count; k++)
            {
                y = Math.Cos(Math.PI * (k + 0.5) / Count);
                f[k] = func(y * bma + bpa);
            }
            var fac = 2.0 / Count;
            for (j = 0; j < Count; j++)
            {
                var sum = 0.0;
                for (k = 0; k < Count; k++)
                    sum += f[k] * Math.Cos(Math.PI * j * (k + 0.5) / Count);

                // We store coefficients as fixed points.
                var c = fac * sum;
                FixedPoints[j] = (short)Math.Round(c * scales[j]);
                Coefficients[j] = FixedPoints[j] / scales[j];
            }
        }

        public double Evaluate(double x, int m)
        {
            double d = 0.0, dd = 0.0, y;
            int j;
            if ((x - MinX) * (x - MaxX) > 0.0)
                throw new ArgumentOutOfRangeException(nameof(x));

            var y2 = 2.0 * (y = (2.0 * x - MinX - MaxX) / (MaxX - MinX));

            for (j = m - 1; j > 0; j--)
            {
                var sv = d;
                d = y2 * d - dd + Coefficients[j];
                dd = sv;
            }
            return y * d - dd + 0.5 * Coefficients[0];
        }

        public double Evaluate(double x) => Evaluate(x, Count);
    }
}