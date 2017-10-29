using NetMsg;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using XFBType;
using XGame.Core.Components;
using XGame.Core.Engine;
using XGame.Core.Engine.Components;
using XGame.Core.Game.Components;
using XGame.Core.System;

namespace XGame.Core.Systems
{
    public class PlayerControllerSystem : ObjectBase, ISystem
    {
        private Vector2 _lastMousePosition;

        public PlayerControllerSystem():
            base(IntPtr.Zero)  { }

        public void Update(SceneBase scene, float dt)
        {
            foreach(var ent in scene.Entities)
            {
                UpdateActionMap(ent, dt);
            }
        }

        public void UpdateActionMap(Entity entity, float dt)
        {
            Controller ctrl = (Controller)entity.GetComponent<Controller>();
            var player = entity.GetComponent<PlayerComponent>();
            CameraFree cameraFree = (CameraFree)entity.GetComponent<CameraFree>();
            var netID = entity.GetComponent<NetIdComponent>();

            if (ctrl == null || player == null)
                return;

            if (netID != null)
            {
                //normally the client just send events to the server
                //for debugging and developement it should be possible to send body pos,rot,loc etc.
                if (netID.ID == 0)
                {
              //      PrefabMsg.SendLogin(netID);
                }

                //logged in
                if(netID.ID > 0)
                {
                    //FlatBuffers.FlatBufferBuilder fbb = new FlatBuffers.FlatBufferBuilder(4);
                    //InputEvent.StartInputEvent(fbb);
                    //InputEvent.AddActionType(fbb, ControllerSettings.ActionType.BackwardRight); // BackwardRight gibts nicht!!
                    //InputEvent.AddActionData(fbb, Vec3f.CreateVec3f(fbb, 0, 0, 0));
                    //var ievt = InputEvent.EndInputEvent(fbb);
                    //fbb.Finish(ievt.Value);//important!

                    //MessageRoot.CreateMessageRoot(fbb, netID.ID, 0, Data.Login, ievt.Value);

                    //UnityContainer.Get().Engine.SendToServer(netID, fbb.SizedByteArray(), (uint)fbb.SizedByteArray().Length);
                }
            }

            Player_UpdateActionMap(CPointer, entity.CPointer, dt);

            if (Player_AMap_IsActive(ctrl.CPointer, ActionType.Forward))
            {
                if (cameraFree != null)
                    cameraFree.CameraNode.Translate(new Vector3(0, 0, 1));
            }
            if (Player_AMap_IsActive(ctrl.CPointer, ActionType.Backward))
            {
                if (cameraFree != null)
                    cameraFree.CameraNode.Translate(new Vector3(0, 0, -1));
            }

            if (Player_AMap_IsActive(ctrl.CPointer, ActionType.TurnLeft))
            {
                if (cameraFree != null)
                    cameraFree.CameraNode.Translate(new Vector3(-1, 0, 0));
            }

            if (Player_AMap_IsActive(ctrl.CPointer, ActionType.TurnRight))
            {
                if (cameraFree != null)
                    cameraFree.CameraNode.Translate(new Vector3(1, 0, 0));
            }


            if (Player_AMap_IsActive(ctrl.CPointer, ActionType.CamRotate))
            {
                var pos = ctrl.GetMousePosition();
                if (_lastMousePosition != pos && _lastMousePosition != new Vector2(0, 0))
                {
                    ctrl.SetMousePosition(_lastMousePosition);
                    var delta = _lastMousePosition - pos;

                    cameraFree.CameraNode.Rotate(delta.X, delta.Y);

                }
            }
            else
            {
                _lastMousePosition = ctrl.GetMousePosition();

         //       Debug.WriteLine("LastMousePos:" + _lastMousePosition.ToString());

            }
        }

        public void SetBasicInputEvents(Controller controller)
        {
            PlayerControllerSystemSetBasicInputEvents(CPointer, controller.CPointer);
        }

        /// <summary>
        /// Handle the destruction of the object
        /// </summary>
        /// <param name="disposing">Is the GC disposing the object, or is it an explicit call ?</param>
        protected override void Destroy(bool disposing)
        {
            //todo   destroy(CPointer);
        }


        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void PlayerControllerSystemSetBasicInputEvents(IntPtr playerCtrlSystem, IntPtr controller);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe void Player_UpdateActionMap(IntPtr playerCtrlSystem, IntPtr entity, float dt);

        [DllImport(EngineBase.DLLPath, CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        private static extern unsafe bool Player_AMap_IsActive(IntPtr controllerComponent, ActionType aType);
    }
}
