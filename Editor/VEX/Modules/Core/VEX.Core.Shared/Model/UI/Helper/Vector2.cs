using System;
using System.Collections.Generic;
using System.Text;

namespace VEX.Core.Shared.Model.UI.Helper
{
    public struct Vector2
    {
        public float X { get; set; }
        public float Y { get; set; }

        public Vector2(float x, float y)
        {
            X = x;
            Y = y;
        }
    }
}
