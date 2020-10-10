namespace iim.AnimationCurveViewer
{
    public struct Vector3
    {
        public double X, Y, Z;

        public Vector3(double x, double y, double z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public void Product(ref Mat3D m, out Vector3 result)
        {
            result.X = m.A1 * X + m.B1 * Y + m.C1 * Z;
            result.Y = m.A2 * X + m.B2 * Y + m.C2 * Z;
            result.Z = m.A3 * X + m.B3 * Y + m.C3 * Z;
        }
    }
}