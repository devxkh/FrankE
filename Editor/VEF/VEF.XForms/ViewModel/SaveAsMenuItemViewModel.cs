using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using VEF.Interfaces;
using VEF.Interfaces.Base;
using VEF.Interfaces.Controls;
using VEF.Interfaces.Events;

namespace VEF.ViewModel
{
    /// <summary>
    /// Class SaveAsMenuItemViewModel - simple menu implementation with events
    /// </summary>
    public sealed class SaveAsMenuItemViewModel : AbstractMenuItem
    {
        #region CTOR

        /// <summary>
        /// Initializes a new instance of the <see cref="MenuItemViewModel"/> class.
        /// </summary>
        /// <param name="header">The header.</param>
        /// <param name="priority">The priority.</param>
        /// <param name="icon">The icon.</param>
        /// <param name="command">The command.</param>
        /// <param name="gesture">The gesture.</param>
        /// <param name="isCheckable">if set to <c>true</c> this menu acts as a checkable menu.</param>
        /// <param name="hideDisabled">if set to <c>true</c> this menu is not visible when disabled.</param>
        /// <param name="container">The container.</param>
        public SaveAsMenuItemViewModel(string header, int priority, IImageSource icon = null, ICommand command = null,
                                 IKeyGesture gesture = null, bool isCheckable = false, bool hideDisabled = false)
            : base(header, priority, icon, command, gesture, isCheckable, hideDisabled)
        {
                VEFModule.EventAggregator.GetEvent<ActiveContentChangedEvent>().Subscribe(SaveAs);
        }

        #endregion

        private void SaveAs(ContentViewModel cvm)
        {
            if (cvm != null)
            {
                this.Header = "Save " + cvm.Title + " As...";
            }
            else
            { this.Header = "Save As..."; }
        }
    }
}
