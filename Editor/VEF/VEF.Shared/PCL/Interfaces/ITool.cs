using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Interfaces.Services;

namespace VEF.Interfaces
{
    public interface ITool
    {
        PaneLocation PreferredLocation { get; }
        double PreferredWidth { get; }
        double PreferredHeight { get; }
        double MinWidth { get; }

        bool IsVisible { get; set; }
    }
}
