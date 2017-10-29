using FrankeCSharp.Interface;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using XGame.Core.Components;
using XGame.Core.Engine.Components;
using XGame.Core.System;

namespace XGame.Core.Engine
{

    public class Entity : ObjectBase
    {
        private IList<IComponent> _components = new List<IComponent>();

        private struct EntityTransfer
        {
            public UInt64 id;
            public IntPtr entityHolderPtr;
        }

        public UInt64 ID { get; private set; }

        //private CameraFree _camera;
        //public CameraFree Assign_Camera(CameraRenderable renderable)
        //{
        //    return _camera = new CameraFree(this, renderable);
        //}

        //private CameraRenderable _cameraRenderable;
        //public CameraRenderable Assign_CameraRenderable(SceneBase scene)
        //{
        //    return _cameraRenderable = new CameraRenderable(0, scene, this);
        //}

        //private Controller _controller;
        //public Controller Assign_Controller()
        //{
        //    return _controller = new Controller(this);
        //}
        
        public IComponent Assign_Component(IComponent component)
        {
            _components.Add(component);
            component.ID = _components.Count();
            return component;
        }

        //private NetIdComponent _NetIdComponent;
        //public NetIdComponent Assign_NetIdComponent()
        //{
        //    return _NetIdComponent = new NetIdComponent(this);
        //}
        //private Body _body;
        //public Body Assign_Body()
        //{
        //    return _body = new Body(this);
        //}

        public T GetComponent<T>() where T : IComponent
        {
            ObjectBase component = null; // new T(); //todo not needed if component already created in c#

            foreach (var comp in _components)
            {
                if (comp.GetType() == typeof(T))
                    component = (ObjectBase)comp;
            }
            //if(typeof(T).Name == "Body" && _body == null)
            //    return null;
            //if (typeof(T).Name == "PlayerComponent" && _player == null)
            //    return null;
            //if (typeof(T).Name == "Controller" && _controller == null)
            //    return null;
            //if (typeof(T).Name == "CameraRenderable" && _cameraRenderable == null)
            //    return null;
            //if (typeof(T).Name == "CameraFree" && _camera == null)
            //    return null;

            //if (typeof(T).Name == "NetIdComponent" && _NetIdComponent == null)
            //    return null;

          //  T component = new T(); //todo not needed if component already created in c#

            component.CPointer = GetComponent(CPointer, typeof(T).Name);

            if (component.CPointer == IntPtr.Zero)
                component = null;//component not found
            
            
                try
                {
                    return (T)Convert.ChangeType(component, typeof(T));
                }
                catch (InvalidCastException)
                {
                    return default(T);
                }
            

//            return (typeof(T))component;
        }


        private ScreenComponent _screenComponent;
        public ScreenComponent Assign_ScreenComponent(CameraRenderable camRenderable)
        {
            return _screenComponent = new ScreenComponent(camRenderable, this);
        }

        /// <summary>
        /// Handle the destruction of the object
        /// </summary>
        /// <param name="disposing">Is the GC disposing the object, or is it an explicit call ?</param>
        protected override void Destroy(bool disposing)
        {
            DestroyEntity(CPointer);
        }

        public Entity(SceneBase scene)
            : base(IntPtr.Zero)
        {
            var transfer = CreateEntity(scene.CPointer);
            CPointer = transfer.entityHolderPtr;
            ID = transfer.id;

        }

        /// <summary>
        /// entity already added to scene
        /// </summary>
        /// <param name="id"></param>
        /// <param name="entityPtr"></param>
        public Entity(UInt64 id, IntPtr entityPtr)
            : base(entityPtr)
        {
            ID = id;

        }


        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe EntityTransfer CreateEntity(IntPtr scenePtr);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe IntPtr GetComponent(IntPtr entityHolder, string component);


        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern unsafe void RemoveComponent(IntPtr entity, string name);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        static extern  unsafe void DestroyEntity(IntPtr ptr);
    }
}
