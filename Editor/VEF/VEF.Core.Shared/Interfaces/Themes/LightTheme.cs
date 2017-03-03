#region License

// Copyright (c) 2013 Chandramouleswaran Ravichandran
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#endregion

using System;
using System.Collections.Generic;
using VEF.Interfaces;

namespace VEF.Interfaces.Themes
{
    public enum AvalonDockThemesEnum
    {
        Generic,
        Aero,
        VS2010,
        Metro,
        Office2007Black,
        Office2007Blue,
        Office2007Silver,
        MetroDark,
        MetroLight
    }

    /// <summary>
    /// Class LightTheme
    /// </summary>
    public class LightTheme : ITheme
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="LightTheme"/> class.
        /// </summary>
        public LightTheme()
        {
            UriList = new List<Uri>
                          {

                              new Uri("pack://application:,,,/MahApps.Metro;component/Styles/Controls.xaml"),
                              new Uri("pack://application:,,,/MahApps.Metro;component/Styles/Fonts.xaml"),
                              new Uri("pack://application:,,,/MahApps.Metro;component/Styles/Colors.xaml"),
                              new Uri("pack://application:,,,/MahApps.Metro;component/Styles/Accents/Blue.xaml"),
                              new Uri("pack://application:,,,/MahApps.Metro;component/Styles/Accents/BaseLight.xaml"),
                              new Uri("pack://application:,,,/MahApps.Metro.Resources;component/Icons.xaml"),
                              new Uri("pack://application:,,,/VEF.Core.WPF;component/View/Icons/WebIcons.xaml"),
                               new Uri("pack://application:,,,/VEF.Core.WPF;component/View/Dialogs/SettingsDialog.xaml"),
                           
                             // new Uri("pack://application:,,,/Wide;component/Interfaces/Styles/VS2012/Menu.xaml"),

                         
                               new Uri("pack://application:,,,/Xceed.Wpf.AvalonDock.Themes.Metro;component/Theme.xaml"),
                                                  
                              //<ResourceDictionary Source="pack://application:,,,/Xceed.Wpf.AvalonDock.Themes.Metro;component/Theme.xaml"/>
                             // new Uri("pack://application:,,,/AvalonDock.Themes.VS2012;component/LightTheme.xaml"), //Tab menu!!!
                         //    new Uri("pack://application:,,,/Wide;component/Interfaces/Styles/VS2012/LightColors.xaml"), //MENU style !!!!!!
                           //   new Uri("pack://application:,,,/Wide;component/Interfaces/Styles/VS2012/LightTheme.xaml"),
                               
                                  new Uri("pack://application:,,,/VEF.Core.WPF;component/View/Styles/ControlsMetro.xaml"),
                                        new Uri("pack://application:,,,/VEF.Core.WPF;component/View/Styles/ToolbarBinding.xaml"),
                           // new Uri("pack://application:,,,/Wide;component/Interfaces/Styles/VS2012/Menu.xaml")
                          };
        }

        #region ITheme Members

        public AvalonDockThemesEnum ADTheme { get { return AvalonDockThemesEnum.Metro; } }

        /// <summary>
        /// Lists of valid URIs which will be loaded in the theme dictionary
        /// </summary>
        /// <value>The URI list.</value>
        public IList<Uri> UriList { get; internal set; }

        /// <summary>
        /// The name of the theme - "Light"
        /// </summary>
        /// <value>The name.</value>
        public string Name
        {
            get { return "Light"; }
        }

        #endregion
    }
}