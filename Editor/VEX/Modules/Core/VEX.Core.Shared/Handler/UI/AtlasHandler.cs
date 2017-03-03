using Microsoft.Win32;
using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Model.Attributes;
using VEF;
using System.Windows.Controls;
using VEF.Model.Services;
using VEX.Core.Shared.ViewModel.UI;
using VEX.Model.UI;
using VEX.Core.View.UI;
using VEX.Interface.UI;

namespace VEX.Core.Shared.Handler.Atlas
{
    // [FileContent("EC Leser", "*.md", 1)]
    [NewContent("Atlas", 1, "Atlas")]
    public class AtlasHandler : IContentHandler
    {
        /// <summary>
        /// The injected logger service
        /// </summary>
        private readonly ILoggerService _loggerService;

        /// <summary>
        /// The save file dialog
        /// </summary>
        private SaveFileDialog _dialog;

        /// <summary>
        /// Constructor of ECHandler - all parameters are injected
        /// </summary>
        /// <param name="container">The injected container of the application</param>
        /// <param name="loggerService">The injected logger service of the application</param>
        public AtlasHandler(ILoggerService loggerService)
        {
            _loggerService = loggerService;
            _dialog = new SaveFileDialog();
        }

        #region IContentHandler Members

        public ContentViewModel NewContent(object parameter)
        {
            var vm = VEFModule.UnityContainer.Resolve(typeof(AtlasViewModel), "") as AtlasViewModel;
            var model = VEFModule.UnityContainer.Resolve(typeof(AtlasModel), "") as AtlasModel  ;
            var view = VEFModule.UnityContainer.Resolve(typeof(AtlasView), "") as AtlasView;

            //Model details
            _loggerService.Log("Creating a new simple file using AtlasHandler", LogCategory.Info, LogPriority.Low);

            //Clear the undo stack
            //   model.Document.UndoStack.ClearAll();

            //Set the model and view
            vm.SetModel(model);
            vm.SetView(view);
            vm.Title = "Atlas";
            (vm.View as UserControl).DataContext = model;
            vm.SetHandler(this);
            model.SetDirty(true);

            model.SetLocation("AtlasID:##:");

            IProjectTreeService pfExplorerService = VEFModule.UnityContainer.Resolve(typeof(IProjectTreeService), "") as IProjectTreeService;
            IAtlasService AtlasService = VEFModule.UnityContainer.Resolve(typeof(IAtlasService), "") as IAtlasService;

            PItem parent = null;

            if (pfExplorerService.SelectedItem != null)
                parent = pfExplorerService.SelectedItem;

            AtlasModel newAtlas = new AtlasModel();
            newAtlas.Parent = parent;

            if (pfExplorerService.SelectedItem != null)
                pfExplorerService.SelectedItem.Items.Add(newAtlas);

            AtlasService.Atlass.Add(newAtlas);
            //  AtlasService.SelectedAtlas = newAtlas;
            newAtlas.Open(-1);


            return vm;
        }

        /// <summary>
        /// Validates the content by checking if a file exists for the specified location
        /// </summary>
        /// <param name="info">The string containing the file location</param>
        /// <returns>True, if the file exists and has a .md extension - false otherwise</returns>
        public bool ValidateContentType(object info)
        {
            string location = info as string;
            string extension = "";

            if (location == null)
            {
                return false;
            }

            extension = Path.GetExtension(location);
            return File.Exists(location) && extension == ".Atlas";
        }

        /// <summary>
        /// Opens a file and returns the corresponding MDViewModel
        /// </summary>
        /// <param name="info">The string location of the file</param>
        /// <returns>The <see cref="MDViewModel"/> for the file.</returns>
        public ContentViewModel OpenContent(object info, object param)
        {
            var location = info as string;
            if (location != null)
            {
                AtlasModel model = null;
                AtlasViewModel vm = VEFModule.UnityContainer.Resolve(typeof(AtlasViewModel), "") as AtlasViewModel;
                var view = VEFModule.UnityContainer.Resolve(typeof(AtlasView), "") as AtlasView;

                try
                {
                    IAtlasService AtlasService = VEFModule.UnityContainer.Resolve(typeof(IAtlasService), "") as IAtlasService;
                    IProjectTreeService pfExplorerService = VEFModule.UnityContainer.Resolve(typeof(IProjectTreeService), "") as IProjectTreeService;

                    //          string[] split = Regex.Split(info.ToString(), ":##:");
                    //if (split.Count() == 2)
                    //{
                    //    string identifier = split[0];
                    //    string ID = split[1];
                    //    if (identifier == "AtlasID")
                    //    {
                    var Atlas = AtlasService.Atlass.Where(x => x.ContentID == info.ToString());
                    if (Atlas.Any())
                    {
                        AtlasService.SelectedAtlas = Atlas.First();
                        AtlasService.SelectedAtlas.Open(info);
                    }
                    else //new Atlas
                    {
                        //    AtlasModel newAtlas = new AtlasModel() { Name = "Atlas NEW", ContentID = "AtlasID:##:" };
                        // newAtlas.Parent = parent;

                        if (pfExplorerService.SelectedItem is AtlasModel)
                        {    // pfExplorerService.SelectedItem.Items.Add(newAtlas);
                            var newAtlas = pfExplorerService.SelectedItem as AtlasModel;
                            if (newAtlas != null)
                            {
                                AtlasService.Atlass.Add(newAtlas);
                                //  AtlasService.SelectedAtlas = newAtlas;
                                newAtlas.Open(-1);

                                model = newAtlas;
                            }
                        }
                    }

                    //Model details
                    if (model == null)
                        model = VEFModule.UnityContainer.Resolve(typeof(AtlasModel), "") as AtlasModel;

                    model.SetLocation(info);

                    //  model.SetLocation("AuftragID:##:" + info + "");

                    //      model.Document.Text = File.ReadAllText(location);
                    model.SetDirty(true);
                    //   }
                }



                catch (Exception exception)
                {
                    _loggerService.Log(exception.Message, LogCategory.Exception, LogPriority.High);
                    _loggerService.Log(exception.StackTrace, LogCategory.Exception, LogPriority.High);
                    return null;
                }

                //Clear the undo stack
                // model.Document.UndoStack.ClearAll();

                //Set the model and view
                vm.SetModel(model);
                vm.SetView(view);
                vm.Title = "AtlasViewer";//model.nae  // Path.GetFileName("Atlas gefunden");
                (vm.View as UserControl).DataContext = model;

                return vm;
            }
            return null;
        }

        public ContentViewModel OpenContentFromId(string contentId, object param)
        {
            //string[] split = Regex.Split(contentId, ":##:");
            //if (split.Count() == 2)
            //{
            //    string identifier = split[0];
            //    string path = split[1];
            //    if (identifier == "FILE" && File.Exists(path))
            //    {
            return OpenContent(contentId, param);
            //    }
            //}
            //return null;
        }

        /// <summary>
        /// Saves the content of the TextViewModel
        /// </summary>
        /// <param name="contentViewModel">This needs to be a TextViewModel that needs to be saved</param>
        /// <param name="saveAs">Pass in true if you need to Save As?</param>
        /// <returns>true, if successful - false, otherwise</returns>
        public virtual bool SaveContent(ContentViewModel contentViewModel, bool saveAs = false)
        {
            var gameProjectViewModel = contentViewModel as AtlasViewModel;

            if (gameProjectViewModel == null)
            {
                _loggerService.Log("ContentViewModel needs to be a AtlasViewertViewModel to save details", LogCategory.Exception,
                                   LogPriority.High);
                throw new ArgumentException("ContentViewModel needs to be a AtlasViewertViewModel to save details");
            }

            var gameProjectModel = gameProjectViewModel.Model as AtlasModel;

            if (gameProjectModel == null)
            {
                _loggerService.Log("AtlasViewertViewModel does not have a AtlasViewertModel which should have the text",
                                   LogCategory.Exception, LogPriority.High);
                throw new ArgumentException("AtlasViewertViewModel does not have a AtlasViewertModel which should have the text");
            }

            var location = gameProjectModel.Location as string;

            if (location == null)
            {
                //If there is no location, just prompt for Save As..
                saveAs = true;
            }

            if (saveAs)
            {
                if (location != null)
                    _dialog.InitialDirectory = Path.GetDirectoryName(location);

                _dialog.CheckPathExists = true;
                _dialog.DefaultExt = "Atlas";
                _dialog.Filter = "Atlas files (*.Atlas)|*.Atlas";

                if (_dialog.ShowDialog() == true)
                {
                    location = _dialog.FileName;
                    gameProjectModel.SetLocation(location);
                    gameProjectViewModel.Title = Path.GetFileName(location);
                    try
                    {
                        //-----------------------------------
                        // Serialize Object
                        //-----------------------------------
                        //using (FileStream Str = new FileStream(location, FileMode.Create))
                        //{
                        //    XmlSerializer Ser = new XmlSerializer(typeof(CollectionOfIItem));
                        //    Ser.Serialize(Str, gameProjectModel.Items);
                        //    Str.Close();
                        //}

                        //####        gameProjectModel.SerializeObjectToXML();
                        //using (FileStream fs = new FileStream(location, FileMode.Open))
                        //{
                        //    System.Xml.Serialization.XmlSerializer x = new System.Xml.Serialization.XmlSerializer(gameProjectModel.GetType());
                        //    x.Serialize(fs, gameProjectModel);
                        //    fs.Close();
                        //}

                        gameProjectModel.SetDirty(false);
                        return true;
                    }
                    catch (Exception exception)
                    {
                        _loggerService.Log(exception.Message, LogCategory.Exception, LogPriority.High);
                        if (exception.InnerException != null) _loggerService.Log(exception.InnerException.Message, LogCategory.Exception, LogPriority.High);
                        _loggerService.Log(exception.StackTrace, LogCategory.Exception, LogPriority.High);
                        return false;
                    }
                }
            }
            else
            {
                try
                {
                    //-----------------------------------
                    // Serialize Object
                    //-----------------------------------
                    //####     gameProjectModel.SerializeObjectToXML();
                    //using (FileStream fs = new FileStream(location, FileMode.Open))
                    //{
                    //    System.Xml.Serialization.XmlSerializer x = new System.Xml.Serialization.XmlSerializer(gameProjectModel.GetType());
                    //    x.Serialize(fs, gameProjectModel);
                    //    fs.Close();
                    //}
                    IAtlasService AtlasService = VEFModule.UnityContainer.Resolve(typeof(IAtlasService), "") as IAtlasService;
                    AtlasService.SelectedAtlas.Save();

                    //  File.WriteAllText(location, gameProjectModel.Ser);
                    gameProjectModel.SetDirty(false);
                    return true;
                }
                catch (Exception exception)
                {
                    _loggerService.Log(exception.Message, LogCategory.Exception, LogPriority.High);
                    _loggerService.Log(exception.StackTrace, LogCategory.Exception, LogPriority.High);
                    return false;
                }
            }

            return false;

        }

        /// <summary>
        /// Validates the content from an ID - the ContentID from the ContentViewModel
        /// </summary>
        /// <param name="contentId">The content ID which needs to be validated</param>
        /// <returns>True, if valid from content ID - false, otherwise</returns>
        public bool ValidateContentFromId(string contentId)
        {
            if (contentId == null)
                return false;

            string[] split = Regex.Split(contentId, ":##:");
            if (split.Count() == 2)
            {
                string identifier = split[0];
                string path = split[1];
                if (identifier == "AtlasID") // && ValidateContentType(path)) no AtlasID = new Atlas
                {
                    return true;
                }
            }
            return false;
            //   return "AtlasViewer" == contentId ? true : false;
        }

        #endregion
    }
}
