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
    public enum Cam_Type
    {
        CA_NONE,
        CA_FREE,
        CA_FIXED,
        CA_MANUAL,
        CA_ORBIT,
        CA_CHARACTER,

        CA_PERSPECTIVE,
        CA_ORTHOGRAPHIC
    };

   

    public class CameraFree : ObjectBase, IComponent
    {
        public int ID { get; set; }

        public CameraFree() : base(IntPtr.Zero) { }


        public CameraFree(Entity entity, CameraRenderable renderable)
            : base(CreateCameraFreeComponent(renderable.CPointer, entity.CPointer))
        {

        }


        //public Cam_Type CamType
        //{
        //    get { return (Cam_Type)GetCameraType(CPointer); }
        //    set { SetCameraType(CPointer, (UInt16)value); }
        //}

        public Body CameraNode
        {
            get { return new Body(GetCameraNode(CPointer)); }
        }

        public Body CameraGoal
        {
            get { return new Body(getCameraGoal(CPointer)); }
        }

        public Body CameraPivot
        {
            get { return new Body(getCameraPivot(CPointer)); }
        }

        /// <summary>
        /// Handle the destruction of the object
        /// </summary>
        /// <param name="disposing">Is the GC disposing the object, or is it an explicit call ?</param>
        protected override void Destroy(bool disposing)
        {
            //todo
        }

        //improving interop performance
        //https://msdn.microsoft.com/en-us/library/ff647812.aspx
        //  [System.Security.SuppressUnmanagedCodeSecurity]
        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe IntPtr CreateCameraFreeComponent(IntPtr entity, IntPtr camRenderable);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe uint GetCameraType(IntPtr camPtr);

        //[DllImport(@"E:\Projekte\coop\XGame_build\Debug\XGame-d.dll", ExactSpelling = true)]
        //private static extern void SetCameraType(IntPtr camPtr, UInt16 type);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe IntPtr GetCameraNode(IntPtr camPtr);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe IntPtr getCameraGoal(IntPtr camPtr);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe IntPtr getCameraPivot(IntPtr camPtr);

    }
}
