

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using VEF.Interface;
using VEF.Interfaces.PFExplorer;
using VEF.Interfaces.Services;
using VEF.Model.Services;
using VEF.View.Types;

namespace Module.PFExplorer.Service
{
    [DataContract(IsReference = true)]
    public class ProjectModel : PItem, IProjectFile, ICategoryItem
    {
        /// <summary>
        /// project filename
        /// </summary>
        [DisplayName("Name")]
        [Description("project filename")]
        [DataMember]
        public override string Name
        {
            get
            {
                return base.Name;
            }
            set
            {
                if (base.Name != value)
                {
                    //name is foldername and will be instantly renamed
                    //      IsDirty = true;
                    if (!String.IsNullOrEmpty(Folder) && !String.IsNullOrEmpty(base.Name))
                    {
                        if (File.Exists(Location.ToString()))
                        {
                            System.IO.File.Move(Location.ToString(), Folder + "\\" + Path.GetFileNameWithoutExtension(value) + Path.GetExtension(Location.ToString()));
                            Location = Folder  + "\\" + Path.GetFileNameWithoutExtension(value) + Path.GetExtension(Location.ToString());
                        }
                    }
                    base.Name = value;
                    RaisePropertyChanged("Name");
                }
            }
        }

        [Editor(typeof(FilePathEditor), typeof(FilePathEditor))]
        [DisplayName("Project folder")]
        [DataMember]
        public virtual string Folder { get; set; }


        //public static void SetRekursivParent(object child, object parent)
        //{
        //    var childItem = child as IItem;
        //    if (childItem != null)
        //    {
        //        childItem.Parent = parent as IItem;

        //        if (childItem.Items != null)
        //        {
        //            foreach (var cItem in childItem.Items)
        //            {
        //                SetRekursivParent(cItem, childItem);
        //            }
        //        }
        //    }
        //}


        public new bool Save()
        {
            foreach (var item in Items) //todo .Where(x => x.IsDirty))
                item.Save();

            return true;
        }


    }
}
