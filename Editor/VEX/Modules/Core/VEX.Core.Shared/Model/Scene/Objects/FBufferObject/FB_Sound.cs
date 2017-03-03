using FlatBuffers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using VEX.Interface.DAL;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using VEX.Model.Scene.Model.Objects.ObjectData;
using System.Linq;
using System.Collections.Specialized;
using System.Collections.ObjectModel;
using System.Runtime.Serialization;

namespace VEX.Model.Scene.Model.Objects
{
    [DataContract]
    public class FB_SoundModel : IFBObject //, INetMsg
    {
        private XFBType.Sound m_FBData = new XFBType.Sound();
  
        #region sceneData


        #endregion

        #region Properties

        //  public NetMsg.Data FBMsgType { get { return NetMsg.Data.NONE; } }


        private ObservableCollection<SoundObject> m_Sounds;
        [Category("Sound Component")]
        [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        public ObservableCollection<SoundObject> Sounds {
            get {
                if (m_Sounds == null)
                    m_Sounds = new ObservableCollection<SoundObject>();
                return m_Sounds; }
            set { m_Sounds = value; } }

        //void OnCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        //{
        //    if (e.NewItems != null)
        //    {
        //        foreach (var newItem in e.NewItems)
        //        {
        //            var soundObj = newItem as SoundObject;
        //            if (soundObj != null)
        //            {
        //                soundObj.Parent = this;
        //            }
        //        }
        //    }
        //}


        [DataMember]
        public object Parent { get; set; }
        

        #endregion

        public FB_SoundModel()
        {
            m_Sounds = new ObservableCollection<SoundObject>();
      //      m_Sounds.CollectionChanged += this.OnCollectionChanged;
        }
        
        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);

            m_FBData = XFBType.Sound.GetRootAsSound(byteBuffer); // read 
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbbParent = null, IFBObject child = null)
        {
            if (fbbParent == null)
                fbbParent = new FlatBufferBuilder(1);
            
            VectorOffset soundsOffset = new VectorOffset();
            if (Sounds.Any())
            {
                List<int> soundOffsets = new List<int>();
                foreach (var sound in Sounds)
                {
                    var localSoundFileOffset = XFBType.LocalFile.CreateLocalFile(fbbParent, sound.FileLocation,
                      fbbParent.CreateString(sound.FileName),
                      fbbParent.CreateString(sound.FilePath),
                      fbbParent.CreateString(sound.ResourceGroup ?? ""));

                    soundOffsets.Add(XFBType.Sound.CreateSound(fbbParent, localSoundFileOffset).Value);
                }

                XFBType.SoundComponent.StartSoundsVector(fbbParent, Sounds.Count);
                foreach (var sound in soundOffsets)
                    fbbParent.AddOffset(sound);
                soundsOffset = fbbParent.EndVector();
            }

            XFBType.SoundComponent.StartSoundComponent(fbbParent);

            if (Sounds.Any()) XFBType.SoundComponent.AddSounds(fbbParent, soundsOffset);
            
            var finishOffset = XFBType.SoundComponent.EndSoundComponent(fbbParent);

            fbbParent.Finish(finishOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbbParent }; //bytebuffer
        }
    }
}
