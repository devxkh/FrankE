using System;
using System.Collections.Generic;
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

namespace VEX.SocketTool.WPF.View.Tools
{
    /// <summary>
    /// Interaktionslogik für SocketServerToolView.xaml
    /// </summary>
    public partial class SocketServerToolView : UserControl
    {
        private static ENet.Peer peer;

        static void Client()
        {
            using (ENet.Host host = new ENet.Host())
            {
                Console.WriteLine("Initializing client...");
                host.Initialize(null, 1);

                peer = host.Connect("127.0.0.1", 1234, 1234, 200);
                
                while (true)
                {
                    ENet.Event @event;

                    if (host.Service(15000, out @event))
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
                                    ushort value = BitConverter.ToUInt16(data, 0);
                                    if (value % 1000 == 0)
                                    {
                                        Console.WriteLine("  Client: Ch={0} Recv={1}", @event.ChannelID, value); 
                                    }
                                    value++; 
                                    peer.Send(@event.ChannelID, BitConverter.GetBytes(value), ENet.PacketFlags.Reliable);
                                    @event.Packet.Dispose();
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

        public SocketServerToolView()
        {
            InitializeComponent();
        }

        private void btnServerStop_Click(object sender, RoutedEventArgs e)
        {

        }

        private void btnConnectToServer_Click(object sender, RoutedEventArgs e)
        {
            Thread client = new Thread(Client); 
            client.Start();

           // PacketManipulationDemo();

         //   client.Join();

       //     SocketInterface.Connect1("127.0.0.1", 1234);
        }

        private void btnSendToClient_Click(object sender, RoutedEventArgs e)
        {
            Byte[] tmp = new Byte[] { 1, 2, 3, 4 };

            peer.Send(0, tmp, ENet.PacketFlags.Reliable);
                        
        }
    }
}
