using Prism.Events;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace VEF.WPF.Core.Events
{
    #if WINDOWS_APP
    /// <summary>
    /// Class LogEvent - This event is used when a logging operation happens.
    /// </summary>
    public class WindowClosingEvent : PubSubEvent<Window>
    {
    }

#endif
}
