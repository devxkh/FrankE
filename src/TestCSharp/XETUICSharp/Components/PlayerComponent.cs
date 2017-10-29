using FrankeCSharp.Interface;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using XGame.Core.Engine;
using XGame.Core.Engine.Components;
using XGame.Core.Game.Components;
using XGame.Core.System;

namespace XGame.Core.Components
{
    public class PlayerComponent : ObjectBase , IComponent
    {
        public int ID { get; set; }

        public PlayerComponent() : base(IntPtr.Zero) { }
        
        public PlayerComponent(Entity entity)
            : base(CreatePlayer(entity.CPointer))
        {
        }

        public void PlayerSetActionMap(Controller controller)
        {
            PlayerSetActionMap(CPointer, controller.CPointer);
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
        private static extern unsafe IntPtr CreatePlayer(IntPtr entity);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe  void PlayerSetActionMap(IntPtr playerComponent, IntPtr controllerComponent);

    }
}

