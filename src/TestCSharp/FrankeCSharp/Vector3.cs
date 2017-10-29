using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace XGame.Core.Engine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector3
    {
        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }

        public Vector3(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        /// <summary>
        /// Operator * overload ; multiply a vector by a scalar value
        /// </summary>
        /// <param name="v">Vector</param>
        /// <param name="x">Scalar value</param>
        /// <returns>v * x</returns>
        public static Vector3 operator *(Vector3 v, float x)
        {
            return new Vector3(v.X * x, v.Y * x, v.Z * x);
        }
        public static Vector3 operator *(float x, Vector3 v)
        {
            return new Vector3(v.X * x, v.Y * x, v.Z * x);
        }

        /// <summary>
        /// Operator - overload ; returns the opposite of a vector
        /// </summary>
        /// <param name="v">Vector to negate</param>
        /// <returns>-v</returns>
        ////////////////////////////////////////////////////////////
        public static Vector3 operator -(Vector3 v)
        {
            return new Vector3(-v.X, -v.Y, -v.Z);
        }

        /// <summary>
        /// Operator - overload ; subtracts two vectors
        /// </summary>
        /// <param name="v1">First vector</param>
        /// <param name="v2">Second vector</param>
        /// <returns>v1 - v2</returns>
        public static Vector3 operator -(Vector3 v1, Vector3 v2)
        {
            return new Vector3(v1.X - v2.X, v1.Y - v2.X, v1.Z - v2.Z);
        }



        public override string ToString()
        {
            return X + ", " + Y + ", " + Z;
        }

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        public static extern unsafe Vector3 Vector3_Normalize(Vector3 vector3);

    }
}
