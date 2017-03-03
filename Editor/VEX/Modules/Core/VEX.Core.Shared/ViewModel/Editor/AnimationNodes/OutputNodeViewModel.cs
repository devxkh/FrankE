using DLL.NodeEditor.Nodes;
using DLL.NodeEditor.ViewModel;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using VEX.Core.Shared.Model.Scene.Objects.ChildObject.Animation;

namespace VEX.Core.Shared.ViewModel.Editor.AnimationNodes
{
    [DisplayName("Out")]
    [DataContract(IsReference = true)]
    public class OutputNodeViewModel : AnimNode
    {
        public OutputNodeViewModel()
        {
            AddInputConnector("In", Colors.DarkSeaGreen);
        }

        protected override void Draw(DrawingContext drawingContext, Rect bounds)
        {
            //  drawingContext.DrawRectangle(new SolidColorBrush(Color), null, bounds);
        }
    }
}
