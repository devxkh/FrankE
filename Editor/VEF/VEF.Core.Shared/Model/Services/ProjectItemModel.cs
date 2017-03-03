using Microsoft.Practices.Unity;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using VEF.Interfaces.PFExplorer;
using VEF.Model.Services;
using VEF.Utils;

namespace Module.PFExplorer.Service
{
    [DataContract(IsReference = true)]
    public class ProjectItemModel : PItem, IProjectItem
    {
        [Category("Debug data")]
        public IProjectFile ParentProject
        {
            get
            {
                string tmpItemFolder = "";
                IProjectFile projectFolder = PFUtilities.GetRekursivPFolder(this.Parent, ref tmpItemFolder) as IProjectFile;  
                return projectFolder;
            }
        }

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
                    //String tmpItemFolder = ItemFolder;
                    ////name is foldername and will be instantly renamed
                    ////      IsDirty = true;
                    //if (!String.IsNullOrEmpty(tmpItemFolder) && !String.IsNullOrEmpty(base.Name))
                    //{
                    //    if (File.Exists(tmpItemFolder + base.Name))
                    //        System.IO.File.Move(tmpItemFolder + base.Name, tmpItemFolder + value);
                    //}
                    base.Name = value;
                    RaisePropertyChanged("Name");
                }
            }
        }

        public virtual bool Save(object param = null)
        {
          //  string tmpItemFolder = ItemFolder;

            //if (Directory.Exists(tmpItemFolder))
            //{
            //    Directory.CreateDirectory(tmpItemFolder); // create folder for item
            //}

            return true;
        }       
    }
}
