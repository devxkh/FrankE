using Microsoft.Practices.Unity;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using VEF.Interfaces.Services;
using VEF.Utils;

namespace VEF.Model.Services
{
    [DataContract(IsReference = true)]
    public abstract class PItem : ViewModelIsRefBase, IItem
    {
        private bool _isDirty;
        private string m_Name;
        private CollectionOfIItem m_Items;
        protected string _contentId = null;
        protected object _location;
        
        [Editable(false)]
        [DataMember]
        [Display(Name = "Visible", Description = "Item is visible", GroupName = "Debug")]
        public virtual bool Visible { get; set; }


        /// <summary>
        /// The document location - could be a file location/server object etc.
        /// </summary>
        [Editable(false)]
        [DataMember]
        [Display(Name = "Location", Description = "", GroupName = "Debug")]
        public virtual object Location
        {
            get { return _location; }
            set { _location = value; RaisePropertyChanged("Location"); }
        }

        [Display(AutoGenerateField = false)]
        public virtual List<System.Type> CanAddThisItems { get; }

        [Display(AutoGenerateField = false)]
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

        private string m_TypeImgSrc;

        [Display(AutoGenerateField = false)]
        [Editable(false)]
        public virtual string TypeImgSrc { get { return m_TypeImgSrc = "pack://application:,,,/Wide;component/Core/Icons/Textfile.png"; } set { m_TypeImgSrc = value; RaisePropertyChanged("TypeImgSrc"); } }

        [Display(Name = "Name", Description = "", GroupName = "General")]
        [DataMember]
        public virtual string Name { get { return m_Name; } set { m_Name = value; RaisePropertyChanged("Name"); } }

        public virtual void Drop(IItem item) { }

        /// <summary>
        /// The content ID - unique value for each document
        /// </summary>
        /// <value>The content id.</value>
        [Editable(false)]
        [Display(Name = "ContentID", Description = "The content ID - unique value for each document", GroupName = "Debug")]
        [DataMember]
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
        public virtual bool HasChildren { get { return Items != null && Items.Count > 0 ? true : false; } }

        [Display(AutoGenerateField = false)]
        [DataMember]
        public virtual bool IsExpanded { get; set; }

        [Display(AutoGenerateField = false)]
        [DataMember]
        public virtual bool IsSelected { get; set; }

        [Display(AutoGenerateField = false)]
        [DataMember]
        public virtual CollectionOfIItem Items
        {
            get
            {
                return m_Items;
            }
            set
            {
                m_Items = value;
            }
        }
        
        [Display(AutoGenerateField = false)]
        public virtual List<IMenuItem> MenuOptions { get; set; }
        
        [Display(AutoGenerateField = false)]
        [DataMember]
        public virtual IItem Parent { get; set; }

        public virtual bool Create() { return true; }
        public virtual bool Closing() { return true; }
        public virtual bool Delete() { return true; }
        public virtual bool Open(object id)
        {

            return true;
        }
        public virtual bool Save(object param = null) { return true; }
        public virtual void Refresh() { }
        public virtual void Finish() { }


        public PItem()
        {
            m_Items = new CollectionOfIItem();
            this.CanAddThisItems = new List<Type>();
            MenuOptions = new List<IMenuItem>();
        }

    }
}
