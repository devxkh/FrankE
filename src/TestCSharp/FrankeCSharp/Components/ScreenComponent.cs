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
    public class ScreenComponent : ObjectBase
    {
        public ScreenComponent() : base(IntPtr.Zero) { }

        public ScreenComponent(CameraRenderable camRenderable, Entity entity)
            : base(CreateScreenComponent(camRenderable.CPointer, UnityContainer.Get().Engine.CPointer, entity.CPointer))
        {

        }

        /// <summary>
        /// Handle the destruction of the object
        /// </summary>
        /// <param name="disposing">Is the GC disposing the object, or is it an explicit call ?</param>
        protected override void Destroy(bool disposing)
        {
            //todo
        }

        public void AddUIState(Entity entity)
        {
            UI_AddUIState(11, entity.CPointer, "UIDebug");
            UI_AddUIState(10, entity.CPointer, "UIConsole");
        }

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe IntPtr CreateScreenComponent(IntPtr camRenderable, IntPtr engine, IntPtr entity);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void UI_AddUIState(UInt16 id, IntPtr entityHolder, string statename, bool replace = true);
    }
}
