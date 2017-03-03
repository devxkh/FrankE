using FlatBuffers;
using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Text;
using System.Xml.Serialization;
using VEX.Interface.DAL;

namespace VEX.Core.Shared.Model.Scene.Objects.ChildObject.Animation
{
    [DataContract]
    public class NodeConnection 
    {
        #region Properties 

        [DataMember]
        public uint In { get; set; }

        [DataMember]
        public uint Out { get; set; }

        [DataMember]
        public uint PortIn { get; set; }

        #endregion

        //#region IFBObject

        //[XmlIgnore]
        //public object Parent { get; set; }

        ///// <summary>
        ///// reads flatbuffers byte data into object
        ///// </summary>
        ///// <param name="fbData"></param>
        //public void Read(Byte[] fbData)
        //{
        //    ByteBuffer byteBuffer = new ByteBuffer(fbData);
        //}

        //public FBNetData CreateFBData(FlatBufferBuilder fbbParent = null, IFBObject child = null)
        //{
        //    if (fbbParent == null)
        //        fbbParent = new FlatBufferBuilder(1);

        //    var connectionOS = XFBType.Connection.CreateConnection(fbbParent, In, Out, PortIn);

        //    fbbParent.Finish(connectionOS.Value); //!!!!! important ..
        //    return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = connectionOS.Value, Fbb = fbbParent };//bytebuffer
        //}

        //#endregion
    }
}
