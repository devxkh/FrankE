using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Module.DB.Service;
using VEF.DAL.Interface;

namespace VEF.Core.Interface.Service
{
    /// <summary>
    /// Interface IToolbarService - the application's toolbar tray is returned by this service
    /// </summary>
    public interface IDatabaseService
    {
        System.Windows.Controls.ContextMenu ContextMenu { get; }

        /// <summary>
        /// The list of database options registered with the database manager
        /// </summary>
        /// <value>The themes.</value>
        ObservableCollection<IDALOptions> DBOptions { get; }

        /// <summary>
        /// The list of databases registered with the database manager
        /// </summary>
        /// <value>The themes.</value>
        ObservableCollection<IDB> DBs { get; }


        /// <summary>
        /// Adds a database to the database manager
        /// </summary>
        /// <param name="theme">The database to add</param>
        /// <returns><c>true</c> if successful, <c>false</c> otherwise</returns>
        bool AddDB(IDB item);

        /// <summary>
        /// Adds a databaseoption to the database manager
        /// </summary>
        /// <param name="theme">The database to add</param>
        /// <returns><c>true</c> if successful, <c>false</c> otherwise</returns>
        bool AddDBOption(IDALOptions item);


        /// <summary>
        /// Called to set the current databse from the list of databases
        /// </summary>
        /// <param name="name">The name of the theme</param>
        /// <returns><c>true</c> if successful, <c>false</c> otherwise</returns>
        bool SetCurrentDB(Guid guid);

        /// <summary>
        /// Returns the current database set in the database manager
        /// </summary>
        /// <value>The current item.</value>
        IDB CurrentDB { get; }

        /// <summary>
        /// get next context ID
        /// </summary>
        /// <returns>next free context ID</returns>
        UInt16 GetNextCtxID();

        /// <summary>
        /// Logged in User
        /// </summary>
        User LoggedUser { get; }

    }
}
