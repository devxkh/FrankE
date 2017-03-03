using FlatBuffers;
using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Text;
using System.Xml.Serialization;
using VEX.Interface.DAL;

namespace VEX.Core.Shared.Model.Scene.Objects.ChildObject.Animation
{
    [DataContract(IsReference = true)]
    public class AnimConstant : AnimNode, IFBObject
    {
        #region Properties 
        
        [DataMember]
        public uint Id { get; set; }
        [DataMember]
        public uint PortId { get; set; }
        [DataMember]
        public float Value { get; set; }

        #endregion

        #region IFBObject

        [XmlIgnore]
        public object Parent { get; set; }

        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbbParent = null, IFBObject child = null)
        {
            if (fbbParent == null)
                fbbParent = new FlatBufferBuilder(1);

            var nameVal = fbbParent.CreateString(Name);

            var paremterNodeOffset = XFBType.Constant.CreateConstant(fbbParent, Id, NodeId,PortId,Value);

            fbbParent.Finish(paremterNodeOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = paremterNodeOffset.Value, Fbb = fbbParent };//bytebuffer
        }

        #endregion

    }
}
