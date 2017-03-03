using VEF.Interfaces.Services;
using VEX.Interface.DAL;
using VEX.Service.Scene;

namespace VEX.Interface.Scene
{
    /// <summary>
    /// Identity Scene Items
    /// </summary>
    public interface ISceneItemID 
    {
        uint SceneItemID { get; set; }
    }
}
