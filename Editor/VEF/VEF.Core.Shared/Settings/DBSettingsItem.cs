using System;
using System.Collections.Generic;
using System.Text;
using VEF.Model.Settings;

namespace VEF.Core.Settings
{
    public class DBSettingsItem : AbstractSettingsItem
    {
        public DBSettingsItem(string title, int priority, AbstractSettings settings)
            : base(title, settings)
        {
            this.Priority = priority;
        }
    }
}
