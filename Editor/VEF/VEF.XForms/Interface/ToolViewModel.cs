using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Interfaces.Services;
using VEF.Utils;

namespace VEF.Interfaces
{
    /// <summary>
    /// The abstract class which has to be inherited if you want to create a tool
    /// </summary>
    public abstract class ToolViewModel : ViewModelBase, ITool
    {
        #region Members

        protected string _contentId = null;
        protected bool _isActive = false;
        protected bool _isSelected = false;
        private bool _isVisible = true;

        protected string _title = null;

        #endregion

        #region Property

        /// <summary>
        /// The name of the tool
        /// </summary>
        public string Name { get; protected set; }

        /// <summary>
        /// The visibility of the tool
        /// </summary>
        public bool IsVisible
        {
            get { return _isVisible; }
            set
            {
                if (_isVisible != value)
                {
                    _isVisible = value;
                    RaisePropertyChanged("IsVisible");
                }
            }
        }


        /// <summary>
        /// pane location
        /// </summary>
        public abstract PaneLocation PreferredLocation { get; }

        /// <summary>
        /// Prefered width
        /// </summary>
        public virtual double PreferredWidth
        {
            get { return 200; }
        }

        /// <summary>
        /// prefered height
        /// </summary>
        public virtual double PreferredHeight
        {
            get { return 200; }
        }

        /// <summary>
        /// minwidth if right docking
        /// </summary>
        public virtual double MinWidth
        {
            get { return 0; }
        }

        /// <summary>
        /// The content model
        /// </summary>
        /// <value>The model.</value>
        public virtual ToolModel Model { get; set; }

        /// <summary>
        /// The content view
        /// </summary>
        /// <value>The view.</value>
        public virtual IContentView View { get; set; }

        /// <summary>
        /// The title of the document
        /// </summary>
        /// <value>The title.</value>
        public virtual string Title
        {
            get { return _title; }
            set
            {
                if (_title != value)
                {
                    _title = value;
                    RaisePropertyChanged("Title");
                }
            }
        }

        //IReadOnlyList -> .Net 4.5
        public IList<string> Menus
        {
            get { return new List<string>() { "a", "b", "c" }; }
        }

        /// <summary>
        /// The image source that can be used as an icon in the tab
        /// </summary>
        /// <value>The icon source.</value>
      //  public virtual ImageSource IconSource { get; protected set; }

        /// <summary>
        /// The content ID - unique value for each document
        /// </summary>
        /// <value>The content id.</value>
        public virtual string ContentId
        {
            get { return _contentId; }
            protected set
            {
                if (_contentId != value)
                {
                    _contentId = value;
                    RaisePropertyChanged("ContentId");
                }
            }
        }

        /// <summary>
        /// Is the document selected
        /// </summary>
        /// <value><c>true</c> if this instance is selected; otherwise, <c>false</c>.</value>
        public virtual bool IsSelected
        {
            get { return _isSelected; }
            set
            {
                if (_isSelected != value)
                {
                    _isSelected = value;
                    RaisePropertyChanged("IsSelected");
                }
            }
        }

        /// <summary>
        /// Is the document active
        /// </summary>
        /// <value><c>true</c> if this instance is active; otherwise, <c>false</c>.</value>
        public virtual bool IsActive
        {
            get { return _isActive; }
            set
            {
                if (_isActive != value)
                {
                    _isActive = value;
                    RaisePropertyChanged("IsActive");
                }
            }
        }

        #endregion
    }
}
