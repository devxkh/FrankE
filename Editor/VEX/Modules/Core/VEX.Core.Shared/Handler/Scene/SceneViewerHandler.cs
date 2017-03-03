using Microsoft.Win32;
using System;
using System.Linq;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEF.Model.Attributes;
using VEX.Core.View;
using VEX.Interface.Scene;
using VEX.Model.Scene.Model;
using VEX.Core.Shared.ViewModel.Scene;
using VEF;
using System.Windows.Controls;
using VEF.Model.Services;

namespace VEX.Core.Shared.Handler.Scene
{
    // [FileContent("EC Leser", "*.md", 1)]
    [NewContent("Scene", 1, "Scene")]
    public class SceneViewerHandler : IContentHandler
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
        public SceneViewerHandler(ILoggerService loggerService)
        {
            _loggerService = loggerService;
            _dialog = new SaveFileDialog();
        }

        #region IContentHandler Members

        public ContentViewModel NewContent(object parameter)
        {
            var vm = VEFModule.UnityContainer.Resolve(typeof(SceneViewModel), "") as SceneViewModel;
            var model = VEFModule.UnityContainer.Resolve(typeof(SceneDataModel), "") as SceneDataModel  ;
            var view = VEFModule.UnityContainer.Resolve(typeof(SceneView), "") as SceneView;

            //Model details
            _loggerService.Log("Creating a new simple file using SceneHandler", LogCategory.Info, LogPriority.Low);

            //Clear the undo stack
            //   model.Document.UndoStack.ClearAll();

            //Set the model and view
            vm.SetModel(model);
            vm.SetView(view);
            vm.Title = "Scene New";
            (vm.View as UserControl).DataContext = model;
            vm.SetHandler(this);
            model.SetDirty(true);

            model.SetLocation("SceneID:##:");

            IProjectTreeService pfExplorerService = VEFModule.UnityContainer.Resolve(typeof(IProjectTreeService), "") as IProjectTreeService;
            ISceneService sceneService = VEFModule.UnityContainer.Resolve(typeof(ISceneService), "") as ISceneService;

            PItem parent = null;

            if (pfExplorerService.SelectedItem != null)
                parent = pfExplorerService.SelectedItem;

            SceneDataModel newScene = new SceneDataModel() { Name = "Scene NEW", ContentID = "SceneID:##:" };
            newScene.Parent = parent;

            if (pfExplorerService.SelectedItem != null)
                pfExplorerService.SelectedItem.Items.Add(newScene);

            sceneService.Scenes.Add(newScene);
            //  sceneService.SelectedScene = newScene;
            newScene.Open(-1);


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
            return File.Exists(location) && extension == ".scene";
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
                SceneDataModel model = null;
                SceneViewModel vm = VEFModule.UnityContainer.Resolve(typeof(SceneViewModel), "") as SceneViewModel;
                var view = VEFModule.UnityContainer.Resolve(typeof(SceneView), "") as SceneView;

                try
                {
                    ISceneService sceneService = VEFModule.UnityContainer.Resolve(typeof(ISceneService), "") as ISceneService;
                    IProjectTreeService pfExplorerService = VEFModule.UnityContainer.Resolve(typeof(IProjectTreeService), "") as IProjectTreeService;

                    //          string[] split = Regex.Split(info.ToString(), ":##:");
                    //if (split.Count() == 2)
                    //{
                    //    string identifier = split[0];
                    //    string ID = split[1];
                    //    if (identifier == "SceneID")
                    //    {
                    var scene = sceneService.Scenes.Where(x => x.ContentID == info.ToString());
                    if (scene.Any())
                    {
                        sceneService.SelectedScene = scene.First();
                        sceneService.SelectedScene.Open(info);
                    }
                    else //new scene
                    {
                        //    SceneDataModel newScene = new SceneDataModel() { Name = "Scene NEW", ContentID = "SceneID:##:" };
                        // newScene.Parent = parent;

                        if (pfExplorerService.SelectedItem is SceneDataModel)
                        {    // pfExplorerService.SelectedItem.Items.Add(newScene);
                            var newScene = pfExplorerService.SelectedItem as SceneDataModel;
                            if (newScene != null)
                            {
                                sceneService.Scenes.Add(newScene);
                                //  sceneService.SelectedScene = newScene;
                                newScene.Open(-1);

                                model = newScene;
                            }
                        }
                    }

                    //Model details
                    if (model == null)
                        model = VEFModule.UnityContainer.Resolve(typeof(SceneDataModel), "") as SceneDataModel;

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
                vm.Title = model.Name ?? "Scene";//model.nae  // Path.GetFileName("Scene gefunden");
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
            var gameProjectViewModel = contentViewModel as SceneViewModel;

            if (gameProjectViewModel == null)
            {
                _loggerService.Log("ContentViewModel needs to be a SceneViewertViewModel to save details", LogCategory.Exception,
                                   LogPriority.High);
                throw new ArgumentException("ContentViewModel needs to be a SceneViewertViewModel to save details");
            }

            var gameProjectModel = gameProjectViewModel.Model as SceneDataModel;

            if (gameProjectModel == null)
            {
                _loggerService.Log("SceneViewertViewModel does not have a SceneViewertModel which should have the text",
                                   LogCategory.Exception, LogPriority.High);
                throw new ArgumentException("SceneViewertViewModel does not have a SceneViewertModel which should have the text");
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
                _dialog.DefaultExt = "scene";
                _dialog.Filter = "Scene files (*.scene)|*.scene";

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
                    ISceneService sceneService = VEFModule.UnityContainer.Resolve(typeof(ISceneService), "") as ISceneService;
                    sceneService.SelectedScene.Save();

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
                if (identifier == "SceneID") // && ValidateContentType(path)) no sceneID = new scene
                {
                    return true;
                }
            }
            return false;
            //   return "SceneViewer" == contentId ? true : false;
        }

        #endregion
    }
}
