using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.Serialization;
using System.Text;
using System.Windows.Input;
using System.Xml.Serialization;
using VEF.Interfaces.Controls;
using VEF.Interfaces.Services;
using VEF.Model.Services;
using VEF.Utils;
using VEF.View.Types;
using VEX.Core.Shared.Interface.Net;
using VEX.Core.Shared.Utility;
using VEX.Core.View.Project;
using VEX.Interface.DAL;
using VEX.Service.Scene;

namespace VEX.Core.Shared.Service.Scene
{
    [DataContract(IsReference = true)]
    [Editor(typeof(ComponentXPropertyEditor), typeof(ComponentXPropertyEditor))]
    public class ComponentX : PItem
    {
        [DataMember]
        public new EntityX Parent { get; set; }
        
        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {
                List<IMenuItem> list = new List<IMenuItem>() {
                    new VEFMenuItem() { Header = "IsVisible" },
                    new VEFMenuItem() { Command = new CmdRemoveObject(this), Header = "Remove" },
                    new VEFMenuItem() { Command = new CmdSendToServer(this), Header = "SendToServer" }
                };
                return list;
            }
        }
        
        [DataMember]
        public virtual NetMsg.UComponent UComponent { get; set; }
        
        [Browsable(false)]
        public IFBObject FBObject { get; set; } //{ return FB_SceneNode; } }
    
    }

    public class CmdRemoveObject : ICommand
    {
        private ComponentX m_StaticObjectModel;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            m_StaticObjectModel.Parent.Components.Remove(m_StaticObjectModel);
        }

        public CmdRemoveObject(ComponentX som)
        {
            m_StaticObjectModel = som;
        }
    }

    public class CmdSendToServer : ICommand
    {
        private ComponentX _component;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            SocketHelper.SendToSocket(_component.FBObject, NetMsg.Data.Entity, _component.Parent.NetID, 0); //todo _component.Parent.Parent.SceneID);
        }

        public CmdSendToServer(ComponentX som)
        {
            _component = som;
        }
    }
}
