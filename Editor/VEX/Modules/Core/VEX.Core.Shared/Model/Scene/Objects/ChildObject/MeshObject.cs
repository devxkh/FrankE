using System;
using System.ComponentModel;
using Microsoft.Practices.Unity;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using FlatBuffers;
using VEX.Model.Scene.Model.Objects.ChildObject;
using System.Xml.Serialization;
using VEX.Interface.DAL;
using System.Linq;
using VEF.Utils;
using VEX.Core.Shared.Interface.Services;
using System.Runtime.Serialization;
using VEX.Core.Shared.Interface.DAL;
using System.Windows;
using System.Collections.Generic;
using VEX.Model.Scene.Model.Objects.ObjectData;
using System.Collections.Specialized;
using System.Collections.ObjectModel;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace VEX.Model.Scene.Model.Objects
{
    [KnownType(typeof(CubeObject))]
    [KnownType(typeof(PlaneObject))]
    [DataContract]
    public class MeshObject : LocalFile, IFBObject
    {
        #region Properties

       // private ObservableCollection<MaterialObject> m_Materials;
        private MaterialObject m_Material;

        [DataMember]
        [ExpandableObject]
      //  [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        public MaterialObject Material
        {
            get
            {
                if (m_Material == null)
                {
                    m_Material = new MaterialObject();
                    m_Material.Parent = this;
                //    m_Materials = new ObservableCollection<MaterialObject>();
                //    m_Materials.CollectionChanged += this.OnCollectionChanged;
                }
                return m_Material;
            } //set { m_Materials = value; } }

            set
            {
                //  value.CollectionChanged += this.OnCollectionChanged;

                m_Material = value;
                m_Material.Parent = this;
            }
        }

        //void OnCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        //{
        //    if (e.NewItems != null)
        //    {
        //        foreach (var newItem in e.NewItems)
        //        {
        //            (newItem as MaterialObject).Parent = (RenderableComponent)this.Parent;
        //        }
        //    }
        //}

        #endregion

        #region IFBObject


        public MeshObject()
        {
            m_Material = new MaterialObject();
            m_Material.Parent = this;
            //m_Materials = new ObservableCollection<MaterialObject>();
            //m_Materials.CollectionChanged += this.OnCollectionChanged;
        }

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
                fbbParent.CreateString(FileName ?? ""),
                fbbParent.CreateString(FilePath ?? ""),
                fbbParent.CreateString(ResourceGroup ?? ""));

            //VectorOffset materialOffset = new VectorOffset();
            //if (Materials.Any())
            //{
            //    List<int> matOffsets = new List<int>();
            //    foreach (var material in m_Materials)
            //    {
            //        matOffsets.Add(XFBType.Material.CreateMaterial(fbbParent, material.CreateFBData(fbbParent).TypeSafeOffset).Value);
            //    }

            //    XFBType.MeshFile.StartMaterialsVector(fbbParent, m_Materials.Count);
            //    foreach (var material in matOffsets)
            //        fbbParent.AddOffset(material);
            //    materialOffset = fbbParent.EndVector();
            //}

            // Offset<XFBType.Material> materialOffset = XFBType.Material.CreateMaterial(fbbParent, m_Material.CreateFBData(fbbParent).TypeSafeOffset);
            Offset<XFBType.Material> materialOffset = m_Material.CreateFBData(fbbParent).TypeSafeOffset;

            XFBType.MeshFile.StartMeshFile(fbbParent);

            XFBType.MeshFile.AddFile(fbbParent, localFileOffset);
            XFBType.MeshFile.AddMaterial(fbbParent, materialOffset);

            var meshFileOffset = XFBType.MeshFile.EndMeshFile(fbbParent);

            fbbParent.Finish(meshFileOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = meshFileOffset.Value, Fbb = fbbParent }; //bytebuffer
        }

        #endregion
    }
}
