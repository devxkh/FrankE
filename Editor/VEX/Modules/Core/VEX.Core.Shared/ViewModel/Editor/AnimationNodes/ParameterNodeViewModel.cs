using DLL.NodeEditor.Nodes;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using VEX.Core.Shared.Model.Scene.Objects.ChildObject.Animation;

namespace VEX.Core.Shared.ViewModel.Editor.AnimationNodes
{
    [DataContract(IsReference = true)]
    [DisplayName("ParameterNode")]
    public class ParameterNodeViewModel : ParameterNode
    {
        public override XFBType.UAnimationNode AnimNodeType { get { return XFBType.UAnimationNode.ParameterNode; } }


        public ParameterNodeViewModel()
        {
               //  AddInputConnector("Left", Colors.DarkSeaGreen);

               UpdatePreviewImage();
        }

        protected override void Draw(DrawingContext drawingContext, Rect bounds)
        {
            drawingContext.DrawRectangle( new SolidColorBrush(Colors.Transparent), null,
                                 bounds);
        }
    }
}
