/*
* Copyright (c) 2012-2014 AssimpNet - Nicholas Woodfield
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

using System;
using System.Globalization;
using System.Runtime.InteropServices;

namespace iim.AnimationCurveViewer
{
    /// <summary>
    /// Represents a 4x4 column-vector matrix (X base is the first column, Y base is the second, Z base the third, and translation the fourth). 
    /// Memory layout is row major. Right handed conventions are used by default.
    /// </summary>
    [Serializable]
    [StructLayout(LayoutKind.Sequential)]
    public struct Mat4D : IEquatable<Mat4D>
    {
        /// <summary>
        /// Value at row 1, column 1 of the matrix
        /// </summary>
        public double A1;

        /// <summary>
        /// Value at row 1, column 2 of the matrix
        /// </summary>
        public double A2;

        /// <summary>
        /// Value at row 1, column 3 of the matrix
        /// </summary>
        public double A3;

        /// <summary>
        /// Value at row 1, column 4 of the matrix
        /// </summary>
        public double A4;

        /// <summary>
        /// Value at row 2, column 1 of the matrix
        /// </summary>
        public double B1;

        /// <summary>
        /// Value at row 2, column 2 of the matrix
        /// </summary>
        public double B2;

        /// <summary>
        /// Value at row 2, column 3 of the matrix
        /// </summary>
        public double B3;

        /// <summary>
        /// Value at row 2, column 4 of the matrix
        /// </summary>
        public double B4;

        /// <summary>
        /// Value at row 3, column 1 of the matrix
        /// </summary>
        public double C1;

        /// <summary>
        /// Value at row 3, column 2 of the matrix
        /// </summary>
        public double C2;

        /// <summary>
        /// Value at row 3, column 3 of the matrix
        /// </summary>
        public double C3;

        /// <summary>
        /// Value at row 3, column 4 of the matrix
        /// </summary>
        public double C4;

        /// <summary>
        /// Value at row 4, column 1 of the matrix
        /// </summary>
        public double D1;

        /// <summary>
        /// Value at row 4, column 2 of the matrix
        /// </summary>
        public double D2;

        /// <summary>
        /// Value at row 4, column 3 of the matrix
        /// </summary>
        public double D3;

        /// <summary>
        /// Value at row 4, column 4 of the matrix
        /// </summary>
        public double D4;

        private static Mat4D _identity = new Mat4D(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

        /// <summary>
        /// Gets the identity matrix.
        /// </summary>
        public static Mat4D Identity
        {
            get
            {
                return _identity;
            }
        }

        /// <summary>
        /// Gets if this matrix is an identity matrix.
        /// </summary>
        public bool IsIdentity
        {
            get
            {
                double epsilon = 10e-3f;

                return (A2 <= epsilon && A2 >= -epsilon &&
                A3 <= epsilon && A3 >= -epsilon &&
                A4 <= epsilon && A4 >= -epsilon &&
                B1 <= epsilon && B1 >= -epsilon &&
                B3 <= epsilon && B3 >= -epsilon &&
                B4 <= epsilon && B4 >= -epsilon &&
                C1 <= epsilon && C1 >= -epsilon &&
                C2 <= epsilon && C2 >= -epsilon &&
                C4 <= epsilon && C4 >= -epsilon &&
                D1 <= epsilon && D1 >= -epsilon &&
                D2 <= epsilon && D2 >= -epsilon &&
                D3 <= epsilon && D3 >= -epsilon &&
                A1 <= 1.0f + epsilon && A1 >= 1.0f - epsilon &&
                B2 <= 1.0f + epsilon && B2 >= 1.0f - epsilon &&
                C3 <= 1.0f + epsilon && C3 >= 1.0f - epsilon &&
                D4 <= 1.0f + epsilon && D4 >= 1.0f - epsilon);
            }
        }

        /// <summary>
        /// Gets or sets the value at the specific one-based row, column
        /// index. E.g. i = 1, j = 2 gets the value in row 1, column 2 (MA2). Indices
        /// out of range return a value of zero.
        /// 
        /// </summary>
        /// <param name="i">One-based Row index</param>
        /// <param name="j">One-based Column index</param>
        /// <returns>Matrix value</returns>
        public double this[int i, int j]
        {
            get
            {
                switch (i)
                {
                    case 1:
                        switch (j)
                        {
                            case 1:
                                return A1;
                            case 2:
                                return A2;
                            case 3:
                                return A3;
                            case 4:
                                return A4;
                            default:
                                return 0;
                        }
                    case 2:
                        switch (j)
                        {
                            case 1:
                                return B1;
                            case 2:
                                return B2;
                            case 3:
                                return B3;
                            case 4:
                                return B4;
                            default:
                                return 0;
                        }
                    case 3:
                        switch (j)
                        {
                            case 1:
                                return C1;
                            case 2:
                                return C2;
                            case 3:
                                return C3;
                            case 4:
                                return C4;
                            default:
                                return 0;
                        }
                    case 4:
                        switch (j)
                        {
                            case 1:
                                return D1;
                            case 2:
                                return D2;
                            case 3:
                                return D3;
                            case 4:
                                return D4;
                            default:
                                return 0;
                        }
                    default:
                        return 0;
                }
            }
            set
            {
                switch (i)
                {
                    case 1:
                        switch (j)
                        {
                            case 1:
                                A1 = value;
                                break;
                            case 2:
                                A2 = value;
                                break;
                            case 3:
                                A3 = value;
                                break;
                            case 4:
                                A4 = value;
                                break;
                        }
                        break;
                    case 2:
                        switch (j)
                        {
                            case 1:
                                B1 = value;
                                break;
                            case 2:
                                B2 = value;
                                break;
                            case 3:
                                B3 = value;
                                break;
                            case 4:
                                B4 = value;
                                break;
                        }
                        break;
                    case 3:
                        switch (j)
                        {
                            case 1:
                                C1 = value;
                                break;
                            case 2:
                                C2 = value;
                                break;
                            case 3:
                                C3 = value;
                                break;
                            case 4:
                                C4 = value;
                                break;
                        }
                        break;
                    case 4:
                        switch (j)
                        {
                            case 1:
                                D1 = value;
                                break;
                            case 2:
                                D2 = value;
                                break;
                            case 3:
                                D3 = value;
                                break;
                            case 4:
                                D4 = value;
                                break;
                        }
                        break;
                }
            }
        }

        /// <summary>
        /// Constructs a new Matrix4x4.
        /// </summary>
        /// <param name="a1">Element at row 1, column 1</param>
        /// <param name="a2">Element at row 1, column 2</param>
        /// <param name="a3">Element at row 1, column 3</param>
        /// <param name="a4">Element at row 1, column 4</param>
        /// <param name="b1">Element at row 2, column 1</param>
        /// <param name="b2">Element at row 2, column 2</param>
        /// <param name="b3">Element at row 2, column 3</param>
        /// <param name="b4">Element at row 2, column 4</param>
        /// <param name="c1">Element at row 3, column 1</param>
        /// <param name="c2">Element at row 3, column 2</param>
        /// <param name="c3">Element at row 3, column 3</param>
        /// <param name="c4">Element at row 3, column 4</param>
        /// <param name="d1">Element at row 4, column 1</param>
        /// <param name="d2">Element at row 4, column 2</param>
        /// <param name="d3">Element at row 4, column 3</param>
        /// <param name="d4">Element at row 4, column 4</param>
        public Mat4D(double a1, double a2, double a3, double a4, double b1, double b2, double b3, double b4,
            double c1, double c2, double c3, double c4, double d1, double d2, double d3, double d4)
        {
            this.A1 = a1;
            this.A2 = a2;
            this.A3 = a3;
            this.A4 = a4;

            this.B1 = b1;
            this.B2 = b2;
            this.B3 = b3;
            this.B4 = b4;

            this.C1 = c1;
            this.C2 = c2;
            this.C3 = c3;
            this.C4 = c4;

            this.D1 = d1;
            this.D2 = d2;
            this.D3 = d3;
            this.D4 = d4;
        }

        /// <summary>
        /// Transposes this matrix (rows become columns, vice versa).
        /// </summary>
        public void Transpose()
        {
            Mat4D m = this;

            m.A4 = A4;
            m.B4 = B4;
            m.C4 = C4;
            m.D1 = D1;
            m.D2 = D2;
            m.D3 = D3;

            A2 = m.B1;
            A3 = m.C1;
            A4 = m.D1;

            B1 = m.A2;
            B3 = m.C2;
            B4 = m.D2;

            C1 = m.A3;
            C2 = m.B3;
            C4 = m.D3;

            D1 = m.A4;
            D2 = m.B4;
            D3 = m.C4;
        }

        public void Adjoints(out Mat4D m)
        {
            m.A1 = (B2 * (C3 * D4 - C4 * D3) + B3 * (C4 * D2 - C2 * D4) + B4 * (C2 * D3 - C3 * D2));
            m.A2 = -(A2 * (C3 * D4 - C4 * D3) + A3 * (C4 * D2 - C2 * D4) + A4 * (C2 * D3 - C3 * D2));
            m.A3 = (A2 * (B3 * D4 - B4 * D3) + A3 * (B4 * D2 - B2 * D4) + A4 * (B2 * D3 - B3 * D2));
            m.A4 = -(A2 * (B3 * C4 - B4 * C3) + A3 * (B4 * C2 - B2 * C4) + A4 * (B2 * C3 - B3 * C2));
            m.B1 = -(B1 * (C3 * D4 - C4 * D3) + B3 * (C4 * D1 - C1 * D4) + B4 * (C1 * D3 - C3 * D1));
            m.B2 = (A1 * (C3 * D4 - C4 * D3) + A3 * (C4 * D1 - C1 * D4) + A4 * (C1 * D3 - C3 * D1));
            m.B3 = -(A1 * (B3 * D4 - B4 * D3) + A3 * (B4 * D1 - B1 * D4) + A4 * (B1 * D3 - B3 * D1));
            m.B4 = (A1 * (B3 * C4 - B4 * C3) + A3 * (B4 * C1 - B1 * C4) + A4 * (B1 * C3 - B3 * C1));
            m.C1 = (B1 * (C2 * D4 - C4 * D2) + B2 * (C4 * D1 - C1 * D4) + B4 * (C1 * D2 - C2 * D1));
            m.C2 = -(A1 * (C2 * D4 - C4 * D2) + A2 * (C4 * D1 - C1 * D4) + A4 * (C1 * D2 - C2 * D1));
            m.C3 = (A1 * (B2 * D4 - B4 * D2) + A2 * (B4 * D1 - B1 * D4) + A4 * (B1 * D2 - B2 * D1));
            m.C4 = -(A1 * (B2 * C4 - B4 * C2) + A2 * (B4 * C1 - B1 * C4) + A4 * (B1 * C2 - B2 * C1));
            m.D1 = -(B1 * (C2 * D3 - C3 * D2) + B2 * (C3 * D1 - C1 * D3) + B3 * (C1 * D2 - C2 * D1));
            m.D2 = (A1 * (C2 * D3 - C3 * D2) + A2 * (C3 * D1 - C1 * D3) + A3 * (C1 * D2 - C2 * D1));
            m.D3 = -(A1 * (B2 * D3 - B3 * D2) + A2 * (B3 * D1 - B1 * D3) + A3 * (B1 * D2 - B2 * D1));
            m.D4 = (A1 * (B2 * C3 - B3 * C2) + A2 * (B3 * C1 - B1 * C3) + A3 * (B1 * C2 - B2 * C1));
        }

        /// <summary>
        /// Compute the determinant of this matrix.
        /// </summary>
        /// <returns>The determinant</returns>
        public double Determinant()
        {
            return A1 * B2 * C3 * D4 - A1 * B2 * C4 * D3 + A1 * B3 * C4 * D2 - A1 * B3 * C2 * D4
                + A1 * B4 * C2 * D3 - A1 * B4 * C3 * D2 - A2 * B3 * C4 * D1 + A2 * B3 * C1 * D4
                - A2 * B4 * C1 * D3 + A2 * B4 * C3 * D1 - A2 * B1 * C3 * D4 + A2 * B1 * C4 * D3
                + A3 * B4 * C1 * D2 - A3 * B4 * C2 * D1 + A3 * B1 * C2 * D4 - A3 * B1 * C4 * D2
                + A3 * B2 * C4 * D1 - A3 * B2 * C1 * D4 - A4 * B1 * C2 * D3 + A4 * B1 * C3 * D2
                - A4 * B2 * C3 * D1 + A4 * B2 * C1 * D3 - A4 * B3 * C1 * D2 + A4 * B3 * C2 * D1;
        }

        public void Product(ref Vec4D v, out Vec4D result)
        {
            result.X = A1 * v.X + A2 * v.Y + A3 * v.Z + A4 * v.W;
            result.Y = B1 * v.X + B2 * v.Y + B3 * v.Z + B4 * v.W;
            result.Z = C1 * v.X + C2 * v.Y + C3 * v.Z + C4 * v.W;
            result.W = D1 * v.X + D2 * v.Y + D3 * v.Z + D4 * v.W;
        }

        /// <summary>
        /// Tests equality between two matrices.
        /// </summary>
        /// <param name="a">First matrix</param>
        /// <param name="b">Second matrix</param>
        /// <returns>True if the matrices are equal, false otherwise</returns>
        public static bool operator ==(Mat4D a, Mat4D b)
        {
            return (((a.A1 == b.A1) && (a.A2 == b.A2) && (a.A3 == b.A3) && (a.A4 == b.A4))
                && ((a.B1 == b.B1) && (a.B2 == b.B2) && (a.B3 == b.B3) && (a.B4 == b.B4))
                && ((a.C1 == b.C1) && (a.C2 == b.C2) && (a.C3 == b.C3) && (a.C4 == b.C4))
                && ((a.D1 == b.D1) && (a.D2 == b.D2) && (a.D3 == b.D3) && (a.D4 == b.D4)));
        }

        /// <summary>
        /// Tests inequality between two matrices.
        /// </summary>
        /// <param name="a">First matrix</param>
        /// <param name="b">Second matrix</param>
        /// <returns>True if the matrices are not equal, false otherwise</returns>
        public static bool operator !=(Mat4D a, Mat4D b)
        {
            return (((a.A1 != b.A1) || (a.A2 != b.A2) || (a.A3 != b.A3) || (a.A4 != b.A4))
                || ((a.B1 != b.B1) || (a.B2 != b.B2) || (a.B3 != b.B3) || (a.B4 != b.B4))
                || ((a.C1 != b.C1) || (a.C2 != b.C2) || (a.C3 != b.C3) || (a.C4 != b.C4))
                || ((a.D1 != b.D1) || (a.D2 != b.D2) || (a.D3 != b.D3) || (a.D4 != b.D4)));
        }


        /// <summary>
        /// Performs matrix multiplication. Multiplication order is B x A. That way, SRT concatenations
        /// are left to right.
        /// </summary>
        /// <param name="a">First matrix</param>
        /// <param name="b">Second matrix</param>
        /// <returns>Multiplied matrix</returns>
        public static Mat4D operator *(Mat4D a, Mat4D b)
        {
            return new Mat4D(a.A1 * b.A1 + a.B1 * b.A2 + a.C1 * b.A3 + a.D1 * b.A4,
                                 a.A2 * b.A1 + a.B2 * b.A2 + a.C2 * b.A3 + a.D2 * b.A4,
                                 a.A3 * b.A1 + a.B3 * b.A2 + a.C3 * b.A3 + a.D3 * b.A4,
                                 a.A4 * b.A1 + a.B4 * b.A2 + a.C4 * b.A3 + a.D4 * b.A4,
                                 a.A1 * b.B1 + a.B1 * b.B2 + a.C1 * b.B3 + a.D1 * b.B4,
                                 a.A2 * b.B1 + a.B2 * b.B2 + a.C2 * b.B3 + a.D2 * b.B4,
                                 a.A3 * b.B1 + a.B3 * b.B2 + a.C3 * b.B3 + a.D3 * b.B4,
                                 a.A4 * b.B1 + a.B4 * b.B2 + a.C4 * b.B3 + a.D4 * b.B4,
                                 a.A1 * b.C1 + a.B1 * b.C2 + a.C1 * b.C3 + a.D1 * b.C4,
                                 a.A2 * b.C1 + a.B2 * b.C2 + a.C2 * b.C3 + a.D2 * b.C4,
                                 a.A3 * b.C1 + a.B3 * b.C2 + a.C3 * b.C3 + a.D3 * b.C4,
                                 a.A4 * b.C1 + a.B4 * b.C2 + a.C4 * b.C3 + a.D4 * b.C4,
                                 a.A1 * b.D1 + a.B1 * b.D2 + a.C1 * b.D3 + a.D1 * b.D4,
                                 a.A2 * b.D1 + a.B2 * b.D2 + a.C2 * b.D3 + a.D2 * b.D4,
                                 a.A3 * b.D1 + a.B3 * b.D2 + a.C3 * b.D3 + a.D3 * b.D4,
                                 a.A4 * b.D1 + a.B4 * b.D2 + a.C4 * b.D3 + a.D4 * b.D4);
        }

        /// <summary>
        /// Tests equality between this matrix and another.
        /// </summary>
        /// <param name="other">Other matrix to test</param>
        /// <returns>True if the matrices are equal, false otherwise</returns>
        public bool Equals(Mat4D other)
        {
            return (((A1 == other.A1) && (A2 == other.A2) && (A3 == other.A3) && (A4 == other.A4))
                && ((B1 == other.B1) && (B2 == other.B2) && (B3 == other.B3) && (B4 == other.B4))
                && ((C1 == other.C1) && (C2 == other.C2) && (C3 == other.C3) && (C4 == other.C4))
                && ((D1 == other.D1) && (D2 == other.D2) && (D3 == other.D3) && (D4 == other.D4)));
        }

        /// <summary>
        /// Determines whether the specified <see cref="System.Object"/> is equal to this instance.
        /// </summary>
        /// <param name="obj">The <see cref="System.Object"/> to compare with this instance.</param>
        /// <returns>
        ///   <c>true</c> if the specified <see cref="System.Object"/> is equal to this instance; otherwise, <c>false</c>.
        /// </returns>
        public override bool Equals(Object obj)
        {
            if (obj is Mat4D)
            {
                return Equals((Mat4D)obj);
            }
            return false;
        }

        /// <summary>
        /// Returns a hash code for this instance.
        /// </summary>
        /// <returns>
        /// A hash code for this instance, suitable for use in hashing algorithms and data structures like a hash table. 
        /// </returns>
        public override int GetHashCode()
        {
            return A1.GetHashCode() + A2.GetHashCode() + A3.GetHashCode() + A4.GetHashCode() + B1.GetHashCode() + B2.GetHashCode() + B3.GetHashCode() + B4.GetHashCode() +
                C1.GetHashCode() + C2.GetHashCode() + C3.GetHashCode() + C4.GetHashCode() + D1.GetHashCode() + D2.GetHashCode() + D3.GetHashCode() + D4.GetHashCode();
        }

        /// <summary>
        /// Returns a <see cref="System.String"/> that represents this instance.
        /// </summary>
        /// <returns>
        /// A <see cref="System.String"/> that represents this instance.
        /// </returns>
        public override String ToString()
        {
            CultureInfo info = CultureInfo.CurrentCulture;
            Object[] args = new object[] { A1.ToString(info), A2.ToString(info), A3.ToString(info), A4.ToString(info),
                B1.ToString(info), B2.ToString(info), B3.ToString(info), B4.ToString(info),
                C1.ToString(info), C2.ToString(info), C3.ToString(info), C4.ToString(info),
                D1.ToString(info), D2.ToString(info), D3.ToString(info), D4.ToString(info) };
            return String.Format(info, "{{[A1:{0} A2:{1} A3:{2} A4:{3}] [B1:{4} B2:{5} B3:{6} B4:{7}] [C1:{8} C2:{9} C3:{10} C4:{11}] [D1:{12} D2:{13} D3:{14} D4:{15}]}}", args);
        }
    }
}