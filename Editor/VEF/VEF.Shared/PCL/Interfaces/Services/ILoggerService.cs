using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VEF.Interfaces.Services
{
    /// <summary>
    /// Enum LogCategory
    /// </summary>
    public enum LogCategory
    {
        Debug,
        Exception,
        Info,
        Warn,
        Error
    }

    /// <summary>
    /// Enum LogPriority
    /// </summary>
    public enum LogPriority
    {
        None,
        Low,
        Medium,
        High
    }

    /// <summary>
    /// Interface ILoggerService - used for logging in the application
    /// </summary>
    public interface ILoggerService
    {
        /// <summary>
        /// Gets the message which just got logged.
        /// </summary>
        /// <value>The message.</value>
        string Message { get; }

        /// <summary>
        /// Gets the category of logging.
        /// </summary>
        /// <value>The category.</value>
        LogCategory Category { get; }

        /// <summary>
        /// Gets the priority of logging.
        /// </summary>
        /// <value>The priority.</value>
        LogPriority Priority { get; }

        /// <summary>
        /// Logs the specified message.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <param name="category">The logging category.</param>
        /// <param name="priority">The logging priority.</param>
        void Log(string message, LogCategory category, LogPriority priority);
    }
}
