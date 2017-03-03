using System;
using System.Collections.Generic;
using System.Text;
using VEF;
using VEX.Core.Model.Services;
using VEX.Interface.DAL;

namespace VEX.Core.Shared.Utility
{
    public class SocketHelper
    {

        public static bool SendToSocket(IFBObject FBObject, NetMsg.Data msgType, uint netID,  uint sceneID)
        {
            var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;
            //if (NetID <= 0)
            //    NetID = _SocketServerManager.NewNetID();

            var fbdata = FBObject.CreateFBData();

            FBObject.Read(fbdata._fbData);

            return _SocketServerManager.SendMessageToServer(netID, sceneID, msgType, fbdata);//Parent.NetID, SceneID, msgType, fbdata);
        }
    }
}
