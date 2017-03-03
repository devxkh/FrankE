using FlatBuffers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using VEF.Utils;
using VEX.Core.Shared.Model.Scene.Objects.ChildObject.Animation;
using VEX.Interface.DAL;
using VEX.Model.Scene.Model.Objects.FBufferObject;
using System.Linq;
using System.Windows;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using System.Collections.Specialized;
using System.Collections.ObjectModel;
using VEX.Interface.UI;
using System.Windows.Media;
using DLL.NodeEditor.ViewModel;
using DLL.NodeEditor.Nodes;
using VEF;
using VEX.Core.Shared.Service.Component;
using VEX.Core.Shared.ViewModel.Editor.AnimationNodes;
using VEX.Core.Shared.ViewModel.Editor;
using System.Runtime.Serialization;
using VEX.Core.Shared.Model.Prefabs;
using VEX.Service.Scene;
using VEF.IDAL;
using VEX.Core.Model.Project;
using VEX.Model.Project;

namespace VEX.Model.Scene.Model.Objects
{
    [KnownType(typeof(AnimationBlendTree))]
    [DataContract]
    public class FB_AnimationComponent : ViewModelBase, IFBObject //, INetMsg
    {
        private XFBType.AnimationComponent m_FBData = new XFBType.AnimationComponent();

        
        private string _AnimationBlendTreeName;

        [DataMember]
        public object Parent { get; set; }

        public AnimationBlendTree AnimationBlendTree
        {
            get
            {
                if (!(Parent is AnimationComponent))
                    return null;

                var prefabCategory = ((((Parent as AnimationComponent).Parent as EntityX).Parent as DBEntitiesModel).Parent as VEXDBFileModel).Items.Where(x => x.GetType() == typeof(PrefabCategoryModel));

                var blendTreeCategoryModel = (prefabCategory.FirstOrDefault() as PrefabCategoryModel).Items.Where(x => x.GetType() == typeof(BlendTreeCategoryModel));
                var animationBlendTree = (blendTreeCategoryModel.FirstOrDefault() as BlendTreeCategoryModel).Items.Where(x => x.GetType() == typeof(AnimationBlendTree) && x.Name == _AnimationBlendTreeName).FirstOrDefault() as AnimationBlendTree;


                return animationBlendTree;
            }
        }

        [DataMember]
        public string AnimationBlendTreeName { get { return _AnimationBlendTreeName; } set { _AnimationBlendTreeName = value; } }


        public FB_AnimationComponent()
        {
        }

        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            try
            {
                ByteBuffer byteBuffer = new ByteBuffer(fbData);
                m_FBData = XFBType.AnimationComponent.GetRootAsAnimationComponent(byteBuffer); // read 
                if (m_FBData.NodesLength > 0)
                {
                    for (int i = 0; i < m_FBData.NodesLength; i++)
                    {
                        var node = m_FBData.GetNodes(i);
                        if (node.NodeType == XFBType.UAnimationNode.AnimationNode)
                        {
                            XFBType.AnimationNode animationNode = new XFBType.AnimationNode();
                            animationNode = node.GetNode<XFBType.AnimationNode>(animationNode);

                            string test = animationNode.Animation.Name;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("error: " + ex.Message);
            }
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbb = null, IFBObject child = null)
        {
            if (fbb == null)
                fbb = new FlatBufferBuilder(1);

         //   StringOffset animInfoOffset = m_AnimationInfo != null ? fbb.CreateString(m_AnimationInfo) : new StringOffset();
         //   StringOffset animTreeOffset = m_AnimationTree != null ? fbb.CreateString(m_AnimationTree) : new StringOffset();

            VectorOffset animNodesOffset = new VectorOffset();
            if (AnimationBlendTree.AnimNodes.Any())
            {
                List<int> animNodeOffsets = new List<int>();
                foreach (var animNode in AnimationBlendTree.AnimNodes)
                {
                    var animNodeObject = animNode as AnimNode;
                    if (animNodeObject != null)
                    {
                        var fbobject = animNodeObject as IFBObject;
                        if(fbobject != null)
                            animNodeOffsets.Add(XFBType.AnimNode.CreateAnimNode(fbb, animNodeObject.NodeId, animNodeObject.AnimNodeType, fbobject.CreateFBData(fbb)._offset).Value);
                    }
                }
                XFBType.AnimationComponent.StartNodesVector(fbb, animNodeOffsets.Count);
                foreach (var animNode in animNodeOffsets)
                    fbb.AddOffset(animNode);
                animNodesOffset = fbb.EndVector();
            }

            VectorOffset connectionsOffset = new VectorOffset();
            if (AnimationBlendTree.NodeConnections.Any())
            {
                XFBType.AnimationComponent.StartConnectionsVector(fbb, AnimationBlendTree.NodeConnections.Count);
                foreach (var connection in AnimationBlendTree.NodeConnections)
                {
                    var animNodeFrom = connection.From.Element as AnimNode; // AnimNode; //from = out

                    var nodeTo = connection.To.Element as AnimNode; //to = in

                    uint outId = animNodeFrom.NodeId;
                    uint inId = 0; //0 = outpout
                    if (nodeTo != null)
                        inId = nodeTo.NodeId;

                    uint portIn = connection.To.PortId; //todo index as port ???

                    
                    XFBType.Connection.CreateConnection(fbb, inId, outId, portIn); //structs doesnt need explicit offset!!
                }
                connectionsOffset = fbb.EndVector();
            }

            VectorOffset constantsOffset = new VectorOffset();
            if (AnimationBlendTree.Constants.Any())
            {
                XFBType.AnimationComponent.StartConstantsVector(fbb, AnimationBlendTree.NodeConnections.Count);
                foreach (var constant in AnimationBlendTree.Constants)
                    XFBType.Constant.CreateConstant(fbb, constant.NodeId, constant.NodeId, constant.PortId, constant.Value);
                constantsOffset = fbb.EndVector();
            }

            //StringOffset BoneparentOffset = m_Boneparent != null ? fbb.CreateString(m_Boneparent) : new StringOffset();

            XFBType.AnimationComponent.StartAnimationComponent(fbb);
            
          //  if (m_Boneparent != null) XFBType.AnimationComponent.AddBoneparent(fbb, BoneparentOffset);
            //   if (m_AnimationInfo != null) XFBType.AnimationComponent.AddAnimationInfo(fbb, animInfoOffset);
            //   if (m_AnimationTree != null) XFBType.AnimationComponent.AddAnimationTree(fbb, animTreeOffset);

            if (AnimationBlendTree.AnimNodes.Any()) XFBType.AnimationComponent.AddNodes(fbb, animNodesOffset);
            if (AnimationBlendTree.NodeConnections.Any()) XFBType.AnimationComponent.AddConnections(fbb, connectionsOffset);
            if (AnimationBlendTree.Constants.Any()) XFBType.AnimationComponent.AddConstants(fbb, constantsOffset);
            XFBType.AnimationComponent.AddOutput(fbb, AnimationBlendTree.Output);

            var finishOffset = XFBType.AnimationComponent.EndAnimationComponent(fbb);
            fbb.Finish(finishOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbb.SizedByteArray(), _offset = finishOffset.Value, Fbb = fbb }; //bytebuffer
        }
    }
}
