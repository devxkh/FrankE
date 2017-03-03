using Microsoft.Practices.Unity;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using VEF.Interfaces.Services;
using VEF.Utils;

namespace VEF.Core.Services
{
    public abstract class PItem : ViewModelBase, IItem
    {
        private bool _isDirty;
        private String m_Name;
        private CollectionOfIItem m_Items;
        protected string _contentId = null;
        protected object _location;

        [Editable(false)]
        public virtual Boolean Visible { get; set; }


        /// <summary>
        /// The document location - could be a file location/server object etc.
        /// </summary>
        [Editable(false)]
        public virtual object Location
        {
            get { return _location; }
            protected set { _location = value; RaisePropertyChanged("Location"); }
        }

        [Display(AutoGenerateField = false)]
        [XmlIgnore]
        public virtual List<System.Type> CanAddThisItems { get; protected set; }

        [Display(AutoGenerateField = false)]
        [XmlIgnore]
        public virtual bool IsDirty
        {
            get { return _isDirty; }
            set
            {
                if (this.Parent != null)
                    this.Parent.IsDirty = true; //set all parents dirty

                _isDirty = value;
                RaisePropertyChanged("IsDirty");
            }
        }

        private String m_TypeImgSrc;

        [Editable(false)]
        public virtual String TypeImgSrc { get { return m_TypeImgSrc = "pack://application:,,,/Wide;component/Core/Icons/Textfile.png"; } set { m_TypeImgSrc = value; RaisePropertyChanged("TypeImgSrc"); } }

        public virtual string Name { get { return m_Name; } set { m_Name = value; RaisePropertyChanged("Name"); } }

        public virtual void Drop(IItem item) { }

        /// <summary>
        /// The content ID - unique value for each document
        /// </summary>
        /// <value>The content id.</value>
        [Editable(false)]
        [Display(Description = "The content ID - unique value for each document", Name = "Maximalbetrag", GroupName = "Karte")]
       // [Display(Description = "The content ID - unique value for each document", Name = "Maximalbetrag", GroupName = "Karte")]
        public virtual string ContentID
        {
            get { return _contentId; }
            //public for serializer
            set
            {
                if (_contentId != value)
                {
                    _contentId = value;
                    RaisePropertyChanged("ContentID");
                }
            }
        }

        [Editable(false)]
        [Display( AutoGenerateField = false)]
        public virtual Boolean HasChildren { get { return Items != null && Items.Count > 0 ? true : false; } }

        [Display(AutoGenerateField = false)]
        public virtual bool IsExpanded { get; set; }

        [Display(AutoGenerateField = false)]
        public virtual bool IsSelected { get; set; }

        [Display(AutoGenerateField = false)]
        [XmlIgnore]
        public virtual CollectionOfIItem Items { get { return m_Items; } set { m_Items = value; } }

        [Display(AutoGenerateField = false)]
        [XmlIgnore]
        public virtual List<IMenuItem> MenuOptions { get; set; }

        [Display(AutoGenerateField = false)]
        [XmlIgnore]
        public virtual IItem Parent { get; set; }

        [Display(AutoGenerateField = false)]
        [XmlIgnore]
        public IUnityContainer Container { get; set; }

        public virtual Boolean Create(IUnityContainer unityContainer) { return true; }
        public virtual Boolean Closing() { return true; }
        public virtual Boolean Delete() { return true; }
        public virtual Boolean Open(IUnityContainer unityContainer, object id)
        {

            return true;
        }
        public virtual Boolean Save(object param = null) { return true; }
        public virtual void Refresh() { }
        public virtual void Finish() { }


        public PItem()
        {
            m_Items = new CollectionOfIItem();
            this.CanAddThisItems = new List<Type>();
        }

    }
}
