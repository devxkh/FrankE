using FlatBuffers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.Serialization;
using System.Windows;
using System.Linq;
using VEX.Interface.DAL;
using VEX.Model.Scene.Model.Objects.ChildObject;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using VEX.Model.Scene.Model.Objects.ObjectData;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using XFBType;
using VEF.Utils;
using VEF;
using VEX.Core.Model.Services;
using VEX.Service.Scene;
using System.Collections.Specialized;
using System.Collections.ObjectModel;
using VEX.Core.Shared.Service.Scene;

namespace VEX.Model.Scene.Model.Objects
{
    [KnownType(typeof(MeshObject))]
    [KnownType(typeof(MaterialObject))]
    [DataContract]
    public class FB_Renderable : ViewModelBase, IFBObject
    {
        #region private members
        
        private uint m_Mode;
        private bool m_ShowDebug;
        private bool m_ShowAABB;
        private uint m_Group;
        private uint m_VisibilityFlags;
        private uint m_lightMask;
        private bool m_Visible;
        private float m_shadowConstBias;

        private bool m_CastShadows;
        private XFBType.MemoryMgrType m_memoryType;
        private uint m_Renderqueue;

        private XFBType.RenderableComponent m_FBData = new XFBType.RenderableComponent();

        #endregion

        #region Properties

        [DataMember]
        public object Parent { get; set; }

        [DataMember]
        public uint Mode { get { return m_Mode; } set { m_Mode = value; SendUpdateToServer<LightComponent>(); RaisePropertyChanged("Mode"); } }

        [DataMember]
        public bool ShowDebug { get { return m_ShowDebug; } set { m_ShowDebug = value; SendUpdateToServer<LightComponent>(); RaisePropertyChanged("ShowDebug"); } }

        [DataMember]
        public bool ShowAABB { get { return m_ShowAABB; } set { m_ShowAABB = value; SendUpdateToServer<LightComponent>(); RaisePropertyChanged("ShowAABB"); } }

        [DataMember]
        public uint Group { get { return m_Group; } set { m_Group = value; SendUpdateToServer<LightComponent>(); RaisePropertyChanged("Group"); } }


        [DataMember]
        public XFBType.MemoryMgrType MemoryType { get { return m_memoryType; } set { m_memoryType = value; SendUpdateToServer<LightComponent>(); RaisePropertyChanged("MemoryType"); } }

        [DataMember]
        public bool CastShadows { get { return m_CastShadows; } set { m_CastShadows = value; SendUpdateToServer<LightComponent>(); RaisePropertyChanged("CastShadows"); } }

        [DataMember]
        public uint Renderqueue { get { return m_Renderqueue; } set { m_Renderqueue = value; SendUpdateToServer<LightComponent>(); RaisePropertyChanged("Renderqueue"); } }
        
        [DataMember]
        public uint VisibilityFlags { get { return m_VisibilityFlags; } set { m_VisibilityFlags = value; SendUpdateToServer<LightComponent>(); RaisePropertyChanged("Renderqueue"); } }

        [DataMember]
        public uint LightMask { get { return m_lightMask; } set { m_lightMask = value; SendUpdateToServer<LightComponent>(); RaisePropertyChanged("LightMask"); } }

        [DataMember]
        public bool Visible { get { return m_Visible; } set { m_Visible = value; SendUpdateToServer<LightComponent>(); RaisePropertyChanged("Visible"); } }

        [DataMember]
        public float ShadowConstBias { get { return m_shadowConstBias; } set {
                m_shadowConstBias = value;
                SendUpdateToServer<LightComponent>();
                RaisePropertyChanged("ShadowConstBias"); } }

        private ObservableCollection<IFBObject> m_Meshes;

        [DataMember]
        [Editor(typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor), typeof(Xceed.Wpf.Toolkit.PropertyGrid.Editors.CollectionEditor))]
        [NewItemTypes(new Type[] { typeof(MeshObject), typeof(PlaneObject), typeof(CubeObject) })]
        public ObservableCollection<IFBObject> Meshes
        {
            get { return m_Meshes; }
            set
            {
                value.CollectionChanged += this.OnCollectionChanged;

                m_Meshes = value;
            }
        }

        void OnCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null)
            {
                foreach (var newItem in e.NewItems)
                {
                    (newItem as IFBObject).Parent = (RenderableComponent)this.Parent;
                }
            }
        }

        //public void ChildChanged(object sender, PropertyChangedEventArgs e)
        //{
        //    var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;

        //    if (Parent == null)
        //        return;

        //    var body = Parent as RenderableComponent;
        //    EntityX entity = body.Parent as EntityX;
        //    if (entity != null)
        //    {
        //        List<Type> types = new List<Type>() { typeof(RenderableComponent) };

        //        FlatBufferBuilder fbb = new FlatBufferBuilder(4);
        //        var fbEntity = entity.FB_Entity.CreateFBData(fbb, types);

        //        var mon = NetMsg.MessageRoot.CreateMessageRoot(fbb, entity.NetID, 1, NetMsg.Data.Entity, fbEntity._offset);
        //        NetMsg.MessageRoot.FinishMessageRootBuffer(fbb, mon);

        //        _SocketServerManager.Client.SendToServer(0, fbb.SizedByteArray(), ENet.PacketFlags.Reliable);
        //    }
        //}


        //  public int Group { get { return m_Group; } set { m_Group = FB_Helper.UpdateSelectedObject(this, m_Group, value); } }

        #endregion

        public FB_Renderable()
        {
            m_Meshes = new ObservableCollection<IFBObject>();
            m_Meshes.CollectionChanged += this.OnCollectionChanged;
        }

        #region methods

        private void SendUpdateToServer<T>()
        {
            var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;

            if (Parent == null)
                return;

            var body = Parent as RenderableComponent;
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

        public void Read(Byte[] fbData)
        {
            try
            {
                ByteBuffer byteBuffer = new ByteBuffer(fbData);
                m_FBData = XFBType.RenderableComponent.GetRootAsRenderableComponent(byteBuffer); // read 
                if(m_FBData.MeshesLength > 0)
                {
                    for (int i = 0; i < m_FBData.MeshesLength; i++)
                    {
                        var mesh = m_FBData.GetMeshes(i);
                        var type = mesh.MeshType;
                     //   var height = plane.Height;
                    }
                }
                //     m_Group = XFBType.Group(); //per node!
            }
            catch (Exception ex)
            {
                MessageBox.Show("error: " + ex.Message);
            }
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbbParent = null, IFBObject child = null)
        {
            if (fbbParent == null)
                fbbParent = new FlatBufferBuilder(1);

            //VectorOffset materialOffset = new VectorOffset();
            //if (m_Materials.Any())
            //{
            //    List<int> matOffsets = new List<int>();
            //    foreach (var material in m_Materials)
            //        matOffsets.Add(XFBType.Material.CreateMaterial(fbbParent, fbbParent.CreateString(material.FileName ?? ""), fbbParent.CreateString(material.ResourceGroup ?? "")).Value);

            //    XFBType.RenderableComponent.StartMaterialsVector(fbbParent, m_Materials.Count);
            //    foreach (var material in matOffsets)
            //        fbbParent.AddOffset(material);
            //    materialOffset = fbbParent.EndVector();
            //}


            VectorOffset meshesOffset = new VectorOffset();
            if (m_Meshes.Any())
            {
                List<int> meshOffsets = new List<int>();
                foreach (var mesh in m_Meshes)
                {
                    var plane = mesh as PlaneObject;
                    if (plane != null)
                    {
                        meshOffsets.Add(XFBType.Mesh.CreateMesh(fbbParent, UMesh.MeshPlane, plane.CreateFBData(fbbParent)._offset).Value);

                        //  meshOffsets.Add(XFBType.Mesh.CreateMesh(fbbParent, fbbParent.CreateString(mesh.Name ?? ""), fbbParent.CreateString(mesh.RessGrp ?? ""), planeOffset, new Offset<OgreCube>()).Value);

                        continue;
                    }
                    var cube = mesh as CubeObject;
                    if (cube != null)
                    {
                        meshOffsets.Add(XFBType.Mesh.CreateMesh(fbbParent, UMesh.MeshCube, cube.CreateFBData()._offset).Value);
                        //                        meshOffsets.Add(XFBType.Mesh.CreateMesh(fbbParent, fbbParent.CreateString(mesh.Name), fbbParent.CreateString(mesh.RessGrp), new Offset<OgrePlane>(), XFBType.OgreCube.CreateOgreCube(fbbParent, cube.width)).Value);
                        continue;
                    }
                    var meshFile = mesh as MeshObject;
                    if (meshFile != null)
                    {
                        meshOffsets.Add(XFBType.Mesh.CreateMesh(fbbParent, UMesh.MeshFile, meshFile.CreateFBData(fbbParent)._offset).Value);
                        continue;
                    }
                }

                XFBType.RenderableComponent.StartMeshesVector(fbbParent, m_Meshes.Count);
                foreach (var mesh in meshOffsets)
                    fbbParent.AddOffset(mesh);
                meshesOffset = fbbParent.EndVector();
            }

          //  var debugOffset = XFBType.Debug.CreateDebug(fbbParent, m_ShowDebug, m_ShowAABB);

            XFBType.RenderableComponent.StartRenderableComponent(fbbParent);

          //  if (m_Materials.Any()) XFBType.RenderableComponent.AddMaterials(fbbParent, materialOffset);
            if (m_Meshes.Any()) XFBType.RenderableComponent.AddMeshes(fbbParent, meshesOffset);
            XFBType.RenderableComponent.AddCastShadows(fbbParent, m_CastShadows);
            XFBType.RenderableComponent.AddMemType(fbbParent, m_memoryType);
            XFBType.RenderableComponent.AddVisible(fbbParent, m_Visible);
            XFBType.RenderableComponent.AddVisibilityFlags(fbbParent, m_VisibilityFlags);
            XFBType.RenderableComponent.AddLightMask(fbbParent, m_lightMask);
            XFBType.RenderableComponent.AddShadowconstBias(fbbParent, m_shadowConstBias);
            //   XFBType.RenderableComponent.AddDebug(fbbParent, debugOffset);
            XFBType.RenderableComponent.AddMode(fbbParent, m_Mode);
            
            var finishOffset = XFBType.RenderableComponent.EndRenderableComponent(fbbParent);

            fbbParent.Finish(finishOffset.Value); //!!!!! important ..
            
            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbbParent }; //bytebuffer   
        }

        #endregion
    }
}
