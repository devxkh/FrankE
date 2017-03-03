using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEF.Module.DB
{
    /// <summary>
    /// used as static ressource in XAML
//  <Application.Resources>
//    <local:LocalizedStrings xmlns:local="clr-namespace:WPLocalization" x:Key="LocalizedStrings" />
//</Application.Resources>
// Text="{Binding Path=AppResources.Title, Source={StaticResource LocalizedStrings}}"
    /// </summary>
    class LocalizedStrings
    {
        public LocalizedStrings()
        {
        }

        private static ModuleResources localizedResources = new ModuleResources();

        public ModuleResources ModuleResources
        {
            get { return localizedResources; }
        }
    }
}
