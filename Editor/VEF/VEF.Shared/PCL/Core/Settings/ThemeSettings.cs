using Prism.Events;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Interfaces;
using VEF.Interfaces.Settings;

namespace VEF.Core.Settings
{
    internal class ThemeSettings : AbstractSettings, IThemeSettings
    {
        public ThemeSettings(IEventAggregator eventAggregator)
        {
          //  eventAggregator.GetEvent<ThemeChangeEvent>().Subscribe(NewSelectedTheme);
        }

        private void NewSelectedTheme(ITheme theme)
        {
            //this.SelectedTheme = theme.Name;
            //this.Save();
        }

        //[UserScopedSetting()]
        //[DefaultSettingValue("Light")]
        public string SelectedTheme
        {
            get { return ""; }
            //         get { return (string)this["SelectedTheme"]; }
            //         set { this["SelectedTheme"] = value; }
        }
    }
}
