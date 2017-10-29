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
    public class CameraRenderable : ObjectBase, IComponent
    {
        public int ID { get; set; }

        public CameraRenderable() : base(IntPtr.Zero) { }


        public CameraRenderable( UInt16 id,SceneBase scene, Entity entity)
            : base(CreateCameraRenderable(  id, UnityContainer.Get().Engine.CPointer, scene.CPointer, entity.CPointer))
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


        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe IntPtr CreateCameraRenderable(UInt16 id, IntPtr engine, IntPtr scene,IntPtr entity);

    }
}
