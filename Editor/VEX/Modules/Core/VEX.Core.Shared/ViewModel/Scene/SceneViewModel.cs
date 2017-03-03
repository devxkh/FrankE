using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Controls;
using VEF;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Model.Services;
using VEX.Interface.Scene;
using VEX.Model.Scene.Model;

namespace VEX.Core.Shared.ViewModel.Scene
{
    public class SceneViewModel : ContentViewModel
    {
        public SceneViewModel(AbstractWorkspace workspace, ICommandManager commandManager, ILoggerService logger,
                           IMenuService menuService)
            : base(workspace, commandManager, menuService)
        {
            // ICommand mOpenCOMCommand;
            //OpenCOMCommand mOpenComCommand;
            // mOpenComCommand = new Commands.OpenCOMCommand();
            // mOpenCOMCommand = new DelegateCommand<OpenCOMCommand>(
            //                           mOpenComCommand.OnSubmit, mOpenComCommand.CanSubmit);
        }

        //   public ICommand OpenCOMCommand { get { return mOpenCOMCommand; } }

        public override bool IsSelected
        {
            get { return _isSelected; }
            set
            {
                if (_isSelected != value)
                {
                    _isSelected = value;

                    if (value)
                    {
                        var sceneService = VEFModule.UnityContainer.Resolve(typeof(ISceneService), "") as ISceneService;
                        sceneService.SelectedScene = base.Model as SceneDataModel;
                    }

                    RaisePropertyChanged("IsSelected");
                }
            }
        }

        internal void SetModel(PItem model)
        {
            base.Model = model;
        }

        internal void SetView(UserControl view)
        {
            base.View = view;
        }

        internal void SetHandler(IContentHandler handler)
        {
            base.Handler = handler;
        }
    }
}
