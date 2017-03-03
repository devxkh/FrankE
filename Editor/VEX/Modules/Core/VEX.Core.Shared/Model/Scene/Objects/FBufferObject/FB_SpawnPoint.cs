using FlatBuffers;
using System;
using System.Runtime.Serialization;
using System.Xml.Serialization;
using VEF.Utils;
using VEX.Interface.DAL;

namespace VEX.Model.Scene.Model.Objects
{
    [DataContract]
    public class FB_SpawnPointModel : ViewModelBase, IFBObject //, INetMsg
    {
        private XFBType.SpawnPointComponent m_FBData = new XFBType.SpawnPointComponent();

        #region Properties

      //  public NetMsg.Data FBMsgType { get { return NetMsg.Data.NONE; } }

        public object Parent { get; set; }

        [DataMember]
        public uint SpawnPointGroup { get; set; }

        [DataMember]
        public uint SpawnPointId { get; set; }

        [DataMember]
        public string SpawnPointName { get; set; }


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
            var finishOffset = XFBType.SpawnPointComponent.CreateSpawnPointComponent(fbb, SpawnPointGroup, SpawnPointId, fbb.CreateString(SpawnPointName ?? "SP New"));
            fbb.Finish(finishOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbb.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbb }; //bytebuffer
        }
    }
}
