namespace iim.AnimationCurveViewer
{
    public struct Vec4D
    {
        public double X, Y, Z, W;

        public Vec4D(double x, double y, double z, double w)
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

        public void Product(ref Mat4D m, out Vec4D result)
        {
            result.X = m.A1 * X + m.B1 * Y + m.C1 * Z + m.D1 * W;
            result.Y = m.A2 * X + m.B2 * Y + m.C2 * Z + m.D2 * W;
            result.Z = m.A3 * X + m.B3 * Y + m.C3 * Z + m.D3 * W;
            result.W = m.A4 * X + m.B4 * Y + m.C4 * Z + m.D4 * W;
        }
    }
}