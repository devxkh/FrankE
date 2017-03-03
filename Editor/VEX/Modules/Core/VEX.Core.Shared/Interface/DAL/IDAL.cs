#region License

//The MIT License (MIT)

//Copyright (c) 2014 Konrad Huber

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#endregion

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Data;
using System.Windows;
using Microsoft.Practices.Unity;
using VEX.IDAL.MDB;
using VEF.Interfaces.Services;
using VEF.Core.Interface.Service;
using VEF.DAL.Interface;
using VEF.Interfaces;
using VEX.Core.Shared.MDB;
using VEF;
using Microsoft.Data.Entity;
using Microsoft.Data.Sqlite;

namespace VEX.Core.Shared.MDB
{
    public partial class dbDataEntities
    {
        public UInt16 CTXID { get; set; }

        private string _connectionString;

        public dbDataEntities(string xconnection)
           // : base(xconnection)
        {
            _connectionString = xconnection;
        }

        // This method connects the context with the database - EF 7
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            var connectionStringBuilder = new SqliteConnectionStringBuilder { DataSource = _connectionString }; // "F:\\Projekte\\coop\\XGame\\data\\dbData.s3db" };
            var connectionString = connectionStringBuilder.ToString();
            var connection = new SqliteConnection(connectionString);

            optionsBuilder.UseSqlite(connection);
        }
    }
}

namespace VEX.IDAL { 


    public class IDAL: IDB
    {
     //   dbDataEntities mCtx;
        ILoggerService m_loggerService;
        public IDALOptions DBOptions { get; set; }
        public Guid Guid { get; set; }


        public IDAL()
        {
            //    mCtx = new dbDataEntities();

            m_loggerService = VEFModule.UnityContainer.Resolve(typeof(ILoggerService), "") as ILoggerService;
            
        //    m(ctx.Context as dbDataEntities).Database.Connection.StateChange += new StateChangeEventHandler(StateChange);
        }

        public async void ShowLoginDialog()
        {
        //    var workspace = container.Resolve<AbstractWorkspace>();
        //    var managerDB = container.Resolve<IDatabaseService>();
        //    var logger = container.Resolve<ILoggerService>();

        //    bool loginOK = false;
        //    string message = "zum einloggen Benutzername und Passwort angeben";

        //    //solange abfragen bis korrekter Login
        //    while (!loginOK)
        //    {
        //        //Login
        //        //MahApps.Metro.Controls.Dialogs.LoginDialogData result = await workspace.LoginDialog("Login", message);
        //        //if (result == null)
        //        //{
        //        //    //user canceled
        //        //    //##    Application.Current.Shutdown();
        //        //}
        //        //else
        //        //{
        //        //    var databaseService = container.Resolve<IDatabaseService>();
        //        //    User user = new User();

        //        //    loginOK = ((IDAL)databaseService.CurrentDB).Login(result.Username, result.Password, ref user);
        //        //    if (loginOK)
        //        //    {
        //        //        workspace.NotificationRequest.Raise(
        //        //                 new Notification { Content = String.Format("eingeloggt als: {0}", result.Username), Title = "Login erfolgreich" });

        //        //        databaseService.LoggedUser.UserID = user.UserID;
        //        //        databaseService.LoggedUser.UserGruppe = user.UserGruppe;
        //        //        databaseService.LoggedUser.LoggedIn = true;
        //        //        databaseService.LoggedUser.Data = user.Data;
        //        //        databaseService.LoggedUser.Status = LogStatus.LoggedIn;
        //        //    }
        //        //    else
        //        //    {
        //        //        message = "Logindaten ungültig!";
        //        //    }
        //        //    //else
        //        //    //{
        //        //    //    workspace.NotificationRequest.Raise(new Notification { Content = "Logindaten falsch", Title = "Login fehlgeschlagen" });
        //        //    //}
        //        //}
        //    }
        }

        public IDAL_DCTX GetDataContext()
        {
            return GetDataContextOpt();
        }

        public IDAL_DCTX GetDataContextOpt(Boolean checkUser = true)
        {
            IDAL_DCTX ctx = new IDAL_DCTX();
           
            try
            {
                 var _databaseService = VEFModule.UnityContainer.Resolve(typeof(IDatabaseService), "") as IDatabaseService;

                ////if (m_DBFound)
                ////{

                ////}
                ////else
                ////    ShowDBSetting(m_Container);

                //   PS_COMID_DataContext crmDataContext = new PS_COMID_DataContext();

                IDALOptions options = _databaseService.CurrentDB.DBOptions;
                if (options.DBType == DBType.MSSQL)
                {
                    //  

                    //string connectionString = "metadata=res://*/MDB.MDB_PNDS.csdl|res://*/MDB.MDB_PNDS.ssdl|res://*/MDB.MDB_PNDS.msl;Server = " + options.Host + "; Database = PNDS; User Id = " + options.User + ";Password = " + options.Password;
                    // string connectionString = "metadata=res://*/MDB.MDB_PNDS.csdl|res://*/MDB.MDB_PNDS.ssdl|res://*/MDB.MDB_PNDS.msl;provider=System.Data.SqlClient;provider connection string=\"data source=AP-HAAG\\SQLEX2008R203;initial catalog=PNDS;user id=PecuSoft;password=sesam1997oeffne;MultipleActiveResultSets=True;App=EntityFramework\"";
                    string connectionString = "metadata=res://*/MDB.MDB_PNDS.csdl|res://*/MDB.MDB_PNDS.ssdl|res://*/MDB.MDB_PNDS.msl;provider=System.Data.SqlClient;provider connection string=\"data source=" + options.Host + ";initial catalog=PNDS;user id=" + options.User + ";password=" + options.Password + ";MultipleActiveResultSets=True;App=EntityFramework\"";

                    //string connectionString = "User Id=" + options.User + ";Password=" + options.Password + ";Server=" + options.Host + ";Direct=True;Sid=" + options.ServiceName + ";Persist Security Info=True";
                    //   string providerPrefix = "";
                    //if (!ConnectionDialog.Show(out connectionString, out providerPrefix))
                    //{
                    //    stripLabel.Text = "Incorrect connection string";
                    //    return;
                    //}

                    //Frame activating
                    //  Stream contextStream = Assembly.GetExecutingAssembly().GetManifestResourceStream(String.Format("ComID.IDAL.MDB.CrmDataMapping{0}.lqml", providerPrefix));
                    //   Devart.Data.Linq.Mapping.MappingSource mappingSource = Devart.Data.Linq.Mapping.XmlMappingSource.FromStream(contextStream);

                    //PNDSEntities crmDataContext = new PNDSEntities(m_Container, connectionString);//, mappingSource);

                    //crmDataContext.CTXID = _databaseService.GetNextCtxID();

                    ////    crmDataContext.Connection.StateChange += new System.Data.StateChangeEventHandler(Connection_StateChange);

                    //crmDataContext.Database.Connection.Open();
                    ////    foreach (ListViewItem lvItem in lvFrames.Items)
                    ////        ((BaseControl)lvItem.Tag).OpenClick();

                    //if (checkUser && _databaseService.LoggedUser.UserID < 1)
                    //{
                    //    ShowLoginDialog(m_Container);
                    //    return null;
                    //}

                    //return crmDataContext;
                }
                else if(options.DBType == DBType.SQLite)
                {

                    //System.Data.SQLite.SQLiteConnection.CreateFile("databaseFile.db3");        // Create the file which will be hosting our database
                    //using (System.Data.SQLite.SQLiteConnection con = new System.Data.SQLite.SQLiteConnection("data source=\"F:\\Projekte\\coop\\XGame\\data\\dbData.s3db\""))
                    //{
                    //    using (System.Data.SQLite.SQLiteCommand com = new System.Data.SQLite.SQLiteCommand(con))
                    //    {
                    //        con.Open();                             // Open the connection to the database

                    //        //com.CommandText = createTableQuery;     // Set CommandText to our query that will create the table
                    //        //com.ExecuteNonQuery();                  // Execute the query

                    //        //com.CommandText = "INSERT INTO MyTable (Key,Value) Values ('key one','value one')";     // Add the first entry into our database 
                    //        //com.ExecuteNonQuery();      // Execute the query
                    //        //com.CommandText = "INSERT INTO MyTable (Key,Value) Values ('key two','value value')";   // Add another entry into our database 
                    //        //com.ExecuteNonQuery();      // Execute the query

                    //        //com.CommandText = "Select * FROM MyTable";      // Select all rows from our database table

                    //        //using (System.Data.SQLite.SQLiteDataReader reader = com.ExecuteReader())
                    //        //{
                    //        //    while (reader.Read())
                    //        //    {
                    //        //        Console.WriteLine(reader["Key"] + " : " + reader["Value"]);     // Display the value of the key and value column for every row
                    //        //    }
                    //        //}
                    //        con.Close();        // Close the connection to the database
                    //    }
                    //}

                    //todo per settings!
                    //       string connectionString = "metadata=res://*/MDB.EDM_DBData.csdl|res://*/MDB.EDM_DBData.ssdl|res://*/MDB.EDM_DBData.msl;provider=System.Data.SQLite.EF6;provider connection string=\"data source=F:\\Projekte\\coop\\XGame\\data\\dbData.s3db\"";
                 
                    //   string connectionString = "data source=F:\\Projekte\\coop\\XGame\\data\\dbData.s3db";
                    string connectionString = _databaseService.CurrentDB.DBOptions.Host;
                    //  string connectionString = "metadata=res://*/MDB.EDM_DBData.csdl|res://*/MDB.EDM_DBData.ssdl|res://*/MDB.EDM_DBData.msl;provider=System.Data.SQLite.EF6;provider connection string=\"data source=" + options.Host + "\""; //D:\\Projekte\\coop\\VEX\\Test\\dbData.s3db\"";

                    //  string connectionString = "metadata=res://*/MDB.MDB_PNDS.csdl|res://*/MDB.MDB_PNDS.ssdl|res://*/MDB.MDB_PNDS.msl;provider=System.Data.SqlClient;provider connection string=\"data source=" + options.Host + ";initial catalog=PNDS;user id=" + options.User + ";password=" + options.Password + ";MultipleActiveResultSets=True;App=EntityFramework\"";
                    dbDataEntities crmDataContext = new dbDataEntities(connectionString);//, mappingSource);

                    crmDataContext.CTXID = _databaseService.GetNextCtxID();

                    //    crmDataContext.Connection.StateChange += new System.Data.StateChangeEventHandler(Connection_StateChange);

                 //-------------   crmDataContext..Database..Connection.Open();
                    //    foreach (ListViewItem lvItem in lvFrames.Items)
                    //        ((BaseControl)lvItem.Tag).OpenClick();

                    if (checkUser && _databaseService.LoggedUser.UserID < 1)
                    {
                        ShowLoginDialog();
                        return null;
                    }
                    ctx.Context = crmDataContext;

                    return ctx;
                }
                else if (options.DBType == DBType.Oracle)
                {
                    //string connectionString = "User Id=" + options.User + ";Password=" + options.Password + ";Server=" + options.Host + ";Direct=True;Sid=" + options.ServiceName + ";Persist Security Info=True";
                    ////   string providerPrefix = "";
                    ////if (!ConnectionDialog.Show(out connectionString, out providerPrefix))
                    ////{
                    ////    stripLabel.Text = "Incorrect connection string";
                    ////    return;
                    ////}

                    ////Frame activating
                    ////  Stream contextStream = Assembly.GetExecutingAssembly().GetManifestResourceStream(String.Format("ComID.IDAL.MDB.CrmDataMapping{0}.lqml", providerPrefix));
                    ////   Devart.Data.Linq.Mapping.MappingSource mappingSource = Devart.Data.Linq.Mapping.XmlMappingSource.FromStream(contextStream);

                    //PNDSEntities crmDataContext = new PNDSEntities(m_Container, connectionString);//, mappingSource);

                    //crmDataContext.CTXID = _databaseService.GetNextCtxID();

                    ////    crmDataContext.Connection.StateChange += new System.Data.StateChangeEventHandler(Connection_StateChange);

                    //crmDataContext.Database.Connection.Open();
                    ////    foreach (ListViewItem lvItem in lvFrames.Items)
                    ////        ((BaseControl)lvItem.Tag).OpenClick();

                    //if (checkUser && _databaseService.LoggedUser.UserID < 1)
                    //{
                    //    ShowLoginDialog(m_Container);
                    //    return null;
                    //}

                    //return crmDataContext;
                }
            }
            catch (Exception ex)
            {
                var loggerService = VEFModule.UnityContainer.Resolve(typeof(ILoggerService), "") as ILoggerService; 
                loggerService.Log("Datenbankverbindung fehlgeschlagen." + (ex.InnerException != null ? ex.InnerException.Message : ex.Message), LogCategory.Exception, LogPriority.High);
                //       
              //  workspace.NotificationRequest.Raise(new Notification { Content = "Datenbankverbindung fehlgeschlagen." + (ex.InnerException != null ? ex.InnerException.Message : ex.Message), Title = "Fehler" });

                //  stripLabel.Text = ex.Message;

            }
            return ctx;
        }

        //public void Dispose()
        //{
        //    //if (mCtx != null)
        //    //{
        //    //    //  Transaction.Dispose();
        //    //    // Transaction = null;
        //    //    m(ctx.Context as dbDataEntities).Dispose();
        //    //    mCtx = null;
        //    //}
        //}

        void StateChange(object sender, StateChangeEventArgs e)
        {
           //if(m(ctx.Context as dbDataEntities).Database.Connection.State == ConnectionState.Broken
           //    || m(ctx.Context as dbDataEntities).Database.Connection.State == ConnectionState.Closed)
           //{
           //    //reconnect
           //}
        }

        //public IEnumerable<PNDS_AUT_PARA> GetAll_PNDS_AUT_PARA(PNDSEntities dc)
        //{
        //    List<String> geraete = new List<String>()
        //                        { "K", //AKI
        //                            "T" //PATX
        //                        };

        //    var found = from d in dc.PNDS_AUT_PARA
        //                where geraete.Contains(d.Geraeteart)
        //                orderby d.Automatennr ascending
        //                select d;
        //    if (found.Any())
        //    {
        //        return found;
        //    }

        //    return null;
        //}

        #region EntityChar


        #endregion

        #region Physics

        public static bool insertEntity(IDAL_DCTX ctx, Entity po)
        {
            try
            {

                var result = (ctx.Context as dbDataEntities).Entity.Where(x => x.EntID == po.EntID);
                if (result.Any())
                {
                    result.First().Data = po.Data;
                }
                else
                {
                    (ctx.Context as dbDataEntities).Entity.Add(po);
                }

                (ctx.Context as dbDataEntities).SaveChanges();

          //      MessageBox.Show("Entity (" + po.EntID + ") saved to DB");
          

                return true;

            }catch(Exception ex)
            {
              MessageBox.Show(ex.InnerException != null ? ex.InnerException.Message : ex.Message);
          
            }

            return false;
        }

        public static bool insertEntityData(IDAL_DCTX ctx, EntityData entityData)
        {
            try
            {
                var result = (ctx.Context as dbDataEntities).EntityData.Where(x => x.EntDID == entityData.EntDID);
                if (result.Any())
                {
                    result.First().Data = entityData.Data;
                }
                else
                {
                    (ctx.Context as dbDataEntities).EntityData.Add(entityData);
                }

                (ctx.Context as dbDataEntities).SaveChanges();
                return true;

            }
            catch (Exception ex)
            {

            }

            return false;
        }

        public static bool TruncateDatabase(IDAL_DCTX ctx)
        {
            try
            {
                (ctx.Context as dbDataEntities).Database.ExecuteSqlCommand("DELETE FROM [SceneNode]; VACUUM;");
                (ctx.Context as dbDataEntities).Database.ExecuteSqlCommand("DELETE FROM [Entity]; VACUUM;");
                (ctx.Context as dbDataEntities).Database.ExecuteSqlCommand("DELETE FROM [EntityData];  VACUUM;");
                (ctx.Context as dbDataEntities).Database.ExecuteSqlCommand("DELETE FROM [State];VACUUM;");
                (ctx.Context as dbDataEntities).Database.ExecuteSqlCommand("DELETE FROM [UI];VACUUM;");
                (ctx.Context as dbDataEntities).Database.ExecuteSqlCommand("DELETE FROM [Scene]; VACUUM;");
    //    (ctx.Context as dbDataEntities).Database.ExecuteSqlCommand("DELETE FROM \"sqlite_sequence\"; VACUUM;");

            }
            catch (Exception ex)
            {

            }

            return false;
        }

        public static bool deleteEntity(IDAL_DCTX ctx, Entity po)
        {
            try
            {
                var result = (ctx.Context as dbDataEntities).Entity.Where(x => x.EntID == po.EntID);
                if (result.Any())
                {
                    (ctx.Context as dbDataEntities).Entity.Remove(result.First());
                    (ctx.Context as dbDataEntities).SaveChanges();
                    return true;
                }
            }
            catch (Exception ex)
            {

            }

            return false;
        }

        public static IEnumerable<EntityData> selectAllEntityData(IDAL_DCTX ctx)
        {
            try
            {
                var result = (ctx.Context as dbDataEntities).EntityData;
                if (result.Any())
                    return result;
                else
                    return null;
            }
             catch(Exception ex)
            {
           //     MessageBox.Show("dreck_" + id + "_!!!!");
            }

            return null;
        }

        public class EntityContainer
        {
            public EntityData EntityData { get; set; }
            public Entity Entity { get; set; }
        }

        public static IEnumerable<EntityContainer> selectAllEntities(IDAL_DCTX ctx)
        {
            try
            {
                var result = from n in (ctx.Context as dbDataEntities).Entity

                             join oj in (ctx.Context as dbDataEntities).EntityData on n.EntDID equals oj.EntDID into gjo
                             from Ent in gjo.DefaultIfEmpty()

                             //where n.SceneID == sceneID
                             //select

                          //   where n.SceneID == sceneID
                             select new EntityContainer { Entity = n, EntityData = Ent };

                if (result.Any())
                    return result;
                else
                    return null;
            }
             catch(Exception ex)
            {
                MessageBox.Show("selectAllEntities. " + ex.Message);
            }

            return null;
        }

        public static Entity selectEntity(IDAL_DCTX ctx, int id)
        {
            try
            {
                var result = (ctx.Context as dbDataEntities).Entity.Where(x => x.EntID == id);
                if (result.Any())
                    return result.First();
                else
                    return new Entity();
            }
             catch(Exception ex)
            {
           //     MessageBox.Show("dreck_" + id + "_!!!!");
            }

            return new Entity();
        }

        public static EntityData selectEntityData(IDAL_DCTX ctx, int id)
        {
            try
            {
                var result = (ctx.Context as dbDataEntities).EntityData.Where(x => x.EntDID == id);
                if (result.Any())
                    return result.First();
                else
                    return new EntityData();
            }
            catch (Exception ex)
            {
                //     MessageBox.Show("dreck_" + id + "_!!!!");
            }

            return new EntityData();
        }

        #endregion


        #region Scene

        public static bool insertScene(IDAL_DCTX ctx, VEX.IDAL.MDB.Scene scene)
        {
            try
            {
                var ctxtmp = (ctx.Context as dbDataEntities);
                var result = ctxtmp.Scene.Where(x => x.SceneID == scene.SceneID);
                if (result.Any())
                {
                    var dbScene = result.First();
                    dbScene.Name = scene.Name;
                    dbScene.Data = scene.Data;
                }
                else
                {
                    (ctx.Context as dbDataEntities).Scene.Add(scene);
                }

                (ctx.Context as dbDataEntities).SaveChanges();
                return true;

            }
            catch (Exception ex)
            {

            }

            return false;
        }

        public static bool DeleteScene(IDAL_DCTX ctx, Int32 id)
        {
            try
            {
                // Scene tmp = new Scene() { Data = data };
                (ctx.Context as dbDataEntities).Scene.Remove((ctx.Context as dbDataEntities).Scene.Where(x => x.SceneID == id).First());
                (ctx.Context as dbDataEntities).SaveChanges();
                // id = (int)tmp.SceneID;
                return true;
            }
            catch (Exception ex)
            {
              //  m_loggerService.Log("error IDAL.DeleteScene(id=" + id + ")" + (ex.InnerException != null ? ex.InnerException.Message : ex.Message), LogCategory.Exception, LogPriority.High);
                //     MessageBox.Show("dreck_" + id + "_!!!!");
            }
            return false;
        }

        //public class SceneContainer
        //{
        //    public Scene Scene { get; set; }
        //    public SceneNode Nodes { get; set; }
        //    public Entity Entity { get; set; }
        //}

        public class SceneNodeContainer
        {
            public SceneNode Node { get; set; }
            public Entity Entity { get; set; }
        }

        public static IEnumerable<SceneNodeContainer> selectSceneNodes(IDAL_DCTX ctx, int sceneID)
        {
            try
            {
                var result = from n in (ctx.Context as dbDataEntities).SceneNode

                             join oj in (ctx.Context as dbDataEntities).Entity on n.EntID equals oj.EntID into gjo
                             from Ent in gjo.DefaultIfEmpty()

                             //where n.SceneID == sceneID
                             //select

                             where n.SceneID == sceneID
                             select new SceneNodeContainer { Node = n, Entity = Ent };

                //  var result = m(ctx.Context as dbDataEntities).Scene.Where(x => x.SceneID == id);
                if (result.Any())
                {
                    return result;//.Data;
                }
            }
            catch (Exception ex)
            {
                //     MessageBox.Show("dreck_" + id + "_!!!!");
            }

            return null;
        }


        //public bool insertSceneNode(SceneNode sceneNode)
        //{
        //    m(ctx.Context as dbDataEntities).SceneNode.Add(sceneNode);
        //    m(ctx.Context as dbDataEntities).SaveChanges();
        //    return true;
        //}

        public static bool DeleteSceneNode(IDAL_DCTX ctx, Int32 id)
        {
            try
            {
                // Scene tmp = new Scene() { Data = data };
                (ctx.Context as dbDataEntities).SceneNode.Remove((ctx.Context as dbDataEntities).SceneNode.Where(x => x.NodeID == id).First());
                (ctx.Context as dbDataEntities).SaveChanges();
                // id = (int)tmp.SceneID;
                return true;
            }catch(Exception ex)
            {
                MessageBox.Show("error in DeleteSceneNode '" + id + "' " + ex.Message);
            }
            return false;
        }

        public static bool insertSceneNode(IDAL_DCTX ctx, SceneNode sceneNode)
        {
            try
            {
                var result = (ctx.Context as dbDataEntities).SceneNode.Where(x => x.NodeID == sceneNode.NodeID
                                                                                && x.SceneID == sceneNode.SceneID);
                if (result.Any())
                {
                    var scenNode = result.First();
                    scenNode.Data = sceneNode.Data;
                    scenNode.SceneID = sceneNode.SceneID;
                    scenNode.EntID = sceneNode.EntID;
                    scenNode.Name = sceneNode.Name;
                    (ctx.Context as dbDataEntities).SaveChanges();
                    return true;
                }
                else
                {
                    (ctx.Context as dbDataEntities).SceneNode.Add(sceneNode);
                    (ctx.Context as dbDataEntities).SaveChanges();
                    return true;
                }
            }catch(Exception ex)
            {

            }
            return false;
        }

        //public IEnumerable<SceneContainer> selectCompleteScene(int id)
        //{
        //    try
        //    {
        //        var result = from n in m(ctx.Context as dbDataEntities).Scene

        //                     join nj in m(ctx.Context as dbDataEntities).SceneNodes on n.SceneID equals nj.SceneID into gj
        //                     from node in gj.DefaultIfEmpty()

        //                     join oj in m(ctx.Context as dbDataEntities).Entity on node.EntID equals oj.EntID into gjo
        //                     from Ent in gjo.DefaultIfEmpty()

        //                     where n.SceneID == id
        //                     select new SceneContainer { Scene = n, Nodes = node, Entity = Ent };

        //        //  var result = m(ctx.Context as dbDataEntities).Scene.Where(x => x.SceneID == id);
        //        if (result.Any())
        //        {
        //            return result;//.Data;
        //        }
        //    }
        //    catch (Exception ex)
        //    {
        //        //     MessageBox.Show("dreck_" + id + "_!!!!");
        //    }

        //    return null;
        //}

        public static IEnumerable<VEX.IDAL.MDB.Scene> selectAllScenesDataOnly(IDAL_DCTX ctx)
        {
            try
            {
                var result = from n in (ctx.Context as dbDataEntities).Scene
                             select n;

                //  var result = m(ctx.Context as dbDataEntities).Scene.Where(x => x.SceneID == id);
                if (result.Any())
                    return result;//.Data;
                else
                    return null;
            }
            catch (Exception ex)
            {
                //     MessageBox.Show("dreck_" + id + "_!!!!");
            }

            return null;
        }

        public static VEX.IDAL.MDB.Scene selectSceneDataOnly(IDAL_DCTX ctx, int id)
        {
            try
            {
                var result = from n in (ctx.Context as dbDataEntities).Scene
                             where n.SceneID == id
                             select n;

                //  var result = m(ctx.Context as dbDataEntities).Scene.Where(x => x.SceneID == id);
                if (result.Any())
                    return result.First();//.Data;
                else
                    return new VEX.IDAL.MDB.Scene();
            }
            catch (Exception ex)
            {
                //     MessageBox.Show("dreck_" + id + "_!!!!");
            }

            return null;
        }

        #endregion
        //public void DownloadBlob(SQLiteConnection sqConnection)
        //{
        //    SQLiteCommand sqCommand = new SQLiteCommand("SELECT * FROM Pictures", sqConnection);
        //    sqConnection.Open();
        //    SQLiteDataReader myReader = sqCommand.ExecuteReader(System.Data.CommandBehavior.Default);
        //    try
        //    {
        //        while (myReader.Read())
        //        {
        //            SQLiteBlob myBlob = myReader.GetSQLiteBlob(myReader.GetOrdinal("Picture"));
        //            if (!myBlob.IsNull)
        //            {
        //                string FN = myReader.GetString(myReader.GetOrdinal("PicName"));
        //                FileStream fs = new FileStream("D:\\Tmp\\" + FN + ".bmp", FileMode.Create);
        //                BinaryWriter w = new BinaryWriter(fs);
        //                w.Write(myBlob.Value);
        //                w.Close();
        //                fs.Close();
        //                Console.WriteLine(FN + " downloaded.");
        //            }
        //        }
        //    }
        //    finally
        //    {
        //        myReader.Close();
        //        sqConnection.Close();
        //    }
        //}

        //public void UploadBlob(SQLiteConnection sqConnection)
        //{
        //    FileStream fs = new FileStream("D:\\Tmp\\_Water.bmp", FileMode.Open, FileAccess.Read);
        //    BinaryReader r = new BinaryReader(fs);
        //    SQLiteBlob myBlob = new SQLiteBlob(r.ReadBytes((int)fs.Length));
        //    SQLiteCommand sqCommand = new SQLiteCommand("INSERT INTO Pictures (ID, PicName, Picture) VALUES(1,'Water',:Pictures)", sqConnection);
        //    sqCommand.Parameters.Add("Pictures", myBlob);
        //    sqConnection.Open();
        //    try
        //    {
        //        Console.WriteLine(sqCommand.ExecuteNonQuery() + " rows affected.");
        //    }
        //    finally
        //    {
        //        sqConnection.Close();
        //        r.Close();
        //    }
        //} 
    }

}
