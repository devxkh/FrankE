using FrankeCSharp.Interface;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using XGame.Core.System;

namespace XGame.Core.Engine.Components
{
    public class Controller : ObjectBase, IComponent
    {
        public int ID { get; set; }

        private Vector2 _mousePos;

        public Controller() : base(IntPtr.Zero) { }

        public Controller(Entity entity)
            : base(CreateController(0, UnityContainer.Get().Engine.CPointer, entity.CPointer, true))
        {
            _mousePos = new Vector2();
        }

        /// <summary>
        /// Handle the destruction of the object
        /// </summary>
        /// <param name="disposing">Is the GC disposing the object, or is it an explicit call ?</param>
        protected override void Destroy(bool disposing)
        {
            //todo
        }

        public void SetMousePosition(Vector2 pos)
        {
            Ctrl_SetMousePos(CPointer, out pos);
        }

        public Vector2 GetMousePosition()
        {
            Ctrl_GetMousePos(CPointer, out _mousePos);
            return _mousePos;
        }

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe IntPtr CreateController(UInt16 id, IntPtr engine, IntPtr entity, bool defaultCtrl);


        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void Ctrl_SetMousePos(IntPtr controllerComponent,out Vector2 pos);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe Vector2 Ctrl_GetMousePos(IntPtr controllerComponent, out Vector2 pos);

    }
}
