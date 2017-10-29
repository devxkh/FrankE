using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using XGame.Core.Engine.Components;
using XGame.Core.System;

namespace XGame.Core.Engine
{
    public class EngineBase : ObjectBase
    {
        public const string DLLPath = @"E:\Projekte\coop\XGame_build2017\Debug\XGame_Client-d.exe";
        
        public EngineBase(IntPtr ptr)
                : base(ptr)
        {

        }

        /// <summary>
        /// Handle the destruction of the object
        /// </summary>
        /// <param name="disposing">Is the GC disposing the object, or is it an explicit call ?</param>
        protected override void Destroy(bool disposing)
        {

            xEngine_destroy(CPointer);
        }

        public void SendToServer(NetIdComponent netID, byte[] buffer, uint size)
        {
            unsafe
            {
                fixed (byte* pByte = buffer)
                SendToServer(netID.CPointer, CPointer, new IntPtr((void*)pByte), size);
            }
        }

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void SendToServer(IntPtr netId, IntPtr engine, IntPtr data, uint dataLength);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void xEngine_destroy(IntPtr CPointer);
    }
}
