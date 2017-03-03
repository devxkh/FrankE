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
using VEX.IDAL.MDB;
using VEF.VEF_Helpers;
using VEF.Interfaces;
using DLL.NodeEditor.ViewModel;
using VEX.Core.Shared.Model.Scene.Objects.ChildObject.Animation;
using VEX.Interface.UI;
using DLL.NodeEditor.Nodes;
using System.Windows.Media;
using VEX.Core.Shared.Service.Component;
using VEX.Core.Shared.ViewModel.Editor.AnimationNodes;
using System.Linq;
using System.Runtime.Serialization;

namespace VEX.Model.Scene.Model
{
    [DataContract(IsReference = true)]
    public class AnimationComponent : ComponentX 
    {
        public bool Watch { get; set; }

        #region INETID
        
        public override NetMsg.UComponent UComponent { get { return NetMsg.UComponent.AnimationComponent; } set { } }

        [ExpandableObject]
        [DataMember]
        public FB_AnimationComponent FB_AnimationComponent { get { return FBObject as FB_AnimationComponent; } set { FBObject = value; } }

        #endregion
        
        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {
                List<IMenuItem> list = new List<IMenuItem>() {
              
                };
                return list;
            }
        }

        public AnimationComponent()
        {
            FBObject = new FB_AnimationComponent();
            FBObject.Parent = this;
            Name = typeof(AnimationComponent).Name;     
        }
    }
}
