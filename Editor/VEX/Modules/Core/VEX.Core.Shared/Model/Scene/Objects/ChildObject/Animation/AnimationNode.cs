using FlatBuffers;
using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;
using VEX.Interface.DAL;
using System.Linq;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using DLL.NodeEditor.ViewModel;
using VEX.Core.Shared.ViewModel.Editor.AnimationNodes;
using System.Windows.Media.Imaging;
using DLL.NodeEditor.Nodes;
using System.Windows.Media;
using System.Windows;
using System.Runtime.Serialization;

namespace VEX.Core.Shared.Model.Scene.Objects.ChildObject.Animation
{
    [KnownType(typeof(AnimationNode))]
    [KnownType(typeof(TransitionSelectNode))]
    [KnownType(typeof(ParameterNode))]
    [KnownType(typeof(AnimationNodeViewModel))]
    [KnownType(typeof(TransitionSelectNodeViewModel))]
    [KnownType(typeof(ParameterNodeViewModel))]
    [KnownType(typeof(OutputNodeViewModel))]
    [DataContract(IsReference = true)]
    public class AnimNode : DynamicNode
    {
        public virtual XFBType.UAnimationNode AnimNodeType { get { return XFBType.UAnimationNode.NONE; } }

        [DataMember]
        public uint NodeId { get; set; }
        
        protected override void Draw(DrawingContext drawingContext, Rect bounds)
        {
            //drawingContext.DrawRectangle(new SolidColorBrush(Color), null, bounds);
        }
    }

    [DataContract]
    public class AnimTrigger
    {
        [DataMember]
        public uint Id { get; set; }

        [DataMember]
        public float Time { get; set; }

        [DataMember]
        public XFBType.TimeType TimeType { get; set; }

        [DataMember]
        public float MinWeightTreshold { get; set; }

        [DataMember]
        public string Name { get; set; }
    }

    [DataContract]
    public class Animation
    {
        [DataMember]
        public uint Id { get; set; }

        [DataMember]
        public bool Loop { get; set; }

        [DataMember]
        public List<AnimTrigger> AnimTriggers { get; set; }

        [DataMember]
        public string Name { get; set; }

        public Animation()
        {
            AnimTriggers = new List<AnimTrigger>();
        }
    }

    [DataContract(IsReference = true)]
    public class AnimationNode : AnimNode, IFBObject
    {
        [ExpandableObject]
        [DataMember]
        public Animation Animation { get; set; }

        public override XFBType.UAnimationNode AnimNodeType { get { return XFBType.UAnimationNode.AnimationNode; } }


        public AnimationNode()
        {
            Animation = new Animation();
        }

        #region IFBObject

        [DataMember]
        public object Parent { get; set; }

        /// <summary>
        /// reads flatbuffers byte data into object
        /// </summary>
        /// <param name="fbData"></param>
        public void Read(Byte[] fbData)
        {
            ByteBuffer byteBuffer = new ByteBuffer(fbData);
        }

        public FBNetData CreateFBData(FlatBufferBuilder fbbParent = null, IFBObject child = null)
        {
            if (fbbParent == null)
                fbbParent = new FlatBufferBuilder(1);

            VectorOffset triggersOffset = new VectorOffset();
            if (Animation.AnimTriggers.Any())
            {
                List<int> triggersOffsets = new List<int>();
                foreach (var trigger in Animation.AnimTriggers)
                {
                    triggersOffsets.Add(XFBType.AnimTrigger.CreateAnimTrigger(fbbParent, trigger.Id, trigger.Time, trigger.TimeType,trigger.MinWeightTreshold).Value);
                }

                XFBType.AnimationComponent.StartConnectionsVector(fbbParent, Animation.AnimTriggers.Count);
               
                foreach (var trigger in triggersOffsets)
                    fbbParent.AddOffset(trigger);
                triggersOffset = fbbParent.EndVector();
            }

            var animation = XFBType.Animation.CreateAnimation(fbbParent,Animation.Id, Animation.Loop, triggersOffset, fbbParent.CreateString(Animation.Name ?? ""));

            XFBType.AnimationNode.StartAnimationNode(fbbParent);
            XFBType.AnimationNode.AddAnimation(fbbParent, animation);
            var animationNodeOffset = XFBType.AnimationNode.EndAnimationNode(fbbParent);
            
            fbbParent.Finish(animationNodeOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = animationNodeOffset.Value, Fbb = fbbParent };//bytebuffer
        }

        #endregion
    }
}
