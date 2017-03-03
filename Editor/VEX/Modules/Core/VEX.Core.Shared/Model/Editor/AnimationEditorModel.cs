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
using VEX.Core.Shared.Model.UI;
using VEF.Model.Services;
using VEX.Model.UI.FBufferObject;
using System.IO;
using VEX.Core.Shared.Model.UI.Helper;
using VEF.View.Types;
using System.Drawing;
using VEX.Core.Shared.Model.UI.Fonts;
using DLL.NodeEditor.ViewModel;
using System.Windows.Media;
using DLL.NodeEditor.Nodes;
using VEX.Core.Shared.Model.Prefabs;

namespace VEX.Model.UI
{  
    public class AnimationEditorModel : ProjectItemModel // todo , IDBFileItem, INetID
    {
        private AnimationBlendTree _AnimationBlendTree;

        /// <summary>
        /// Viewmodel from the Node Editor Control
        /// </summary>
        public GraphViewModel GraphViewModel { get; set; }

        public uint AnimationEditorID { get; set; }

        [ExpandableObject]
        public AnimationBlendTree AnimationBlendTree { get { return _AnimationBlendTree; } set { _AnimationBlendTree = value;  RaisePropertyChanged("AnimationBlendTree"); } }

        #region INETID


        [XmlIgnore]
        [Browsable(false)]
        public IFBObject FBObject { get; set; } //{ return FB_SceneNode; } }


        #endregion
        
        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {
                List<IMenuItem> list = new List<IMenuItem>();

             //   list.Add(new VEFMenuItem() { Header = "Generate AnimationEditor", Command = new CmdGenerateAnimationEditor(this) });
                list.Add(new VEFMenuItem() { Header = "Generate FB File", Command = new CmdGenFBAnimationEditorFile(this) });
            //    list.Add(new VEFMenuItem() { Header = "Load Gorilla File", Command = new CmdLoadGorillaFile(this) });

                return list;
            }
        }

        public AnimationEditorModel()
        {
            AnimationBlendTree = new AnimationBlendTree();
            Name = typeof(AnimationEditorModel).Name;

        }


        #region contentmodel

        internal void SetLocation(object location)
        {
            this.Location = location;
            RaisePropertyChanged("Location");
        }

        internal void SetDirty(bool value)
        {
            this.IsDirty = value;
        }

        #endregion
    }

    public class CmdGenFBAnimationEditorFile : ICommand
    {
        private AnimationEditorModel mpm;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
          
      }

        public CmdGenFBAnimationEditorFile(AnimationEditorModel pm)
        {
            mpm = pm;
        }
    }
}
