using Prism.Events;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Interfaces.Services;

namespace VEF.Interfaces.Events
{  
    /// <summary>
    /// Class LogEvent - This event is used when a logging operation happens.
    /// </summary>
    public class LogEvent : PubSubEvent<ILoggerService>
    {
    }
}
