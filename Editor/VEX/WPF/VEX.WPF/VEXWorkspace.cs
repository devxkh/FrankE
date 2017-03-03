using System;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Microsoft.Practices.Unity;
using System.ComponentModel;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using Prism.Events;
using VEF.Interfaces.Events;
using VEF;

namespace VEX.WPF
{
    internal class VEXWorkspace : AbstractWorkspace
    {
        private string _document;
        private ContentViewModel _lastDocument;
        private ILoggerService _logger;
        private const string _title = "VEX";

        public VEXWorkspace()
        {
            VEFModule.EventAggregator.GetEvent<ActiveContentChangedEvent>().Subscribe(ContentChanged);
            _document = "";
        }

        //public override ImageSource Icon
        //{
        //    get
        //    {
        //        ImageSource imageSource = new BitmapImage(new Uri("pack://application:,,,/OIDE;component/Icon.png"));
        //        return imageSource;
        //    }
        //}

        public override string Title
        {
            get
            {
                string newTitle = _title;
                if (_document != "")
                {
                    newTitle += " - " + _document;
                }
                return newTitle;
            }
        }

        private ILoggerService Logger
        {
            get
            {
                if (_logger == null)
                    _logger = VEFModule.UnityContainer.Resolve<ILoggerService>();
                return _logger;
            }
        }

        private void ContentChanged(ContentViewModel model)
        {
            _document = model == null ? "" : model.Title;
            RaisePropertyChanged("Title");
            if(model != null)
            {
                if (_lastDocument != null)
                    _lastDocument.IsSelected = false;

                _lastDocument = model;
                model.IsSelected = true;
                //--------------------------------------------------------------------
                //set current model for propertygrid if active document has changed
                var propService = VEFModule.UnityContainer.Resolve(typeof(IPropertiesService), "") as IPropertiesService;
                    propService.CurrentItem = model.Model;
                //--------------------------------------------------------------------


                Logger.Log("Active document changed to " + model.Title, LogCategory.Info, LogPriority.None);
            }
        }

        protected override void ModelChangedEventHandler(object sender, PropertyChangedEventArgs e)
        {
            string newValue = ActiveDocument == null ? "" : ActiveDocument.Title;
            if (_document != newValue)
            {
                _document = newValue;
                RaisePropertyChanged("Title");
                base.ModelChangedEventHandler(sender, e);
            }
        }
    }
}