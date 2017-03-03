using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using VEF.Interfaces.Base;

namespace VEF.Core.WPF.Util
{
    public class KeyGestureWPF : IKeyGesture
    {
        public KeyGesture Gesture { get; set; }
    }
}
