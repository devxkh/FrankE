using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VEF.Interfaces.Services;
using VEX.Core.Interfaces.Services;
using VEX.Enet.Interface;
using VEX.Interface.DAL;

namespace VEX.Core.Model.Services
{
    /// <summary>
    /// The main project tree manager
    /// </summary>
    public sealed class SocketServerManager : ISocketServerService
    {
    //    private ushort _NetIdPool;
        private Client _client;

        public Client Client { get { return _client; } }

        /// <summary>
        /// The injected logger
        /// </summary>
        //    private readonly ILoggerService _logger;

        //public ushort NewNetID()
        //{
        //    return _NetIdPool = (ushort)(_NetIdPool + 1);
        //}

        /// <summary>
        /// The theme manager constructor
        /// </summary>
        /// <param name="eventAggregator">The injected event aggregator</param>
        /// <param name="logger">The injected logger</param>
        public SocketServerManager()//IEventAggregator eventAggregator, ILoggerService logger)
        {
            //_eventAggregator = eventAggregator;
            //_logger = logger;

            _client = new Client();
        }

        public bool SendMessageToServer(uint netid, uint sceneId, NetMsg.Data type, FBNetData fbNetData)
        {
        //    FlatBuffers.FlatBufferBuilder fbb = new FlatBuffers.FlatBufferBuilder(1);
            var mon = NetMsg.MessageRoot.CreateMessageRoot(fbNetData.Fbb, netid, sceneId, type, fbNetData._offset);
            NetMsg.MessageRoot.FinishMessageRootBuffer(fbNetData.Fbb, mon);

            //send node data and object to the server 
            return Client.SendToServer(0, fbNetData.Fbb.SizedByteArray(), ENet.PacketFlags.Reliable);
        }

        public SocketServerToolModel SocketServerToolModel { get; internal set; }

        /// <summary>
        /// The current item selected
        /// </summary>
        //private IItem mCurrentItem;
        //public IItem CurrentItem
        //{
        //    get { return PropertiesToolModel.SelectedObject; }
        //    set { PropertiesToolModel.SelectedObject = value; }
        //}

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
