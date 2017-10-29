using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using XGame.Core.Engine;
using XGame.Core.System;

namespace XGame.Core.Network
{
    internal unsafe sealed class PinnedManagedArrayAllocator<T>
       // : Disposable
          where T : struct
    {
        private Dictionary<IntPtr, T[]> pbArrayToArray;
        private Dictionary<IntPtr, GCHandle> pbArrayToGCHandle;

        public PinnedManagedArrayAllocator()
        {
            this.pbArrayToArray = new Dictionary<IntPtr, T[]>();
            this.pbArrayToGCHandle = new Dictionary<IntPtr, GCHandle>();
        }

        // (Finalizer is already implemented by the base class (Disposable))

        //protected override void Dispose(bool disposing)
        //{
        //    if (this.pbArrayToGCHandle != null)
        //    {
        //        foreach (GCHandle gcHandle in this.pbArrayToGCHandle.Values)
        //        {
        //            gcHandle.Free();
        //        }

        //        this.pbArrayToGCHandle = null;
        //    }

        //    this.pbArrayToArray = null;

        //    base.Dispose(disposing);
        //}

        // Pass a delegate to this method for “gpc_vertex_calloc_fn”. Don’t forget to use GC.KeepAlive() on the delegate! 
        //public IntPtr AllocateArray(int count)
        //{
        //    T[] array = new T[count];
        //    GCHandle gcHandle = GCHandle.Alloc(array, GCHandleType.Pinned);
        //    IntPtr pbArray = gcHandle.AddrOfPinnedObject();
        //    this.pbArrayToArray.Add(pbArray, array);
        //    this.pbArrayToGCHandle.Add(pbArray, gcHandle);
        //    return pbArray;
        //}

        // This is what you would use instead of, e.g. Marshal.Copy()
        public T[] GetManagedArray(IntPtr pbArray)
        {
            return this.pbArrayToArray[pbArray];
        }
    }

    //http://stackoverflow.com/questions/17549123/c-sharp-performance-using-unsafe-pointers-instead-of-intptr-and-marshal
    public class MarshalMatters
    {
        public static T ReadUsingMarshalUnsafe<T>(byte[] data) where T : struct
        {
            unsafe
            {
                fixed (byte* p = &data[0])
                {
                    return (T)Marshal.PtrToStructure(new IntPtr(p), typeof(T));
                }
            }
        }

        public unsafe static byte[] WriteUsingMarshalUnsafe<selectedT>(selectedT structure, ushort len) where selectedT : struct
        {
            byte[] byteArray = new byte[len];//Marshal.SizeOf(structure)];
            fixed (byte* byteArrayPtr = byteArray)
            {
                Marshal.StructureToPtr(structure, (IntPtr)byteArrayPtr, false);
            }
            return byteArray;
        }
    }


    public class DanB
    {
        /// <summary>
        /// uses Marshal.Copy! Not run in unsafe. Uses AllocHGlobal to get new memory and copies.
        /// </summary>
        public static byte[] GetBytes<T>(T structure) where T : struct
        {
            var size = Marshal.SizeOf(structure); //or Marshal.SizeOf<selectedT>(); in .net 4.5.1
            byte[] rawData = new byte[size];
            IntPtr ptr = Marshal.AllocHGlobal(size);

            Marshal.StructureToPtr(structure, ptr, true);
            Marshal.Copy(ptr, rawData, 0, size);
            Marshal.FreeHGlobal(ptr);
            return rawData;
        }

        public static T FromBytes<T>(byte[] bytes) where T : struct
        {
            var structure = new T();
            int size = Marshal.SizeOf(structure);  //or Marshal.SizeOf<selectedT>(); in .net 4.5.1
            IntPtr ptr = Marshal.AllocHGlobal(size);

            Marshal.Copy(bytes, 0, ptr, size);

            structure = (T)Marshal.PtrToStructure(ptr, structure.GetType());
            Marshal.FreeHGlobal(ptr);

            return structure;
        }
    }

    public class NetObserver : ObjectBase
    {
        public NetObserver(State state)
            : base(IntPtr.Zero)
        {
      
            HandleDataCallback updateCallback = ( fbData, len, entity) =>
            {
                HandleData(fbData, len, entity);
            };

            StartNetObserver(UnityContainer.Get().Engine.CPointer, state.CPointer ,0, true, updateCallback);

        }

        /// <summary>
        /// callback
        /// </summary>
        /// <param name="fbData"></param>
        /// <param name="entity"></param>
        void HandleData(IntPtr fbData, ushort len, IntPtr entity)
        {
              byte[] ba = new byte[len];
              Marshal.Copy(fbData, ba, 0, len);

         //doesnt work!!   var ba= MarshalMatters.WriteUsingMarshalUnsafe(fbData,len);

            //FlatBuffers.ByteBuffer fbb = new FlatBuffers.ByteBuffer(ba);
            //var root = NetMsg.MessageRoot.GetRootAsMessageRoot(fbb);

            //if (root.DataType == NetMsg.Data.ReturnStatus)
            //{
            //    // method filling a preconstructed object
            //    var preconstructedReturnStatus = new NetMsg.ReturnStatus();
            //    var returnStatus = root.GetData(preconstructedReturnStatus);
            //    switch (returnStatus.Status)
            //    {
            //        case NetMsg.MsgStatus.S_LoginSuccess:
            //            //netID already set from server
            //            break;
            //        default:
            //            Debug.WriteLine("Login Error:" + returnStatus.Status.ToString());
            //            break;
            //    }
            //}
            //else if (root.DataType == NetMsg.Data.RenderableComponent)
            //{

            //}
            //else if (root.DataType == NetMsg.Data.Node)
            //{
            //    // method filling a preconstructed object
            //    var preconstructedNode = new XFBType.Node();
            //    root.GetData(preconstructedNode);
            //}
                    
        }

        /// <summary>
        /// Handle the destruction of the object
        /// </summary>
        /// <param name="disposing">Is the GC disposing the object, or is it an explicit call ?</param>
        protected override void Destroy(bool disposing)
        {
            //todo   destroy(CPointer);
        }

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void HandleDataCallback(IntPtr fbData, ushort len, IntPtr entity);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void StartNetObserver(IntPtr engine, IntPtr state, ushort stateId, bool isClient, [MarshalAs(UnmanagedType.FunctionPtr)] HandleDataCallback callbackPointer);

        

    }
}
