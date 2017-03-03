using Microsoft.Practices.Unity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEF.Interfaces.Services
{
    /// <summary>
    /// Treeview item
    /// </summary>
    public interface IItem
    {
        /// <summary>
        /// unique identifier for this item in the application
        /// </summary>
        //   Guid Guid { get;  }

        List<System.Type> CanAddThisItems { get; }

        Boolean Visible { get; set; }

        /// <summary>
        /// Path to image source of item type
        /// </summary>
        String TypeImgSrc { get; set; }

        /// <summary>
        /// Document Identifier
        /// </summary>
        String ContentID { get; }

        /// <summary>
        /// subitems of this item
        /// </summary>
        CollectionOfIItem Items { get; }

        /// <summary>
        /// name of the item
        /// </summary>
        String Name { get; }

        /// <summary>
        /// Menu Options
        /// </summary>
        List<IMenuItem> MenuOptions { get; }

        /// <summary>
        /// Item has children = true, else false
        /// </summary>
        Boolean HasChildren { get; }

        /// <summary>
        /// Item is expanded = true, else false
        /// </summary>
        Boolean IsExpanded { get; set; }

        /// <summary>
        /// Item is selected = true, else false
        /// </summary>
        Boolean IsSelected { get; set; }

        /// <summary>
        /// Parent Item of this Item
        /// </summary>
        IItem Parent { get; set; }

        /// <summary>
        /// create a new item
        /// </summary>
        /// <returns>true = opened, false = not opened</returns>
        Boolean Create(IUnityContainer unityContainer);

        /// <summary>
        /// Open the Item
        /// </summary>
        /// <param name="paramID">identifier for opening</param>
        /// <returns>true = opened, false = not opened</returns>
        Boolean Open(IUnityContainer unityContainer, object paramID);

        /// <summary>
        /// Save the Item
        /// </summary>
        /// <returns>true =  saved, false = not saved</returns>
        Boolean Save(object param = null);

        /// <summary>
        /// Finish Item
        /// </summary>
        void Finish();

        /// <summary>
        /// Delete Item
        /// </summary>
        /// <returns>true =  deleted, false = not deleted</returns>
        Boolean Delete();
        //DelegateCommand ToggleExpandCollapseCommand { get; set; }


        /// <summary>
        /// Refresh Item
        /// </summary>
        void Refresh();


        void Drop(IItem item);


        IUnityContainer Container { get; set; }


        bool IsDirty { get; set; }

        //void ExecuteToggleExpandCollapse();

        //   Dictionary<Type,IItem> mItems;
    }
}
