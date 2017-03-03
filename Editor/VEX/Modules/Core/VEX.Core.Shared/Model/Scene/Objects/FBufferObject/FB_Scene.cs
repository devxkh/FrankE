using FlatBuffers;
using System;
using System.Xml.Serialization;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using Microsoft.Practices.Unity;
using System.ComponentModel;
using VEX.Interface.DAL;
using VEX.Interface.Scene;
using System.Runtime.Serialization;

namespace VEX.Model.Scene.Model.Objects
{
    [DataContract]
    public class FB_Scene : IFBObject 
    {
        private XFBType.Scene m_FBData = new XFBType.Scene();

        #region sceneData
        
        #endregion

        #region Properties

        [DataMember]
        public object Parent { get; set; }

            
        #endregion
  
        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);

            m_FBData = XFBType.Scene.GetRootAsScene(byteBuffer); // read 
          //  XFBType.Colour colour = m_FBData.ColourAmbient;

       //     m_ColourAmbient = System.Windows.Media.Color.FromScRgb(colour.A, colour.R, colour.G, colour.B);

            //ByteBuffer byteBuffer2 = new ByteBuffer(fbData);
            //var m_FBDataNOT = XFBType.Scene.GetRootAsScene(byteBuffer2); // read      
            //XFBType.Colour colourNOT = m_FBDataNOT.ColourAmbient();
            //m_ColourAmbient = System.Windows.Media.Color.FromScRgb(colourNOT.A(), colourNOT.R(), colourNOT.G(), colourNOT.B());
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbb = null, IFBObject child = null)
        {
            if (fbb == null)
                fbb = new FlatBufferBuilder(1);

           
           XFBType.Scene.StartScene(fbb);
            var finishOffset = XFBType.Scene.EndScene(fbb);
            fbb.Finish(finishOffset.Value); //!!!!! important ..

            // Dump to output directory so we can inspect later, if needed
            //using (var ms = new MemoryStream(fbb.DataBuffer().Data))//, fbb.DataBuffer().position(), fbb.Offset()))
            //{
            //    var data = ms.ToArray();
            //FBType.Sound test = FBType.Sound.GetRootAsSound(fbb.DataBuffer(), fbb.DataBuffer().position());
            //    string gg = test.FileName(); // funtzt 
            //  File.WriteAllBytes(@"Resources/monsterdata_cstest.mon", data);
            //   }
            
            return new FBNetData() { _fbData = fbb.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbb }; //bytebuffer
            //--------------------------------------
        }
    }
}
