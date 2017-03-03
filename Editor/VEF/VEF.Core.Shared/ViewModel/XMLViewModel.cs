using System;
using System.Collections.Generic;
using System.Text;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Model.Services;

namespace VEF.Core.Shared.ViewModel
{
    public class XMLViewModel : ContentViewModel
    {
        public XMLViewModel(AbstractWorkspace workspace, ICommandManager commandManager,                       IMenuService menuService)
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

        internal void SetView(object view)
        {
            base.View = view;
        }

        internal void SetHandler(IContentHandler handler)
        {
            base.Handler = handler;
        }
    }
}
