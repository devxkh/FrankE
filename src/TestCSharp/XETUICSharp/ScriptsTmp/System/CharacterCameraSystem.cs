using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using XGame.Core.Components;
using XGame.Core.Engine;
using XGame.Core.System;

namespace XGame.Core.Systems
{
    public class CharacterCameraSystem : ObjectBase , ISystem
    {
        public CharacterCameraSystem():
            base(IntPtr.Zero)
        {

        }

        public void Update(SceneBase scene, float dt)
        {
            foreach(var entity in scene.Entities)
            {
                var camera = entity.GetComponent<CameraFree>();
             //   var cameraRenderable = entity.GetComponent<CameraRenderable>();
                if (camera != null)
                {

                  
                    //if (camera.CamType == Cam_Type.CA_CHARACTER)
                    //{
                    //    // move the camera smoothly to the goal
                    //    Vector3 goalOffset = camera.CameraGoal.WorldPosition - camera.CameraNode.Position;
                    //    camera.CameraNode.Translate(goalOffset * dt * 9.0f);

                    //    // always look at the pivot
                    //    camera.CameraNode.LookAt(camera.CameraPivot.WorldPosition);

                    //}else if(camera.CamType == Cam_Type.CA_FREE)
                    //{
                        //bool speedmodifier = false;
                        //Vector3 camMovementDir = camera.Camera_GetMove();
                        //camMovementDir = Vector3.Vector3_Normalize(camMovementDir);
                        //camMovementDir *= dt * 10.0f * (1);// + speedmodifier * 5);
                        
                        //camera.Camera_MoveRelative(camMovementDir);


              //      }
                }
            }
        }
        

        /// <summary>
        /// Handle the destruction of the object
        /// </summary>
        /// <param name="disposing">Is the GC disposing the object, or is it an explicit call ?</param>
        protected override void Destroy(bool disposing)
        {
            //todo   destroy(CPointer);
        }
    }
}
