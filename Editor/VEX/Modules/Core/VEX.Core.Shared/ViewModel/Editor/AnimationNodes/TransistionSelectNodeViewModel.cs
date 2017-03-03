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
    [DisplayName("TransitionSelectNode")]
    public class TransitionSelectNodeViewModel : TransitionSelectNode
    {
        public override XFBType.UAnimationNode AnimNodeType { get { return XFBType.UAnimationNode.TransitionSelectNode; } }
        
        public TransitionSelectNodeViewModel()
        {
            AddInputConnector("select", Colors.Blue);
            AddInputConnector("time in", Colors.Blue);
            AddInputConnector("time out", Colors.Blue);

            AddInputConnector("Animation 0", Colors.DarkSeaGreen);
            AddInputConnector("Animation 1", Colors.DarkSeaGreen);
            AddInputConnector("Animation 2", Colors.DarkSeaGreen);
            AddInputConnector("Animation 3", Colors.DarkSeaGreen);

            UpdatePreviewImage();
        }

        protected override void Draw(DrawingContext drawingContext, Rect bounds)
        {
            drawingContext.DrawRectangle( new SolidColorBrush(Colors.Transparent), null, bounds);
        }
    }
}
