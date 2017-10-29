using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using XGame.Core.Components;
using XGame.Core.System;

namespace XGame.Core.Engine
{
    public class SceneBase : ObjectBase
    {
        protected State _parentState;
        private int _id;
        protected List<ISystem> _systems;
        protected List<Entity> _entities;

        public List<Entity> Entities { get { return _entities; } }
      
        public List<ISystem> Systems { get { return _systems; } }

        public SceneBase(int id,State state)
            : base(IntPtr.Zero)
        {
            _parentState = state;
            _id = id;
            _entities = new List<Entity>();
            _systems = new List<ISystem>();

            SceneCreatedCallback callback = () =>
            {

                // Console.WriteLine("Progress = {0}", value);
            };

             SceneUpdateCallback updateCallback = (value) =>
             {
                 //not used !!!!!!!!!!!!
                 Updated(value);
                 // Console.WriteLine("Progress = {0}", value);
             };

            EntityAddedCallback entityAddedCallback = (UInt64 entityID, IntPtr entityHolder) =>
            {
                _entities.Add(new Entity(entityID, entityHolder));
                // Console.WriteLine("Progress = {0}", value);
            };

            EntityRemovedCallback entityRemovedCallback = (UInt64 entityID) =>
            {

                // Console.WriteLine("Progress = {0}", value);
            };

            CPointer = GetScene(_parentState.CPointer, id, callback, updateCallback, entityAddedCallback, entityRemovedCallback, true); //call sceneCreate in c++

        }

        public T AddSystem<T>() where T : ObjectBase , ISystem, new()
        {
            T system = new T();

            system.CPointer = AddSystem(CPointer, typeof(T).Name);

            if (system.CPointer == IntPtr.Zero)
                system = null;//system not created
            else
                _systems.Add(system); 

            return system;
        }


        public virtual void Updated(float dt)
        { }

        public Entity CreateEntity()
        {
            Entity newEntity = new Entity(this);
            _entities.Add(newEntity);
            return newEntity;
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
        private delegate void SceneCreatedCallback();

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void SceneUpdateCallback(float deltaTime);

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void EntityAddedCallback(UInt64 entityID, IntPtr entityHolder);

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void EntityRemovedCallback(UInt64 entityID);


        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe IntPtr GetScene(IntPtr parentStateNativePtr, int id
            , [MarshalAs(UnmanagedType.FunctionPtr)] SceneCreatedCallback callbackPointer
            , [MarshalAs(UnmanagedType.FunctionPtr)] SceneUpdateCallback sceneUpdateCB
            , [MarshalAs(UnmanagedType.FunctionPtr)] EntityAddedCallback EntityAddedCB
            , [MarshalAs(UnmanagedType.FunctionPtr)] EntityRemovedCallback EntityRemovedCB, bool createNew);


        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe IntPtr AddSystem(IntPtr scenePtr, string systemName);


    }
}
