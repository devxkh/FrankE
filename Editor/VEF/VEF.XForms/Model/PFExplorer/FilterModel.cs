using System.Runtime.Serialization;
using VEF.Interfaces.Services;
using VEF.Model.Services;
namespace VEF.Model.PFExplorer
{
    [DataContract(IsReference = true)]
    public class FilterModel : PItem
    {
        public FilterModel(ICommandManager commandManager, IMenuService menuService)
        {
        }

    }
}