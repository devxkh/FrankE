using FrankeCSharp.Interface;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using XGame.Core.Engine;
using XGame.Core.System;

namespace XGame.Core.Components
{
    public class Body : ObjectBase, IComponent
    {
        public int ID { get; set; }

        public Body() : base(IntPtr.Zero) { }

        public Body(Entity entity)
            : base(CreateBodyComponent(entity.CPointer))
        {

        }

        public Body(IntPtr bodyPtr)
            : base(bodyPtr)
        {

        }

        public Quaternion Orientation
        {
            get { return GetBodyOrientation(CPointer); }
           set { SetBodyOrientation(CPointer, value); }
        }

        public Vector3 Position
        {
            get { return GetBodyPosition(CPointer); }
            set { SetBodyPosition(CPointer, value); }
        }

        //public UInt32 ID
        //{
        //    get { return GetBodyID(CPointer); }
        //    set { SetBodyID(CPointer, value); }
        //}



        public Vector3 WorldPosition
        {
            get { return BodyGetWorldPosition(CPointer); }
        }

        public void Translate(Vector3 translate)
        {
            BodyTranslate(CPointer, translate);
        }

        public void LookAt(Vector3 lookat)
        {
            BodyTranslate(CPointer, lookat);
        }

        public void Rotate(float x, float y)
        {
            BodyRotate(CPointer, x, y);
        }

        //public string Name
        //{
        //    get
        //    {
        //        return ""; //todo get name from sqllite db per ID, name not used in c++ code
        //    }
        //    set
        //    {

        //    }
        //}

        /// <summary>
        /// Handle the destruction of the object
        /// </summary>
        /// <param name="disposing">Is the GC disposing the object, or is it an explicit call ?</param>
        protected override void Destroy(bool disposing)
        {
            //todo
        }

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe IntPtr CreateBodyComponent(IntPtr entity);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe Vector3 GetBodyPosition(IntPtr body);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void SetBodyPosition(IntPtr body, Vector3 pos);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe Quaternion GetBodyOrientation(IntPtr body);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void SetBodyOrientation(IntPtr body, Quaternion pos);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe uint GetBodyID(IntPtr body);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void SetBodyID(IntPtr body, UInt32 id);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe Vector3 BodyGetWorldPosition(IntPtr body);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void BodyTranslate(IntPtr body, Vector3 trans);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void BodyLookAt(IntPtr body, Vector3 lookAt);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void BodyRotate(IntPtr body, float x , float y);

    }
}
