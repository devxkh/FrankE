using VEF.Module.DB;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEF.Shared.DB.MSSQL
{
    public class MSSQL_DBConnection : DBConnection
    {

        /// <summary>
        /// creates/tests and returns a valid database connection String
        /// </summary>
        /// <param name="dbInformation">database information</param>
        /// <returns>connectionstring</returns>
        public static string GetConnection(DBInformation dbInformation, DBType dbType = DBType.MSSQL)
        {
            // Initialize the EntityConnectionStringBuilder.
            //    EntityConnectionStringBuilder entityBuilder = new EntityConnectionStringBuilder(); 
            

            // Specify the provider name, server and database.
            string providerName = "System.Data.SqlClient";

            // Initialize the connection string builder for the
            // underlying provider.
            SqlConnectionStringBuilder sqlBuilder = new SqlConnectionStringBuilder();

            // Set the properties for the data source.
            sqlBuilder.DataSource = dbInformation.Host;

            //Achtung! Hier wird _Zentral hinter den Datenbankname angehängt!!
            sqlBuilder.InitialCatalog = dbInformation.DatabaseName;// + (pDBServer == DBS.Zentral ? "_" + pDBServer.ToString() : "");

            sqlBuilder.IntegratedSecurity = dbInformation.WinAuthent;
            if (!dbInformation.WinAuthent)
            {
                sqlBuilder.Password = dbInformation.Password;
                sqlBuilder.UserID = dbInformation.Username;
            }

            sqlBuilder.MultipleActiveResultSets = true; // für Replikation!

            sqlBuilder.Enlist = dbInformation.Enlist; //wegen transactionscope!

            sqlBuilder.MultipleActiveResultSets = true; // für Replikation!


            // Build the SqlConnection connection string.
            string providerString = sqlBuilder.ToString();

            //Set the provider name.
            //entityBuilder.Provider = providerName;

            //// Set the provider-specific connection string.
            //entityBuilder.ProviderConnectionString = providerString;

            ////metadata=res://*/DB.MDB_PAD.csdl|res://*/DB.MDB_PAD.ssdl|res://*/DB.MDB_PAD.msl;

            //// Set the Metadata location.
            //switch (pDBConData.DB)
            //{
            //    //  case DB.PAD:
            //    //metadata=                res://*/DB.MDB_PNDS.csdl|res://*/DB.MDB_PNDS.ssdl|res://*/DB.MDB_PNDS.msl;provider=System.Data.SqlClient;provider connection string=&quot;Data Source=SOFTDEV03\SQLEXPRESS2008;Initial Catalog=PNDS;Integrated Security=True;MultipleActiveResultSets=True&quot;
            //    //       entityBuilder.Metadata = @"res://*/DB." + pDBServer.ToString() + ".MDB_PAD_" + pDBServer.ToString() + ".csdl|res://*/DB." + pDBServer.ToString() + ".MDB_PAD_" + pDBServer.ToString() + ".ssdl|res://*/DB." + pDBServer.ToString() + ".MDB_PAD_" + pDBServer.ToString() + ".msl";
            //    //      break;
            //    //metadata=                res://*/DB.Lokal.MDB_PAD_Lokal.csdl|res://*/DB.Lokal.MDB_PAD_Lokal.ssdl|res://*/DB.Lokal.MDB_PAD_Lokal.msl;
            //    case DB.PNDS:
            //        entityBuilder.Metadata = @"res://*/DB." + pDBConData.DBServer.ToString() + ".MDB_PNDS_" + pDBConData.DBServer.ToString() + pDBConData.Suffix + ".csdl|res://*/DB." + pDBConData.DBServer.ToString() + ".MDB_PNDS_" + pDBConData.DBServer.ToString() + pDBConData.Suffix + ".ssdl|res://*/DB." + pDBConData.DBServer.ToString() + ".MDB_PNDS_" + pDBConData.DBServer.ToString() + pDBConData.Suffix + ".msl";
            //        break;
            //    //case DB.PPM:
            //    //    entityBuilder.Metadata = @"res://*/DB." + pDBConData.DBServer.ToString() + ".MDB_" + DB.PPM + "_" + pDBConData.DBServer.ToString() + pDBConData.Suffix + ".csdl|res://*/DB." + pDBConData.DBServer.ToString() + ".MDB_" + DB.PPM + "_" + pDBConData.DBServer.ToString() + pDBConData.Suffix + ".ssdl|res://*/DB." + pDBConData.DBServer.ToString() + ".MDB_" + DB.PPM + "_" + pDBConData.DBServer.ToString() + pDBConData.Suffix + ".msl";
            //    //    break;
            //    case DB.ZAP:
            //        entityBuilder.Metadata = @"res://*/DB." + pDBConData.DBServer.ToString() + ".MDB_ZAP_" + pDBConData.DBServer.ToString() + pDBConData.Suffix + ".csdl|res://*/DB." + pDBConData.DBServer.ToString() + ".MDB_ZAP_" + pDBConData.DBServer.ToString() + pDBConData.Suffix + ".ssdl|res://*/DB." + pDBConData.DBServer.ToString() + ".MDB_ZAP_" + pDBConData.DBServer.ToString() + pDBConData.Suffix + ".msl";
            //        break;
            //}

            //metadata=res://*/DB.Zentral.MDM_PNDS_Zentral.csdl|res://*/DB.Zentral.MDM_PNDS_Zentral.ssdl|res://*/DB.Zentral.MDM_PNDS_Zentral.msl;provider=System.Data.SqlClient;provider connection string="Data Source=TEST;Initial Catalog=PNDS;Persist Security Info=True;User ID=pecusoft;Password=sesam1997oeffne;MultipleActiveResultSets=True;Application Name=EntityFramework"
            // Debug.WriteLine(entityBuilder.ToString());
            //  String test = entityBuilder.ToString();

            //      String test2 = "metadata=res://*/DB.MDB_PAD.csdl|res://*/DB.MDB_PAD.ssdl|res://*/DB.MDB_PAD.msl;provider=System.Data.SqlClient;provider connection string=\"Data Source=SOFTDEV03\\SQLEXPRESS2008;Initial Catalog=PAD;Integrated Security=True;MultipleActiveResultSets=True\"";

            using (SqlConnection conn = new SqlConnection(providerString))
            {
                conn.Open();
                //   Debug.WriteLine("Just testing the connection.");
                conn.Close();

                //    CPManager.Instance.DBZ_ERR = DBZ_ERR.OK;
                //   CPManager.Instance.VMMain.DBZERR = false;

            }
            return providerString;
        }
    }
}
