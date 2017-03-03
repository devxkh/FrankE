using FlatBuffers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Runtime.Serialization;
using System.Text;
using System.Xml.Serialization;
using VEX.Core.Shared.ViewModel.Editor.AnimationNodes;
using VEX.Interface.DAL;

namespace VEX.Core.Shared.Model.Scene.Objects.ChildObject.Animation
{
    [DataContract(IsReference = true)]
    public class TransitionSelectNode : AnimNode, IFBObject
    {
        #region Properties 
        
        [DataMember]
        [Range(1, int.MaxValue, ErrorMessage = "Please enter a value bigger than {1}")]
        public ushort Size { get; set; }


        [DataMember]
        public ushort Select { get; set; }
        [DataMember]
        public float TimeIn { get; set; }
        [DataMember]
        public float TimeOut { get; set; }

        #endregion


        #region IFBObject

        public object Parent { get; set; }

        public TransitionSelectNode()
        {
        }

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
            if (Size == 0)
                throw new Exception("TransitionSelectNode(NodeId:" + base.NodeId +"):Please enter a value bigger than 0");

            if (fbbParent == null)
                fbbParent = new FlatBufferBuilder(1);
            
            XFBType.TransitionSelectNode.StartTransitionSelectNode(fbbParent);
         //   XFBType.TransitionSelectNode.AddId(fbbParent, Id);
            XFBType.TransitionSelectNode.AddSize(fbbParent, Size);
            var paremterNodeOffset = XFBType.TransitionSelectNode.EndTransitionSelectNode(fbbParent);

            fbbParent.Finish(paremterNodeOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = paremterNodeOffset.Value, Fbb = fbbParent };//bytebuffer
        }

        #endregion
    }
}
