using System.Collections.ObjectModel;
using VEF.Interfaces.Controls;
using VEF.Interfaces.Services;
using VEX.Model.Scene;
using VEX.Model.Scene.Model;

namespace VEX.Interface.Scene
{
    /// <summary>
    /// Interface IToolbarService - the application's toolbar tray is returned by this service
    /// </summary>
    public interface ISceneService
    {


        System.Windows.Controls.ContextMenu ContextMenu { get; }

        ObservableCollection<IItem> PredefObjects { get; }

        /// <summary>
        /// The list of themes registered with the theme manager
        /// </summary>
        /// <value>The themes.</value>
        ObservableCollection<SceneDataModel> Scenes { get; }

     //   TreeList TreeList { get; set; }

      //  IScene RootItem { get; }

      //  void SetAsRoot(IScene scene);

        bool AddScene(SceneDataModel scene);

        /// <summary>
        /// Called to set the current theme from the list of themes
        /// </summary>
        /// <param name="name">The name of the theme</param>
        /// <returns><c>true</c> if successful, <c>false</c> otherwise</returns>
       // bool SetCurrent(Guid guid);

        SceneDataModel SelectedScene { get; set; }

        SceneGraphToolModel SGTM { get; set; }
        /// <summary>
        /// Gets the right click menu.
        /// </summary>
        /// <value>The right click menu.</value>
        AbstractMenuItem RightClickMenu { get; }
    }
}
