using FlatBuffers;
using System;
using System.Runtime.Serialization;
using System.Xml.Serialization;
using VEF.Utils;
using VEX.Interface.DAL;

namespace VEX.Model.Scene.Model.Objects
{
    [DataContract]
    public class FB_SpawnModel : ViewModelBase, IFBObject //, INetMsg
    {
        private XFBType.SpawnComponent m_FBData = new XFBType.SpawnComponent();

        #region Properties

      //  public NetMsg.Data FBMsgType { get { return NetMsg.Data.NONE; } }

        public object Parent { get; set; }

        [DataMember]
        public uint SpawnPointGroup { get; set; }

        [DataMember]
        public uint SpawnPointId { get; set; }

        [DataMember]
        public XFBType.SpawnType SpawnType { get; set; }

        #endregion

        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbb = null, IFBObject child = null)
        {
            if (fbb == null)
                fbb = new FlatBufferBuilder(1);

            //todo
            var finishOffset = XFBType.SpawnComponent.CreateSpawnComponent(fbb, SpawnPointGroup, SpawnPointId, XFBType.SpawnType.STYPE_RANDOM);
            fbb.Finish(finishOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbb.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbb }; //bytebuffer
        }
    }
}
