using Microsoft.Practices.Unity;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Controls;
using VEF.Core.Model;
using VEF.Core.Shared.ViewModel;
using VEF.Core.View;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Model.Attributes;

namespace VEF.Core.Handler
{
    [NewContent("XML", 1, "XML", "pack://application:,,,/Module.XML;component/Icons/MDType.png")]
    internal class XMLHandler : IContentHandler
    {

        /// <summary>
        /// The injected logger service
        /// </summary>
       // private readonly ILoggerService _loggerService;

        /// <summary>
        /// The save file dialog
        /// </summary>
        //     private SaveFileDialog _dialog;

        /// <summary>
        /// Constructor of ECHandler - all parameters are injected
        /// </summary>
        /// <param name="container">The injected container of the application</param>
        /// <param name="loggerService">The injected logger service of the application</param>
        public XMLHandler()
        {
           // _loggerService = loggerService;
            //     _dialog = new SaveFileDialog();
        }

        #region IContentHandler Members

        public ContentViewModel NewContent(object parameter)
        {
            var vm = VEFModule.UnityContainer.Resolve(typeof(XMLViewModel), "") as XMLViewModel;
            var model = VEFModule.UnityContainer.Resolve(typeof(XMLModel), "") as XMLModel;
            var view = VEFModule.UnityContainer.Resolve(typeof(XMLView), "") as XMLView;

            //Model details
         //   _loggerService.Log("Creating a new simple file using XMLHandler", LogCategory.Info, LogPriority.Low);

            //Clear the undo stack
            model.Document.UndoStack.ClearAll();

            //Set the model and view
            vm.SetModel(model);
            vm.SetView(view);
            vm.Title = "XML File";
            (vm.View as UserControl).DataContext = model;
            vm.SetHandler(this);
            model.SetDirty(true);

            return vm;
        }

        /// <summary>
        /// Validates the content by checking if a file exists for the specified location
        /// </summary>
        /// <param name="info">The string containing the file location</param>
        /// <returns>True, if the file exists and has a .md extension - false otherwise</returns>
        public bool ValidateContentType(object info)
        {
            return true;
        }

        /// <summary>
        /// Opens a file and returns the corresponding MDViewModel
        /// </summary>
        /// <param name="info">The string location of the file</param>
        /// <returns>The <see cref="MDViewModel"/> for the file.</returns>
        public ContentViewModel OpenContent(object info, object param)
        {
            //var location = info as string;
            //if (location != null)
            //{
            var vm = VEFModule.UnityContainer.Resolve(typeof(XMLViewModel), "") as XMLViewModel;
            var model = VEFModule.UnityContainer.Resolve(typeof(XMLModel), "") as XMLModel;
            var view = VEFModule.UnityContainer.Resolve(typeof(XMLView), "") as XMLView;

            //Model details
            model.SetLocation(info);
            try
            {
                //      model.Document.Text = File.ReadAllText(location);
                model.SetDirty(false);
            }
            catch (Exception exception)
            {
               // _loggerService.Log(exception.Message, LogCategory.Exception, LogPriority.High);
              //  _loggerService.Log(exception.StackTrace, LogCategory.Exception, LogPriority.High);
                return null;
            }

            //Clear the undo stack
            model.Document.UndoStack.ClearAll();

            //Set the model and view
            vm.SetModel(model);
            vm.SetView(view);
            vm.Title = "todo .. file name";
            (vm.View as UserControl).DataContext = model;

            return vm;
            //   }
            //   return null;
        }

        public ContentViewModel OpenContentFromId(string contentId, object param)
        {
            //    string[] split = Regex.Split(contentId, ":##:");
            //    if (split.Count() == 2)
            //    {
            //        string identifier = split[0];
            //        string path = split[1];
            //        if (identifier == "FILE" && File.Exists(path))
            //        {
            //            return OpenContent(path);
            //        }
            //    }
            return null;
        }

        /// <summary>
        /// Saves the content of the TextViewModel
        /// </summary>
        /// <param name="contentViewModel">This needs to be a TextViewModel that needs to be saved</param>
        /// <param name="saveAs">Pass in true if you need to Save As?</param>
        /// <returns>true, if successful - false, otherwise</returns>
        public virtual bool SaveContent(ContentViewModel contentViewModel, bool saveAs = false)
        {
            return true;
        }

        /// <summary>
        /// Validates the content from an ID - the ContentID from the ContentViewModel
        /// </summary>
        /// <param name="contentId">The content ID which needs to be validated</param>
        /// <returns>True, if valid from content ID - false, otherwise</returns>
        public bool ValidateContentFromId(string contentId)
        {

            return contentId == "XML" ? true : false;
        }

        #endregion
    }
}
