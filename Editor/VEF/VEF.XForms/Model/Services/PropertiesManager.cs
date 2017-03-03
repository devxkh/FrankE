using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Interfaces.Services;
using VEF.Model;

namespace VEF.XForms.Model.Services
{
    /// <summary>
    /// The main project tree manager
    /// </summary>
    public sealed class PropertiesManager : IPropertiesService
    {
        /// <summary>
        /// The injected logger
        /// </summary>
    //    private readonly ILoggerService _logger;

        /// <summary>
        /// The theme manager constructor
        /// </summary>
        /// <param name="eventAggregator">The injected event aggregator</param>
        /// <param name="logger">The injected logger</param>
        public PropertiesManager()//IEventAggregator eventAggregator, ILoggerService logger)
        {
            //_eventAggregator = eventAggregator;
            //_logger = logger;
        }


        public PropertiesToolModel PropertiesToolModel { get; internal set; }

        /// <summary>
        /// The current item selected
        /// </summary>
        private Object mCurrentItem;
        public Object CurrentItem
        {
            get { return PropertiesToolModel.SelectedObject; }
            set { PropertiesToolModel.SelectedObject = value; }
        }

        #region IPropertiesTreeService Members

        /// <summary>
        /// Set the current item
        /// </summary>
        /// <param name="guid">The guid of the item</param>
        /// <returns>true if the new item is set, false otherwise</returns>
        //public bool SetCurrent(IItem item)
        //{
        //    CurrentItem = item;

        //    _logger.Log("proerties item set", LogCategory.Info, LogPriority.None);
        //    _eventAggregator.GetEvent<ItemChangeEvent>().Publish(item);

        //    return false;
        //}

        #endregion
    }
}
