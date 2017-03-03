using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEF.Interface
{
    public interface IModule
    {
        void PreInitialize();
        void Initialize();
        void PostInitialize();
    }
}
