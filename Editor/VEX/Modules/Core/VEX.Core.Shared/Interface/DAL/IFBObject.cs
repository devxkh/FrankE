using FlatBuffers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEX.Interface.DAL
{
    public struct FBNetData
    {
        public byte[] _fbData { get; set; }
        public int _offset { get; set; }
        public FlatBufferBuilder Fbb { get; set; }
        public dynamic TypeSafeOffset { get; set; }
    }

    //public interface INetMsg
    //{
    //    NetMsg.Data FBMsgType { get; }
    //}
    
        /// <summary>
        /// Interface for flatbuffer object
        /// </summary>
     public interface IFBObject
    {
        /// <summary>
        /// create flatbuffer
        /// </summary>
        /// <returns></returns>
        FBNetData CreateFBData(FlatBufferBuilder fbbParent = null, IFBObject child = null);

        /// <summary>
        /// read data from flatbuffer-bytebuffer
        /// </summary>
        void Read(Byte[] fbData);

        /// <summary>
        /// parent object
        /// </summary>
        object Parent { get; set; }
    }
}
