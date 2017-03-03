using FlatBuffers;
using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Text;
using System.Xml.Serialization;
using VEX.Core.Shared.ViewModel.Editor.AnimationNodes;
using VEX.Interface.DAL;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;

namespace VEX.Core.Shared.Model.Scene.Objects.ChildObject.Animation
{
    [DataContract]
    public class AnimParameter
    {
        [DataMember]
        public uint Id { get; set; }
        [DataMember]
        public float Value { get; set; }
        [DataMember]
        public string Name { get; set; }
    }

    [DataContract(IsReference = true)]
    public class ParameterNode : AnimNode, IFBObject
    {
        #region Properties 
        
        [DataMember]
        [ExpandableObject]
        public AnimParameter Parameter { get; set; }

        #endregion
        
        #region IFBObject

        [XmlIgnore]
        public object Parent { get; set; }

        public ParameterNode()
        {
            Parameter = new AnimParameter();
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
            if (fbbParent == null)
                fbbParent = new FlatBufferBuilder(1);

            var parameter = XFBType.Parameter.CreateParameter(fbbParent, Parameter.Value);

            XFBType.ParameterNode.StartParameterNode(fbbParent);
       //     XFBType.ParameterNode.AddId(fbbParent, Id);
            XFBType.ParameterNode.AddParam(fbbParent, parameter);
            var paremterNodeOffset = XFBType.ParameterNode.EndParameterNode(fbbParent);

            fbbParent.Finish(paremterNodeOffset.Value); //!!!!! important ..
            return new FBNetData() { _fbData = fbbParent.SizedByteArray(), _offset = paremterNodeOffset.Value, Fbb = fbbParent };//bytebuffer
        }

        #endregion
    }
}
