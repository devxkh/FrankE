using FlatBuffers;
using NetMsg;
using PCL.XEditor;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using VEF;
using VEF.IDAL;
using VEF.Interfaces;
using VEF.Interfaces.Services;
using VEX.Core.Model;
using VEX.Core.Model.Project;
using VEX.Core.Model.Services;
using VEX.Core.ViewModel;
using VEX.Enet.Interface;
using VEX.Interface.Scene;
using VEX.Interface.Scene.Services;
using VEX.Model.Scene.Model;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using VEX.Service.Scene;

namespace VEX.Core.View.Tools
{
    /// <summary>
    /// Interaktionslogik für SocketServerToolView.xaml
    /// </summary>
    public partial class SocketServerToolView : UserControl, IContentView, INotifyPropertyChanged
    {
        SocketServerManager _SocketServerManager;

        public SocketServerToolView()
        {
            InitializeComponent();

            _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;

        }

        private void btnServerStop_Click(object sender, RoutedEventArgs e)
        {
            _SocketServerManager.Client.DisconnectFromServer();
        }


        // This will be called whenever the list changes.
        private void ServerEvent(object sender, SampleEventArgs e)
        {
            Console.WriteLine("-> ServerEvent incoming Message");

            // Verify the message contents are trustworthy.

            try
            {
                ByteBuffer byteBuffer = new ByteBuffer(e.Data);

                var message = NetMsg.MessageRoot.GetRootAsMessageRoot(byteBuffer); // read 

                Console.WriteLine("-> ServerEvent incoming Message.DataType:" + message.DataType);

                switch (message.DataType)
                {
                    case NetMsg.Data.ReturnStatus:

                        NetMsg.ReturnStatus status = new NetMsg.ReturnStatus();
                        status = message.GetData<NetMsg.ReturnStatus>(status);

                        switch (status.Status)
                        {
                            case NetMsg.MsgStatus.S_LoginSuccess:
                                _SocketServerManager.Client.HostInfo.isLoggedIn = true;
                                break;
                        }

                        break;
                    case NetMsg.Data.Chatmessage:
                        NetMsg.Chatmessage msg = new NetMsg.Chatmessage();
                        msg = message.GetData<NetMsg.Chatmessage>(msg);

                        Console.WriteLine("NetMsg.Data.Chatmessage:" + msg.Text);

                        break;

                    case NetMsg.Data.Scene:
                        XFBType.Scene scene = new XFBType.Scene();
                        scene = message.GetData<XFBType.Scene>(scene);

                        Console.WriteLine("NetMsg.Data.Scene:" + scene.Sceneid);

                        break;

                    case NetMsg.Data.Entity:

                        Entity ent = new Entity();
                        ent = message.GetData<Entity>(ent);
                       

                        Application.Current.Dispatcher.BeginInvoke(
                                DispatcherPriority.Normal,
                                new Action(() =>
                                {
                                    var model = this.DataContext as SocketServerToolModel;

                                    var entityExists = model.SceneItems.Where(x => x.Entity.EntityID == ent.EntityID);
                                    if (entityExists.Any())
                                    {
                                        var existingEntity = entityExists.First();

                                        for (int i = 0; i < ent.ComponentsLength; i++)
                                        {
                                            var comp = ent.GetComponents(i);

                                            Console.WriteLine("NetMsg.Data.Entity -> ComponentType:" + comp.CompType);

                                            if (comp.CompType == UComponent.BodyComponent)
                                            {
                                                XFBType.BodyComponent fbBody = new XFBType.BodyComponent();
                                                comp.GetComp(fbBody);

                                                var body = existingEntity.Entity.GetComponentX<BodyComponent>() as BodyComponent;
                                                body.FB_BodyComponent.Location = new Interface.Scene.Services.Vector3() { X = fbBody.Position.X, Y = fbBody.Position.Y, Z = fbBody.Position.Z };
                                                body.FB_BodyComponent.Rotation = new Interface.Scene.Services.Quaternion() { W = fbBody.Rotation.W, X = fbBody.Rotation.X, Y = fbBody.Rotation.Y, Z = fbBody.Rotation.Z };
                                                body.FB_BodyComponent.Scale = new Interface.Scene.Services.Vector3() { X = fbBody.Scale.X, Y = fbBody.Scale.Y, Z = fbBody.Scale.Z };
                                             
                                            }
                                        }
                                    }
                                    else { // new entity

                                        var newEntity = new EntityX()
                                        {
                                            EntityID = ent.EntityID,
                                            NetID = message.Netid,
                                            SceneID = message.Scene
                                        };

                                        for (int i = 0; i < ent.ComponentsLength; i++)
                                        {
                                            var comp = ent.GetComponents(i);

                                            Console.WriteLine("NetMsg.Data.Entity -> ComponentType:" + comp.CompType);

                                            if (comp.CompType == UComponent.BodyComponent)
                                            {
                                                XFBType.BodyComponent fbBody = new XFBType.BodyComponent();
                                                comp.GetComp(fbBody);

                                                var body = new BodyComponent() { Parent = newEntity };
                                                body.FB_BodyComponent.Location = new Interface.Scene.Services.Vector3() { X = fbBody.Position.X, Y = fbBody.Position.Y, Z = fbBody.Position.Z };
                                                body.FB_BodyComponent.Rotation = new Interface.Scene.Services.Quaternion() { W = fbBody.Rotation.W, X = fbBody.Rotation.X, Y = fbBody.Rotation.Y, Z = fbBody.Rotation.Z };
                                                body.FB_BodyComponent.Scale = new Interface.Scene.Services.Vector3() { X = fbBody.Scale.X, Y = fbBody.Scale.Y, Z = fbBody.Scale.Z };
                                                newEntity.Components.Add(body);
                                            }
                                        }

                                        model.SceneItems.Add(new SourceItem()
                                        {
                                            Entity = newEntity
                                        });
                                    }
                                }));

                        break;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(e.Data);
            }
        }


        private void btnConnectToServer_Click(object sender, RoutedEventArgs e)
        {
            var tvm = VEFModule.UnityContainer.Resolve(typeof(SocketServerToolViewModel), "") as SocketServerToolViewModel;

            var model = tvm.Model as SocketServerToolModel;

            model.HostInfo.hostName = "127.0.0.1";
            model.HostInfo.port = 1234;
            model.HostInfo.data = 1234;
            model.HostInfo.channelLimit = 255;

            var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;
            _SocketServerManager.Client.ConnectToServer(model.HostInfo);
            _SocketServerManager.Client.SampleEvent += new Client.SampleEventHandler(ServerEvent);
            // PacketManipulationDemo();

            //   client.Join();
        }

        private void btnSendToClient_Click(object sender, RoutedEventArgs e)
        {
            //var model = this.DataContext as SocketServerToolModel;
            //foreach(var item in model.SourceItems)
            //{
            //    foreach (var sceneitem in item.SceneItem.Items)
            //    {
            //        var sendItem = sceneitem as SceneItem;
            //        if(sendItem != null)
            //        _client.SendToServer(0, sendItem.FBObject.CreateByteBuffer()._fbData, ENet.PacketFlags.Reliable);
            //    }   
            //}

            //  XFBType.
              FlatBufferBuilder fbb = new FlatBufferBuilder(4);
            
            var offset = NetMsg.Login.CreateLogin(fbb, fbb.CreateString("xx"));
             var mon = NetMsg.MessageRoot.CreateMessageRoot(fbb,0,1,NetMsg.Data.Login, offset.Value);
               NetMsg.MessageRoot.FinishMessageRootBuffer(fbb, mon);

            var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;
            _SocketServerManager.Client.SendToServer(0, fbb.SizedByteArray(), ENet.PacketFlags.Reliable);
        }

        protected virtual void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void btn_Test_Click(object sender, RoutedEventArgs e)
        {
            //Convert();

            //return;

            string fbxfilename = @"F:\Projekte\coop\XGame\_devFolder\Work\Character\character@Idle.fbx";
            string skeletonfilename = @"F:\Projekte\coop\XGame\data\assets\TestModel\TestModel.SKELETON";
            string meshfilename = @"F:\Projekte\coop\XGame\data\assets\TestModel.MESH";
            string logfilename = "log.txt";
            string animname = "Idle";
            int start = Int32.MinValue; int stop = Int32.MaxValue; float rate = 0;
           
            DLL_FBXToOgre tmp = new DLL_FBXToOgre();
            tmp.Test_AddFBXAnimationToExisting( fbxfilename,  skeletonfilename,  meshfilename,  logfilename,
                                                         animname, start, stop, rate); 
        }

        private void Convert()
        {
            //opts.outputmeshfile = opts.fbxfile.substr(0, opts.fbxfile.length() - 4) + ".MESH";
            //opts.inputskeletonfile = opts.fbxfile.substr(0, opts.fbxfile.length() - 4) + ".SKELETON";
            //opts.inputmeshfile = opts.fbxfile.substr(0, opts.fbxfile.length() - 4) + ".MESH";

            //opts.frame0Name = "BaseFBXFrame0Anim";
            //opts.quickexportAnimName = "BaseFBXFileAnim";

          //  string fbxfilename = @"F:\Projekte\Game\3d Models\Work\fighter\test\test.fbx";
              string fbxfilename = @"F:\Projekte\Game\3d Models\SFV\Ryu-Final\Ryu\ryu.FBX";
          string outmeshfilename = "test.MESH";
            string animname = "";
            string logfilename = "log.txt"; 
            string frame0name = "BaseFBXFrame0Anim";
            bool copyUniqueTextures = false;
            int bindframe = 0;

            DLL_FBXToOgre tmp = new DLL_FBXToOgre();
           bool result = tmp.Test_ExportOgreFromFBX(fbxfilename,  outmeshfilename,  logfilename,  animname,
                                                        frame0name,  copyUniqueTextures,  bindframe);
        }

        private void btn_convert_Click(object sender, RoutedEventArgs e)
        {
        }

        private void btn_ChatMsg_Click(object sender, RoutedEventArgs e)
        {
            //FlatBufferBuilder fbb = new FlatBufferBuilder(4);
            //var offset = NetMsg.Chatmessage.CreateChatmessage(fbb,0, fbb.CreateString(tbConsoleText.Text));
            //var mon = NetMsg.MessageRoot.CreateMessageRoot(fbb, 0, 1, NetMsg.Data.Chatmessage, offset.Value);
            //NetMsg.MessageRoot.FinishMessageRootBuffer(fbb, mon);

            //var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;
            //_SocketServerManager.Client.SendToServer(0, fbb.SizedByteArray(), ENet.PacketFlags.Reliable);
        }

        private void _dataGrid_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
        }

        private void _dataGrid_MouseUp(object sender, MouseButtonEventArgs e)
        {

            var mPropertiesService = VEFModule.UnityContainer.Resolve(typeof(IPropertiesService), "") as IPropertiesService;
            mPropertiesService.CurrentItem = _dataGrid.SelectedItem;
        }

        private void btn_Hostproperties_Click(object sender, RoutedEventArgs e)
        {
            var mPropertiesService = VEFModule.UnityContainer.Resolve(typeof(IPropertiesService), "") as IPropertiesService;
            mPropertiesService.CurrentItem = this.DataContext;
        }

        private void btn_SyncWithCurrentScene_Click(object sender, RoutedEventArgs e)
        {
            var model = this.DataContext as SocketServerToolModel;

            if (model.SceneItems.Any())
            {
                var sceneService = VEFModule.UnityContainer.Resolve(typeof(ISceneService), "") as ISceneService;
                var projTreeService = VEFModule.UnityContainer.Resolve(typeof(IProjectTreeService), "") as IProjectTreeService;


                var projITem = projTreeService.Items.Where(x => x is VEXProjectModel).FirstOrDefault();
                var DBITem = projITem.Items.Where(x => x is VEXDBFileModel).FirstOrDefault();
                var projEntities = DBITem.Items.Where(x => x is DBEntitiesModel).FirstOrDefault().Items.Cast<EntityX>();

   
                foreach (var netIDItem in model.SceneItems)
                {
                    var projEntity = projEntities.Where(x => x.EntityID == netIDItem.Entity.EntityID).FirstOrDefault();
                    projEntity.NetID = netIDItem.Entity.NetID;

                    if (sceneService.SelectedScene == null)
                        continue;

                    var sceneGraphItems = sceneService.SelectedScene.Entities.Where(x => x.EntityID == netIDItem.Entity.EntityID);
                    if(sceneGraphItems.Any())
                    {
                        var sceneGraphEntity = sceneGraphItems.First();

                        //todo   Type test = typeof(netIDItem.Component);
                        var netComponent = netIDItem.Entity.GetComponentX<BodyComponent>() as BodyComponent;

                        var sceneEntityComponent = sceneGraphEntity.GetComponentX<BodyComponent>();
                        var fb_body = sceneEntityComponent.FBObject as FB_BodyComponent;
                        fb_body.Location = netComponent.FB_BodyComponent.Location as Vector3;
                        fb_body.Rotation = netComponent.FB_BodyComponent.Rotation as Quaternion;
                        fb_body.Scale = netComponent.FB_BodyComponent.Scale as Vector3;

                        sceneGraphEntity.NetID = netIDItem.Entity.NetID;
                    }

                }                
            }
        }
    }
}
