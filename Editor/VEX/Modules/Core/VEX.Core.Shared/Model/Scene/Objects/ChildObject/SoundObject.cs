using FlatBuffers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using VEX.Core.Shared.Interface.DAL;
using VEX.Core.Shared.Interface.Services;
using VEX.Interface.DAL;
using VEX.Model.Scene.Model.Objects.FBufferObject;

namespace VEX.Model.Scene.Model.Objects.ObjectData
{
    [DataContract]
    public class SoundObject : LocalFile, IFBObject
    {
        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public override void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);

            var test = XFBType.MeshFile.GetRootAsMeshFile(byteBuffer); // read 
        }

        /// <summary>
        /// resets the flatbufferbuilder
        /// </summary>
        /// <returns>byte data</returns>
        public override FBNetData CreateFBData(FlatBufferBuilder fbbParent = null, IFBObject child = null)
        {
            if (fbbParent == null)
                fbbParent = new FlatBufferBuilder(1);

            var localFileOffset = XFBType.LocalFile.CreateLocalFile(fbbParent, FileLocation,
                fbbParent.CreateString(FileName),
                fbbParent.CreateString(FilePath),
                fbbParent.CreateString(ResourceGroup ?? ""));

            VectorOffset materialOffset = new VectorOffset();
            //if (Materials.Any())
            //{
            //    List<int> matOffsets = new List<int>();
            //    foreach (var material in m_Materials)
            //    {
            //        var localMaterialFileOffset = XFBType.LocalFile.CreateLocalFile(fbbParent, FileLocation,
            //        fbbParent.CreateString(FileName),
            //        fbbParent.CreateString(FilePath),
            //        fbbParent.CreateString(ResourceGroup ?? ""));

            //        matOffsets.Add(XFBType.Material.CreateMaterial(fbbParent, localMaterialFileOffset).Value);
            //    }

            //    XFBType.MeshFile.StartMaterialsVector(fbbParent, m_Materials.Count);
            //    foreach (var material in matOffsets)
            //        fbbParent.AddOffset(material);
            //    materialOffset = fbbParent.EndVector();
            //}

            XFBType.MeshFile.StartMeshFile(fbbParent);

            XFBType.MeshFile.AddFile(fbbParent, localFileOffset);
          //  XFBType.MeshFile.AddMaterials(fbbParent, materialOffset);

            var meshFileOffset = XFBType.MeshFile.EndMeshFile(fbbParent);

            fbbParent.Finish(meshFileOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = meshFileOffset.Value, Fbb = fbbParent }; //bytebuffer
        }       
    }
}
