using NLog;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Text;
using VEF.Interfaces.Events;
using VEF.Interfaces.Services;

namespace VEF.Core.Model.Services
{
    public class LoggerService : ILoggerService
    {
        private static readonly Logger Logger = LogManager.GetLogger("VEF");

        /// <summary>
        /// The NLogService constructor
        /// </summary>
        /// <param name="aggregator">The injected event aggregator</param>
        public LoggerService()
        {

        }

        #region ILoggerService Members

        /// <summary>
        /// The logging function
        /// </summary>
        /// <param name="message">A message to log</param>
        /// <param name="category">The category of logging</param>
        /// <param name="priority">The priority of logging</param>
        public void Log(string message, LogCategory category, LogPriority priority)
        {
            Message = message;
            Category = category;
            Priority = priority;

            var trace = new StackTrace();
            StackFrame frame = trace.GetFrame(1); // 0 will be the inner-most method
            MethodBase method = frame.GetMethod();

            Logger.Log(LogLevel.Info, method.DeclaringType + ": " + message);

            VEFModule.EventAggregator.GetEvent<LogEvent>().Publish(new LoggerService
                                                         {Message = Message, Category = Category, Priority = Priority});
        }

        /// <summary>
        /// The message which was last logged using the service
        /// </summary>
        public string Message { get; internal set; }

        /// <summary>
        /// The log message's category
        /// </summary>
        public LogCategory Category { get; internal set; }

        /// <summary>
        /// The log message's priority
        /// </summary>
        public LogPriority Priority { get; internal set; }

        #endregion
    }
}
