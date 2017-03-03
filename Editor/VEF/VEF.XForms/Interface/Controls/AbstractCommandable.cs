using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using VEF.Interfaces.Base;
using VEF.Model.Services;

namespace VEF.Interfaces.Controls
{
    /// <summary>
    /// Class AbstractCommandable
    /// </summary>
    public class AbstractCommandable : AbstractPrioritizedTree<AbstractCommandable>, ICommandable
    {
        #region CTOR

        /// <summary>
        /// Initializes a new instance of the <see cref="AbstractCommandable"/> class.
        /// </summary>
        protected AbstractCommandable()
            : base()
        {
        }

        #endregion

        #region ICommandable

        /// <summary>
        /// Gets the command.
        /// </summary>
        /// <value>The command.</value>
        public virtual ICommand Command { get; protected internal set; }

        /// <summary>
        /// Gets or sets the command parameter.
        /// </summary>
        /// <value>The command parameter.</value>
        public virtual object CommandParameter { get; set; }

        /// <summary>
        /// Gets the input gesture text.
        /// </summary>
        /// <value>The input gesture text.</value>
        public string InputGestureText { get; internal set; }

        #endregion
    }
}
