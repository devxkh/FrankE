#region License

// Copyright (c) 2014

#endregion

namespace VEF.Interfaces.Services
{
    /// <summary>
    /// Interface ILoggerService - used for logging in the application
    /// </summary>
    public interface IOutputService
    {
        object TBStreamWriter { get; set; }

        /// <summary>
        /// Gets the message which just got logged.
        /// </summary>
        /// <value>The message.</value>
        string Message { get; }    
    }
}