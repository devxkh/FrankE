using DLL.NodeEditor.ViewModel;
using System;
using System.Linq;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.Serialization;
using System.Windows.Input;
using VEF;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Model.Services;
using VEX.Core.Shared.Model.Scene.Objects.ChildObject.Animation;
using VEX.Core.Shared.Service.Component;
using VEX.Core.Shared.ViewModel.Editor.AnimationNodes;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using Microsoft.Practices.Unity;
using System.Collections.Generic;
using VEF.Interfaces.Controls;
using DLL.NodeEditor.Nodes;
using VEX.Core.Shared.ViewModel.UI;
using VEX.Model.UI;

namespace VEX.Core.Shared.Model.Prefabs
{
    [KnownType(typeof(AnimationNodeViewModel))]
    [KnownType(typeof(TransitionSelectNodeViewModel))]
    [KnownType(typeof(ParameterNodeViewModel))]
    [KnownType(typeof(MixNodeViewModel))]
    //  [KnownType(typeof(NodeConnectionViewModel))]
    [KnownType(typeof(OutputNodeViewModel))]
    [KnownType(typeof(Multiply))]
    [KnownType(typeof(ColorInput))]
    [DataContract]
    public class AnimationBlendTree : PItem
    {
        //     private string m_Boneparent;

        #region Properties

        [Browsable(false)]
        public override List<IMenuItem> MenuOptions
        {
            get
            {

                List<IMenuItem> list = new List<IMenuItem>()
                {
                    new VEFMenuItem() { Command = new CmdEditAnimationBlendTree(this), Header = "Edit" }

            };

                //VEFMenuItem miAddItem = new VEFMenuItem() { Header = "Add Item" };

                //foreach (var type in CanAddThisItems)
                //{
                //    miAddItem.Items.Add(new MenuItem() { Header = type.Name, Command = new CmdAddNewBlendTree(this), CommandParameter = type });
                //}

                //list.Add(miAddItem);


                //VEFMenuItem miAdd = new VEFMenuItem() { Command = new CmdCreateStaticObj(), CommandParameter = this, Header = "Create static object" };
                //menuOptions.Add(miAdd);

                return list;
            }
        }

        //   [DataMember]
        //   public string Boneparent { get { return m_Boneparent; } set { m_Boneparent = FB_Helper.UpdateSelectedObject(this, m_Boneparent, value); RaisePropertyChanged("Boneparent"); } }


        //  public NetMsg.Data FBMsgType { get { return NetMsg.Data.NONE; } }

        private ObservableCollection<ElementViewModel> m_AnimNodes;

        [DataMember]
        [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        [NewItemTypes(new Type[] { typeof(AnimationNodeViewModel), typeof(TransitionSelectNodeViewModel), typeof(ParameterNodeViewModel), typeof(MixNodeViewModel) })]
        public ObservableCollection<ElementViewModel> AnimNodes { get { return m_AnimNodes; } set { m_AnimNodes = value; } }

        private ObservableCollection<ConnectionViewModel> m_connections = new ObservableCollection<ConnectionViewModel>();

        [DataMember]
        [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        //   [NewItemTypes(new Type[] { typeof(NodeConnectionViewModel) })]
        public ObservableCollection<ConnectionViewModel> NodeConnections { get { return m_connections; } set { m_connections = value; } }

        private ObservableCollection<AnimConstant> m_constants = new ObservableCollection<AnimConstant>();

        [DataMember]
        [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        public ObservableCollection<AnimConstant> Constants { get { return m_constants; } set { m_constants = value; } }

        /// <summary>
        /// id of the output nodeid
        /// </summary>
        [DataMember]
        public uint Output { get; set; }

        #endregion

        public AnimationBlendTree()
        {
            this.Name = "AnimationBlendTree";
            m_AnimNodes = new ObservableCollection<ElementViewModel>();
        }
    }

    public class CmdEditAnimationBlendTree : ICommand
    {
        private AnimationBlendTree _AnimationBlendTree;
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public void Execute(object parameter)
        {
            IWorkspace workspace = VEFModule.UnityContainer.Resolve<AbstractWorkspace>();

            IOpenDocumentService odS = VEFModule.UnityContainer.Resolve<IOpenDocumentService>();

            AnimationEditorViewModel openValue = odS.OpenFromID("AnimationEditorID:##:", true) as AnimationEditorViewModel; ////item.ContentID, true);
            var model = openValue.Model as AnimationEditorModel;
            model.AnimationBlendTree = _AnimationBlendTree;
            AnimationEditorManager AnimationEditorService = VEFModule.UnityContainer.Resolve(typeof(AnimationEditorManager), "") as AnimationEditorManager;

            AnimationEditorService.AnimationEditors[0].GraphViewModel.Elements = _AnimationBlendTree.AnimNodes;
            AnimationEditorService.AnimationEditors[0].GraphViewModel.Connections = _AnimationBlendTree.NodeConnections;

            if (!AnimationEditorService.AnimationEditors[0].GraphViewModel.Elements.Where(x => x is OutputNodeViewModel).Any())
                AnimationEditorService.AnimationEditors[0].GraphViewModel.AddElement<OutputNodeViewModel>(300, 200);

            //foreach(var connection in _AnimationComponent.FB_AnimationComponent.NodeConnections)
            //{
            //    if (connection.OutputConnectorID != 0)
            //    {
            //        var resultOutputConnector = _AnimationComponent.FB_AnimationComponent.AnimNodes.Where(x => x.OutputConnector.ConnectorID == connection.OutputConnectorID);
            //        if (resultOutputConnector.Any())
            //            connection.From = resultOutputConnector.First().OutputConnector;
            //    }
            //    else if (connection.InputConnectorID != 0)
            //    {
            //        foreach(var ele in _AnimationComponent.FB_AnimationComponent.AnimNodes)
            //        {
            //            var resultInputConnector = ele.InputConnectors.Where(x =>  x.ConnectorID == connection.InputConnectorID);
            //            if (resultInputConnector.Any())
            //                connection.To = resultInputConnector.First();
            //        }


            //    }
            //}

            //GraphViewModel test = new GraphViewModel();
            ////  openValue.GraphViewModel
            //test.Elements = _AnimationComponent.FB_AnimationComponent.AnimNodes;
            //test.Connections = _AnimationComponent.FB_AnimationComponent.AnimNodes;

            //  _AnimationComponent.SendToSocket();

        }

        public CmdEditAnimationBlendTree(AnimationBlendTree som)
        {
            _AnimationBlendTree = som;
        }
    }
}
