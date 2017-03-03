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
    public class FB_Ability : ViewModelBase, IFBObject //, INetMsg
    {
        private NetMsg.AbilityComponent m_FBData = new NetMsg.AbilityComponent();
        private ushort _id;
        private Vector3 _size;
        private Vector3 _offset;
        private bool _hasPhysics;
        private float _Duration;
        private float _Cooldown;
        private float _Power;
        private XFBType.PhysicsShape _shape;
        private NetMsg.AbilityBehavior _abilityBehavior;

        #region Properties

        [DataMember]
        public NetMsg.AbilityBehavior AbilityBehavior
        {
            get { return _abilityBehavior; }
            set
            {
                _abilityBehavior = value;
                SendUpdateToServer<AbilityComponent>();
            }
        }

        //  public NetMsg.Data FBMsgType { get { return NetMsg.Data.NONE; } }
        [DataMember]
        public float Duration
        {
            get { return _Duration; }
            set
            {
                _Duration = value;
                SendUpdateToServer<AbilityComponent>();
            }
        }

        [DataMember]
        public float Power
        {
            get { return _Power; }
            set
            {
                _Power = value;
                SendUpdateToServer<AbilityComponent>();
            }
        }

        [DataMember]
        public float Cooldown
        {
            get { return _Cooldown; }
            set
            {
                _Cooldown = value;
                SendUpdateToServer<AbilityComponent>();
            }
        }


        [DataMember]
        public XFBType.PhysicsShape Shape
        {
            get { return _shape; }
            set
            {
                _shape = value;
                SendUpdateToServer<AbilityComponent>();
            }
        }

        [DataMember]
        [ExpandableObject]
        public Vector3 Offset
        {
            get
            { return _offset; }
            set
            {
                _offset = value;
                PropertyChangedEventHandler eh = new PropertyChangedEventHandler(ChildChanged);
                if (_offset != null)
                {
                    _offset.PropertyChanged -= eh;
                }

                _offset = value;
                _offset.PropertyChanged += eh;
            }
        }

        [DataMember]
        [ExpandableObject]
        public Vector3 Size
        {
            get
            { return _size; }
            set
            {
                _size = value;
                PropertyChangedEventHandler eh = new PropertyChangedEventHandler(ChildChanged);
                if (_size != null)
                {
                    _size.PropertyChanged -= eh;
                }

                _size = value;
                _size.PropertyChanged += eh;
            }
        }
        
        [DataMember]
        public bool HasPhysics
        {
            get
            {
                return _hasPhysics;
            }
            set
            {
                _hasPhysics = value;
                SendUpdateToServer<AbilityComponent>();
            }
        }

        public void ChildChanged(object sender, PropertyChangedEventArgs e)
        {
            SendUpdateToServer<AbilityComponent>();
        }

        private void SendUpdateToServer<T>()
        {
            var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;

            if (Parent == null)
                return;

            var body = Parent as AbilityComponent;
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
        public object Parent { get; set; }

        #endregion

        public FB_Ability()
        {
            _size = new Vector3();
            _offset = new Vector3();
        }

        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);
            var tmpFBData = NetMsg.AbilityComponent.GetRootAsAbilityComponent(byteBuffer); // read 
            var test = tmpFBData.Offset;
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbb = null, IFBObject child = null)
        {
            if (fbb == null)
                fbb = new FlatBufferBuilder(1);
            
            NetMsg.AbilityComponent.StartAbilityComponent(fbb);
            NetMsg.AbilityComponent.AddHasPhysics(fbb, _hasPhysics);
            NetMsg.AbilityComponent.AddDuration(fbb, _Duration);
            NetMsg.AbilityComponent.AddPower(fbb, _Power);
            NetMsg.AbilityComponent.AddCooldown(fbb, _Cooldown);
            NetMsg.AbilityComponent.AddId(fbb, _id);
            NetMsg.AbilityComponent.AddOffset(fbb, XFBType.Vec3f.CreateVec3f(fbb, _offset.X, _offset.Y, _offset.Z));
            NetMsg.AbilityComponent.AddShape(fbb, _shape);
            NetMsg.AbilityComponent.AddSize(fbb, XFBType.Vec3f.CreateVec3f(fbb, _size.X, _size.Y, _size.Z));
            NetMsg.AbilityComponent.AddAbilityBehavior(fbb, _abilityBehavior);

            var finishOffset = NetMsg.AbilityComponent.EndAbilityComponent(fbb);

            fbb.Finish(finishOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbb.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbb }; //bytebuffer
        }
    }
}
