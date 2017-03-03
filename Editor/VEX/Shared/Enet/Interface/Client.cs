using FlatBuffers;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using VEF.Utils;

namespace VEX.Enet.Interface
{
    public class SampleEventArgs
    {
        public SampleEventArgs(byte[] s) { Data = s; }
        public byte[] Data { get; private set; } // readonly
    }

    public class Client
    {
        private Thread client;
        private ENet.Peer peer;
        private HostInfo _hostInfo;

        public HostInfo HostInfo { get { return _hostInfo; } }

        // Declare the delegate (if using non-generic pattern).
        public delegate void SampleEventHandler(object sender, SampleEventArgs e);


        // Declare the event.
        public event SampleEventHandler SampleEvent;

        void ClientThread(HostInfo hostinfo)
        {
            _hostInfo = hostinfo;

            using (ENet.Host host = new ENet.Host())
            {
                Console.WriteLine("Initializing client...");
                host.Initialize(hostinfo.address, hostinfo.peerLimit,
                               hostinfo.channelLimit, hostinfo.incomingBandwidth, hostinfo.outgoingBandwidth);

                peer = host.Connect(hostinfo.hostName, hostinfo.port, hostinfo.data, hostinfo.channelLimit);
                hostinfo.isConnected = true;
                while (hostinfo.isConnected)
                {
                    ENet.Event @event;

                    if (host.Service(hostinfo.timeout, out @event))
                    {
                        do
                        {
                            switch (@event.Type)
                            {
                                case ENet.EventType.Connect:
                                    Console.WriteLine("Connected to server at IP/port {0}.", peer.GetRemoteAddress());
                                    break;

                                case ENet.EventType.Receive:
                                    byte[] data = @event.Packet.GetBytes();

                                    HandleMessage(data);

                                    ushort value = BitConverter.ToUInt16(data, 0);
                                    if (value % 1000 == 0)
                                    {
                                        Console.WriteLine("  Client: Ch={0} Recv={1}", @event.ChannelID, value);
                                    }
                                    value++;
                                  //  peer.Send(@event.ChannelID, BitConverter.GetBytes(value), ENet.PacketFlags.Reliable);
                                    @event.Packet.Dispose();
                                    break;
                                case ENet.EventType.Disconnect:
                                    Console.WriteLine("Disconnected from server at IP/port {0}.", peer.GetRemoteAddress());
                                    hostinfo.isConnected = false;
                                    hostinfo.isLoggedIn = false;
                                    break;
                                default:
                                    Console.WriteLine(@event.Type);
                                    break;
                            }
                        }
                        while (host.CheckEvents(out @event));
                    }
                }
            }
        }

        private void HandleMessage(byte[] data)
        {
            // Raise the event by using the () operator.
            if (SampleEvent != null)
                SampleEvent(this, new SampleEventArgs(data));


        
        }

        public void DisconnectFromServer()
        {
            _hostInfo.isConnected = false;
            _hostInfo.isLoggedIn = false;
            Join();
        }

        public void ConnectToServer(HostInfo hostinfo)
        {
            client = new Thread(() => ClientThread(hostinfo));
            client.Start();
        }

        public void Join()
        {
            if (client != null)
                client.Join();
        }

        public bool SendToServer(byte channelID, Byte[] data, ENet.PacketFlags PacketFlags = ENet.PacketFlags.Reliable)
        {
            try
            {
                unsafe {
                    if (peer.NativeData != null)
                        peer.Send(channelID, data, PacketFlags);
                }

                return true;
            }
            catch (Exception ex)
            {

            }
            return false;
        }
    }
}
