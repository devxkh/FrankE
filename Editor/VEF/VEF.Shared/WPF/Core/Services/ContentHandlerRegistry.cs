#region License

// Copyright (c) 2013 Chandramouleswaran Ravichandran
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#endregion

using System.Collections.Generic;
using System.Linq;
using System.Windows.Input;
using System.Windows;
using VEF.Core.Attributes;
using VEF.Interfaces.Services;
using VEF.Interfaces;
using Prism.Commands;
using Microsoft.Practices.Unity;

namespace VEF.WPF.Core.Services
{
    /// <summary>
    /// The content handler registry which manages different content handlers
    /// </summary>
    public class ContentHandlerRegistry : VEF.Core.Services.ContentHandlerRegistry
    {
        #region Fields

        #endregion

        #region Properties

        #endregion

        #region CTOR

        /// <summary>
        /// Constructor of content handler registry
        /// </summary>
        /// <param name="container">The injected container of the application</param>
        public ContentHandlerRegistry(IUnityContainer container, IStatusbarService statusBar)
            : base(container, statusBar)
        { }

        #endregion

        #region IContentHandlerRegistry Members

        /// <summary>
        /// Register a content handler with the registry
        /// </summary>
        /// <param name="handler">The content handler</param>
        /// <returns>true, if successful - false, otherwise</returns>
        public override bool Register(IContentHandler handler)
        {
#if WINDOWS_APP
            ContentHandlers.Add(handler);
            NewContentAttribute[] handlerAttributes = (NewContentAttribute[])(handler.GetType()).GetCustomAttributes(typeof(NewContentAttribute), true);
            _availableNewContent.AddRange(handlerAttributes);
            foreach (NewContentAttribute newContentAttribute in handlerAttributes)
            {
                _dictionary.Add(newContentAttribute, handler);
            }

            _availableNewContent.Sort((attribute, contentAttribute) => attribute.Priority - contentAttribute.Priority);

#endif
            return true;
        }

        /// <summary>
        /// Unregisters a content handler
        /// </summary>
        /// <param name="handler">The handler to remove</param>
        /// <returns></returns>
        public override bool Unregister(IContentHandler handler)
        {
#if WINDOWS_APP
            NewContentAttribute[] handlerAttributes = (NewContentAttribute[])(handler.GetType()).GetCustomAttributes(typeof(NewContentAttribute), true);
            _availableNewContent.RemoveAll(handlerAttributes.Contains);
            foreach (NewContentAttribute newContentAttribute in handlerAttributes)
            {
                _dictionary.Remove(newContentAttribute);
            }

            _availableNewContent.Sort((attribute, contentAttribute) => attribute.Priority - contentAttribute.Priority);
            return ContentHandlers.Remove(handler);
#endif
            return true;
        }

        #endregion

        #region New Command

        protected override void NewDocument()
        {
            if (_workspace == null)
                _workspace = _container.Resolve<AbstractWorkspace>();

            if (_availableNewContent.Count == 1)
            {
                IContentHandler handler = _dictionary[_availableNewContent[0]];
                var openValue = handler.NewContent(_availableNewContent[0]);

                if (openValue == null)
                    return;

                _workspace.Documents.Add(openValue);
                _workspace.ActiveDocument = openValue;
            }
            else
            {
                // The new glow background brush

                //todo


                //SolidColorBrush _newBackground = new SolidColorBrush(Color.FromRgb(104,33,122));

                //NewFileWindow window = new NewFileWindow();
                //window.Owner = Application.Current.MainWindow;
                //Brush backup = _statusBar.Background;
                //_statusBar.Background = _newBackground;
                //_statusBar.Text = "Select a new file";
                //if(Application.Current.MainWindow is MetroWindow)
                //{
                //    window.Resources = Application.Current.MainWindow.Resources;
                //    Window win = Application.Current.MainWindow as MetroWindow;
                //    window.Resources = win.Resources;
                //    //window.GlowBrush = win.GlowBrush;
                //    //window.TitleForeground = win.TitleForeground;
                //}
                //window.DataContext = _availableNewContent;
                //if(window.ShowDialog() == true)
                //{
                //    NewContentAttribute newContent = window.NewContent;
                //    if(newContent != null)
                //    {
                //        IContentHandler handler = _dictionary[newContent];
                //        var openValue = handler.NewContent(newContent);
                //        if (openValue != null)
                //        {
                //            _workspace.Documents.Add(openValue);
                //            _workspace.ActiveDocument = openValue;
                //        }
                //    }
                //}
                //_statusBar.Background = backup;
                //_statusBar.Clear();
            }
        }
        #endregion
    }
}