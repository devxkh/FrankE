using Prism.Events;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using VEF.Interfaces;
using VEF.Interfaces.Services;

namespace VEF.WPF.Core.Services
{
    class ThemeManager : VEF.Core.Services.ThemeManager
    {
        public ThemeManager(AbstractWorkspace workspace, IEventAggregator eventAggregator, ILoggerService logger)
            : base (workspace, eventAggregator, logger)
        {

        }

        /// <summary>
        /// Set the current theme
        /// </summary>
        /// <param name="name">The name of the theme</param>
        /// <returns>true if the new theme is set, false otherwise</returns>
        public bool SetCurrent(string name) 
        {

            #if WINDOWS_APP
            if (ThemeDictionary.ContainsKey(name))
            {
                ITheme newTheme = ThemeDictionary[name];
                CurrentTheme = newTheme;

                //   ResourceDictionary theme = Application.Current.MainWindow.Resources.MergedDictionaries[0];
                ResourceDictionary appTheme = Application.Current.Resources.MergedDictionaries.Count > 0
                                                  ? Application.Current.Resources.MergedDictionaries[0]
                                                  : null;
                //  theme.BeginInit();
                //   theme.MergedDictionaries.Clear();
                if (appTheme != null)
                {
                    appTheme.BeginInit();
                    appTheme.MergedDictionaries.Clear();
                }
                else
                {
                    appTheme = new ResourceDictionary();
                    appTheme.BeginInit();
                    Application.Current.Resources.MergedDictionaries.Add(appTheme);
                }

                foreach (Uri uri in newTheme.UriList)
                {
                    ResourceDictionary newDict = new ResourceDictionary { Source = uri };
                    /*AvalonDock and menu style needs to move to the application
                     * 1. AvalonDock needs global styles as floatable windows can be created
                     * 2. Menu's need global style as context menu can be created
                    */
                    //if (uri.ToString().Contains("AvalonDock") ||
                    //    uri.ToString().Contains("Wide;component/Interfaces/Styles/VS2012/Menu.xaml"))
                    //{
                    appTheme.MergedDictionaries.Add(newDict);
                    //}
                    //else
                    //{
                    //    theme.MergedDictionaries.Add(newDict);
                    //}
                }
                appTheme.EndInit();

                //set Avalondock theme
                //todo in wpf dll       m_workspace.ADTheme = newTheme.ADTheme;

                //    theme.EndInit();
                _logger.Log("Theme set to " + name, LogCategory.Info, LogPriority.None);
                //todo         _eventAggregator.Publish<ThemeChangeEvent>()(newTheme);
            }

#endif
            return false;
        }
    }
}
