using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Interfaces.Services;

namespace VEX.Core.Interfaces.Services
{
    /// <summary>
    /// Interface IToolbarService - the application's toolbar tray is returned by this service
    /// </summary>
    public interface IFileWatcherService
    {
        /// <summary>
        /// Called to set the current theme from the list of themes
        /// </summary>
        /// <param name="name">The name of the theme</param>
        /// <returns><c>true</c> if successful, <c>false</c> otherwise</returns>
        //  bool SetCurrent(IItem item);

        /// <summary>
        /// Returns the current item set in the project/file manager
        /// </summary>
        /// <value>The current item.</value>
        //IItem CurrentItem { get; set; }
    }
}
