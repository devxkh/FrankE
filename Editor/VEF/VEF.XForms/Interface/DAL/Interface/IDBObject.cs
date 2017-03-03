using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEF.DAL.Interface
{
    /// <summary>
    /// Interface for each database Object
    /// </summary>
    public interface IDBObject<T>
    {
        /// <summary>
        /// one datacontext per object
        /// </summary>
        T DataContext { get; }

        /// <summary>
        /// save object into database
        /// </summary>
        /// <returns>true =  ok , false = else</returns>
        bool Save(object param = null);

        /// <summary>
        /// delete object
        /// </summary>
        /// <returns>true =  ok , false = else</returns>
        bool Delete();
    }
}
