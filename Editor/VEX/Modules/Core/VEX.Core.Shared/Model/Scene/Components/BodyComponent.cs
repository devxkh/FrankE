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
using System.Runtime.Serialization;

namespace VEX.Model.Scene.Model
{
    [DataContract(IsReference = true)]
    /// <summary>
    /// SceneNode is currently an entity!! dirty change that! todo split into entity and bodycomponent!
    /// </summary>
    public class BodyComponent : ComponentX //,  ISceneNodeID //, INetIDIDBFileItem,
    {
        /// <summary>
        /// needed for SceneNodeID
        /// </summary>
        //[DataMember]
        //public uint SceneNodeID { get; set; }
        
        public bool Watch { get; set; }

        #region INETID

        [DataMember]
        public override NetMsg.UComponent UComponent { get { return NetMsg.UComponent.BodyComponent; } set { } }

        [ExpandableObject]
        [DataMember]
        public FB_BodyComponent FB_BodyComponent { get { return FBObject as FB_BodyComponent; } set { FBObject = value; } }

        #endregion


        #region UI Properties

        //  private bool _UseNetID;

        //public bool UseNetID
        //{
        //    get { return _UseNetID; }
        //    set
        //    {
        //        _UseNetID = value;

        //        RaisePropertyChanged("UseNetID");

        //        if (SendToSocket()) //send node to server
        //        {
        //            var _SocketServerTLVM = VEFModule.UnityContainer.Resolve(typeof(SocketServerToolViewModel), "") as SocketServerToolViewModel;
        //            _SourceItem.Watch = value;

        //            //if (value)
        //            //    (_SocketServerTLVM.Model as SocketServerToolModel).SourceItems.Add(_SourceItem);
        //            //else
        //            //    (_SocketServerTLVM.Model as SocketServerToolModel).SourceItems.Remove(_SourceItem);
        //        }
        //        else
        //        {
        //            MessageBox.Show("Send to SockerServer failed");
        //        }
        //    }
        //}

        public bool IsVisible { get { return FB_BodyComponent.IsVisible; } set { FB_BodyComponent.IsVisible = value; RaisePropertyChanged("IsVisible"); } }

        //[ExpandableObject]
        //public Quaternion Rotation { get { return FB_BodyComponent.Rotation; } set { FB_BodyComponent.Rotation = value; RaisePropertyChanged("Rotation"); } }

        //[ExpandableObject]
        //public Vector3 Position { get { return FB_BodyComponent.Location; } set {
        //        FB_BodyComponent.Location = value;
        //        RaisePropertyChanged("Location");
        //    } }

        //[ExpandableObject]
        //public Vector3 Scale { get { return FB_BodyComponent.Scale; } set { FB_BodyComponent.Scale = value; RaisePropertyChanged("Scale"); } }

        #endregion

        #region DBProperties

        //private long m_EntityID;

        //[XmlIgnore]
        //[Browsable(false)]
        //public long EntityID { get { return m_EntityID; } set { m_EntityID = value; RaisePropertyChanged("EntityID"); } }

        #endregion
        
        [XmlIgnore]
        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {
                return base.MenuOptions;
                //List<IMenuItem> list = new List<IMenuItem>() {
                //    new VEFMenuItem() { Header = "IsVisible" },
                //    new VEFMenuItem() { Command = new CmdDeleteNode(this), Header = "Delete Node" },
                //    new VEFMenuItem() { Command = new CmdSendToServer(this), Header = "SendToServer" }
                //};
                //return list;
            }
        }

        public BodyComponent()
        {
            Name = typeof(BodyComponent).Name;
      
            FBObject = new FB_BodyComponent();
            FBObject.Parent = this;
        }
    }
}
