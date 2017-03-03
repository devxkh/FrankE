using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Core.WPF.View;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.XForms.Model;
using VEX.Core.Model;
using VEX.Core.View.Tools;

namespace VEX.Core.ViewModel
{
    public class SocketServerToolViewModel : ToolViewModel
    {
        private readonly SocketServerToolModel _model;
        private readonly SocketServerToolView _view;
        private IWorkspace _workspace;

        public SocketServerToolViewModel(AbstractWorkspace workspace)
        {
            Name = "SocketServer";
            Title = "Socket Server";
            ContentId = "SocketServer";
            _model = new SocketServerToolModel();//.Resolve<ICommandManager>(), container.Resolve<IMenuService>());
            Model = _model;
            IsVisible = true;


            _view = new SocketServerToolView();
            _view.DataContext = _model;
            View = _view;

         //    VEFModule.EventAggregator.GetEvent<LogEvent>().Subscribe(AddLog);

       //     _logger = _container.Resolve<ILoggerService>();
        }

        public override PaneLocation PreferredLocation
        {
            get { return PaneLocation.Right; }
        }
    }
}
