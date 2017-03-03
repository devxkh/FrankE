using FlatBuffers;
using System;
using System.Linq;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Windows;
using System.Xml.Serialization;
using VEX.Core.Shared.Service.Scene;
using VEX.Interface.DAL;
using VEX.Service.Scene;
using System.Runtime.Serialization;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using VEX.Core.Shared.ViewModel.Editor.Components;

namespace VEX.Model.Scene.Model.Objects
{
    [KnownType(typeof(ComponentX))]
    [DataContract]
    public class FB_Entity : IFBObject// , INetMsg
    {
        #region private members
        
        private ComponentsList<ComponentX> _Components;

        private NetMsg.Entity m_FBData = new NetMsg.Entity();

        //     public NetMsg.Data FBMsgType { get { return NetMsg.Data.StaticComponent; } }

        #endregion

        #region Properties

        [DataMember]
        [Browsable(false)]
        [ExpandableObject]
        public ComponentsList<ComponentX> Components
        {
            get {
                return _Components;
            }
            set
            {
                if (_Components == null && value != null)
                    value.CollectionChanged += this.OnCollectionChanged;

                _Components = value;
            }
        }

        [DataMember]
        public uint EntityID { get; set; }

        [DataMember]
        public object Parent { get; set; }

        //  public int Group { get { return m_Group; } set { m_Group = FB_Helper.UpdateSelectedObject(this, m_Group, value); } }

        #endregion


        void OnCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null)
            {
                foreach (var newItem in e.NewItems)
                {
                    if((EntityX) this.Parent == null)
                        continue; //an entity has only an id if it's added to a scene

                    (newItem as ComponentX).Parent = (EntityX)this.Parent;

                    if (newItem is BodyComponent && (newItem as ComponentX).Parent.Parent != null)
                    {
                  //      (newItem as BodyComponent).SceneNodeID = (uint)((newItem as ComponentX).Parent.Parent.Entities.Count);
                    }
                }
            }
        }


        public FB_Entity()
        {
            _Components = new ComponentsList<ComponentX>();
            _Components.CollectionChanged += this.OnCollectionChanged;
        }

        #region methods

        public void Read(Byte[] fbData)
        {
            try
            {
                ByteBuffer byteBuffer = new ByteBuffer(fbData);
                m_FBData = NetMsg.Entity.GetRootAsEntity(byteBuffer); // read 
                if(m_FBData.ComponentsLength > 0)
                {
                    for (int i = 0; i < m_FBData.ComponentsLength; i++)
                    {
                        var component = m_FBData.GetComponents(i);
                        if (component.CompType == NetMsg.UComponent.AnimationComponent)
                        {
                            XFBType.AnimationComponent acomp = new XFBType.AnimationComponent();
                            component.GetComp<XFBType.AnimationComponent>(acomp);

                            if (acomp.NodesLength > 0)
                            {
                                for (int j = 0; j < acomp.NodesLength; j++)
                                {
                                    var node = acomp.GetNodes(j);
                                    if (node.NodeType == XFBType.UAnimationNode.AnimationNode)
                                    {
                                        XFBType.AnimationNode animationNode = new XFBType.AnimationNode();
                                        animationNode = node.GetNode<XFBType.AnimationNode>(animationNode);

                                        string test = animationNode.Animation.Name;
                                    }
                                }
                            }

                            if (acomp.ConnectionsLength > 0)
                            {
                                for (int j = 0; j < acomp.ConnectionsLength; j++)
                                {
                                    var connection = acomp.GetConnections(j);
                                  
                                        var test = connection.NodeIn;
                                }
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("error: " + ex.Message);
            }
        }

        public FBNetData CreateFBData( List<Type> types, FlatBufferBuilder fbbParent = null)
        {
            if (fbbParent == null)
                fbbParent = new FlatBufferBuilder(1);


            //  NetMsg.Component comp = new NetMsg.Component();
            VectorOffset componentsOffset = new VectorOffset();
            if (_Components.Any())
            {
                List<int> componentOffsets = new List<int>();
                int componentCount = 0;
                foreach (var component in _Components)
                {
                    if (!types.Contains(component.GetType()))
                        continue;

                    componentCount++;
                    var test = component.FBObject.CreateFBData(fbbParent);
                    componentOffsets.Add(NetMsg.Component.CreateComponent(fbbParent, component.UComponent, test._offset).Value);// fbbParent.CreateString(mesh.Name ?? ""), fbbParent.CreateString(mesh.RessGrp ?? ""), planeOffset, new Offset<OgreCube>()).Value);
                }

                NetMsg.Entity.StartComponentsVector(fbbParent, componentCount);
                foreach (var component in componentOffsets)
                    fbbParent.AddOffset(component);
                componentsOffset = fbbParent.EndVector();
            }

            var finishOffset = NetMsg.Entity.CreateEntity(fbbParent, EntityID, false, componentsOffset);

            fbbParent.Finish(finishOffset.Value); //!!!!! important ..

            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbbParent, TypeSafeOffset = finishOffset }; //bytebuffer   
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbbParent = null, IFBObject child = null)
        {
            if (fbbParent == null)
                fbbParent = new FlatBufferBuilder(1);

            List<Offset<NetMsg.Component>> componentOffsets = new List<Offset<NetMsg.Component>>();
            foreach (var component in _Components)
            {
                var test = component.FBObject.CreateFBData(fbbParent);
                component.FBObject.Read(test._fbData);
                // NetMsg.Component.StartComponent(fbbParent);
                // NetMsg.Component.AddComp(fbbParent, test);
                // NetMsg.Component.AddCompType(fbbParent, NetMsg.UComponent.Camera);
                //var compOffset = NetMsg.Component.EndComponent(fbbParent);

                componentOffsets.Add(NetMsg.Component.CreateComponent(fbbParent, component.UComponent, test._offset));// fbbParent.CreateString(mesh.Name ?? ""), fbbParent.CreateString(mesh.RessGrp ?? ""), planeOffset, new Offset<OgreCube>()).Value);
            }

            VectorOffset componentsOffset = NetMsg.Entity.CreateComponentsVector(fbbParent, componentOffsets.ToArray());

            var finishOffset = NetMsg.Entity.CreateEntity(fbbParent, EntityID, false, componentsOffset);

            fbbParent.Finish(finishOffset.Value); //!!!!! important ..

            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbbParent, TypeSafeOffset = finishOffset }; //bytebuffer   
        }

        #endregion
    }
}
