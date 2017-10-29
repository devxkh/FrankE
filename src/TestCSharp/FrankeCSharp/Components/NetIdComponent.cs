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
    public class NetIdComponent :  ObjectBase, IComponent
    {
        public int ID { get; set; }

        public NetIdComponent() : base(IntPtr.Zero) { }

        public ushort NetComponentID { get { return NetIdComponent_GetID(CPointer); } }

        public NetIdComponent(Entity entity)
            : base(CreateNetIdComponent(entity.CPointer))
        {

        }

        public NetIdComponent(IntPtr bodyPtr)
            : base(bodyPtr)
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
        private static extern unsafe IntPtr CreateNetIdComponent(IntPtr entity);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe ushort NetIdComponent_GetID(IntPtr netIDComponent);



    }
}
