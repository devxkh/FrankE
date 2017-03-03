using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.ComponentModel;

namespace VEF.Interfaces.Settings
{
    public abstract class AbstractSettings : IDataErrorInfo //: ApplicationSettingsBase, IDataErrorInfo
    {
        #region Member

        protected Dictionary<string, object> Backup;

        #endregion

        #region CTOR

        protected AbstractSettings()
        {
            Backup = new Dictionary<string, object>();
        }

        #endregion

        #region Methods

        //protected virtual void UpdateBackup(string propertyName = "")
        //{
        //    if (propertyName == null || string.IsNullOrEmpty(propertyName) == true)
        //    {
        //        throw new ArgumentException("Error handling null property for object");
        //    }

        //    if (Backup.ContainsKey(propertyName))
        //        Backup.Remove(propertyName);
        //    Backup.Add(propertyName, this[propertyName]);
        //}

        ////.Net 4.5 [CallerMemberName]
        //protected virtual void ApplyDefault(string propertyName = "")
        //{
        //    if (propertyName == null || string.IsNullOrEmpty(propertyName) == true)
        //    {
        //        throw new ArgumentException("Error handling null property for object");
        //    }

        //    PropertyInfo prop = this.GetType().GetProperty(propertyName);
        //    if (prop.GetCustomAttributes(true).Length > 0)
        //    {
        //        object[] defaultValueAttribute = prop.GetCustomAttributes(typeof(DefaultValueAttribute), true);
        //        if (defaultValueAttribute != null)
        //        {
        //            DefaultValueAttribute defaultValue = defaultValueAttribute[0] as DefaultValueAttribute;
        //            if (defaultValue != null)
        //            {
        //                prop.SetValue(this, defaultValue.Value, null);
        //            }
        //        }
        //    }
        //}

        #endregion

        #region IDataErrorInfo

        [Display(Description = "Error", Name = "Error", GroupName = "Error", AutoGenerateField = false)]
        public virtual string Error
        {
            get { return null; }
        }

        string IDataErrorInfo.this[string columnName]
        {
            get { return null; }
        }

        #endregion
    }
}
