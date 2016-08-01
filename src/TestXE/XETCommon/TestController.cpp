#include "TestController.hpp"

#include <XEngine.hpp>

#include "Controllers_generated.h"
#include "Netmsg_generated.h"

namespace XET
{
	TestControllerComponent::TestControllerComponent(XE::Uint16 id, XE::XEngine& engine, SDL_Window* window, bool defaultCtrl)
		: ControllerComponent(id, engine, window, defaultCtrl)
	{
	}

	void TestControllerComponent::setActionMap(XE::ControllerComponent& controller)
	{
		std::cout << "settingActionMap!" << std::endl;

		controller.actionmap[ControllerSettings::ActionType::ActionType_TextEntered] = XE::Action(SDL_TEXTINPUT);
		controller.actionmap[ControllerSettings::ActionType::ActionType_KeyPressed] = XE::Action(SDL_KEYUP);
		controller.actionmap[ControllerSettings::ActionType::ActionType_KeyDown] = XE::Action(SDL_KEYDOWN);

		// Resize: Change window size (single event)
		controller.actionmap[ControllerSettings::ActionType::ActionType_Resized] = XE::Action(SDL_WINDOWEVENT);
		//actionmap[ControllerSettings::ActionType::ActionType_Quit] = Action(Event::Closed);

		//Actions festlegen
		controller.actionmap[ControllerSettings::ActionType::ActionType_PointSelectStart] = XE::Action(SDL_MOUSEBUTTONDOWN);// || XE::Action(sf::Mouse::Right, XE::Action::PressOnce);
		controller.actionmap[ControllerSettings::ActionType::ActionType_PointSelectEnd] = XE::Action(SDL_MOUSEBUTTONUP);// || XE::Action(sf::Mouse::Right, XE::Action::ReleaseOnce);
		controller.actionmap[ControllerSettings::ActionType::ActionType_PointMoved] = XE::Action(SDL_MOUSEMOTION);

		controller.actionmap[ControllerSettings::ActionType::ActionType_Quit] = XE::Action(SDL_SCANCODE_ESCAPE, XE::Action::PressOnce);// || XE::Action(SDL_SCANCODE_qui sf::Event::Closed);
		controller.actionmap[ControllerSettings::ActionType::ActionType_NavLeft] = XE::Action(SDL_SCANCODE_LEFT, XE::Action::PressOnce);
		controller.actionmap[ControllerSettings::ActionType::ActionType_NavRight] = XE::Action(SDL_SCANCODE_RIGHT, XE::Action::PressOnce);
		controller.actionmap[ControllerSettings::ActionType::ActionType_NavUp] = XE::Action(SDL_SCANCODE_UP, XE::Action::PressOnce);
		controller.actionmap[ControllerSettings::ActionType::ActionType_NavDown] = XE::Action(SDL_SCANCODE_DOWN, XE::Action::PressOnce);
		controller.actionmap[ControllerSettings::ActionType::ActionType_NavEnter] = XE::Action(SDL_SCANCODE_RETURN, XE::Action::PressOnce);
		
		//std::string schemafile;
		//std::string jsonfile;

		//flatbuffers::LoadFile("F:\\Projekte\\coop\\XGame\\_devFolder\\FlatBufTypes\\Controllers.fbs", false, &schemafile);
		//flatbuffers::LoadFile("F:\\Projekte\\coop\\XGame\\_devFolder\\FlatBufTypes\\Player_1.json", false, &jsonfile);
		//
		//// parse schema first, so we can use it to parse the data after
		//flatbuffers::Parser parser;

		////	const char *include_directories[] = { "samples", nullptr };
		//const char *include_directories[] = { nullptr };
		//parser.Parse(schemafile.c_str(), include_directories);
		//parser.Parse(jsonfile.c_str(), include_directories);

		//auto controllers = ControllerSettings::GetControllerList(parser.builder_.GetBufferPointer());

		XE::PhysFsStream wonderfullStream;
		if (!wonderfullStream.open("inputMap.fbbin"))
			return;

		// Make sure that the stream's reading position is at the beginning
		wonderfullStream.seek(0);

		std::vector<char> buffer(wonderfullStream.getSize());
		if (!wonderfullStream.read(buffer.data(), wonderfullStream.getSize()))
			return;

		auto controllers = ControllerSettings::GetControllerList(&buffer[0]);

		auto controller1 = controllers->ctrlList()->Get(0);

		//actions
		for (auto it = controller1->actionMap()->begin(); it != controller1->actionMap()->end(); ++it)
		{
			int j = 0;
			XE::Action::ActionType evtType = XE::Action::ActionType((*it)->eventType());

			auto events = (*it)->events();
			if (!events)
				continue;

			//events
			for (auto itEvt = events->begin(); itEvt != events->end(); ++itEvt)
			{
				XE::Action action;

				std::cout << "joyAxis:" << (*itEvt)->joyAxis() << "|EvtType:" << ControllerSettings::EnumNamesEventType()[evtType] << "|KeyCode:" << ((*itEvt)->kCode() < 0 ? -1 : (*itEvt)->kCode()) << "|name:" << ((*itEvt)->kCode() < 0 ? "-1" : ControllerSettings::EnumNamesKeyID()[(*itEvt)->kCode()]) << "|actionType:" << ControllerSettings::EnumNameActionType((*it)->actionType()) << "|actionOperator:" << ControllerSettings::EnumNameActionOperator((*itEvt)->actionOperator()) << std::endl;


				//if ((*itEvt)->joyAxis() != 0 && (*itEvt)->joyBtn() != -1)
				//{
				//	//	action = XE::Action(XE::JoystickButton(0, (*itEvt)->joyBtn()), evtType);
				//}
				//else
				if ((*itEvt)->kCode() != ControllerSettings::KeyID::KeyID_SDL_SCANCODE_UNKNOWN)
				{
					action = XE::Action((SDL_Scancode)(*itEvt)->kCode(), evtType);
				}
				else if ((*itEvt)->mouseBtn() != -1)
				{
					action = XE::Action((thor::MouseBottonID)(*itEvt)->mouseBtn());
				}
				else if ((*itEvt)->mWheel() != -1) //!= 0 -> none
				{
					action = XE::Action((thor::MouseWheelEvt)(*itEvt)->mWheel());
				}
				else
					continue;

				if (j == 0)
				{
					controller.actionmap[(*it)->actionType()] = action; // XE::Action(XE::JoystickButton(0, 2), evtType);
					j++;
				}
				else if ((*itEvt)->actionOperator() == ControllerSettings::ActionOperator::ActionOperator_And)
				{
					controller.actionmap[(*it)->actionType()] = controller.actionmap[(*it)->actionType()] && action;
				}
				else //or and none .....  if ((*itEvt)->actionOperator() == ControllerSettings::ActionOperator::ActionOperator_Or)
				{
					controller.actionmap[(*it)->actionType()] = controller.actionmap[(*it)->actionType()] || action;
				}
			}
		}
	}
}