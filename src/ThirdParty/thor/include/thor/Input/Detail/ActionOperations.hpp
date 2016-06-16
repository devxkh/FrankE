/////////////////////////////////////////////////////////////////////////////////
//
// Thor C++ Library
// Copyright (c) 2011-2014 Jan Haller
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

#ifndef THOR_ACTIONOPERATIONS_HPP
#define THOR_ACTIONOPERATIONS_HPP

#include <Thor/Input/Joystick.hpp>
#include <Thor/Config.hpp>

#include <Aurora/SmartPtr/CopiedPtr.hpp>

//#include <SFML/Window/Event.hpp>
//#include <SFML/Window/Keyboard.hpp>
//#include <SFML/Window/Mouse.hpp>
//#include <SFML/Window/Joystick.hpp>

#include <SDL.h>

#include <vector>
#include <functional>


namespace thor
{
	enum MouseBottonID;
	enum MouseWheelEvt;

	namespace detail
	{
		class EventNode;

		// Class that stores events and provides methods for lookup
		// Note: Since there are at most a few dozens of events per frame (at a decent framerate not even that), std::vector and linear search is fine
		class THOR_API EventBuffer
		{
		public:
			EventBuffer();

			// Modifiers
			void						pushEvent(const SDL_Event& event);
			void						clearEvents();
			void						pollEvents();

			// Accessors
			bool						containsEvent(const EventNode& filterNode) const;
			bool						filterEvents(const EventNode& filterNode, std::vector<SDL_Event>& out) const;
			bool						isRealtimeInputEnabled() const;

		private:
			std::vector<SDL_Event>		mEvents;
			bool						mRealtimeEnabled;
		};

		// Structure to collect the SDL_Event instances and number of realtime triggers.
		struct THOR_API ActionResult
		{
			ActionResult();

			std::vector<SDL_Event>		eventContainer;
			unsigned int				nbRealtimeTriggers;
		};

		// ---------------------------------------------------------------------------------------------------------------------------


		// Operation base class for event actions. The operations are organized in a tree structure.
		class ActionNode
		{
		public:
			typedef aurora::CopiedPtr<ActionNode>	CopiedPtr;

		public:
			virtual						~ActionNode();
			virtual bool				isActionActive(const EventBuffer& buffer) const = 0;
			virtual bool				isActionActive(const EventBuffer& buffer, ActionResult& out) const = 0;
		};

		// Class between ActionNode and concrete Event classes
		class EventNode : public ActionNode
		{
		public:
			EventNode();

			virtual bool				isActionActive(const EventBuffer& buffer) const;
			virtual bool				isActionActive(const EventBuffer& buffer, ActionResult& out) const;
			virtual bool				isEventActive(const SDL_Event& event) const = 0;

		protected:
			SDL_Event					mEvent;
		};

		// Class between ActionNode and concrete Realtime classes
		class RealtimeNode : public ActionNode
		{
		public:
			virtual bool				isActionActive(const EventBuffer& buffer) const;
			virtual bool				isActionActive(const EventBuffer& buffer, ActionResult& out) const;
			virtual bool				isRealtimeActive() const = 0;
		};

		// Operation node class for keys currently held down
		class RealtimeKeyLeaf : public RealtimeNode
		{
		public:
			explicit					RealtimeKeyLeaf(SDL_Scancode key);
			virtual bool				isRealtimeActive() const;

		private:
			SDL_Scancode			mKey;
		};

		// Operation node class for key events (either pressed or released)
		class EventKeyLeaf : public EventNode
		{
		public:
			EventKeyLeaf(SDL_Scancode key, bool pressed);
			virtual bool				isEventActive(const SDL_Event& event) const;
		};

		// Operation node class for mouse buttons currently held down
		class RealtimeMouseLeaf : public RealtimeNode
		{
		public:
			explicit					RealtimeMouseLeaf(MouseBottonID mouseButton);
			virtual bool				isRealtimeActive() const;

		private:
			MouseBottonID			mMouseButton;
		};

		// Operation node class for mouse button events (either pressed or released)
		class EventMouseLeaf : public EventNode
		{
		public:
			EventMouseLeaf(MouseBottonID mouseButton, bool pressed);
			virtual bool				isEventActive(const SDL_Event& event) const;
		};

		class EventMouseWheelLeaf : public EventNode
		{
		public:
			EventMouseWheelLeaf(MouseWheelEvt mouseWheel);
			virtual bool				isEventActive(const SDL_Event& event) const;
		};

		// Operation node class for joystick buttons currently held down
		class RealtimeJoystickButtonLeaf : public RealtimeNode
		{
		public:
			explicit					RealtimeJoystickButtonLeaf(SDL_JoyButtonEvent joystick);
			virtual bool				isRealtimeActive() const;

		private:
			SDL_JoyButtonEvent				mJoystick;
		};

		// Operation node class for joystick axis events (movement of certain axis above threshold)
		class RealtimeJoystickAxisLeaf : public RealtimeNode
		{
		public:
			RealtimeJoystickAxisLeaf(SDL_JoyAxisEvent joystick);
			virtual bool				isRealtimeActive() const;

		private:
			SDL_JoyAxisEvent				mJoystick;
		};

		// Operation node class for joystick button events (either pressed or released)
		class EventJoystickLeaf : public EventNode
		{
		public:
			EventJoystickLeaf(SDL_JoyButtonEvent joystick, bool pressed);
			virtual bool				isEventActive(const SDL_Event& event) const;
		};

		// Operation node class for other SFML events
		class MiscEventLeaf : public EventNode
		{
		public:
			explicit					MiscEventLeaf(SDL_EventType eventType);
			virtual bool				isEventActive(const SDL_Event& event) const;
		};

		// Operation node class for user-defined event-based actions
		class CustomEventLeaf : public EventNode
		{
		public:
			explicit					CustomEventLeaf(std::function<bool(const SDL_Event&)> filter);
			virtual bool				isEventActive(const SDL_Event& event) const;

		private:
			std::function<bool(const SDL_Event&)>	mFilter;
		};

		// Operation node class for user-defined realtime-based actions
		class CustomRealtimeLeaf : public RealtimeNode
		{
		public:
			explicit					CustomRealtimeLeaf(std::function<bool()> filter);
			virtual bool				isRealtimeActive() const;

		private:
			std::function<bool()>		mFilter;
		};

		// Logical OR operator
		class OrNode : public ActionNode
		{
		public:
			OrNode(ActionNode::CopiedPtr lhs, ActionNode::CopiedPtr rhs);
			virtual bool				isActionActive(const EventBuffer& buffer) const;
			virtual bool				isActionActive(const EventBuffer& buffer, ActionResult& out) const;

		private:
			ActionNode::CopiedPtr		mLhs;
			ActionNode::CopiedPtr		mRhs;
		};

		// Logical AND operator
		class AndNode : public ActionNode
		{
		public:
			AndNode(ActionNode::CopiedPtr lhs, ActionNode::CopiedPtr rhs);
			virtual	bool				isActionActive(const EventBuffer& buffer) const;
			virtual bool				isActionActive(const EventBuffer& buffer, ActionResult& out) const;

		private:
			ActionNode::CopiedPtr		mLhs;
			ActionNode::CopiedPtr		mRhs;
		};

		// Logical NOT operator
		class NotNode : public ActionNode
		{
		public:
			explicit					NotNode(ActionNode::CopiedPtr action);
			virtual	bool				isActionActive(const EventBuffer& buffer) const;
			virtual bool				isActionActive(const EventBuffer& buffer, ActionResult& out) const;

		private:
			ActionNode::CopiedPtr		mAction;
		};

	} // namespace detail
} // namespace thor

#endif // THOR_ACTIONOPERATIONS_HPP
