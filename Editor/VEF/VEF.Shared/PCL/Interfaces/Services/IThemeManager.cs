using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEF.Interfaces.Services
{
    /// <summary>
    /// Interface IThemeManager
    /// </summary>
    public interface IThemeManager
    {
        /// <summary>
        /// The list of themes registered with the theme manager
        /// </summary>
        /// <value>The themes.</value>
        ObservableCollection<ITheme> Themes { get; }

        /// <summary>
        /// Adds a theme to the theme manager
        /// </summary>
        /// <param name="theme">The theme to add</param>
        /// <returns><c>true</c> if successful, <c>false</c> otherwise</returns>
        bool AddTheme(ITheme theme);

        /// <summary>
        /// Called to set the current theme from the list of themes
        /// </summary>
        /// <param name="name">The name of the theme</param>
        /// <returns><c>true</c> if successful, <c>false</c> otherwise</returns>
        bool SetCurrent(string name);

        /// <summary>
        /// Returns the current theme set in the theme manager
        /// </summary>
        /// <value>The current theme.</value>
        ITheme CurrentTheme { get; }
    }
}
