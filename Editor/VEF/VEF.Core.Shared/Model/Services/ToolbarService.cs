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
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Markup;
using VEF.Interfaces.Base;
using VEF.Interfaces.Controls;
using VEF.Interfaces.Services;
using Xceed.Wpf.AvalonDock.Converters;

namespace VEF.Model.Services
{
    /// <summary>
    /// The VEF tool bar service
    /// </summary>
    public class ToolbarService : AbstractToolbar, IToolbarService
    {
        private static BoolToVisibilityConverter btv = new BoolToVisibilityConverter();
        private AbstractMenuItem menuItem;
        private ToolBarTray tray;
        private bool m_ToolBarTrayVisible;

        public ToolbarService() : base("$MAIN$", 0)
        {
        }

        /// <summary>
        /// Adds the specified item.
        /// </summary>
        /// <param name="item">The item.</param>
        /// <returns><c>true</c> if successfully added, <c>false</c> otherwise</returns>
        public override string Add(AbstractCommandable item)
        {
            AbstractToolbar tb = item as AbstractToolbar;
            if (tb != null)
            {
                tb.IsCheckable = true;
              //  tb.IsChecked = true; default = unchecked
            }

            string res = base.Add(item);
            return res;
              
        }

        /// <summary>
        /// Hide/Show ToolbarTray
        /// </summary>
        public bool ToolBarTrayVisible { get { return m_ToolBarTrayVisible; } set { m_ToolBarTrayVisible = value; } }

        /// <summary>
        /// The toolbar tray which will be used in the application
        /// </summary>
        public object ToolBarTray
        {
            get
            {
                if (tray == null)
                {
                    tray = new ToolBarTray();
                    tray.ContextMenu = new ContextMenu();
                   
                    tray.ContextMenu.ItemContainerStyle = Application.Current.FindResource("ToolbarContextMenu") as Style;
                }

                tray.ContextMenu.ItemsSource = _children;
                IAddChild child = tray;

                //get all Toolbars for this toolbartray
                foreach (var node in this.Children)
                {
                    var value = node as AbstractToolbar;
                    
                    //continue if toolbar already exists
                    if (tray.ToolBars.Where(x => x.Header.ToString() == value.Header).Any())
                        continue;

                    if (value != null)
                    {
                        var tb = new ToolBar();
                        var t = Application.Current.FindResource("toolBarItemTemplateSelector") as DataTemplateSelector;
                        tb.SetValue(ItemsControl.ItemTemplateSelectorProperty, t);

                        //Set the necessary bindings
                        var bandBinding = new Binding("Band");
                        var bandIndexBinding = new Binding("BandIndex");
                        var visibilityBinding = new Binding("IsChecked") { Converter = btv };

                        bandBinding.Source = value;
                        bandIndexBinding.Source = value;
                        visibilityBinding.Source = value;

                        bandBinding.Mode = BindingMode.TwoWay;
                        bandIndexBinding.Mode = BindingMode.TwoWay;

                        tb.SetBinding(ToolBar.BandProperty, bandBinding);
                        tb.SetBinding(ToolBar.BandIndexProperty, bandIndexBinding);
                        tb.SetBinding(ToolBar.VisibilityProperty, visibilityBinding);
                        
                        tb.Header = value.Header;

                        tb.ItemsSource = value.Children;
                        child.AddChild(tb);
                    }
                }

                return tray;
            }
        }

        public AbstractMenuItem RightClickMenu
        {
            get
            {
                if (tray == null)
                {
                    tray = this.ToolBarTray as ToolBarTray;
                }
                if (menuItem == null)
                {
                    menuItem = new MenuItemViewModel("_Toolbars", 100);
                    foreach (var value in tray.ContextMenu.ItemsSource)
                    {
                        var menu = value as AbstractMenuItem;
                        menuItem.Add(menu);
                    }
                }
                return menuItem;
            }
        }
    }
}