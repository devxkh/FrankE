using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows.Controls;
using System.Windows.Input;
using System.Xml.Serialization;
using Microsoft.Practices.Unity;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using System.Windows;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using VEX.Service.Scene;
using VEX.Interface.Scene.Services;
using VEF.Interfaces.Services;
using VEX.Interface.Scene;
using VEF.Interfaces.Controls;
using VEF.Core.Interface.Service;
using VEX.IDAL;
using VEX.Core.Shared.Interface.Net;
using VEF;
using VEX.Core.Model.Services;
using VEX.Interface.DAL;
using VEF.DAL.Interface;
using VEX.Core.ViewModel;
using VEX.Core.Model;
using Module.PFExplorer.Service;
using System.Collections.Specialized;
using VEX.Core.Shared.Service.Scene;
using VEX.Model.Scene.Model.Objects;
using System.Runtime.Serialization;

namespace VEX.Model.Scene.Model
{
    [DataContract(IsReference = true)]
    public class SpawnPointComponent : ComponentX
    {
        #region INETID

        public override NetMsg.UComponent UComponent { get { return NetMsg.UComponent.SpawnPointComponent; } set { } }

        [ExpandableObject]
        [DataMember]
        public FB_SpawnPointModel FB_SpawnPoint { get { return FBObject as FB_SpawnPointModel; } set { FBObject = value; } }

        #endregion


        #region UI Properties
        
        #endregion
                
        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {
                return base.MenuOptions;
            }
        }

        public SpawnPointComponent()
        {
            Name = typeof(SpawnPointComponent).Name;
            
            FBObject = new FB_SpawnPointModel();
            FBObject.Parent = this;
        }
    }
}
