using FlatBuffers;
using System;
using System.Windows;
using System.ComponentModel;
using VEX.Interface.DAL;
using System.Runtime.Serialization;
using VEF.Utils;
using System.Collections.Generic;
using VEX.Service.Scene;
using VEX.Core.Model.Services;
using VEF;
using System.Collections.ObjectModel;
using VEX.Interface.Scene.Services;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace VEX.Model.Scene.Model.Objects
{
    [DataContract]
    public class AbilityInfoEditor
    {
        [DataMember]
        public uint AbilityId { get; set; }

        [DataMember]
        public bool Instant { get; set; }

        [DataMember]
        public bool IsAttached { get; set; }
    }

    [DataContract]
    public class FB_Character : ViewModelBase, IFBObject //, INetMsg
    {
        #region private members

        private new NetMsg.CharacterComponent m_FBData = new NetMsg.CharacterComponent();
        private ObservableCollection<AbilityInfoEditor> _abilities;
        private Vector3 m_OffsetPunch;

        #endregion

        #region Properties

        [DataMember]
        public string Name { get; set; }
        [DataMember]
        public float MoveSpeed { get; set; }
        [DataMember]
        public ushort HP { get; set; }
        [DataMember]
        public ushort ResourcePoints { get; set; }

        [DataMember]
        //  [Editor(typeof(Vector3Editor), typeof(Vector3Editor))]
        [ExpandableObject]
        public Vector3 OffsetPunch
        {
            get {

                if (m_OffsetPunch == null)
                    m_OffsetPunch = new Vector3();

                return m_OffsetPunch; }
            set
            {
                value.PropertyChanged += new PropertyChangedEventHandler(ChildChanged);

                m_OffsetPunch = value;
            }
        }


   //     public NetMsg.Data FBMsgType { get { return NetMsg.Data..CharacterComponent; } }
        

        [DataMember]
        public ObservableCollection<AbilityInfoEditor> Abilities
        {
            get
            {
                return _abilities;
            }
            set
            {
                //PropertyChangedEventHandler eh = new PropertyChangedEventHandler(ChildChanged);
                //if (_abilities != null)
                //{
                //    _abilities.PropertyChanged -= eh;
                //}

                _abilities = value;
               // _abilities.PropertyChanged += eh;
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

            var body = Parent as CharacterComponent;
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

        public FB_Character()
        {
            _abilities = new ObservableCollection<AbilityInfoEditor>();
            m_OffsetPunch = new Vector3();
        }

        #region methods

        public new void Read(Byte[] fbData)
        {
            try
            {
                ByteBuffer byteBuffer = new ByteBuffer(fbData);
                m_FBData = NetMsg.CharacterComponent.GetRootAsCharacterComponent(byteBuffer); // read 

               // base.m_FBData = m_FBData.Entitybase;

               // var entbase = m_FBData.Entitybase;
              //  var animinfo = entbase.AnimationInfo;

              //  var len = entbase.MeshesLength;
              //  var lenmat = entbase.MaterialsLength;

              ////  var lensound = entbase.SoundsLength;
              // // var lenphys = entbase.PhysicsLength;

              //  var mat = entbase.GetMaterials(0);
              //  var mat1 = entbase.GetMaterials(1);

            //    var matname = mat.Name;
          //      var matname1 = mat1.Name;

              //  var phyiscs = entbase.GetPhysics(0);
              //  var phyT1 = phyiscs.Boneparent;

              //  var meshes = entbase.GetMeshes(0);
           //     var type = meshes.MeshType;


                //     m_Group = XFBType.Group(); //per node!
            }
            catch (Exception ex)
            {
                MessageBox.Show("error: " + ex.Message);
            }
        }

        public new FBNetData CreateFBData(FlatBufferBuilder fbb = null, IFBObject child = null)
        {
            if (fbb == null)
                fbb = new FlatBufferBuilder(1);

            VectorOffset abilitiesOffset = new VectorOffset();
            if (Abilities.Count > 0)
            {
                List<int> abilitiesOffsets = new List<int>();
                foreach (var ability in Abilities)
                {
                    NetMsg.AbilityInfo.StartAbilityInfo(fbb);
                    NetMsg.AbilityInfo.AddAbilityId(fbb, ability.AbilityId);
                    NetMsg.AbilityInfo.AddInstant(fbb, ability.Instant);
                    NetMsg.AbilityInfo.AddIsAttached(fbb, ability.IsAttached);
                    abilitiesOffsets.Add(NetMsg.AbilityInfo.EndAbilityInfo(fbb).Value);
                }

                NetMsg.CharacterComponent.StartAbilitiesVector(fbb, Abilities.Count);
                foreach (var ability in abilitiesOffsets)
                    fbb.AddOffset(ability);
                abilitiesOffset = fbb.EndVector();
            }

            var name = fbb.CreateString(Name ?? "Unknown");

            NetMsg.CharacterComponent.StartCharacterComponent(fbb);
            
            NetMsg.CharacterComponent.AddName(fbb, name);
            NetMsg.CharacterComponent.AddMoveSpeed(fbb, MoveSpeed );
            NetMsg.CharacterComponent.AddHp(fbb, HP);
            NetMsg.CharacterComponent.AddResourcePoints(fbb, ResourcePoints );
            NetMsg.CharacterComponent.AddOffsetPunch(fbb, XFBType.Vec3f.CreateVec3f(fbb, OffsetPunch.X, OffsetPunch.Y, OffsetPunch.Z));
            NetMsg.CharacterComponent.AddAbilities(fbb, abilitiesOffset);

           var finishOffset = NetMsg.CharacterComponent.EndCharacterComponent(fbb);

            fbb.Finish(finishOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbb.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbb }; //bytebuffer
        }

        #endregion
    }
}
