using Prism.Events;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Interfaces;
using VEF.Interfaces.Services;

namespace VEF.Model.Services
{
    /// <summary>
    /// The main theme manager used in Wide
    /// </summary>
    abstract public class ThemeManager : IThemeManager
    {
        /// <summary>
        /// Dictionary of different themes
        /// </summary>
        protected static readonly Dictionary<string, ITheme> ThemeDictionary = new Dictionary<string, ITheme>();

        /// <summary>
        /// The injected logger
        /// </summary>
        protected readonly ILoggerService _logger;

        private AbstractWorkspace m_workspace;

        /// <summary>
        /// The theme manager constructor
        /// </summary>
        /// <param name="eventAggregator">The injected event aggregator</param>
        /// <param name="logger">The injected logger</param>
        public ThemeManager(AbstractWorkspace workspace)
        {
            Themes = new ObservableCollection<ITheme>();
       //     _logger = VEFModule.UnityContainer.Resolve(typeof(ILoggerService), "ILoggerService") as ILoggerService;
            m_workspace = workspace;
        }

        /// <summary>
        /// The current theme set in the theme manager
        /// </summary>
        public ITheme CurrentTheme { get; protected set; }

        #region IThemeManager Members

        /// <summary>
        /// The collection of themes
        /// </summary>
        public ObservableCollection<ITheme> Themes { get; internal set; }

        /// <summary>
        /// Set the current theme
        /// </summary>
        /// <param name="name">The name of the theme</param>
        /// <returns>true if the new theme is set, false otherwise</returns>
       abstract public bool SetCurrent(string name);

       // {
       //     if (ThemeDictionary.ContainsKey(name))
       //     {
       //         ITheme newTheme = ThemeDictionary[name];
       //         CurrentTheme = newTheme;

       //         //   ResourceDictionary theme = Application.Current.MainWindow.Resources.MergedDictionaries[0];
       //         ResourceDictionary appTheme = Application.Current.Resources.MergedDictionaries.Count > 0
       //                                           ? Application.Current.Resources.MergedDictionaries[0]
       //                                           : null;
       //         //  theme.BeginInit();
       //         //   theme.MergedDictionaries.Clear();
       //         if (appTheme != null)
       //         {
       //             appTheme.BeginInit();
       //             appTheme.MergedDictionaries.Clear();
       //         }
       //         else
       //         {
       //             appTheme = new ResourceDictionary();
       //             appTheme.BeginInit();
       //             Application.Current.Resources.MergedDictionaries.Add(appTheme);
       //         }
       //         foreach (Uri uri in newTheme.UriList)
       //         {
       //             ResourceDictionary newDict = new ResourceDictionary { Source = uri };
       //             /*AvalonDock and menu style needs to move to the application
       //              * 1. AvalonDock needs global styles as floatable windows can be created
       //              * 2. Menu's need global style as context menu can be created
       //             */
       //             //if (uri.ToString().Contains("AvalonDock") ||
       //             //    uri.ToString().Contains("Wide;component/Interfaces/Styles/VS2012/Menu.xaml"))
       //             //{
       //             appTheme.MergedDictionaries.Add(newDict);
       //             //}
       //             //else
       //             //{
       //             //    theme.MergedDictionaries.Add(newDict);
       //             //}
       //         }
       //         appTheme.EndInit();

       //         //set Avalondock theme
       //  //todo in wpf dll       m_workspace.ADTheme = newTheme.ADTheme;

       //         //    theme.EndInit();
       //         _logger.Log("Theme set to " + name, LogCategory.Info, LogPriority.None);
       ////todo         _eventAggregator.Publish<ThemeChangeEvent>()(newTheme);
       //     }
       //     return false;
       // }

        /// <summary>
        /// Adds a theme to the theme manager
        /// </summary>
        /// <param name="theme">The theme to add</param>
        /// <returns>true, if successful - false, otherwise</returns>
        public bool AddTheme(ITheme theme)
        {
            if (!ThemeDictionary.ContainsKey(theme.Name))
            {
                ThemeDictionary.Add(theme.Name, theme);
                Themes.Add(theme);
                return true;
            }
            return false;
        }

        #endregion
    }
}
