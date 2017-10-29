using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XGame.Core.Engine
{

    public class UnityContainer
    {
        private static UnityContainer _singleton;

        public static UnityContainer Get()
        {
            if (_singleton == null)
            {
                return _singleton = new UnityContainer();
            }
            else
                return _singleton;
        }

        public EngineBase Engine { get; set; }
    }
}
