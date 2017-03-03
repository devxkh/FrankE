using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEF.DAL.Interface
{
    public interface IDALOptions
    {
        string Name { get; set; }

        DBType DBType { get; set; }

        string Host { get; set; }
        string User { get; set; }
        string Password { get; set; }
    }
}
