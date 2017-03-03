#region License

//The MIT License (MIT)

//Copyright (c) 2014 Konrad Huber

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#endregion

using System;
using System.ComponentModel;
using FlatBuffers;
using Microsoft.Practices.Unity;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using VEF.Utils;
using VEF.Interfaces.Services;
using VEX.Interface.Scene.Services;
using VEX.Core.Shared.Interface.Services;
using VEX.Interface.DAL;
using System.Xml.Serialization;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using System.Runtime.Serialization;
using VEX.Core.Shared.Interface.DAL;
using VEX.Service.Scene;
using VEF;
using VEX.Core.Model.Services;
using System.Collections.Generic;

namespace VEX.Model.Scene.Model.Objects
{
    /// <summary>
    /// class represents a physics object on view
    /// </summary>
    [DataContract]
    public class PhysicObject : ViewModelBase
    {
        private FB_Physics m_Physics_FBData;
        private ILoggerService m_Logger;
        
        private short m_colMask;
        private XFBType.PhysicsType m_type;
        private uint m_mode;
        private XFBType.PhysicsShape m_shape;
        private float m_mass;
        private float m_margin;
        private float m_radius;
        private float m_angularDamp;
        private float m_linearDamp;
        private float m_formFactor;
        private float m_minVel;
        private float m_maxVel;
        private float m_restitution;
        private float m_friction;
        private short m_colGroupMask;
        private float m_charStepHeight;
        private float m_charJumpSpeed;
        private float m_charFallSpeed;
        private bool m_parentIsNode;

        private Vector3 m_Offset;
        private Vector3 m_size;
        private Vector3 m_scale;
        private string m_AttachToBone;


        [DataMember]
        public IFBObject Parent { get; set; }

        //  [Editor(typeof(Module.Properties.Types.Vector3Editor), typeof(Module.Properties.Types.Vector3Editor))]
        [DataMember]
        [ExpandableObject]
        public Vector3 Offset
        {
            get { return m_Offset; }
            set
            {
                value.PropertyChanged += new PropertyChangedEventHandler(VectorChanged);
                
                m_Offset = value;
                RaisePropertyChanged("Offset");
            }
        }

        public void VectorChanged(object sender, PropertyChangedEventArgs e)
        {
            SendToSocketServer();
        }

        private void SendToSocketServer()
        {
            if (Parent == null)
                return;

            var entity = (((Parent as FB_Physics).Parent as PhysicsComponent).Parent as EntityX);
            entity.SendToSocket(entity.FB_Entity, NetMsg.Data.Entity, new System.Collections.Generic.List<Type>() { typeof(PhysicsComponent) });
        }

        //  [Editor(typeof(Module.Properties.Types.Vector3Editor), typeof(Module.Properties.Types.Vector3Editor))]
        [DataMember]
        [ExpandableObject]
        public Vector3 Scale
        {
            get { return m_scale; }
            set
            {
                value.PropertyChanged += new PropertyChangedEventHandler(VectorChanged);
                m_scale = value;
                RaisePropertyChanged("Scale");
            }
        }

        //  [Editor(typeof(Module.Properties.Types.Vector3Editor), typeof(Module.Properties.Types.Vector3Editor))]
        [DataMember]
        [ExpandableObject]
        public Vector3 Size
        {
            get { return m_size; }
            set
            {
                value.PropertyChanged += new PropertyChangedEventHandler(VectorChanged);
                m_size = value;
                RaisePropertyChanged("Size");
            }
        }

        [DataMember]
        public ushort Id { get; set; }

        [DataMember]
        public bool ParentIsNode { get { return m_parentIsNode; } set { m_parentIsNode = value;  SendToSocketServer();  } }

        [DataMember]
        public string AttachToBone { get { return m_AttachToBone; } set { m_AttachToBone = value; SendToSocketServer(); } }

        [DataMember]
        public short colMask { get { return m_colMask; } set { m_colMask = value; SendToSocketServer(); } }

        [DataMember]
        public XFBType.PhysicsType type { get { return m_type; } set { m_type = value; SendToSocketServer(); } }

        [DataMember]
        public uint mode { get { return m_mode; } set { m_mode = value; SendToSocketServer(); } }

        [DataMember]
        public XFBType.PhysicsShape shape { get { return m_shape; } set { m_shape = value; SendToSocketServer(); } }

        [DataMember]
        public float mass { get { return m_mass; } set { m_mass = value; SendToSocketServer(); } }

        [DataMember]
        public float margin { get { return m_margin; } set { m_margin = value; SendToSocketServer(); } }

        [DataMember]
        public float radius { get { return m_radius; } set { m_radius = value; SendToSocketServer(); } }

        [DataMember]
        public float angularDamp { get { return m_angularDamp; } set { m_angularDamp = value; SendToSocketServer(); } }

        [DataMember]
        public float linearDamp { get { return m_linearDamp; } set { m_linearDamp = value; SendToSocketServer(); } }

        [DataMember]
        public float formFactor { get { return m_formFactor; } set { m_formFactor = value; SendToSocketServer(); } }

        [DataMember]
        public float minVel { get { return m_minVel; } set { m_minVel = value; SendToSocketServer(); } }

        [DataMember]
        public float maxVel { get { return m_maxVel; } set { m_maxVel = value; SendToSocketServer(); } }

        [DataMember]
        public float restitution { get { return m_restitution; } set { m_restitution = value; SendToSocketServer(); } }

        [DataMember]
        public float friction { get { return m_friction; } set { m_friction = value; SendToSocketServer(); } }

        [DataMember]
        public short colGroupMask { get { return m_colGroupMask; } set { m_colGroupMask = value; SendToSocketServer(); } }

        [DataMember]
        public float charStepHeight { get { return m_charStepHeight; } set { m_charStepHeight = value; SendToSocketServer(); } }

        [DataMember]
        public float charJumpSpeed { get { return m_charJumpSpeed; } set { m_charJumpSpeed = value; SendToSocketServer(); } }

        [DataMember]
        public float charFallSpeed { get { return m_charFallSpeed; } set { m_charFallSpeed = value; SendToSocketServer(); } }


        public PhysicObject()
        {
            m_Physics_FBData = new FB_Physics();
            m_Offset = new Vector3();
            m_size = new Vector3();
            m_scale = new Vector3();
        }
    }
}
