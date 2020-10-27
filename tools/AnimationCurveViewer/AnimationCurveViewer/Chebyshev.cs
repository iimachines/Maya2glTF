using System;
using System.Collections.Generic;
using System.Linq;

namespace iim.AnimationCurveViewer
{
    public class Chebyshev
    {
        public readonly int Count;
        public readonly double[] Coefficients;
        public readonly double MinX;
        public readonly double MaxX;

        public Chebyshev(ReadOnlySpan<double> coefficients, double minX, double maxX)
        {
            Count = coefficients.Length;
            Coefficients = coefficients.ToArray();
            MinX = minX;
            MaxX = maxX;
        }

        public Chebyshev(IEnumerable<float> coefficients, double minX, double maxX) : this(coefficients.Select(f => (double) f).ToArray(), minX, maxX)
        {
        }

        public Chebyshev(Func<double, double> func, double minX, double maxX, int count)
        {
            Count = count;
            Coefficients = new double[count];
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
                Coefficients[j] = fac * sum;
            }
        }

        public int GetTruncatedCount(double threshold)
        {
            for (int m = Count; --m >= 1;)
            {
                if (Math.Abs(Coefficients[m - 1]) > threshold)
                {
                    return m;
                }
            }

            return 1;
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

        // int setm(double thresh) { while (m > 1 && abs(c[m - 1]) < thresh) m--; return m; }
        //
        // double eval(double x, int m);
        // inline double operator() (double x) {return eval(x, m);
    }

#if false
Chebyshev Chebyshev::derivative()
{
    int j;
    double con;
    double[] cder(n);
    cder[n - 1] = 0.0;
    cder[n - 2] = 2 * (n - 1) * c[n - 1];
    for (j = n - 2; j > 0; j--)
        cder[j - 1] = cder[j + 1] + 2 * j * c[j];
    con = 2.0 / (b - a);
    for (j = 0; j < n; j++) cder[j] *= con;
    return Chebyshev(cder, a, b);
}
Chebyshev Chebyshev::integral()
{
    int j;
    double sum = 0.0, fac = 1.0, con;
    double[] cint(n);
    con = 0.25 * (b - a);
    for (j = 1; j < n - 1; j++)
    {
        cint[j] = con * (c[j - 1] - c[j + 1]) / j;
        sum += fac * cint[j];
        fac = -fac;
    }
    cint[n - 1] = con * c[n - 2] / (n - 1);
    sum += fac * cint[n - 1];
    cint[0] = 2.0 * sum;
    return Chebyshev(cint, a, b);
}
Chebyshev::Chebyshev(double[] & d)
	: n(d.size()), m(n), c(n), a(-1.), b(1.)
    {
    c[n - 1] = d[n - 1];
    c[n - 2] = 2.0 * d[n - 2];
    for (int j = n - 3; j >= 0; j--)
    {
        c[j] = 2.0 * d[j] + c[j + 2];
        for (int i = j + 1; i < n - 2; i++)
        {
            c[i] = (c[i] + c[i + 2]) / 2;
        }
        c[n - 2] /= 2;
        c[n - 1] /= 2;
    }
}
double[] Chebyshev::polycofs(int m)
{
    int k, j;
    double sv;
    double[] d(m),dd(m);
    for (j = 0; j < m; j++) d[j] = dd[j] = 0.0;
    d[0] = c[m - 1];
    for (j = m - 2; j > 0; j--)
    {
        for (k = m - j; k > 0; k--)
        {
            sv = d[k];
            d[k] = 2.0 * d[k - 1] - dd[k];
            dd[k] = sv;
        }
        sv = d[0];
        d[0] = -dd[0] + c[j];
        dd[0] = sv;
    }
    for (j = m - 1; j > 0; j--) d[j] = d[j - 1] - dd[j];
    d[0] = -dd[0] + 0.5 * c[0];
    return d;
}
#endif
}