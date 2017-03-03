using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.DAL.Interface;

namespace VEX.IDAL
{
    public interface IDBFileItem
    {
        bool SaveToDB(IDAL_DCTX ctx);
    }
}
