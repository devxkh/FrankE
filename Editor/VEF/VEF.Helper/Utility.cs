using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;

namespace VEF.Helper
{
    public static partial class Utility
    {
        /// <summary>
        /// Converts a datetime into Unixtimestamp (culute depended)
        /// </summary>
        /// <param name="MyDateTime">datetime to convert</param>
        /// <param name="name">culture name</param>
        /// <returns>Unix timestamp</returns>
        public static UInt32 DateTimeToUint(DateTime MyDateTime, string name = "en-US")
        {
            CultureInfo tmpC = new CultureInfo(name);// 127); //en-US

            String strDT = String.Format("{0:yyyyMMdd}", MyDateTime);
            return Convert.ToUInt32(strDT);
        }

        /// <summary>
        /// delivers a number of a BCD byte array
        /// </summary>
        /// <param name="pWert">BCD byte Array</param>
        /// <returns>number</returns>
        public static Int64 GetInt64FBCD(Byte[] pWert)
        {
            String longBytes = BitConverter.ToString(pWert).Replace("-", "");
            Int64 erg = 0;
            Int64.TryParse(longBytes, out erg);
            return erg;
        }

        /// <summary>
        /// checks, if a bit is set wihtin a Byte
        /// </summary>
        /// <param name="b">Byte, wanted to check</param>
        /// <param name="BitNumber">bit to check (0 - 7).</param>
        /// <returns>setted=true, not setted =false</returns>
        public static Boolean CheckBitSet(Byte b, Int32 BitNumber)
        {
            //Kleine Fehlerbehandlung
            if (BitNumber < 8 && BitNumber > -1)
            {
                return (b & (1 << BitNumber)) > 0;
            }
            else
            {
                throw new Exception("Der Wert für BitNumber " + BitNumber.ToString() + " war nicht im zulässigen Bereich! (BitNumber = (min)0 - (max)7)");
            }
        }

        /// <summary>
        ///short version of tryparse bool
        /// </summary>
        /// <param name="pString">Boolean String</param>
        /// <returns>Boolean</returns>
        public static Boolean fStringToBool(String pString)
        {
            bool tmp;
            bool.TryParse(pString, out tmp);
            return tmp;
        }

        /// <summary>
        /// convert string to Bytearray
        /// </summary>
        /// <param name="str">String</param>
        /// <returns>Arraybyte from passed string</returns>
        public static Byte[] StringToByteArray(String str)
        {
            return Encoding.Unicode.GetBytes(str);
        }

        /// <summary>
        /// convert a bytearray into a string
        /// </summary>
        /// <param name="arr">Bytearray</param>
        /// <returns>String</returns>
        public static String ByteArrayToString(Byte[] arr)
        {
            System.Text.UnicodeEncoding enc = new System.Text.UnicodeEncoding();
            return enc.GetString(arr,0,arr.Length);
        }

        /// <summary>
        /// convert a Integerarray into a string
        /// </summary>
        /// <param name="arr">array of integers</param>
        /// <returns>string representation of the integer array</returns>
        public static String UintArrayToString(UInt32[] arr)
        {
            var sb = arr.Aggregate(new StringBuilder(), (s, i) => s.Append(i));
            return sb.ToString();
        }

        /// <summary>
        /// delivers Unixepoche time
        /// </summary>
        private static DateTime UnixEpoch
        {
            //time_t contains the number of seconds since midnight 1/1/1970
            get { return new DateTime(1970, 1, 1); }
        }

        /// <summary>
        /// Unixzeitstempel in Datetime umwandeln
        /// </summary>
        /// <param name="unixTime">Unix Zeitstempel</param>
        /// <returns>Datetime format</returns>
        public static DateTime uiTimeToDTime(uint unixTime)
        {
            String FDT = "";

            try
            {
                FDT = String.Format("{0:00}.{1:00}.{2}", unixTime % 100, (unixTime / 100) % 100, unixTime / 10000);
            }
            catch { }


            DateTime testc = DateTime.Now;
            DateTime.TryParse(FDT, out testc);

            return testc;//UnixEpoch.AddSeconds(Convert.ToDouble(unixTime));
        }

        public static DateTime UInttoDateTime(UInt32 pTime)
        {
            String tmp = pTime.ToString();
            return new DateTime();
        }

        /// <summary>
        /// Wandelt ein Hexadezimal Byte in einen Character um 
        /// </summary>
        /// <param name="pByte">HexByte</param>
        /// <returns>Character dür das Hexbyte</returns>
        public static Char fHexByteToChar(Byte pByte)
        {
            int i = Convert.ToInt32(pByte); // i now = 65
            Char schar = Convert.ToChar(i);
            return schar;
        }


        /// <summary>
        /// Liefert true wenn das Bit == 1
        /// </summary>
        /// <param name="b">Byte</param>
        /// <param name="bitNumber">Bitposition</param>
        /// <returns>true = 1,false = 0</returns>
        public static Boolean GetBit(this Byte b, Int32 bitNumber)
        {
            return (b & (1 << bitNumber)) != 0;
        }

        public static Byte[] ToBcd(Int64 value)
        {
            if (value < 0 || value > 9999999999999999)
                throw new ArgumentOutOfRangeException("value");
            byte[] ret = new byte[16];

            for (int i = 0; i < 16; i++)
            {
                ret[i] = (byte)(value % 10);
                value /= 10;
                ret[i] |= (byte)((value % 10) << 4);
                value /= 10;
            }

            if (BitConverter.IsLittleEndian)
                Array.Reverse(ret); //need the bytes in the reverse order

            return ret;
        }

        public static UInt64 fGetUint64FBCD(Byte[] pWert)
        {
            String longBytes = BitConverter.ToString(pWert).Replace("-", "");
            UInt64 erg = 0;
            UInt64.TryParse(longBytes, out erg);
            return erg;
        }
    }
}
