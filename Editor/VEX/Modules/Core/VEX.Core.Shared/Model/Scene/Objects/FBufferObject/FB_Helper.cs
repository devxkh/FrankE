using Microsoft.Practices.Unity;
using System;
using System.Collections.Generic;
using VEF;
using VEF.Interfaces.Services;
using VEX.Core.Model.Services;
using VEX.Interface.DAL;
using VEX.Interface.Scene;
using VEX.Service.Scene;

namespace VEX.Model.Scene.Model.Objects.FBufferObject
{
    public static class FB_Helper
    {
        //update selected object on c++ side
        public static T UpdateSelectedObject<T>(IFBObject objectdata, T oldValue, T newValue)
        {
            //todo !! only update if not loaded from xml!

            //var _SocketServerManager = VEFModule.UnityContainer.Resolve(typeof(SocketServerManager), "") as SocketServerManager;

            //EntityX entity = objectdata.Parent as EntityX;
            //if (entity != null)
            //{
            //    List<Type> types = new List<Type>() { typeof(BodyComponent) };
            //    var fbData = entity.FB_Entity.CreateFBData(types);
            //    _SocketServerManager.Client.SendToServer(0, fbData._fbData, ENet.PacketFlags.Reliable);
            //}

            int res = 0;

            //    string objectName = objectdata.GetType().Name; //object name e.g. FB_Physics

            //todo   send only if changed from GUI!
            //var sceneData = objectdata.Parent as IEntity;
            //if (sceneData != null)
            //{
            //    (VEFModule.UnityContainer.Resolve(typeof(ILoggerService), "") as ILoggerService).Log("Flatbuffer SceneDataModel.ColourAmbient.SetColourAmbient ungültig (" + newValue.ToString() + "): " + res, LogCategory.Error, LogPriority.High);


            //    //send to c++ DLL
            //    FBNetData tmp = objectdata.CreateFBData(null, null);

            //    //if (DLL_Singleton.Instance != null)
            //    //{
            //    //    //  todo  res = DLL_Singleton.Instance.command("cmd update 0", tmp, tmp.Length);
            //    //}
            //}

            if (res == 0) // OK = 0
            {
                oldValue = newValue;
            }

            return oldValue;
        }
    }
}
