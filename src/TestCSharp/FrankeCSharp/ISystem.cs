using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using XGame.Core.System;

namespace XGame.Core.Engine
{
    public interface ISystem 
    {
        void Update(SceneBase scene, float dt);

        IntPtr CPointer { get; set; }
    }
}
