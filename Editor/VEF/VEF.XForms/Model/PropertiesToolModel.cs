using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.XForms.Model.Services;

namespace VEF.Model
{
    public class PropertiesToolModel : ToolModel
    {
        Object mSelectedObject;
        public Object SelectedObject { get { return mSelectedObject; } set { mSelectedObject = value; RaisePropertyChanged("SelectedObject"); } }

        /// <summary>
        /// Initializes a new instance of the <see cref="MDModel" /> class.
        /// </summary>
        /// <param name="commandManager">The injected command manager.</param>
        /// <param name="menuService">The menu service.</param>
        public PropertiesToolModel()//ICommandManager commandManager, IMenuService menuService)
        {
            var commandManager = VEFModule.UnityContainer.Resolve(typeof(ICommandManager), "") as ICommandManager;
            var menuService = VEFModule.UnityContainer.Resolve(typeof(IMenuService), "") as IMenuService;
            PropertiesManager propMgr = (PropertiesManager)VEFModule.UnityContainer.Resolve(typeof(IPropertiesService),"");
            propMgr.PropertiesToolModel = this;
        }
    }
}
