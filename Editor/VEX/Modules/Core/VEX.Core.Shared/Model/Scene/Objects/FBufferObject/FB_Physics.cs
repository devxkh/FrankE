using FlatBuffers;
using System;
using System.Collections.Generic;
using System.Xml.Serialization;
using VEX.Interface.DAL;
using VEX.Interface.Scene.Services;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using System.Linq;
using System.ComponentModel;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Runtime.Serialization;

namespace VEX.Model.Scene.Model.Objects
{
    [KnownType(typeof(PhysicObject))]
    [DataContract(IsReference = true)]
    public class FB_Physics : IFBObject//, INetMsg
    {
        private XFBType.PhysicsComponent m_FBData = new XFBType.PhysicsComponent();

        //   public NetMsg.Data FBMsgType { get { return NetMsg.Data.NONE; } }

        private ObservableCollection<PhysicObject> m_Physics;

        [DataMember]
        [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        public ObservableCollection<PhysicObject> Physics
        {
            get { return m_Physics; }
            set
            {
                if (m_Physics == null)
                    value.CollectionChanged += this.OnCollectionChanged;

                m_Physics = value;
            }
        }

        void OnCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null)
            {
                foreach (var newItem in e.NewItems)
                {
                    var physObj = newItem as PhysicObject;
                    if (physObj != null)
                    {
                        physObj.Parent = this;
                        physObj.Id = (ushort)m_Physics.Count();
                    }
                }
            }
        }

        public FB_Physics()
        {
            m_Physics = new ObservableCollection<PhysicObject>();
            m_Physics.CollectionChanged += this.OnCollectionChanged;
        }

        #region PhysicsData



        #endregion

        #region Properties

        [DataMember]
        public object Parent { get; set; }

        //public string AbsPathToXML { get; set; }
        //public string RelPathToXML { get; set; }

        //public Vector3 scale { get { return m_scale; } set { m_scale = FB_Helper.UpdateSelectedObject(this, m_scale, value); } }
        //public Vector3 size { get { return m_size; } set { m_size = FB_Helper.UpdateSelectedObject(this, m_size, value); } }
        //public bool parentIsNode { get { return m_parentIsNode; } set { m_parentIsNode = FB_Helper.UpdateSelectedObject(this, m_parentIsNode, value); } }
        
        //public Vector3 Offset { get { return m_Offset; } set { m_Offset = FB_Helper.UpdateSelectedObject(this, m_Offset, value); } }
      
        //public string AttachToBone { get { return m_AttachToBone; } set { m_AttachToBone = FB_Helper.UpdateSelectedObject(this, m_AttachToBone, value); } }

        //public short colMask { get { return m_colMask; } set { m_colMask = FB_Helper.UpdateSelectedObject(this, m_colMask, value); } }
        //public XFBType.PhysicsType type { get { return m_type; } set { m_type = FB_Helper.UpdateSelectedObject(this, m_type, value); } }
        //public uint mode { get { return m_mode; } set { m_mode = FB_Helper.UpdateSelectedObject(this, m_mode, value); } }
        //public XFBType.PhysicsShape shape { get { return m_shape; } set { m_shape = FB_Helper.UpdateSelectedObject(this, m_shape, value); } }
        //public float mass { get { return m_mass; } set { m_mass = FB_Helper.UpdateSelectedObject(this, m_mass, value); } }
        //public float margin { get { return m_margin; } set { m_margin = FB_Helper.UpdateSelectedObject(this, m_margin, value); } }
        //public float radius { get { return m_radius; } set { m_radius = FB_Helper.UpdateSelectedObject(this, m_radius, value); } }
        //public float angularDamp { get { return m_angularDamp; } set { m_angularDamp = FB_Helper.UpdateSelectedObject(this, m_angularDamp, value); } }
        //public float linearDamp { get { return m_linearDamp; } set { m_linearDamp = FB_Helper.UpdateSelectedObject(this, m_linearDamp, value); } }
        //public float formFactor { get { return m_formFactor; } set { m_formFactor = FB_Helper.UpdateSelectedObject(this, m_formFactor, value); } }
        //public float minVel { get { return m_minVel; } set { m_minVel = FB_Helper.UpdateSelectedObject(this, m_minVel, value); } }
        //public float maxVel { get { return m_maxVel; } set { m_maxVel = FB_Helper.UpdateSelectedObject(this, m_maxVel, value); } }
        //public float restitution { get { return m_restitution; } set { m_restitution = FB_Helper.UpdateSelectedObject(this, m_restitution, value); } }
        //public float friction { get { return m_friction; } set { m_friction = FB_Helper.UpdateSelectedObject(this, m_friction, value); } }
        //public short colGroupMask { get { return m_colGroupMask; } set { m_colGroupMask = FB_Helper.UpdateSelectedObject(this, m_colGroupMask, value); ; } }
        //public float charStepHeight { get { return m_charStepHeight; } set { m_charStepHeight = FB_Helper.UpdateSelectedObject(this, m_charStepHeight, value); } }
        //public float charJumpSpeed { get { return m_charJumpSpeed; } set { m_charJumpSpeed = FB_Helper.UpdateSelectedObject(this, m_charJumpSpeed, value); } }
        //public float charFallSpeed { get { return m_charFallSpeed; } set { m_charFallSpeed = FB_Helper.UpdateSelectedObject(this, m_charFallSpeed, value); } }

        #endregion

        #region IFBObject

        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);

            m_FBData = XFBType.PhysicsComponent.GetRootAsPhysicsComponent(byteBuffer); // read 

        }

        public FBNetData CreateFBData(FlatBufferBuilder fbbParent = null, IFBObject child = null)
        {
            if (fbbParent == null)
                fbbParent = new FlatBufferBuilder(1);



            VectorOffset physicsOffset = new VectorOffset();
            if (m_Physics.Any())
            {
                List<int> physOffsets = new List<int>();
                foreach (var physic in m_Physics)
                {
                    StringOffset boneParentOS = new StringOffset();
                    if (physic.AttachToBone != null)
                        boneParentOS = fbbParent.CreateString(physic.AttachToBone);

                    XFBType.PhysicsObject.StartPhysicsObject(fbbParent);
                    XFBType.PhysicsObject.AddId(fbbParent, physic.Id);
                    XFBType.PhysicsObject.AddColMask(fbbParent, physic.colMask);
                    XFBType.PhysicsObject.AddType(fbbParent, physic.type);
                    XFBType.PhysicsObject.AddMode(fbbParent, physic.mode);
                    XFBType.PhysicsObject.AddShape(fbbParent, physic.shape);
                    XFBType.PhysicsObject.AddMass(fbbParent, physic.mass);
                    XFBType.PhysicsObject.AddMargin(fbbParent, physic.margin);
                    XFBType.PhysicsObject.AddRadius(fbbParent, physic.radius);
                    XFBType.PhysicsObject.AddAngularDamp(fbbParent, physic.angularDamp);
                    XFBType.PhysicsObject.AddLinearDamp(fbbParent, physic.linearDamp);
                    XFBType.PhysicsObject.AddFormFactor(fbbParent, physic.formFactor);
                    XFBType.PhysicsObject.AddMinVel(fbbParent, physic.minVel);
                    XFBType.PhysicsObject.AddMaxVel(fbbParent, physic.maxVel);
                    XFBType.PhysicsObject.AddRestitution(fbbParent, physic.restitution);
                    XFBType.PhysicsObject.AddFriction(fbbParent, physic.friction);
                    XFBType.PhysicsObject.AddColGroupMask(fbbParent, physic.colGroupMask);
                    XFBType.PhysicsObject.AddCharStepHeight(fbbParent, physic.charStepHeight);
                    XFBType.PhysicsObject.AddCharJumpSpeed(fbbParent, physic.charJumpSpeed);
                    XFBType.PhysicsObject.AddCharFallSpeed(fbbParent, physic.charFallSpeed);

                    //Structures are always stored inline, they need to be created right where they're used
                    XFBType.PhysicsObject.AddOffset(fbbParent, XFBType.Vec3f.CreateVec3f(fbbParent, physic.Offset.X, physic.Offset.Y, physic.Offset.Z));
                    XFBType.PhysicsObject.AddSize(fbbParent, XFBType.Vec3f.CreateVec3f(fbbParent, physic.Size.X, physic.Size.Y, physic.Size.Z));
                    XFBType.PhysicsObject.AddScale(fbbParent, XFBType.Vec3f.CreateVec3f(fbbParent, physic.Scale.X, physic.Scale.Y, physic.Scale.Z));

                    XFBType.PhysicsObject.AddParentIsNode(fbbParent, physic.ParentIsNode);

                    if (physic.AttachToBone != null)
                        XFBType.PhysicsObject.AddBoneparent(fbbParent, boneParentOS);

                    physOffsets.Add(XFBType.PhysicsObject.EndPhysicsObject(fbbParent).Value);
                }


                XFBType.PhysicsComponent.StartPhysicsVector(fbbParent, m_Physics.Count);
                foreach (var physic in physOffsets)
                    fbbParent.AddOffset(physic);
                physicsOffset = fbbParent.EndVector();
            }


            XFBType.PhysicsComponent.StartPhysicsComponent(fbbParent);

            if (m_Physics.Any()) XFBType.PhysicsComponent.AddPhysics(fbbParent, physicsOffset);

            var finishOffset = XFBType.PhysicsComponent.EndPhysicsComponent(fbbParent);

            fbbParent.Finish(finishOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbbParent }; //bytebuffer           
        }

        #endregion
    }
}
