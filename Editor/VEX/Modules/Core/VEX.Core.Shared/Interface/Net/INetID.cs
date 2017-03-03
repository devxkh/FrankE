using System;
using System.Collections.Generic;
using System.Text;
using VEX.Interface.DAL;

namespace VEX.Core.Shared.Interface.Net
{
    public interface INetID
    {
      //  ushort NetID { get; } only scenenode aka bodycomponenet has netID

   //     bool SendToSocket(IFBObject FBObject, NetMsg.Data msgTyp);

        IFBObject FBObject { get;  }

     //   NetMsg.Data Type { get; }
    }
}
