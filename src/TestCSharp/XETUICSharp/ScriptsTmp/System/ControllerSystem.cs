using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using XGame.Core.Engine;

namespace XGame.Core.System
{
    public class ControllerSystem : ObjectBase, ISystem
    {
        public ControllerSystem():
            base(IntPtr.Zero)
        {

        }

        public void Update(SceneBase scene, float dt)
        {
        }

        /// <summary>
        /// Handle the destruction of the object
        /// </summary>
        /// <param name="disposing">Is the GC disposing the object, or is it an explicit call ?</param>
        protected override void Destroy(bool disposing)
        {
        }


    }
}
