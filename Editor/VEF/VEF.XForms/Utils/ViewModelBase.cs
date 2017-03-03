using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace VEF.Utils
{
    [DataContract]
    public class ViewModelBase : INotifyPropertyChanged
    {
        // Helper-Methode, um nicht in jedem Set-Accessor zu prüfen, ob PropertyChanged!=null
        //protected void Changed(string propertyName)
        //{
        //    if (PropertyChanged != null)
        //        PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        //}

        //public event PropertyChangedEventHandler PropertyChanged;


        #region INotifyPropertyChanged Members

        /// <summary>
        /// Event handler that gets triggered when a property changes
        /// </summary>
        public virtual event PropertyChangedEventHandler PropertyChanged;

        #endregion


        /// <summary>
        /// Should be called when a property value has changed
        /// </summary>
        /// <param name="propertyName">The property name</param>
        /// .net 4.5 [CallerMemberName]
        protected virtual void RaisePropertyChanged(string propertyName = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        /// <summary>
        /// Raises the property changed with undo.
        /// </summary>
        /// <param name="oldValue">The old value.</param>
        /// <param name="newValue">The new value.</param>
        /// <param name="description">The description.</param>
        /// <param name="propertyName">Name of the property.</param>
        protected virtual void RaisePropertyChangedWithValues(object oldValue, object newValue, string description, string propertyName = "")
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedExtendedEventArgs(propertyName, oldValue, newValue, description));
            }
        }

    }

    [DataContract(IsReference = true)]
    public class ViewModelIsRefBase : INotifyPropertyChanged
    {
        // Helper-Methode, um nicht in jedem Set-Accessor zu prüfen, ob PropertyChanged!=null
        //protected void Changed(string propertyName)
        //{
        //    if (PropertyChanged != null)
        //        PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        //}

        //public event PropertyChangedEventHandler PropertyChanged;


        #region INotifyPropertyChanged Members

        /// <summary>
        /// Event handler that gets triggered when a property changes
        /// </summary>
        public virtual event PropertyChangedEventHandler PropertyChanged;

        #endregion


        /// <summary>
        /// Should be called when a property value has changed
        /// </summary>
        /// <param name="propertyName">The property name</param>
        /// .net 4.5 [CallerMemberName]
        protected virtual void RaisePropertyChanged(string propertyName = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        /// <summary>
        /// Raises the property changed with undo.
        /// </summary>
        /// <param name="oldValue">The old value.</param>
        /// <param name="newValue">The new value.</param>
        /// <param name="description">The description.</param>
        /// <param name="propertyName">Name of the property.</param>
        protected virtual void RaisePropertyChangedWithValues(object oldValue, object newValue, string description, string propertyName = "")
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedExtendedEventArgs(propertyName, oldValue, newValue, description));
            }
        }

    }
}
