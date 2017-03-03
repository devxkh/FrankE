using FlatBuffers;
using Microsoft.Practices.Unity;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using System;
using System.Xml.Serialization;
using VEX.Interface.DAL;
using VEX.Interface.Scene.Services;
using System.Runtime.Serialization;
using VEF.Utils;
using VEX.Model.Scene.Model.Objects.ObjectData;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace VEX.Model.Scene.Model.Objects.ChildObject
{
    /// <summary>
    /// Plane Object
    /// </summary>
    [DataContract]
    public class PlaneObject : MeshObject
    {
        #region private members

        private Vector3 m_normal;
        private float m_constant;
        private float m_width;
        private float m_height;
        private uint m_xsegments;
        private uint m_ysegments;
        private bool m_normals;
        private uint m_numTexCoordSets;
        private float m_xTile;
        private float m_yTile;
        private Vector3 m_upVector;

        #endregion

        #region Properties
        
        [DataMember]
        public Vector3 normal { get { return m_normal; } set { m_normal = FB_Helper.UpdateSelectedObject(this, m_normal, value); } }

        [DataMember]
        public float constant { get { return m_constant; } set { m_constant = FB_Helper.UpdateSelectedObject(this, m_constant, value); } }

        [DataMember]
        public float width { get { return m_width; } set { m_width = FB_Helper.UpdateSelectedObject(this, m_width, value); } }

        [DataMember]
        public float height { get { return m_height; } set { m_height = FB_Helper.UpdateSelectedObject(this, m_height, value); } }

        [DataMember]
        public uint xsegments { get { return m_xsegments; } set { m_xsegments = FB_Helper.UpdateSelectedObject(this, m_xsegments, value); } }

        [DataMember]
        public uint ysegments { get { return m_ysegments; } set { m_ysegments = FB_Helper.UpdateSelectedObject(this, m_ysegments, value); } }

        [DataMember]
        public bool normals { get { return m_normals; } set { m_normals = FB_Helper.UpdateSelectedObject(this, m_normals, value); } }

        [DataMember]
        public uint numTexCoordSets { get { return m_numTexCoordSets; } set { m_numTexCoordSets = FB_Helper.UpdateSelectedObject(this, m_numTexCoordSets, value); } }

        [DataMember]
        public float xTile { get { return m_xTile; } set { m_xTile = FB_Helper.UpdateSelectedObject(this, m_xTile, value); } }

        [DataMember]
        public float yTile { get { return m_yTile; } set { m_yTile = FB_Helper.UpdateSelectedObject(this, m_yTile, value); } }

        [DataMember]
        public Vector3 upVector { get { return m_upVector; } set { m_upVector = FB_Helper.UpdateSelectedObject(this, m_upVector, value); } }

        #endregion
        

        /// <summary>
        /// needed for propertygrid collection
        /// </summary>
        public PlaneObject()
        {
            m_normal = new Vector3();
            m_upVector = new Vector3();
        }

        #region IFBObject
        
        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public override void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);
        }

        public override FBNetData CreateFBData(FlatBufferBuilder fbbParent = null, IFBObject child = null)
        {
            if (fbbParent == null)
                fbbParent = new FlatBufferBuilder(1);


            //  XFBType.LocalFile.StartLocalFile(fbbParent);

            //var material = Materials[0];

            //var localMaterialFileOffset = XFBType.LocalFile.CreateLocalFile(fbbParent, FileLocation,
            //                            fbbParent.CreateString(FileName ?? ""),
            //                            fbbParent.CreateString(FilePath ?? ""),
            //                            fbbParent.CreateString(ResourceGroup ?? ""));


            //XFBType.LocalFile.AddFileLocation(fbbParent, material.FileLocation);

            //if (material.FileName != null)
            //    XFBType.LocalFile.AddFileName(fbbParent, fbbParent.CreateString(material.FileName));
            //if (material.FilePath != null)
            //    XFBType.LocalFile.AddFilePath(fbbParent, fbbParent.CreateString(material.FilePath));
            //if (material.ResourceGroup != null)
            //    XFBType.LocalFile.AddResourceGrp(fbbParent, fbbParent.CreateString(material.ResourceGroup));

            //var localMaterialFileOffset = XFBType.LocalFile.EndLocalFile(fbbParent);



            var localFileOffset = XFBType.LocalFile.CreateLocalFile(fbbParent, FileLocation,
                  fbbParent.CreateString(FileName ?? ""),
                  fbbParent.CreateString(FilePath ?? ""),
                  fbbParent.CreateString(ResourceGroup ?? ""));
            
            Offset<XFBType.Material> materialOffset = base.Material.CreateFBData(fbbParent).TypeSafeOffset;

            XFBType.MeshPlane.StartMeshPlane(fbbParent);
            XFBType.MeshPlane.AddMaterial(fbbParent, materialOffset);
            XFBType.MeshPlane.AddConstant(fbbParent, constant);
            XFBType.MeshPlane.AddHeight(fbbParent, height);
            XFBType.MeshPlane.AddNormal(fbbParent, XFBType.Vec3f.CreateVec3f(fbbParent, normal.X, normal.Y, normal.Z));
            XFBType.MeshPlane.AddNormals(fbbParent, normals);
            XFBType.MeshPlane.AddNumTexCoordSets(fbbParent, numTexCoordSets);
            XFBType.MeshPlane.AddUpVector(fbbParent, XFBType.Vec3f.CreateVec3f(fbbParent, upVector.X, upVector.Y, upVector.Z));
            XFBType.MeshPlane.AddWidth(fbbParent, width);
            XFBType.MeshPlane.AddXsegments(fbbParent, xsegments);
            XFBType.MeshPlane.AddXTile(fbbParent, xTile);
            XFBType.MeshPlane.AddYsegments(fbbParent, ysegments);
            XFBType.MeshPlane.AddYTile(fbbParent, yTile);
            var planeOffset = XFBType.MeshPlane.EndMeshPlane(fbbParent);

            // int soundoffset = XFBType.Sound.CreateSound(fbb, fbb.CreateString(m_Name), fbb.CreateString(m_FileName), fbb.CreateString(m_RessGrp));
            fbbParent.Finish(planeOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = planeOffset.Value, Fbb = fbbParent };//bytebuffer
        }

        #endregion
    }

}
