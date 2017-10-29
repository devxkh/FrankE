using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using XGame.Core.System;

namespace XGame.Core.Engine
{
    public class State : ObjectBase
    {
        public State(IntPtr nativePtr)
            :base(nativePtr)
        {
            StateCreatedCallback callback = (value) =>
            {
                StateCreated();
                // Console.WriteLine("Progress = {0}", value);
            };

            // call DoWork in C code
            StateCreate(callback);

            
        }

        /// <summary>
        /// Handle the destruction of the object
        /// </summary>
        /// <param name="disposing">Is the GC disposing the object, or is it an explicit call ?</param>
        protected override void Destroy(bool disposing)
        {
         //todo   destroy(CPointer);
        }

        protected virtual void StateCreated() { }

        protected virtual void SceneCreated() { }

        // public delegate void MessageReceivedDelegate(IntPtr state);


        //Define an unmanaged delegate in the C# code like –
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void StateCreatedCallback(IntPtr statePtr);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void StateCreate([MarshalAs(UnmanagedType.FunctionPtr)] StateCreatedCallback callbackPointer);

        //[DllImport(@"E:\Projekte\coop\XGame_build\Debug\XGame-d.dll")]
        //protected static extern void CtrlSetBasicInputEvents(IntPtr controller, string filename);

        // [DllImport(@"E:\Projekte\coop\XGame_build\Debug\XGame-d.dll", EntryPoint = "FreeImage_SetOutputMessage")]
        // public static extern void an_unmanaged_function(IntPtr state, MessageReceivedDelegate call);
    }
}
