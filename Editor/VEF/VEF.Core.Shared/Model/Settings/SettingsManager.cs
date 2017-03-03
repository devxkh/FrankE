#region License

// Copyright (c) 2013 Chandramouleswaran Ravichandran
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#endregion


using System.Windows;
using MahApps.Metro.Controls.Dialogs;
using VEF.Interfaces.Settings;
using Prism.Commands;
using VEF.View.Settings;
using VEF.Model.Services;
using VEF.Interfaces.Controls;
using System.Windows.Input;

namespace VEF.Model.Settings
{
    /// <summary>
    /// Class VEFSettingsManager
    /// </summary>
    class SettingsManager : AbstractSettingsItem, ISettingsManager
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="VEFSettingsManager"/> class.
        /// </summary>
        public SettingsManager() : base("", null)
        {
            SettingsCommand = new DelegateCommand(OpenSettings);
        }

        /// <summary>
        /// Gets the settings menu.
        /// </summary>
        /// <value>The settings menu.</value>
        public ICommand SettingsCommand { get; private set; }

        /// <returns>The GUID for the item added which needs to be used to remove the item</returns>
        public string Add(IAbstractSettingsItem item)
        {
            return "";
        }

        /// <summary>
        /// Gets the node with the specified key.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <returns>`0.</returns>
        public IAbstractSettingsItem Get(string key)
        {
            return null;
        }

        public void OpenSettings()
        {
            SettingsWindow window = new SettingsWindow();
            window.Owner = Application.Current.MainWindow;
          //  var test = Application.Current.Resources["settingsDialog"];

            //BaseMetroDialog dialog = (BaseMetroDialog)Application.Current.Resources["settingsDialog"];
            //dialog.DataContext = this;
            //dialog = dialog.ShowModalDialogExternally();
         //   await TaskEx.Delay(5000);
         //   await dialog.RequestCloseAsync();
          //  this.Save();
            window.DataContext = this;
            bool? result = window.ShowDialog();
            if (result == true)
            {
                this.Save();
            }
            else
            {
                this.Reset();
            }
        }
    }
}