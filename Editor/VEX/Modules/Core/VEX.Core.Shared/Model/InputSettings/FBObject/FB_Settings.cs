using FlatBuffers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.Serialization;
using System.Text;
using VEF.View.Types;
using VEX.Interface.DAL;

namespace VEX.Core.Shared.Model.InputSettings.FBObject
{
    //[DataContract]
    //public enum FSAA : ushort
    //{
    //    x8,
    //    x16,
    //    x32
    //}

    [DataContract]
    public class FB_Settings
    {
        //       game.settings.dataFolder = "F:\\Projekte\\coop\\XGame\\data\\assets";
        //game.settings.dbDataFolder = "F:\\Projekte\\coop\\XGame\\data\\dbData";
        //game.settings.assetsFolder = "F:\\Projekte\\coop\\XGame\\data\\assets";
        //game.settings.dbFileName = "F:\\Projekte\\coop\\XGame\\data\\dbData.s3db";
        //game.settings.windowTitle =  "Ogre3D v2.0 and SDL 2 - XETUI";

        #region Graphics

        [DataMember]
        public bool Fullscreen { get; set; }

        [DataMember]
        public FBSettings.FSAA FSAA { get; set; }

        #endregion

        //#region ResourceData

        //[Editor(typeof(FolderEditor), typeof(FolderEditor))]
        //[DataMember]
        //public string HLMSDataFolder { get; set; }

        //[Editor(typeof(FolderEditor), typeof(FolderEditor))]
        //[DataMember]
        //public string AssetsFolder { get; set; }

        //[DataMember]
        //[Editor(typeof(FolderEditor), typeof(FolderEditor))]
        //public string DBDataFolder { get; set; }

        //[DataMember]
        //[Editor(typeof(FilePathEditor), typeof(FilePathEditor))]
        //public string DBFileName { get; set; }
        
        //#endregion

        #region mainsettings

        [DataMember]
        public string WindowTitle { get; set; }

        #endregion

        #region Methods 

        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);
            var  tmp = FBSettings.Settings.GetRootAsSettings(byteBuffer); // read 
            var title = tmp.WindowTitle;
            //m_Rotation = new Quaternion() { W = m_FBData.Transform.Rot.W, X = m_FBData.Transform.Rot.X, Y = m_FBData.Transform.Rot.Y, Z = m_FBData.Transform.Rot.Z };
            //m_Location = new Vector3() { X = m_FBData.Transform.Loc.X, Y = m_FBData.Transform.Loc.Y, Z = m_FBData.Transform.Loc.Z };
            //m_Scale = new Vector3() { X = m_FBData.Transform.Scl.X, Y = m_FBData.Transform.Scl.Y, Z = m_FBData.Transform.Scl.Z };
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbb = null, IFBObject child = null)
        {
            if (fbb == null)
                fbb = new FlatBufferBuilder(1);

            var graphics = FBSettings.Graphics.CreateGraphics(fbb,Fullscreen,FSAA);
            //var ressData = FBSettings.ResourceData.CreateResourceData(fbb, fbb.CreateString(HLMSDataFolder ?? ""),
            //                    fbb.CreateString(DBDataFolder ?? ""), fbb.CreateString(AssetsFolder ?? ""), fbb.CreateString(DBFileName ?? ""));

            var windowTitle = fbb.CreateString(WindowTitle ?? "");

            FBSettings.Settings.StartSettings(fbb);
            FBSettings.Settings.AddGraphics(fbb,graphics);
          //  FBSettings.Settings.AddResourceData(fbb, ressData);
            FBSettings.Settings.AddWindowTitle(fbb, windowTitle);

            var finishOffset = FBSettings.Settings.EndSettings(fbb);

            fbb.Finish(finishOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbb.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbb }; //bytebuffer
        }
    }

    #endregion
}
