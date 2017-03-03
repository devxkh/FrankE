using Microsoft.Practices.Unity;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using FlatBuffers;
using VEX.Interface.DAL;
using System.Runtime.Serialization;

namespace VEX.Model.Scene.Model.Objects.ChildObject
{

    [DataContract]
    public class CubeObject : MeshObject, IFBObject//, INetMsg
    {
        private float m_width;

        /// <summary>
        /// needed for propertygrid collection
        /// </summary>
        public CubeObject()
        {

        }

        //    public NetMsg.Data FBMsgType { get { return NetMsg.Data.NONE; } }

        #region properties

        [DataMember]
        public float width { get { return m_width; } set { m_width = FB_Helper.UpdateSelectedObject(this, m_width, value); } }

        #endregion
        
        #region IFBObject
        
        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public new void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);
            // XFBType.Mesh.
            //  m_FBData = XFBType.Mesh.GetRootAsMesh(byteBuffer); // read 
        }

        /// <summary>
        /// resets the flatbufferbuilder
        /// </summary>
        /// <param name="fbb">flatbufferbuilder from parent object</param>
        /// <returns>byte data</returns>
        public new FBNetData CreateFBData(FlatBufferBuilder fbbParent = null, IFBObject child = null)
        {
            if (fbbParent == null)
                fbbParent = new FlatBufferBuilder(1);

            XFBType.MeshCube.StartMeshCube(fbbParent);
            var cubeOffset = XFBType.MeshCube.EndMeshCube(fbbParent);

            //   var finishOffset = XFBType.OgreCube.CreateOgreCube(fbb, m_width);
            fbbParent.Finish(cubeOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = cubeOffset.Value, Fbb = fbbParent }; //bytebuffer
        }

        #endregion
    }
}
