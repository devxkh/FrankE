using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using XFBType;
using XGame.Core.Engine.Components;

namespace XGame.Core.Engine
{
    public class PrefabMsg
    {
        public static void SendLogin(NetIdComponent netID)
        {
            //FlatBuffers.FlatBufferBuilder fbb = new FlatBuffers.FlatBufferBuilder(1);
            //var loginName = fbb.CreateString("MyLoginName");

            //Login.StartLogin(fbb);
            //Login.AddIdentity(fbb, loginName);
            //var login = Login.EndLogin(fbb);
            //var offset = MessageRoot.CreateMessageRoot(fbb, 0, 0, Data.Login, login.Value);
            //fbb.Finish(offset.Value); //important!

            //byte[] tmp = fbb.SizedByteArray();

            //UnityContainer.Get().Engine.SendToServer(netID, tmp, (uint)tmp.Length);

        }

    }
}
