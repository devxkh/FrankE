using System;
using System.Collections.Generic;
using System.Text;

namespace VEF.Shared.Sockets.SocketHandler
{
    public class SocketClient
    {
        String sIP;    //ClientIP
        int iClientID; //ClientID im Server
        int iStatusID;

        public int ClientID
        {
            get { return iClientID; }
            set { iClientID = value; }
        }

        public String IP
        {
            get { return sIP; }
            set { sIP = value; }
        }
    }
}
