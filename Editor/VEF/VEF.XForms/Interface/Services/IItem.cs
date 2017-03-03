using Microsoft.Practices.Unity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Model.Services;

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

        bool Visible { get; set; }

        /// <summary>
        /// Path to image source of item type
        /// </summary>
        string TypeImgSrc { get; set; }

        /// <summary>
        /// Document Identifier
        /// </summary>
        string ContentID { get; }

        /// <summary>
        /// subitems of this item
        /// </summary>
        CollectionOfIItem Items { get; }

        /// <summary>
        /// name of the item
        /// </summary>
        string Name { get; }

        /// <summary>
        /// Menu Options
        /// </summary>
        List<IMenuItem> MenuOptions { get; }

        /// <summary>
        /// Item has children = true, else false
        /// </summary>
        bool HasChildren { get; }

        /// <summary>
        /// Item is expanded = true, else false
        /// </summary>
        bool IsExpanded { get; set; }

        /// <summary>
        /// Item is selected = true, else false
        /// </summary>
        bool IsSelected { get; set; }

        /// <summary>
        /// Parent Item of this Item
        /// </summary>
        IItem Parent { get; set; }

        /// <summary>
        /// create a new item
        /// </summary>
        /// <returns>true = opened, false = not opened</returns>
        bool Create();

        /// <summary>
        /// Open the Item
        /// </summary>
        /// <param name="paramID">identifier for opening</param>
        /// <returns>true = opened, false = not opened</returns>
        bool Open(object paramID);

        /// <summary>
        /// Save the Item
        /// </summary>
        /// <returns>true =  saved, false = not saved</returns>
        bool Save(object param = null);

        /// <summary>
        /// Finish Item
        /// </summary>
        void Finish();

        /// <summary>
        /// Delete Item
        /// </summary>
        /// <returns>true =  deleted, false = not deleted</returns>
        bool Delete();
        //DelegateCommand ToggleExpandCollapseCommand { get; set; }

        /// <summary>
        /// Refresh Item
        /// </summary>
        void Refresh();

        void Drop(IItem item);
        

        bool IsDirty { get; set; }

        //void ExecuteToggleExpandCollapse();

        //   Dictionary<Type,IItem> mItems;
    }
}
