using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEF.Interface
{
    public class ModuleInformation
    {
        public List<ModuleInformation> Dependencies { get; set; }

        public string Name { get; set; }
    }

    public class ModuleConfiguration
    {
        public List<ModuleInformation> Modules { get; set; }
        public List<String> Folders { get; set; }
    }
}
