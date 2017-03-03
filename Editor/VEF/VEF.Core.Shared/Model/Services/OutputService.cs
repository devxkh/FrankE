#region License

// Copyright (c) 2014

#endregion

using System;
using System.Diagnostics;
using System.Reflection;
using VEF.Interfaces.Services;
using VEF.Util;

namespace VEF.Model.Services
{
    /// <summary>
    /// The NLogService for logging purposes
    /// </summary>
    internal class OutputService : IOutputService
    {
        //private static readonly Logger Logger = LogManager.GetLogger("Wide");
     //   private readonly IEventAggregator _aggregator;

      

        public OutputService()
        {
        }

        /// <summary>
        /// The NLogService constructor
        /// </summary>
        /// <param name="aggregator">The injected event aggregator</param>
        //public OutputService(IEventAggregator aggregator)
        //{
        //    _aggregator = aggregator;
        //}

        #region ILoggerService Members

        ///// <summary>
        ///// The logging function
        ///// </summary>
        ///// <param name="message">A message to log</param>
        ///// <param name="category">The category of logging</param>
        ///// <param name="priority">The priority of logging</param>
        //public void Log(string message, LogCategory category, LogPriority priority)
        //{
        //    Message = message;
        //    Category = category;
        //    Priority = priority;

        //    var trace = new StackTrace();
        //    StackFrame frame = trace.GetFrame(1); // 0 will be the inner-most method
        //    MethodBase method = frame.GetMethod();

        //    Logger.Log(LogLevel.Info, method.DeclaringType + ": " + message);

        //    _aggregator.GetEvent<LogEvent>().Publish(new OutputService {Message = Message, Category = Category, Priority = Priority});
        //}

        private TextBoxStreamWriter m_TextBoxStreamWriter;

        public object TBStreamWriter
        {
            get
            {
                if (m_TextBoxStreamWriter == null)
                    m_TextBoxStreamWriter = new TextBoxStreamWriter();
                
                // Redirect the out Console stream
                Console.SetOut(m_TextBoxStreamWriter);

                return m_TextBoxStreamWriter;
            }
            set
            {
                m_TextBoxStreamWriter = value as TextBoxStreamWriter;
            }
        }

        /// <summary>
        /// The message which was last logged using the service
        /// </summary>
        public string Message { get; internal set; }

        #endregion
    }
}