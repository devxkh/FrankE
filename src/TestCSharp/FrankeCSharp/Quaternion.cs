using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace XGame.Core.Engine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Quaternion
    {
        public float W { get; set; }
        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }

        public Quaternion(float w, float x, float y, float z)
        {
            W = w;
            X = x;
            Y = y;
            Z = z;
        }

    }
}
