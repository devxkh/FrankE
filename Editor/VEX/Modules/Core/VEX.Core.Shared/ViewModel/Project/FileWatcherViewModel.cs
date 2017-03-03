using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using VEF.Core.WPF.View;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Model.Services;
using VEF.XForms.Model;
using VEX.Core.Model;
using VEX.Core.View.Tools;

namespace VEX.Core.ViewModel.Project
{
    internal class FileWatcherViewModel : ContentViewModel
    {
        public FileWatcherViewModel(AbstractWorkspace workspace, ICommandManager commandManager, ILoggerService logger,
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