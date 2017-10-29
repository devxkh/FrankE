using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using XGame.Core.Components;
using XGame.Core.Engine;
using XGame.Core.System;

namespace XGame.Core
{
    public class XGame : ObjectBase
    {
        public string ResourceConfigFile { get; set; }

        public string Title { get; set; }

        private GameState _currentState;

        public XGame() :
              base(IntPtr.Zero)
        {
            
        }

        public void Run()
        {
            try
            {
                bool test = xEngine_test(true);

                UnityContainer.Get().Engine = new EngineBase(CPointer = xEngine_create(Title, ResourceConfigFile));

                CreateStateCallback createStateCallback =
               (newState) =>
               {
                   //create State
                   _currentState = new GameState(newState);
                    // Console.WriteLine("Progress = {0}", value);
                };

                MainLoopBeforeUpdateCallback beforeUpdateCallback =
             (deltaTime) =>
             {
                 BeforeUpdate(deltaTime);
                 // Console.WriteLine("Progress = {0}", value);
             };

                MainLoopAfterUpdateCallback afterUpdateCallback =
             (deltaTime) =>
             {
                 AfterUpdate(deltaTime);
                   // Console.WriteLine("Progress = {0}", value);
               };


                xEngine_run(CPointer, createStateCallback, beforeUpdateCallback
                    , afterUpdateCallback); //-> calls create state callback on c side
            }
            catch (Exception ex)
            {

            }

        }

        private void BeforeUpdate(float deltaTime)
        {
            _currentState.Scene.Updated(deltaTime);
        }

        private void AfterUpdate(float deltaTime)
        {

        }

        /// <summary>
        /// Handle the destruction of the object
        /// </summary>
        /// <param name="disposing">Is the GC disposing the object, or is it an explicit call ?</param>
        protected override void Destroy(bool disposing)
        {
        }


        #region Imports

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern unsafe IntPtr xEngine_create([MarshalAs(UnmanagedType.LPStr)] string title,
                                                      [MarshalAs(UnmanagedType.LPStr)] string resourceFile);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern bool xEngine_test(bool test);

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void CreateStateCallback(IntPtr statePtr);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void MainLoopBeforeUpdateCallback(float delateTime);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void MainLoopAfterUpdateCallback(float delateTime);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern unsafe void xEngine_run(IntPtr CPointer, CreateStateCallback callbackPointer , MainLoopBeforeUpdateCallback beforeUpdateCallbackPointer , MainLoopAfterUpdateCallback afterUpdateCallbackPointer);
       
        #endregion
    }

}
