#region License

// Copyright (c) 2014

#endregion


using Prism.Events;
using VEF.Interfaces.Services;
namespace VEF.Interfaces.Events
{
    /// <summary>
    /// Class LogEvent - This event is used when a logging operation happens.
    /// </summary>
    public class OutputEvent : PubSubEvent<IOutputService>
    {
    }
}