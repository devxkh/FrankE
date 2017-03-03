using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Practices.Unity;

namespace VEF.DAL.Interface
{
    /// <summary>
    /// Database Type
    /// </summary>
    public enum DBType
    {
        /// <summary>
        /// unknown database type
        /// </summary>
        Unknown,
        /// <summary>
        /// sqlite database
        /// </summary>
        SQLite,
        /// <summary>
        /// oracle database
        /// </summary>
        Oracle,
        /// <summary>
        /// microsoft sql server database
        /// </summary>
        MSSQL,
        /// <summary>
        /// mysql database
        /// </summary>
        Mysql
    };


    public class IDAL_DCTX
    {
        public object Context { get; set; }
    }

    /// <summary>
    /// Database item
    /// </summary>
    public interface IDB
    {
        /// <summary>
        /// Database identifier
        /// </summary>
        Guid Guid { get; set; }

        /// <summary>
        /// Database options 
        /// </summary>
        IDALOptions DBOptions { get; set; }

        /// <summary>
        /// creates a datacontext
        /// </summary>
        /// <returns></returns>
        IDAL_DCTX GetDataContext();

        IDAL_DCTX GetDataContextOpt(Boolean checkUser = true);


        void ShowLoginDialog();

        ///// <summary>
        ///// Open database context
        ///// </summary>
        //void OpenContext();

        ///// <summary>
        ///// close database context
        ///// </summary>
        //void CloseContext();
    }
}
