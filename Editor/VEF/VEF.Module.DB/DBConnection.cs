using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using VEF.Module.DB;

namespace VEF.Module.DB
{
    public enum DBType
    {
        /// <summary>
        /// microsoft sql server
        /// </summary>
        MSSQL,
        /// <summary>
        /// sqlite datenbank
        /// </summary>
        SQLITE,
        /// <summary>
        /// oracle datenbank
        /// </summary>
        Oracle
    }

    /// <summary>
    /// database access information
    /// </summary>
    public class DBInformation
    {
        /// <summary>
        /// database host
        /// </summary>
        //todo   [Display(Description = ModuleResources.DBHostDesc, Name = ModuleResources.DBHost, GroupName = ModuleResources.DBGroup)]
        [Display(Description = "DBHostDesc", Name = "DBHost", GroupName = "DBGroup")]
        public string Host { get; set; }

        /// <summary>
        /// database username
        /// </summary>
        public string Username { get; set; }

        /// <summary>
        /// database password
        /// </summary>
        public string Password { get; set; }

        /// <summary>
        /// windows authentification = true, false = user login
        /// </summary>
        public bool WinAuthent { get; set; }

        /// <summary>
        /// metadata name for entity framework connection
        /// </summary>
        public string MetadataName { get; set; }

        /// <summary>
        /// database name
        /// </summary>
        public string DatabaseName { get; set; }

        /// <summary>
        ///  Ruft einen booleschen Wert ab oder legt einen fest, der angibt, ob der Verbindungspooler
        ///     in SQL Server die Verbindung automatisch in den aktuellen Transaktionskontext
        ///     des Erstellungsthreads einträgt.
        ///     Der Wert der System.Data.SqlClient.SqlConnectionStringBuilder.Enlist-Eigenschaft
        ///     bzw. true , wenn kein Wert angegeben wurde.
        /// </summary>
        public bool Enlist { get; set; }
    }

    /// <summary>
    /// database connection class
    /// </summary>
    public class DBConnection
    {
    

        /// <summary>
        /// creates/tests and returns a valid database connection String
        /// </summary>
        /// <param name="dbInformation">database information</param>
        /// <returns>connectionstring</returns>
        public static string GetConnection( DBInformation dbInformation, DBType dbType = DBType.MSSQL )
        {
            return "";
        }
    }
}
