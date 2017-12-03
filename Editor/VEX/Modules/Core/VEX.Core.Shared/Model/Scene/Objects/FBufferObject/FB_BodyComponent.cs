using System;
using System.Windows;
using FlatBuffers;
using System.Xml.Serialization;
using VEX.Interface.DAL;
using VEX.Interface.Scene.Services;
using System.Runtime.Serialization;
using System.ComponentModel;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using VEX.Core.Model.Services;
using VEX.Service.Scene;
using System.Collections.Generic;
using VEF;
using VEF.View.Types;

namespace VEX.Model.Scene.Model.Objects.FBufferObject
{
    [DataContract]
    public class FB_BodyComponent : IFBObject//, INetMsg
    {
        #region private members

        private XFBType.BodyComponent m_FBData = new XFBType.BodyComponent();

        private Quaternion m_Rotation;
        private Vector3 m_Location;
        private Vector3 m_Scale;
        private bool m_IsVisible;
        private bool m_IsEnabled;

        #endregion

        #region Properties

        //   public NetMsg.Data FBMsgType { get { return NetMsg.Data.Node; } }

        [DataMember]
        public object Parent { get; set; }

        [DataMember]
        public bool IsVisible { get { return m_IsVisible; } set { m_IsVisible = value; SendToSocketServer(); } }

        [DataMember]
        public bool IsEnabled { get { return m_IsEnabled; } set { m_IsEnabled = value; SendToSocketServer(); } }
        
        [DataMember]
        [ExpandableObject]
        public Quaternion Rotation
        {
            get { return m_Rotation; }
            set
            {
                value.PropertyChanged += new PropertyChangedEventHandler(ChildChanged);
                m_Rotation = value;
            }
        }

        [DataMember]
        //  [Editor(typeof(Vector3Editor), typeof(Vector3Editor))]
        [ExpandableObject]
        public Vector3 Location
        {
            get { return m_Location; }
            set
            {
                value.PropertyChanged += new PropertyChangedEventHandler(ChildChanged);

                m_Location = value;
            }
        }

        public void ChildChanged(object sender, PropertyChangedEventArgs e)
        {
            SendToSocketServer();
        }

        private void SendToSocketServer()
        {
            if (Parent == null)
                return;

            var entity = ((Parent as BodyComponent).Parent as EntityX);
            entity.SendToSocket(entity.FB_Entity, NetMsg.Data.Entity, new System.Collections.Generic.List<Type>() { typeof(BodyComponent) });
        }


        [DataMember]
        [ExpandableObject]
        public Vector3 Scale
        {
            get { return m_Scale; }
            set
            {
                value.PropertyChanged += new PropertyChangedEventHandler(ChildChanged);
                m_Scale = value;
            }
        }

        #endregion

        public FB_BodyComponent()
        {
            Rotation = new Quaternion() { W = 1, X = 0, Y = 0, Z = 0 };
            Location = new Vector3();
            Scale = new Vector3() { X = 1, Y = 1, Z = 1 };
        }

        #region Methods 

        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);
            m_FBData = XFBType.BodyComponent.GetRootAsBodyComponent(byteBuffer); // read 

            m_Rotation = new Quaternion() { W = m_FBData.Rotation.W, X = m_FBData.Rotation.X, Y = m_FBData.Rotation.Y, Z = m_FBData.Rotation.Z };
            m_Location = new Vector3() { X = m_FBData.Position.X, Y = m_FBData.Position.Y, Z = m_FBData.Position.Z };
            m_Scale = new Vector3() { X = m_FBData.Scale.X, Y = m_FBData.Scale.Y, Z = m_FBData.Scale.Z };
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbb = null, IFBObject child = null)
        {
            if (fbb == null)
                fbb = new FlatBufferBuilder(1);

            XFBType.BodyComponent.StartBodyComponent(fbb);
            //struct must be serialized inline
            XFBType.BodyComponent.AddRotation(fbb, XFBType.Quat4f.CreateQuat4f(fbb, m_Rotation.W, m_Rotation.X, m_Rotation.Y, m_Rotation.Z));
            XFBType.BodyComponent.AddPosition(fbb, XFBType.Vec3f.CreateVec3f(fbb, m_Location.X, m_Location.Y, m_Location.Z));
            XFBType.BodyComponent.AddScale(fbb, XFBType.Vec3f.CreateVec3f(fbb, m_Scale.X, m_Scale.Y, m_Scale.Z));
            XFBType.BodyComponent.AddGroup(fbb, 0);
            XFBType.BodyComponent.AddVisible(fbb, m_IsVisible);
            var finishOffset = XFBType.BodyComponent.EndBodyComponent(fbb);

            fbb.Finish(finishOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbb.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbb }; //bytebuffer
        }

        #endregion
    }
}
