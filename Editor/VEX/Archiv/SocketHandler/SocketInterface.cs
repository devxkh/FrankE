using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;

namespace VEF.Shared.Sockets.SocketHandler
{
    /// <summary>
    /// FehlerID's
    /// </summary>
    enum FehlerID : uint
    {
        NO = 0, //Kein Fehler
        LOCKED = 1, //Benutzer gesperrt
        USERCARDNR = 2, //Kartennummer nicht vorhanden
        IP = 3 //Benutzer IP nicht vorhanden 
    }

    /// <summary>
    /// Nachrichtentypen
    /// </summary>
    enum MessageType : int
    {
        UNKNOWN = 0,
        CANCEL = 1, //Abbruch#
        FEHLER = 2 //FehlerID
    }

    [StructLayout(
    LayoutKind.Sequential,      //must specify a layout
    CharSet = CharSet.Ansi)]    //if you intend to use char


    public class SocketInterface
    {
        /// <summary>
        /// Nachrichtenkopf
        /// </summary>
        public struct MSG_HEADER
        {
            public ushort iMessageType; //Numer des Nachrichtentyps
            //ushort = 2 byte
            public ushort iLength; //Länge der Nachricht
        };

        /// <summary>
        /// Automaten, Status
        /// 0 = nichts
        /// 1 = Produkt ausgegeben und abgerechnet
        /// </summary>
        public struct MSG_STATUS
        {
            public MSG_HEADER sMsgHeader;
            public uint uiStatus;
        }

        /// <summary>
        /// FehlerID
        /// </summary>
        public struct MSG_FEHLER
        {
            public MSG_HEADER sMsgHeader;
            public UInt16 uiFehlerID;
        }

        /// <summary>
        /// Abbruch
        /// </summary>
        public struct MSG_CANCEL
        {
            public uint iCancel; //1 = Abbruch,0 = kein Abbruch
        }

        /// <summary>
        /// Konvertiert Strukturdaten in ein ByteArray
        /// </summary>
        /// <param name="obj">Struktur Objekt</param>
        /// <returns>ByteArray der Struktur</returns>
        static byte[] StructureToByteArray(object obj)
        {
            int len = Marshal.SizeOf(obj);
            byte[] arr = new byte[len];

            IntPtr ptr = Marshal.AllocHGlobal(len);
            Marshal.StructureToPtr(obj, ptr, true);
            Marshal.Copy(ptr, arr, 0, len);
            Marshal.FreeHGlobal(ptr);

            return arr;
        }

        /// <summary>
        /// Konvertiert ein Bytearray in ein Strukturtyp
        /// </summary>
        /// <param name="bytearray">Bytearray der Struktur</param>
        /// <param name="obj">Strukturobjekt</param>
        static void ByteArrayToStructure(byte[] bytearray, ref object obj)
        {
            int len = Marshal.SizeOf(obj);

            IntPtr i = Marshal.AllocHGlobal(len);
            Marshal.Copy(bytearray, 0, i, len);
            obj = Marshal.PtrToStructure(i, obj.GetType());
            Marshal.FreeHGlobal(i);
        }

        public static int SendEditorCommand(NetworkStream networkStream, UInt16 pFehlerID)
        {
            return 0;
        }

        public static int fSendFehler(NetworkStream networkStream, UInt16 pFehlerID)
        {
            MSG_FEHLER sMsgFehler = new MSG_FEHLER();
            sMsgFehler.sMsgHeader.iLength = (ushort)(Marshal.SizeOf(sMsgFehler));
            sMsgFehler.sMsgHeader.iMessageType = (ushort)MessageType.FEHLER;

            sMsgFehler.uiFehlerID = pFehlerID;

            byte[] msg = StructureToByteArray(sMsgFehler);
            int length = fWriteToStream(networkStream, msg);
            Console.WriteLine("SendFehler: (" + length + ")Byte");
            return length;
        }


        public static int fWriteToStream(NetworkStream networkStream, byte[] msg)
        {
            try
            {
                if (networkStream.CanWrite)
                {
                    networkStream.Write(msg, 0, msg.Length);
                }
                else
                {
                    Console.WriteLine("In den Stream können keine Daten geschrieben werden");
                    networkStream.Close();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Fehler bei Write Stream:", ex.Message);
                return 0;
            }
            return msg.Length;
        }

        /// <summary>
        /// Liest den Netzwerk Nachrichten Header aus
        /// </summary>
        /// <param name="sslStream"></param>
        /// <returns></returns>
        public static uint fReadHeader(NetworkStream networkStream, ref  MSG_HEADER sHeader)
        {
            // MSG_HEADER sHeader = new MSG_HEADER();
            byte[] bytesFrom = new byte[4]; //Header 4 Byte
            uint i = 0;

            try
            {
                if (networkStream.CanRead)
                {
                    i = (uint)networkStream.Read(bytesFrom, 0, 2);
                    sHeader.iLength = BitConverter.ToUInt16(bytesFrom, 0);
                    i = (uint)networkStream.Read(bytesFrom, 0, 2);
                    sHeader.iMessageType = BitConverter.ToUInt16(bytesFrom, 0);
                }
                else
                {
                    Console.WriteLine("Aus dem Stream können keine Daten gelesen werden");
                    networkStream.Close();
                }
                //Fehler beim auslesen des Headers
            }
            catch (Exception ex)
            {
                sHeader.iLength = 0;
                sHeader.iMessageType = 0;
                Console.WriteLine("Fehler beim auslesen des Headers:", ex.Message);
            }
            return i;
        }

        // Synchronous connect using IPAddress to resolve the 
        // host name.
        public static void Connect1(string host, int port)
        {

            IPAddress[] IPs = Dns.GetHostAddresses(host);

            Socket s = new Socket(AddressFamily.InterNetwork,
                SocketType.Dgram,
                ProtocolType.Udp);

            Console.WriteLine("Establishing Connection to {0}",
                host);
            s.Connect(IPs[0], port);
            Console.WriteLine("Connection established");

            Byte[] tmp = new Byte[50];
            s.Send(tmp);
        }

        /// <summary>
        /// Liest den Cancel Status aus
        /// </summary>
        /// <param name="sslStream">Stream</param>
        /// <returns>FehlerID</returns>
        public static uint fReadCancel(NetworkStream sslStream, ref  MSG_CANCEL sCancel)
        {
            //    MSG_CANCEL sCancel = new MSG_CANCEL();

            byte[] bytesFrom = new byte[8]; //int = 8byte
            uint i = 0;

            try
            {
                if (sslStream.CanRead)
                {
                    i = (uint)sslStream.Read(bytesFrom, 0, 8);
                    sCancel.iCancel = BitConverter.ToUInt16(bytesFrom, 0);
                }
                else
                {
                    Console.WriteLine("Aus dem Stream können keine Daten gelesen werden");
                    sslStream.Close();
                }
            }
            catch (Exception ex)
            {
                sCancel.iCancel = 0;
                Console.WriteLine("Fehler beim auslesen von Cancel:", ex.Message);
            }
            return i;
        }

    }
}
