using System;
using System.Collections.Generic;
using System.Text;

namespace VEF.Shared.Sockets.SocketHandler
{

   // #if WINDOWS_APP
    using System.Threading;
    using System.Net.Sockets;
    using System.Security.Authentication;

    public class HandleClient
    {
        public TcpClient ClientSocket { get; set; }
        int iClientID;
        Thread ctThread;
        NetworkStream networkStream;
        public SocketClient oClient;

        public HandleClient(int pClientID)
        {
            oClient = new SocketClient();
            iClientID = pClientID;
        }

        string clNo;


        public void startClient(string clineNo)
        {
            clNo = clineNo;

            try
            {
                //Client Objekt
                oClient.IP = ClientSocket.Client.RemoteEndPoint.ToString();
                oClient.ClientID = iClientID;

                Console.WriteLine(Convert.ToString(iClientID) + "#" + ClientSocket.Client.RemoteEndPoint);

                networkStream = ClientSocket.GetStream();

                //IP ungültig
                //if (oClient.KartenNr == 0)
                //   {
                //      SocketInterface.fSendFehler(sslStream, (UInt16)FehlerID.USERCARDNR);
                //     StopClient();
                //    else
                //    {
                ctThread = new Thread(doChat);
                ctThread.Start();
                ctThread.Join();
                //    }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Fehler bei client(" + iClientID + ") Thread:", ex.Message);
            }
        }

        public void fWriteToStream(int pMsgType)
        {
            int length = 0;

            switch (pMsgType)
            {
                case 0://Editor Command   
                    length = SocketInterface.SendEditorCommand(networkStream, 1);

                    break;
                case 8: //Versendet FehlerId
                    length = SocketInterface.fSendFehler(networkStream, 1);
                    break;
            }

            Console.WriteLine("Server->Client:Länge: " + length + " Byte");
        }

        private void doChat()
        {
            byte[] bytesFrom = new byte[10025];
            string dataFromClient = null;
            uint iMoreData = 0; //Weitere Daten im Stream vorhanden?

            while ((true))
            {
                try
                {
                    //Client anpollen um zu prüfen ob Stream noch verfügbar
                    //Problemlösung für: Client App schließt ohne Stream zu beenden und versucht selben Stream wieder zu verwenden
                    if (ClientSocket.Client.Poll(0, SelectMode.SelectRead))
                    {
                        byte[] checkConn = new byte[1];
                        if (ClientSocket.Client.Receive(checkConn, SocketFlags.Peek) == 0)
                        {
                            Console.WriteLine("ClientSocket nicht mehr verfügbar");
                            StopClient();
                            return;
                        }
                    }

                    dataFromClient = null;

                    SocketInterface.MSG_HEADER sMsgHeader = new SocketInterface.MSG_HEADER();
                    while ((iMoreData = SocketInterface.fReadHeader(networkStream, ref  sMsgHeader)) != 0)
                    {
                        Console.WriteLine("Client(" + iClientID + ")->Server: Length:" + sMsgHeader.iLength + "");
                        Console.WriteLine("Client(" + iClientID + ")->Server: MsgType:" + sMsgHeader.iMessageType + "");
                        Console.WriteLine("Readfrom stream: (4 Byte)");

                        int length = 0;

                        switch (sMsgHeader.iMessageType)
                        {


                            case (int)MessageType.CANCEL:
                                SocketInterface.MSG_CANCEL sMsgCancel = new SocketInterface.MSG_CANCEL();
                                SocketInterface.fReadCancel(networkStream, ref  sMsgCancel);

                                Console.WriteLine("Client(" + iClientID + ")->Server: Cancel:" + sMsgCancel.iCancel + "");

                                break;
                            default:
                                int i;

                                //Restliche Daten aus Stream auslesen
                                // Loop to receive all the data sent by the client.
                                while ((i = networkStream.Read(bytesFrom, 0, bytesFrom.Length)) != 0)
                                {
                                    // Translate data bytes to a ASCII string.
                                    dataFromClient = System.Text.Encoding.UTF8.GetString(bytesFrom, 0, i);

                                    Console.WriteLine("Default: >> " + "Client (" + iClientID + "): " + dataFromClient + "");
                                }
                                break;
                        }
                    }
                    int itmp;

                    //Restliche Daten aus Stream auslesen
                    // Loop to receive all the data sent by the client.
                    while ((itmp = networkStream.Read(bytesFrom, 0, bytesFrom.Length)) != 0)
                    {
                        // Translate data bytes to a ASCII string.
                        dataFromClient = System.Text.Encoding.UTF8.GetString(bytesFrom, 0, itmp);

                        Console.WriteLine("Müll: >> " + "Client (" + iClientID + "): " + dataFromClient + "");
                    }
                }
                catch (AuthenticationException e)
                {
                    Console.WriteLine("Client (" + iClientID + ") Exception: " + e.Message + "");

                    if (e.InnerException != null)
                    {
                        //  tbLog.Text = "Inner exception: " + e.InnerException.Message +"";
                    }

                    Console.WriteLine("Client (" + iClientID + ") Authentication failed - closing the connection.");

                    StopClient();
                    break;
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Client (" + iClientID + ") Exception: >> " + ex.ToString() + "");

                    StopClient();
                    break;
                }
            }
        }

        public void StopClient()
        {
            networkStream.Close();
            ClientSocket.Close();
            ctThread.Abort();
        }
    }

//#endif

}
