using VEF.Interfaces.Services;
using VEX.Interface.DAL;
using VEX.Model.Scene.Model;
using VEX.Service.Scene;

namespace VEX.Interface.Scene
{
    public interface IEntityComponent 
    {
        IFBObject FBObject { get; set; }

      //   NetMsg.Data Type { get;  }
    }
}
