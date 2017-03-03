using Prism.Events;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Interfaces;
using VEF.Interfaces.Events;
using VEF.Interfaces.Settings;
using VEF.XForms.Interfaces.Settings;

namespace VEF.Model.Settings
{
    //public class ThemeSettings : IAbstractSettings, IThemeSettings
    //{
    //    //public ThemeSettings(IEventAggregator eventAggregator)
    //    //{
    //    //   VEFModule.EventAggregator.GetEvent<ThemeChangeEvent>().Subscribe(NewSelectedTheme);
    //    //}

    //    //private void NewSelectedTheme(ITheme theme)
    //    //{
    //    //    //this.SelectedTheme = theme.Name;
    //    //    //this.Save();
    //    //}

    //    ////[UserScopedSetting()]
    //    ////[DefaultSettingValue("Light")]
    //    //public string SelectedTheme
    //    //{
    //    //           get { return (string)this["SelectedTheme"]; }
    //    //             set { this["SelectedTheme"] = value; }
    //    //}
    //}
}
