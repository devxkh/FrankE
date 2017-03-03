using System;
using System.Collections.Generic;
using System.Text;
using VEF.Utils;

namespace VEX.Enet.Interface
{
    public class HostInfo : ViewModelBase
    {
        private bool _isConnected;
        private bool _isLoggedIn;

        public string hostName { get; set; }
        public int port { get; set; }
        public int data { get; set; }
        public int peerLimit { get; set; }
        public System.Net.IPEndPoint address { get; set; }
        public int channelLimit { get; set; }
        public int incomingBandwidth { get; set; }
        public int outgoingBandwidth { get; set; }
        public int timeout { get; set; }
        public bool isConnected { get { return _isConnected; } set { _isConnected = value; RaisePropertyChanged("isConnected"); } }
        public bool isLoggedIn { get { return _isLoggedIn; } set { _isLoggedIn = value; RaisePropertyChanged("isLoggedIn"); } }

        public HostInfo()
        {
            hostName = "127.0.0.1";
            port = 1234;
            data = 1234;
            peerLimit = 255;
            address = null;
            channelLimit = 255;
            incomingBandwidth = 0;
            outgoingBandwidth = 0;
            timeout = 15000;
        }
    }

}
