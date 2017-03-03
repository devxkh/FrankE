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
using System;

namespace VEF.Core.Services
{
    /// <summary>
    /// The content handler registry which manages different content handlers
    /// </summary>
    public class ContentHandlerRegistry : IContentHandlerRegistry
    {
        #region Fields
        /// <summary>
        /// List of content handlers
        /// </summary>
        protected readonly List<IContentHandler> _contentHandlers;

        /// <summary>
        /// The _available new content
        /// </summary>
        protected List<NewContentAttribute> _availableNewContent;

        /// <summary>
        /// The dictionary
        /// </summary>
        protected Dictionary<NewContentAttribute, IContentHandler> _dictionary;

        /// <summary>
        /// The workspace - NEEDS to be resolved in function call. Else this leads to recursive resolution in constructor.
        /// </summary>
        protected IWorkspace _workspace;

        /// <summary>
        /// The container
        /// </summary>
        protected readonly IUnityContainer _container;

        /// <summary>
        /// The status bar service
        /// </summary>
        protected readonly IStatusbarService _statusBar;

    
        #endregion

        #region Properties
        /// <summary>
        /// The new document command
        /// </summary>
        public ICommand NewCommand { get; protected set; }
        
        /// <summary>
        /// Gets the available contents which can be created.
        /// </summary>
        /// <value>The new content of the available.</value>
        /// IReadOnlyCollection -> .Net 4.5
        public ICollection<NewContentAttribute> AvailableNewContent
        {
            get { return _availableNewContent; }
        }

        /// <summary>
        /// List of content handlers
        /// </summary>
        public List<IContentHandler> ContentHandlers
        {
            get { return _contentHandlers; }
        }
        #endregion

        #region CTOR
        /// <summary>
        /// Constructor of content handler registry
        /// </summary>
        /// <param name="container">The injected container of the application</param>
        public ContentHandlerRegistry(IUnityContainer container, IStatusbarService statusBar)
        {
            _contentHandlers = new List<IContentHandler>();
            _container = container;
            _statusBar = statusBar;
            _dictionary = new Dictionary<NewContentAttribute, IContentHandler>();
            _availableNewContent = new List<NewContentAttribute>();
            this.NewCommand = new DelegateCommand(NewDocument,CanExecuteNewCommand);
        }
        #endregion

        #region IContentHandlerRegistry Members

        /// <summary>
        /// Register a content handler with the registry
        /// </summary>
        /// <param name="handler">The content handler</param>
        /// <returns>true, if successful - false, otherwise</returns>
        public virtual bool Register(IContentHandler handler)
        {
            return true;
        }

        /// <summary>
        /// Unregisters a content handler
        /// </summary>
        /// <param name="handler">The handler to remove</param>
        /// <returns></returns>
        public virtual bool Unregister(IContentHandler handler)
        {         
            return true;
        }

        #endregion

        #region Get the view model

        /// <summary>
        /// Returns a content view model for the specified object which needs to be displayed as a document
        /// The object could be anything - based on the handlers, a content view model is returned
        /// </summary>
        /// <param name="info">The object which needs to be displayed as a document in Wide</param>
        /// <returns>The content view model for the given info</returns>
        public ContentViewModel GetViewModel(object info, object param)
        {
            for (int i = ContentHandlers.Count - 1; i >= 0; i--)
            {
                var opener = ContentHandlers[i];
                if (opener.ValidateContentType(info))
                {
                    ContentViewModel vm = opener.OpenContent(info, param);
                    vm.Handler = opener;
                    return vm;
                }
            }
            return null;
        }

        /// <summary>
        /// Returns a content view model for the specified contentID which needs to be displayed as a document
        /// The contentID is the ID used in AvalonDock
        /// </summary>
        /// <param name="contentId">The contentID which needs to be displayed as a document in Wide</param>
        /// <returns>The content view model for the given info</returns>
        public ContentViewModel GetViewModelFromContentId(string contentId, object param)
        {
            for (int i = ContentHandlers.Count - 1; i >= 0; i--)
            {
                var opener = ContentHandlers[i];
                if (opener.ValidateContentFromId(contentId))
                {
                    ContentViewModel vm = opener.OpenContentFromId(contentId, param);
                    if (vm == null)
                        return null;

                    vm.Handler = opener;
                    return vm;
                }
            }
            return null;
        }

        #endregion

        #region New Command

        private bool CanExecuteNewCommand()
        {
            return true;
        }

        protected virtual void NewDocument()
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
                throw new NotImplementedException();
            }
        }
        #endregion
    }
}