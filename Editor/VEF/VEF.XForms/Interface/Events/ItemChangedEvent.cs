
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
    /// Class ThemeChangeEvent - This event happens when a theme is changed.
    /// </summary>
    public class ItemChangeEvent : PubSubEvent<IItem>
    {

    }
}
