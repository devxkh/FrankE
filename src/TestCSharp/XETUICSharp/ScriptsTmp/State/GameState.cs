using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using XGame.Core.Components;
using XGame.Core.Engine;
using XGame.Core.Engine.Components;
using XGame.Core.Network;
using XGame.Core.Scene;
using XGame.Core.System;
using XGame.Core.Systems;

namespace XGame.Core
{
    public class GameState : State
    {   
        private PlayerControllerSystem _playerControllerSystem;
        private CharacterCameraSystem _characterCameraSystem;

        private CombatScene _scene;

        private Entity _entityBase;

        private CameraRenderable _cameraRender;
        private Controller _controller;
        private PlayerComponent _player;
        private ScreenComponent _screen;
        private CameraFree _camera;
        private NetObserver _NetObserver;


        public CameraFree CameraFree { get { return _camera; } }
        public PlayerComponent Player { get { return _player; } }

        public CombatScene Scene { get { return _scene; } }

        public GameState(IntPtr nativePtr)
            : base(nativePtr)
        {
            _scene = new CombatScene(0, this);

            _scene.AddSystem<CharacterCameraSystem>();
            var playerCtrlSystem = _scene.AddSystem<PlayerControllerSystem>();
        //    ControllerSystem ctrlSystem =_scene.AddSystem<ControllerSystem>();

            _entityBase =  _scene.CreateEntity();

            _cameraRender = (CameraRenderable)_entityBase.Assign_Component(new CameraRenderable());
            _camera = (CameraFree)_entityBase.Assign_Component(new CameraFree(_entityBase, _cameraRender));

            _controller = (Controller)_entityBase.Assign_Component(new Controller(_entityBase));
            _player = (PlayerComponent)_entityBase.Assign_Component(new PlayerComponent(_entityBase));

            _entityBase.Assign_Component(new NetIdComponent(_entityBase));
            
            _player.PlayerSetActionMap(_controller);
            _screen = _entityBase.Assign_ScreenComponent(_cameraRender);

            playerCtrlSystem.SetBasicInputEvents( _controller);
            //   CtrlSetBasicInputEvents(_controller.CPointer, "E:\\Projekte\\coop\\XEngine\\data\\Test\\XETController\\Controller.cfg");

            _screen.AddUIState(_entityBase);


            _NetObserver = new NetObserver(this);


        }

        void Constructed()
        {

        }

        void Destroying()
        {
          //  an_unmanaged_function(state, new MessageReceivedDelegate(OnMessageReceived));
        }
    }
}
