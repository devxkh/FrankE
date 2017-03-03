using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace VEF.Interfaces.Services
{
    /// <summary>
    /// Interface ICommandManager
    /// </summary>
    public interface ICommandManager
    {
        /// <summary>
        /// Registers the command.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="command">The command.</param>
        /// <returns><c>true</c> if successfully added the command, <c>false</c> otherwise</returns>
        bool RegisterCommand(string name, ICommand command);

        /// <summary>
        /// Gets the command.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <returns>ICommand.</returns>
        ICommand GetCommand(string name);

        /// <summary>
        /// Refreshes this instance.
        /// </summary>
        void Refresh();
    }
}
