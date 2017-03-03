using FlatBuffers;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Windows;
using VEF;
using VEX.Core.Model.Services;
using VEX.Core.Shared.Interface.DAL;
using VEX.Core.Shared.Interface.Services;
using VEX.Interface.DAL;
using VEX.Service.Scene;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace VEX.Model.Scene.Model.Objects.ObjectData
{
    [DataContract]
    public class TextureFile : LocalFile
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
        ///  used by Editor Filewatcher Event
        /// </summary>
        /// <param name="localFile"></param>
        /// <returns></returns>
        public override FBNetData CreateFBData(FlatBufferBuilder fbbParent, IFBObject child = null)
        {
            var offset = XFBType.LocalFile.CreateLocalFile(fbbParent, FileLocation,
                     fbbParent.CreateString(FileName ?? ""),
                     fbbParent.CreateString(FilePath ?? ""),
                     fbbParent.CreateString(ResourceGroup ?? ""));
           

            fbbParent.Finish(offset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = offset.Value, Fbb = fbbParent, TypeSafeOffset = offset }; //bytebuffer
        }
    }

    [KnownType("GetKnownTypes")]
    [DataContract]
    public class MaterialObject : LocalFile
    {
        private ObservableCollection<LocalFile> _Textures;

        static IEnumerable<Type> GetKnownTypes()
        {
            return new Type[]
             {
                typeof(TextureFile)
              };
        }

        #region Properties

        [NewItemTypes(new Type[] { typeof(TextureFile) })]
        [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        [DataMember]
        public ObservableCollection<LocalFile> Textures { get
            {
                if (_Textures == null)
                {
                    _Textures = new ObservableCollection<LocalFile>();
                    _Textures.CollectionChanged += this.OnCollectionChanged;
                }
                return _Textures;
            }
            set
            {
                _Textures = value;
                _Textures.CollectionChanged += this.OnCollectionChanged;
            }
        }

        [DataMember]
        public XFBType.TextureType TextureType
        {
            get;set;
        }

        [DataMember]
        public string Name
        {
            get;set;
        }

        #endregion

        public MaterialObject()
        {
            _Textures = new ObservableCollection<LocalFile>();
            _Textures.CollectionChanged += this.OnCollectionChanged;
        }

        void OnCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null)
            {
                foreach (var newItem in e.NewItems)
                {
                    (newItem as LocalFile).Parent = (MeshObject)this.Parent;
                }
            }
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
        ///  used by Editor Filewatcher Event
        /// </summary>
        /// <param name="localFile"></param>
        /// <returns></returns>
        public override FBNetData CreateFBData(FlatBufferBuilder fbbParent, IFBObject child = null)
        {
            var fileOffset = XFBType.LocalFile.CreateLocalFile(fbbParent, FileLocation,
                     fbbParent.CreateString(FileName ?? ""),
                     fbbParent.CreateString(FilePath ?? ""),
                     fbbParent.CreateString(ResourceGroup ?? ""));
            
            VectorOffset texturesOffset = new VectorOffset();
            if (Textures.Count > 0)
            {
                List<int> texturesOffsets = new List<int>();
                foreach (var texture in Textures)
                {
                    texturesOffsets.Add(fbbParent.CreateString(texture.FileName).Value);
                }

                XFBType.Material.StartTexturesVector(fbbParent, Textures.Count);
                foreach (var texture in texturesOffsets)
                    fbbParent.AddOffset(texture);
                texturesOffset = fbbParent.EndVector();
            }

            var name = fbbParent.CreateString(Name ?? "");
            var offset = XFBType.Material.CreateMaterial(fbbParent , fileOffset, texturesOffset, TextureType, name);


            fbbParent.Finish(offset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = offset.Value, Fbb = fbbParent , TypeSafeOffset = offset }; //bytebuffer
        }
    }
}
