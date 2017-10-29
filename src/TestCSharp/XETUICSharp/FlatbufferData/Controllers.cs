// automatically generated, do not modify

namespace ControllerSettings
{
    
public enum Button : short
{
 None = -1,
 Left = 0,
 Right = 1,
 Middle = 2,
  ///< The middle (wheel) mouse button  
  ///< The first extra mouse button
 XButton1 = 3,
  ///< The second extra mouse button
 XButton2 = 4,
  ///< Keep last -- the total number of mouse buttons
 ButtonCount = 5,
};

public enum Axis : short
{
 None = -1,
 X = 0,
 Y = 1,
 Z = 2,
 R = 3,
 U = 4,
 V = 5,
  ///< The X axis of the point-of-view hat
 PovX = 6,
  ///< The Y axis of the point-of-view hat
 PovY = 7,
};

public enum KeyID : short
{
  ///< Unhandled key fb array index starts with 0!
 None = -1,
 A = 0,
 B = 1,
 C = 2,
 D = 3,
 E = 4,
 F = 5,
 G = 6,
 H = 7,
 I = 8,
 J = 9,
 K = 10,
 L = 11,
 M = 12,
 N = 13,
 O = 14,
 P = 15,
 Q = 16,
 R = 17,
 S = 18,
 T = 19,
 U = 20,
 V = 21,
 W = 22,
 X = 23,
 Y = 24,
 Z = 25,
 Num0 = 26,
 Num1 = 27,
 Num2 = 28,
 Num3 = 29,
 Num4 = 30,
 Num5 = 31,
 Num6 = 32,
 Num7 = 33,
 Num8 = 34,
 Num9 = 35,
  ///< The Escape key
 Escape = 36,
  ///< The left Control key
 LControl = 37,
  ///< The left Shift key
 LShift = 38,
  ///< The left Alt key
 LAlt = 39,
 LSystem = 40,
  ///< The right Control key
 RControl = 41,
  ///< The right Shift key
 RShift = 42,
  ///< The right Alt key
 RAlt = 43,
  ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...   
 RSystem = 44,
  ///< The Menu key  
 Menu = 45,
  ///< The [ key  
 LBracket = 46,
  ///< The ] key 
 RBracket = 47,
  ///< The ; key 
 SemiColon = 48,
  ///< The , key
 Comma = 49,
  ///< The . key
 Period = 50,
  ///< The ' key
 Quote = 51,
  ///< The / key
 Slash = 52,
  ///< The \ key
 BackSlash = 53,
  ///< The ~ key
 Tilde = 54,
  ///< The = key
 Equal = 55,
  ///< The - key
 Dash = 56,
  ///< The Space key    
 Space = 57,
  ///< The Return key
 Return = 58,
  ///< The Backspace key
 BackSpace = 59,
  ///< The Tabulation key
 Tab = 60,
  ///< The Page up key    
 PageUp = 61,
  ///< The Page down key
 PageDown = 62,
  ///< The End key
 End = 63,
  ///< The Home key
 Home = 64,
  ///< The Insert key
 Insert = 65,
  ///< The Delete key
 Delete = 66,
  ///< The + key     
 Add = 67,
  ///< The - key   
 Subtract = 68,
  ///< The * key
 Multiply = 69,
  ///< The / key   
 Divide = 70,
  ///< Left arrow
 Left = 71,
  ///< Right arrow
 Right = 72,
  ///< Up arrow
 Up = 73,
  ///< Down arrow
 Down = 74,
  ///< The numpad 0 key
 Numpad0 = 75,
  ///< The numpad 1 key 
 Numpad1 = 76,
  ///< The numpad 2 key 
 Numpad2 = 77,
  ///< The numpad 3 key
 Numpad3 = 78,
  ///< The numpad 4 key 
 Numpad4 = 79,
  ///< The numpad 5 key  
 Numpad5 = 80,
  ///< The numpad 6 key
 Numpad6 = 81,
  ///< The numpad 7 key
 Numpad7 = 82,
  ///< The  numpad 8 key
 Numpad8 = 83,
  ///< The numpad 9 key
 Numpad9 = 84,
 F1 = 85,
 F2 = 86,
 F3 = 87,
 F4 = 88,
 F5 = 89,
 F6 = 90,
 F7 = 91,
 F8 = 92,
 F9 = 93,
 F10 = 94,
 F11 = 95,
 F12 = 96,
 F13 = 97,
 F14 = 98,
 F15 = 99,
  ///< The Pause key
 Pause = 100,
  ///< Keep last -- the total number of keyboard keys
 KeyCount = 101,
};

public enum ActionType : ushort
{
 None = 0,
  ///< move forward
 Forward = 1,
  ///< move ForwardLeft
 ForwardLeft = 2,
  ///< move ForwardRight
 ForwardRight = 3,
  ///< move backward
 Backward = 4,
  ///< move BackwardLeft
 BackwardLeft = 5,
  ///< move BackwardRight
 BackwardRight = 6,
  ///< TurnLeft
 TurnLeft = 7,
  ///< TurnRight
 TurnRight = 8,
  ///< StrafeLeft
 StrafeLeft = 9,
  ///< StrafeRight
 StrafeRight = 10,
  ///< Jump
 Jump = 11,
  ///< Run
 Run = 12,
  ///< Walk
 Walk = 13,
  ///< Next Target
 NextTarget = 14,
  ///< Preview Target
 PrevTarget = 15,
  ///< Punch1
 Punch1 = 16,
  ///< Kick1
 Kick1 = 17,
  ///< Entity mit Camera drehen
 ObjRotate = 18,
  ///< ZoomIn
 ZoomIn = 19,
  ///< ZoomOut
 ZoomOut = 20,
  ///< Rotate Camera
 CamRotate = 21,
  ///< Point selection
 PointSelectStart = 22,
  ///< Point selection
 PointSelectEnd = 23,
  ///< Point selection
 PointMoved = 24,
  ///< Spell 1
 Spell1 = 25,
  ///< Spell 2
 Spell2 = 26,
  ///< Spell 3
 Spell3 = 27,
  ///< Aktion 1
 Action1 = 28,
  ///< Aktion 2	
 Action2 = 29,
  ///< Menu NavigationUP 
 NavUp = 30,
  ///< Menu NavigationDown 				
 NavDown = 31,
  ///< Menu NavigationLeft 			
 NavLeft = 32,
  ///< Menu NavigationRight 	
 NavRight = 33,
  ///< Menu Navigation selection
 NavSelect = 34,
 NavEnter = 35,
 TextEntered = 36,
 KeyPressed = 37,
 Shoot = 38,
 Resized = 39,
 Quit = 40,
};

public enum DeviceType : ushort
{
 DT_unknown = 0,
 DT_KeyMouse = 1,
 DT_Joy = 2,
 DT_Gamepad = 3,
 DT_count = 4,
};

public enum MouseWheelEvent : short
{
 None = -1,
 Plus = 0,
 Substract = 1,
};

public enum ActionOperator : ushort
{
 Or = 0,
 And = 1,
};

public enum EventType : short
{
  ///< Repeated input (e.g. a key that is held down).
 Hold = 0,
  ///< Press events that occur only once (e.g. key pressed).
 PressOnce = 1,
  ///< Release events that occur only once (e.g. key released).
 ReleaseOnce = 2,
};
    
}
