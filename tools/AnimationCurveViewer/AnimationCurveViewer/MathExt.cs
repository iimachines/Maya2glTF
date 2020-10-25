using System;
using System.Numerics;

namespace iim.AnimationCurveViewer
{
    public static class MathExt
    {
        public static Vector3 Log(this in Quaternion q)
        {
            // https://math.stackexchange.com/questions/2552/the-logarithm-of-quaternion
            var s = q.X;
            var v = new Vector3(q.Y, q.Z, q.W);
            var ang = MathF.Acos(s);
            var l = v.Length();

            if (l < 1e-9)
                return Vector3.Zero;

            return v * ang / l;
        }

        public static Quaternion Exp(this in Vector3 v)
        {
            var ang = v.Length();

            if (ang < 1e-9)
                return Quaternion.Identity;

            var n = v / ang;

            // https://math.stackexchange.com/questions/2552/the-logarithm-of-quaternion
            var cosAng = MathF.Cos(ang);
            var sinAng = MathF.Sin(ang);

            return new Quaternion(cosAng, n.X * sinAng, n.Y * sinAng, n.Z * sinAng);
        }
    }
}