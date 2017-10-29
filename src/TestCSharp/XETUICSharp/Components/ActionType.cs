using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XGame.Core.Game.Components
{
    enum ActionType : ushort
    {
        None,
        //Steuerung
        ///< move forward
        Forward,
        ///< move ForwardLeft
        ForwardLeft,
        ///< move ForwardRight
        ForwardRight,
        ///< move backward
        Backward,
        ///< move BackwardLeft
        BackwardLeft,
        ///< move BackwardRight
        BackwardRight,
        ///< TurnLeft
        TurnLeft,
        ///< TurnRight
        TurnRight,
        ///< StrafeLeft
        StrafeLeft,
        ///< StrafeRight
        StrafeRight,
        ///< Jump
        Jump,
        ///< Run
        Run,
        ///< Walk
        Walk,
        ///< Next Target
        NextTarget,
        ///< Preview Target
        PrevTarget,
        ///< Punch1
        Punch1,
        ///< Kick1
        Kick1,
        ///< Entity mit Camera drehen
        ObjRotate,

        //Camera
        ///< ZoomIn
        ZoomIn,
        ///< ZoomOut
        ZoomOut,
        ///< Rotate Camera
        CamRotate,
        ///< Point selection
        PointSelectStart,
        ///< Point selection
        PointSelectEnd,
        ///< Point selection
        PointMoved,

        //Ohne Combos
        ///< Spell 1
        Spell1,
        ///< Spell 2
        Spell2,
        ///< Spell 3
        Spell3,
        ///< Aktion 1
        Action1,
        ///< Aktion 2	
        Action2,

        //Menu
        ///< Menu NavigationUP 
        NavUp,
        ///< Menu NavigationDown 				
        NavDown,
        ///< Menu NavigationLeft 			
        NavLeft,
        ///< Menu NavigationRight 	
        NavRight,
        ///< Menu Navigation selection
        NavSelect,
        NavEnter,

        TextEntered,
        KeyPressed,

        Shoot,
        Resized,
        Quit
    }

}
