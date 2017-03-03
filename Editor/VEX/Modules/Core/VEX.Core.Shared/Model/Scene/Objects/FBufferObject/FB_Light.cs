using FlatBuffers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.Serialization;
using System.Xml.Serialization;
using VEF;
using VEF.Utils;
using VEF.View.Types;
using VEX.Core.Model.Services;
using VEX.Interface.DAL;
using VEX.Interface.Scene.Services;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using VEX.Service.Scene;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using XFBType;

namespace VEX.Model.Scene.Model.Objects
{
    [DataContract]
    public class Ambient : ViewModelBase
    {
        private System.Windows.Media.Color m_LowerHemisphere;
        private System.Windows.Media.Color m_UpperHemisphere;

        public Ambient()
        {
            m_LowerHemisphere = new System.Windows.Media.Color();
            m_UpperHemisphere = new System.Windows.Media.Color();
        }

        [DataMember]
        public System.Windows.Media.Color LowerHemisphere { get { return m_LowerHemisphere; } set { m_LowerHemisphere = value; } } //public setter needed for serialization

        [DataMember]
        public System.Windows.Media.Color UpperHemisphere { get { return m_UpperHemisphere; } set { m_UpperHemisphere = value; } } //public setter needed for serialization

        [DataMember]
        public bool UserAmbient { get; set; }
    }

    [DataContract]
    public class Attenuation : ViewModelBase
    {
        private float m_range;
        private float m_constant;
        private float m_linear;
        private float m_quadratic;

        [DataMember]
        public float range
        {
            get { return m_range; }
            set
            {
                m_range = value;
                RaisePropertyChanged("range");
            }
        }
        [DataMember]
        public float constant
        {
            get { return m_constant; }
            set
            {
                m_constant = value;
                RaisePropertyChanged("constant");
            }
        }
        [DataMember]
        public float linear
        {
            get { return m_linear; }
            set
            {
                m_linear = value;
                RaisePropertyChanged("linear");
            }
        }
        [DataMember]
        public float quadratic
        {
            get { return m_quadratic; }
            set
            {
                m_quadratic = value;
                RaisePropertyChanged("quadratic");
            }
        }
    }

    [DataContract]
    public class FB_Light : ViewModelBase, IFBObject //, INetMsg
    {
        private XFBType.Light m_FBData = new XFBType.Light();
        private float m_PowerScale;
        private bool m_CastShadows;
        private bool m_UseInstantRadiosity;
        private float m_IRVplThreshold;
        private Attenuation m_Attenuation;
        private Vector3 m_DirectionVector;
        private LightType m_LightType;
        private System.Windows.Media.Color m_ColorDiffuse;
        private System.Windows.Media.Color m_ColorSpecular;

        #region Properties

        //  public NetMsg.Data FBMsgType { get { return NetMsg.Data.NONE; } }

        [DataMember]
        public float PowerScale
        {
            get { return m_PowerScale; }
            set
            {
                m_PowerScale = value;
                SendUpdateToServer<LightComponent>();
            }
        }

        [DataMember]
        public bool CastShadows
        {
            get { return m_CastShadows; }
            set
            {
                m_CastShadows = value;
                SendUpdateToServer<LightComponent>();
            }
        }


        [DataMember]
        public bool UseInstantRadiosity
        {
            get { return m_UseInstantRadiosity; }
            set
            {
                m_UseInstantRadiosity = value;
                SendUpdateToServer<LightComponent>();
            }
        }

        [DataMember]
        public float IRVplThreshold
        {
            get { return m_IRVplThreshold; }
            set
            {
                m_IRVplThreshold = value;
                SendUpdateToServer<LightComponent>();
            }
        }

        [DataMember]
        [ExpandableObject]
        public Attenuation Attenuation
        {
            get
            {
                return m_Attenuation;
            }
            set
            {
                PropertyChangedEventHandler eh = new PropertyChangedEventHandler(ChildChanged);
                if (m_Attenuation != null)
                {
                    m_Attenuation.PropertyChanged -= eh;
                }

                m_Attenuation = value;
                m_Attenuation.PropertyChanged += eh;
            }
        }

        [DataMember]
        public XFBType.LightType LightType
        {
            get
            { return m_LightType; }
            set
            {
                m_LightType = value;
                SendUpdateToServer<LightComponent>();
            }
        }

        [DataMember]
        [ExpandableObject]
        public Vector3 DirectionVector
        {
            get
            {
                return m_DirectionVector;
            }
            set
            {
                PropertyChangedEventHandler eh = new PropertyChangedEventHandler(ChildChanged);
                if (m_DirectionVector != null)
                {
                    m_DirectionVector.PropertyChanged -= eh;
                }

                m_DirectionVector = value;
                m_DirectionVector.PropertyChanged += eh;
            }
        }

        public void ChildChanged(object sender, PropertyChangedEventArgs e)
        {
            SendUpdateToServer<LightComponent>();
        }

        private void SendUpdateToServer<T>()
        {
            var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;

            if (Parent == null)
                return;

            var body = Parent as LightComponent;
            EntityX entity = body.Parent as EntityX;
            if (entity != null)
            {
                List<Type> types = new List<Type>() { typeof(T) };

                FlatBufferBuilder fbb = new FlatBufferBuilder(4);
                if (entity.FB_Entity == null)
                    return;

                var fbEntity = entity.FB_Entity.CreateFBData(types, fbb);

                var mon = NetMsg.MessageRoot.CreateMessageRoot(fbb, entity.NetID, 1, NetMsg.Data.Entity, fbEntity._offset);
                NetMsg.MessageRoot.FinishMessageRootBuffer(fbb, mon);

                _SocketServerManager.Client.SendToServer(0, fbb.SizedByteArray(), ENet.PacketFlags.Reliable);
            }
        }

        [DataMember]
        public System.Windows.Media.Color ColorDiffuse
        {
            get { return m_ColorDiffuse; }
            set
            {
                m_ColorDiffuse = value;
                SendUpdateToServer<LightComponent>();
            }
        }

        [DataMember]
        public System.Windows.Media.Color ColorSpecular
        {
            get
            {
                return m_ColorSpecular;
            }

            set
            {
                m_ColorSpecular = value;
                SendUpdateToServer<LightComponent>();
            }
        }

        [DataMember]
        [ExpandableObject]
        public Ambient Ambient { get; set; }

        [DataMember]
        public object Parent { get; set; }

        #endregion

        public FB_Light()
        {
            DirectionVector = new Vector3();
            Ambient = new Ambient();
            m_Attenuation = new Attenuation();
        }

        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);
            var tmpFBData = XFBType.Light.GetRootAsLight(byteBuffer); // read 
            var test = tmpFBData.ColourDiffuse;
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbb = null, IFBObject child = null)
        {
            if (fbb == null)
                fbb = new FlatBufferBuilder(1);

            Offset<AmbientLight> ambientlight = new Offset<AmbientLight>();

            if (Ambient.UserAmbient)
            {
                XFBType.AmbientLight.StartAmbientLight(fbb);
                XFBType.AmbientLight.AddLowerHemisphere(fbb, XFBType.Colour.CreateColour(fbb, Ambient.LowerHemisphere.ScR, Ambient.LowerHemisphere.ScG, Ambient.LowerHemisphere.ScB, Ambient.LowerHemisphere.ScA));
                XFBType.AmbientLight.AddUpperHemisphere(fbb, XFBType.Colour.CreateColour(fbb, Ambient.UpperHemisphere.ScR, Ambient.UpperHemisphere.ScG, Ambient.UpperHemisphere.ScB, Ambient.UpperHemisphere.ScA));
                XFBType.AmbientLight.AddHemisphereDir(fbb, XFBType.Vec3f.CreateVec3f(fbb, 0, -1, 0));
                XFBType.AmbientLight.AddEnvmapScale(fbb, 1);
                ambientlight = XFBType.AmbientLight.EndAmbientLight(fbb);
            }

            XFBType.Light.StartLight(fbb);
            XFBType.Light.AddColourDiffuse(fbb, XFBType.Colour.CreateColour(fbb, ColorDiffuse.ScR, ColorDiffuse.ScG, ColorDiffuse.ScB, ColorDiffuse.ScA));
            XFBType.Light.AddColourSpecular(fbb, XFBType.Colour.CreateColour(fbb, ColorSpecular.ScR, ColorSpecular.ScG, ColorSpecular.ScB, ColorSpecular.ScA));
            XFBType.Light.AddDirectionVector(fbb, XFBType.Vec3f.CreateVec3f(fbb, DirectionVector.X, DirectionVector.Y, DirectionVector.Z));
            XFBType.Light.AddLightType(fbb, LightType);
            XFBType.Light.AddAttenuation(fbb, XFBType.Attenuation.CreateAttenuation(fbb, Attenuation.range, Attenuation.constant, Attenuation.linear, Attenuation.quadratic));
            XFBType.Light.AddPowerScale(fbb, PowerScale);
            XFBType.Light.AddCastShadows(fbb,CastShadows);
            XFBType.Light.AddUseInstantRadiosity(fbb, UseInstantRadiosity);
            XFBType.Light.AddIRVplThreshold(fbb, IRVplThreshold);


            if (Ambient.UserAmbient)
                XFBType.Light.AddAmbientLight(fbb, ambientlight);

            var finishOffset = XFBType.Light.EndLight(fbb);

            fbb.Finish(finishOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbb.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbb }; //bytebuffer
        }
    }
}
