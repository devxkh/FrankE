using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using VEF.Interfaces.Controls;
using VEF.Model.Services;

namespace VEF.Interfaces.Base
{
    /// <summary>
    /// Interface ICommandable
    /// </summary>
    internal interface ICommandable
    {
        /// <summary>
        /// Gets the command.
        /// </summary>
        /// <value>The command.</value>
        ICommand Command { get; }

        /// <summary>
        /// Gets the command parameter.
        /// </summary>
        /// <value>The command parameter.</value>
        object CommandParameter { get; }

        /// <summary>
        /// Gets the input gesture text.
        /// </summary>
        /// <value>The input gesture text.</value>
        string InputGestureText { get; }
    }
}
