using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEF.Interfaces
{
    public interface IWorkspace
    {
        /// <summary>
        /// The list of documents which are open in the workspace
        /// </summary>
        ObservableCollection<ContentViewModel> Documents { get; set; }

        /// <summary>
        /// The list of tools that are available in the workspace
        /// </summary>
        ObservableCollection<ToolViewModel> Tools { get; set; }

        /// <summary>
        /// The current document which is active in the workspace
        /// </summary>
        ContentViewModel ActiveDocument { get; set; }

        /// <summary>
        /// Gets the title of the application.
        /// </summary>
        /// <value>The title.</value>
        string Title { get; }

        /// <summary>
        /// minimum width of the workspace
        /// </summary>
        UInt32 MinWidth { get; set; }

        /// <summary>
        /// minimum height of the workspace
        /// </summary>
        UInt32 MinHeight { get; set; }

        /// <summary>
        /// Gets the icon of the application.
        /// </summary>
        /// <value>The icon.</value>
        //ImageSource Icon { get; }

        //InteractionRequest<Confirmation> ConfirmationRequest { get; }
        //InteractionRequest<Notification> NotificationRequest { get; }
        //Task<ProgressDialogController> ProgressDialog(String title, string content);
        //Task<String> InputDialog(String title, string content);
        //Task<MessageDialogResult> MessageDialog(String title, string content, MessageDialogStyle msgDialogStyle, MetroDialogSettings dialogSettings);

        /// <summary>
        /// Closing this instance.
        /// </summary>
        /// <param name="e">The <see cref="CancelEventArgs"/> instance containing the event data.</param>
        /// <returns><c>true</c> if the application is closing, <c>false</c> otherwise</returns>
        bool Closing(CancelEventArgs e);
    }
}
