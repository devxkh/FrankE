using FlatBuffers;
using System;
using System.Windows;
using System.ComponentModel;
using VEX.Interface.DAL;
using System.Runtime.Serialization;
using VEF.Utils;

namespace VEX.Model.Scene.Model.Objects
{
    [DataContract]
    public class FB_AIComponent : ViewModelBase, IFBObject //, INetMsg
    {
        #region private members

        private new NetMsg.AIComponent m_FBData = new NetMsg.AIComponent();

        #endregion

        #region Properties

   //     public NetMsg.Data FBMsgType { get { return NetMsg.Data..CharacterComponent; } }
        
        //todo prototype!!!! or? skeleton path is located in mesh  file ...
        private string _script;

    //todo    [Editor(typeof(VFPathEditor), typeof(VFPathEditor))]
        [DataMember]
        public string Script { get { return _script; } set { _script = value; } }

        [DataMember]
        public object Parent { get; set; }

        #endregion

        #region methods

        public void Read(Byte[] fbData)
        {
            try
            {
                ByteBuffer byteBuffer = new ByteBuffer(fbData);
                m_FBData = NetMsg.AIComponent.GetRootAsAIComponent(byteBuffer); // read 

               // base.m_FBData = m_FBData.Entitybase;

               // var entbase = m_FBData.Entitybase;
              //  var animinfo = entbase.AnimationInfo;

              //  var len = entbase.MeshesLength;
              //  var lenmat = entbase.MaterialsLength;

              ////  var lensound = entbase.SoundsLength;
              // // var lenphys = entbase.PhysicsLength;

              //  var mat = entbase.GetMaterials(0);
              //  var mat1 = entbase.GetMaterials(1);

            //    var matname = mat.Name;
          //      var matname1 = mat1.Name;

              //  var phyiscs = entbase.GetPhysics(0);
              //  var phyT1 = phyiscs.Boneparent;

              //  var meshes = entbase.GetMeshes(0);
           //     var type = meshes.MeshType;


                //     m_Group = XFBType.Group(); //per node!
            }
            catch (Exception ex)
            {
                MessageBox.Show("error: " + ex.Message);
            }
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbb = null, IFBObject child = null)
        {
            if (fbb == null)
                fbb = new FlatBufferBuilder(1);

            var script = fbb.CreateString(Script ?? "");
            NetMsg.AIComponent.StartAIComponent(fbb); //, new Offset<XFBType.EntityBase>(base.CreateFBData(fbb)._offset));
            NetMsg.AIComponent.AddScript(fbb, script);
            var finishOffset = NetMsg.AIComponent.EndAIComponent(fbb);

            fbb.Finish(finishOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbb.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbb }; //bytebuffer
        }

        #endregion
    }
}
