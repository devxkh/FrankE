
using System.Windows.Controls;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Model.Services;
namespace VEF.ViewModel
{
    public class ProjectViewModel : ContentViewModel
    {
        public ProjectViewModel(AbstractWorkspace workspace, ICommandManager commandManager, ILoggerService logger,
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