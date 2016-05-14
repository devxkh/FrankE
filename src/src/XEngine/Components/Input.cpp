#include <XEngine/Components/Input.hpp>

namespace XE
{
	using namespace thor;
	using namespace sf;

	InputComponent::InputComponent(bool defaultCtrl = false)
	{
		//default mouse keyboard
		if (defaultCtrl)
		{
			std::cout << "settingActionMap!" << std::endl;

			actionmap[InputCmd::TextEntered] = Action(Event::TextEntered);
			actionmap[InputCmd::KeyPressed] = Action(Event::KeyPressed);

			// Resize: Change window size (single event)
			actionmap[InputCmd::Resized] = Action(Event::Resized);
			actionmap[InputCmd::Quit] = Action(Event::Closed);

			//Actions festlegen
			actionmap[InputCmd::PointSelectStart] = Action(Mouse::Left, Action::PressOnce) || Action(Mouse::Right, Action::PressOnce);
			actionmap[InputCmd::PointSelectEnd] = Action(Mouse::Left, Action::ReleaseOnce) || Action(Mouse::Right, Action::ReleaseOnce);
			actionmap[InputCmd::PointMoved] = Action(Event::MouseMoved);

			actionmap[InputCmd::CamRotateStart] = Action(Mouse::Left, Action::PressOnce);
			actionmap[InputCmd::CamRotate] = Action(Mouse::Left, Action::Hold);
			actionmap[InputCmd::ObjRotateStart] = Action(Mouse::Right, Action::PressOnce);
			actionmap[InputCmd::ObjRotate] = Action(Mouse::Right, Action::Hold);

			actionmap[InputCmd::ZoomIn] = Action(Event::MouseWheelMoved);
			actionmap[InputCmd::ZoomOut] = Action(Event::MouseWheelMoved);


			actionmap[InputCmd::Quit] = Action(Keyboard::Escape, Action::PressOnce) || Action(Event::Closed);
			actionmap[InputCmd::NavLeft] = Action(Keyboard::Left, Action::PressOnce);
			actionmap[InputCmd::NavRight] = Action(Keyboard::Right, Action::PressOnce);
			actionmap[InputCmd::NavUp] = Action(Keyboard::Up, Action::PressOnce);
			actionmap[InputCmd::NavDown] = Action(Keyboard::Down, Action::PressOnce);
			actionmap[InputCmd::NavEnter] = Action(Keyboard::Return, Action::PressOnce);
		}
	}

	void InputComponent::loadControllerFile()
	{
		InputConfigFile cfg;

		//todo load from resource !!
		cfg.load("E:\\Projekte\\coop\\XEngine\\data\\Test\\XETController\\Controller.cfg", "=:\t", false);

		//---------------------------------------------------------------------------
		// Alle Aktionen auslesen
		// Aktion: z.B. Forward
		//---------------------------------------------------------------------------
		for (int actionInt = InputCmd::None; actionInt != InputCmd::Count; actionInt++)
		{
			InputCmd::MyAction action = static_cast<InputCmd::MyAction>(actionInt);

			std::string actionName = InputCmd::EnumStrings[action];

			std::stringstream controllerName;
			controllerName << mID;

			std::string actionCfg = cfg.getSetting(actionName, controllerName.str());

			std::cout << "Action:" << actionName;

			//---------------------------------------------------------------------
			// EventTyp
			// z.B. Key,Mouse etc.
			//---------------------------------------------------------------------

			std::vector<std::string> eventTypes = split(actionCfg, ',');
			std::queue<Action> eventsCombined; // Actions aus cfg file mit && verknüpft
			for (std::vector<std::string>::iterator it = eventTypes.begin(); it != eventTypes.end(); ++it)
			{
				std::vector<std::string> actions = split(*it, '_');
				//std::cout << ",Events:" << actions.size();

				int i = 0;
				std::string sType;
				std::string sEvent;

				for (std::vector<std::string>::iterator it = actions.begin(); it != actions.end(); ++it)
				{
					if (i == 0) sType = *it;
					else if (i == 1) sEvent = *it;

					std::cout << (i == 0 ? "#_Type:" : "#Event:") << *it;

					if (i == 1) // nur die Events adden nicht die typen an sich
					{
						switch (action){
						case InputCmd::Forward:
						case InputCmd::Backward:
						case InputCmd::StrafeLeft:
						case InputCmd::StrafeRight:
						case InputCmd::ForwardLeft:
						case InputCmd::ForwardRight:
						case InputCmd::BackwardLeft:
						case InputCmd::BackwardRight:
						case InputCmd::TurnLeft:
						case InputCmd::TurnRight:
							if (sType.compare("Key") == 0)
							{
								eventsCombined.push(Action(toKeyboardKey(sEvent), Action::Hold));
								mCrtlDevice = CD_KeyMouse;
							}
							else if (sType.compare("Joy") == 0)
							{
								//	Joy(0).button(2)
								Event testEv;
								testEv.joystickMove.axis = toJoystickAxis(sEvent);
								eventsCombined.push(Action(JoystickButton(0, 2), Action::PressOnce));
								mCrtlDevice = CD_Joy;
							}
							break;
						default:
							if (sType.compare("Key") == 0)
								eventsCombined.push(Action(toKeyboardKey(sEvent), Action::PressOnce));
							else if (sType.compare("Joy") == 0)
								//todo joy Buttons!
								eventsCombined.push(Action(JoystickButton(0, 2), Action::PressOnce));
							else if (sType.compare("MOUSE") == 0)
								eventsCombined.push(Action(toMouseButton(sEvent), Action::PressOnce));

							break;
						}
					}
					i++;
				}


			}

			//	mActionmap[action] =  Action(Mouse::Left, Action::PressOnce);
			//	mActionmap[action] &&  Action(Mouse::Right, Action::PressOnce);
			int j = 0;
			while (!eventsCombined.empty())
			{
				if (j == 0)
					actionmap[action] = eventsCombined.front();
				else
					actionmap[action] = actionmap[action] && eventsCombined.front();

				eventsCombined.pop();
				j++;
			}


			//		mActionmap[action] = eventsCombined.back() && eventsCombined.back();


			//map[foo] = Action(toKeyboardKey(sEvent), Action::PressOnce);*/

			//map[foo] = Action(Mouse::Left, Action::PressOnce) || Action(Joy(0).button(2), Action::PressOnce);


			std::cout << std::endl;
		}
	}


	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}

	std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}


}
