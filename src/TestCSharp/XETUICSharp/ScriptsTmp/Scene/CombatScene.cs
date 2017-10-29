using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using XGame.Core.Components;
using XGame.Core.Engine;
using XGame.Core.Engine.Components;

namespace XGame.Core.Scene
{
    public class CombatScene : SceneBase
    {
        public CombatScene(int id, GameState state)
            : base(id, state)
        {

        }

        public override void Updated(float dt)
        {
            foreach (var system in Systems)
            {
                system.Update(this, dt);
            }

            var position = ((GameState)_parentState).CameraFree.CameraNode.Position;
            var orientation = ((GameState)_parentState).CameraFree.CameraNode.Orientation;

            position.Y = 80;
            ((GameState)_parentState).CameraFree.CameraNode.Position = position;
            //  orientation = ((GameState)_parentState).CameraFree.CameraNode.Orientation;

            foreach (var entity in _entities)
            {
                Body body = (Body)entity.GetComponent<Body>();
                var controller = (Controller)entity.GetComponent<Controller>();
                if (body != null)
                {
                    //body.Position = new Components.Vector3()
                    //{
                    //    X = 0,
                    //    Y = 1,
                    //    Z = 0
                    //};
                }
                if (controller != null)
                {
                    var pos = controller.GetMousePosition();
            
                }
            }
        }

        public void OnCreated()
        {

        }

        public void OnUpdate()
        {

        }
    }
}
