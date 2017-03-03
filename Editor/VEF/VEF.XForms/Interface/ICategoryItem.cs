using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEF.Interface
{
    public interface ICategoryItem
    {
        List<Type> CanAddThisItems { get; }
    }
}
