/*
* Copyright (c) 2012-2013 AssimpNet - Nicholas Woodfield
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
    /// Represents a 3x3 matrix. Assimp docs say their matrices are always row-major,
    /// and it looks like they're only describing the memory layout. Matrices are treated
    /// as column vectors however (X base in the first column, Y base the second, and Z base the third)
    /// </summary>
    [Serializable]
    [StructLayout(LayoutKind.Sequential)]
    public struct Mat3D : IEquatable<Mat3D>
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

        private static Mat3D _identity = new Mat3D(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

        /// <summary>
        /// Gets the identity matrix.
        /// </summary>
        public static Mat3D Identity
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
                B1 <= epsilon && B1 >= -epsilon &&
                B3 <= epsilon && B3 >= -epsilon &&
                C1 <= epsilon && C1 >= -epsilon &&
                C2 <= epsilon && C2 >= -epsilon &&
                A1 <= 1.0f + epsilon && A1 >= 1.0f - epsilon &&
                B2 <= 1.0f + epsilon && B2 >= 1.0f - epsilon &&
                C3 <= 1.0f + epsilon && C3 >= 1.0f - epsilon);
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
                        }
                        break;
                }
            }
        }

        /// <summary>
        /// Constructs a new Matrix3x3.
        /// </summary>
        /// <param name="a1">Element at row 1, column 1</param>
        /// <param name="a2">Element at row 1, column 2</param>
        /// <param name="a3">Element at row 1, column 3</param>
        /// <param name="b1">Element at row 2, column 1</param>
        /// <param name="b2">Element at row 2, column 2</param>
        /// <param name="b3">Element at row 2, column 3</param>
        /// <param name="c1">Element at row 3, column 1</param>
        /// <param name="c2">Element at row 3, column 2</param>
        /// <param name="c3">Element at row 3, column 3</param>
        public Mat3D(double a1, double a2, double a3, double b1, double b2, double b3, double c1, double c2, double c3)
        {
            this.A1 = a1;
            this.A2 = a2;
            this.A3 = a3;
            this.B1 = b1;
            this.B2 = b2;
            this.B3 = b3;
            this.C1 = c1;
            this.C2 = c2;
            this.C3 = c3;
        }

        /// <summary>
        /// Transposes this matrix (rows become columns, vice versa).
        /// </summary>
        public void Transpose()
        {
            Mat3D m = this;

            A2 = m.B1;
            A3 = m.C1;

            B1 = m.A2;
            B3 = m.C2;

            C1 = m.A3;
            C2 = m.B3;
        }

        public void Product(ref Vec3D v, out Vec3D result)
        {
            result.X = A1 * v.X + A2 * v.Y + A3 * v.Z;
            result.Y = B1 * v.X + B2 * v.Y + B3 * v.Z;
            result.Z = C1 * v.X + C2 * v.Y + C3 * v.Z;
        }

        public void Scale(double s)
        {
            A1 *= s;
            A2 *= s;
            A3 *= s;
            B1 *= s;
            B2 *= s;
            B3 *= s;
            C1 *= s;
            C2 *= s;
            C3 *= s;
        }

        public void Quant(double s = 1 << 4)
        {
            A1 = Math.Round(A1 * s) / s;
            A2 = Math.Round(A2 * s) / s;
            A3 = Math.Round(A3 * s) / s;
            B1 = Math.Round(B1 * s) / s;
            B2 = Math.Round(B2 * s) / s;
            B3 = Math.Round(B3 * s) / s;
            C1 = Math.Round(C1 * s) / s;
            C2 = Math.Round(C2 * s) / s;
            C3 = Math.Round(C3 * s) / s;
        }

        public void Adjoints(out Mat3D result)
        {
            result.A1 = (B2 * C3 - B3 * C2);
            result.A2 = (A3 * C2 - A2 * C3);
            result.A3 = (A2 * B3 - A3 * B2);
            result.B1 = (B3 * C1 - B1 * C3);
            result.B2 = (A1 * C3 - A3 * C1);
            result.B3 = (A3 * B1 - A1 * B3);
            result.C1 = (B1 * C2 - B2 * C1);
            result.C2 = (A2 * C1 - A1 * C2);
            result.C3 = (A1 * B2 - A2 * B1);
        }

        /// <summary>
        /// Compute the determinant of this matrix.
        /// </summary>
        /// <returns>The determinant</returns>
        public double Determinant()
        {
            return A1 * B2 * C3 - A1 * B3 * C2 + A2 * B3 * C1 - A2 * B1 * C3 + A3 * B1 * C2 - A3 * B2 * C1;
        }

        /// <summary>
        /// Tests equality between two matrices.
        /// </summary>
        /// <param name="a">First matrix</param>
        /// <param name="b">Second matrix</param>
        /// <returns>True if the matrices are equal, false otherwise</returns>
        public static bool operator ==(Mat3D a, Mat3D b)
        {
            return (((a.A1 == b.A1) && (a.A2 == b.A2) && (a.A3 == b.A3))
                && ((a.B1 == b.B1) && (a.B2 == b.B2) && (a.B3 == b.B3))
                && ((a.C1 == b.C1) && (a.C2 == b.C2) && (a.C3 == b.C3)));
        }

        /// <summary>
        /// Tests inequality between two matrices.
        /// </summary>
        /// <param name="a">First matrix</param>
        /// <param name="b">Second matrix</param>
        /// <returns>True if the matrices are not equal, false otherwise</returns>
        public static bool operator !=(Mat3D a, Mat3D b)
        {
            return (((a.A1 != b.A1) || (a.A2 != b.A2) || (a.A3 != b.A3))
                || ((a.B1 != b.B1) || (a.B2 != b.B2) || (a.B3 != b.B3))
                || ((a.C1 != b.C1) || (a.C2 != b.C2) || (a.C3 != b.C3)));
        }


        /// <summary>
        /// Performs matrix multiplication.Multiplication order is B x A. That way, SRT concatenations
        /// are left to right.
        /// </summary>
        /// <param name="a">First matrix</param>
        /// <param name="b">Second matrix</param>
        /// <returns>Multiplied matrix</returns>
        public static Mat3D operator *(Mat3D a, Mat3D b)
        {
            return new Mat3D(a.A1 * b.A1 + a.B1 * b.A2 + a.C1 * b.A3,
                                 a.A2 * b.A1 + a.B2 * b.A2 + a.C2 * b.A3,
                                 a.A3 * b.A1 + a.B3 * b.A2 + a.C3 * b.A3,
                                 a.A1 * b.B1 + a.B1 * b.B2 + a.C1 * b.B3,
                                 a.A2 * b.B1 + a.B2 * b.B2 + a.C2 * b.B3,
                                 a.A3 * b.B1 + a.B3 * b.B2 + a.C3 * b.B3,
                                 a.A1 * b.C1 + a.B1 * b.C2 + a.C1 * b.C3,
                                 a.A2 * b.C1 + a.B2 * b.C2 + a.C2 * b.C3,
                                 a.A3 * b.C1 + a.B3 * b.C2 + a.C3 * b.C3);
        }

        /// <summary>
        /// Tests equality between this matrix and another.
        /// </summary>
        /// <param name="other">Other matrix to test</param>
        /// <returns>True if the matrices are equal, false otherwise</returns>
        public bool Equals(Mat3D other)
        {
            return (((A1 == other.A1) && (A2 == other.A2) && (A3 == other.A3))
                && ((B1 == other.B1) && (B2 == other.B2) && (B3 == other.B3))
                && ((C1 == other.C1) && (C2 == other.C2) && (C3 == other.C3)));
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
            if (obj is Mat3D)
            {
                return Equals((Mat3D)obj);
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
            return A1.GetHashCode() + A2.GetHashCode() + A3.GetHashCode() + B1.GetHashCode() + B2.GetHashCode() + B3.GetHashCode() +
                C1.GetHashCode() + C2.GetHashCode() + C3.GetHashCode();
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
            Object[] args = new object[] { A1.ToString(info), A2.ToString(info), A3.ToString(info),
                B1.ToString(info), B2.ToString(info), B3.ToString(info),
                C1.ToString(info), C2.ToString(info), C3.ToString(info)};
            return String.Format(info, "{{[A1:{0} A2:{1} A3:{2}] [B1:{3} B2:{4} B3:{5}] [C1:{6} C2:{7} C3:{8}]}}", args);
        }
    }
}