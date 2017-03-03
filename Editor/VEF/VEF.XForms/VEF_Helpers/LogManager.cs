using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Logging;

namespace VEF.VEF_Helpers
{
    public class PCLILogDependency
    {
        private readonly ILog _logger;

        public ILog Log { get { return _logger; } }
        public PCLILogDependency(ILog logger)
        {
            _logger = logger;
        }

        //public void Info(string message)
        //{
        //    _logger.Info(message);
        //}
    }


    public class PortableClassWithILogManagerDependency
    {
        private readonly ILogManager _logManager;

        public PortableClassWithILogManagerDependency(ILogManager logManager)
        {
            _logManager = logManager;
        }

        public void SomeMethodThatLogs(string message)
        {
            //var logger = _logManager.GetLogger(this.GetType());

            //logger.Info(message);
        }
    }
}
