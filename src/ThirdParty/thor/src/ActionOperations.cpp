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

#include <Thor/Input/Detail/ActionOperations.hpp>

#include <SDL.h>

#include <iterator>
#include <algorithm>

using namespace std::placeholders;

#include <Thor/Input/Action.hpp>

namespace thor
{
namespace detail
{
	EventBuffer::EventBuffer()
	: mEvents()
	, mRealtimeEnabled(true)
	{
	}

	void EventBuffer::pushEvent(const SDL_Event& event)
	{
		// Generate realtime actions only if window has the focus. For example, key presses don't invoke callbacks when the
		// window is not focussed.
		switch (event.type)
		{
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			mRealtimeEnabled = true;
			break;

		case SDL_WINDOWEVENT_FOCUS_LOST:
			mRealtimeEnabled = false;
			break;
		}

		// Store event
		mEvents.push_back(event);
	}

	void EventBuffer::clearEvents()
	{
		mEvents.clear();
	}

	bool EventBuffer::containsEvent(const EventNode& filterNode) const
	{
		std::vector<SDL_Event> unused;
		return filterEvents(filterNode, unused);
	}

	bool EventBuffer::filterEvents(const EventNode& filterNode, std::vector<SDL_Event>& out) const
	{
		// Variable to check if something was actually inserted (don't look at range, it's not filtered yet)
		std::size_t oldSize = out.size();

		// Copy events that fulfill filter criterion to the end of the output vector
		std::copy_if(mEvents.begin(), mEvents.end(), std::back_inserter(out), std::bind(&EventNode::isEventActive, &filterNode, _1));
		return oldSize != out.size();
	}

	bool EventBuffer::isRealtimeInputEnabled() const
	{
		return mRealtimeEnabled;
	}

	void EventBuffer::pollEvents()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
			pushEvent(event);
	}
	
	// ---------------------------------------------------------------------------------------------------------------------------
	
	
	ActionResult::ActionResult()
	: eventContainer()
	, nbRealtimeTriggers(0u)
	{
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	ActionNode::~ActionNode()
	{
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	EventNode::EventNode()
	: mEvent()
	{
	}

	bool EventNode::isActionActive(const EventBuffer& buffer) const
	{
		return buffer.containsEvent(*this);
	}

	bool EventNode::isActionActive(const EventBuffer& buffer, ActionResult& out) const
	{
		return buffer.filterEvents(*this, out.eventContainer);
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	bool RealtimeNode::isActionActive(const EventBuffer& buffer) const
	{
		return buffer.isRealtimeInputEnabled() && isRealtimeActive();
	}

	bool RealtimeNode::isActionActive(const EventBuffer& buffer, ActionResult& out) const
	{
		if (isActionActive(buffer))
		{
			++out.nbRealtimeTriggers;
			return true;
		}
		else
		{
			return false;
		}
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	RealtimeKeyLeaf::RealtimeKeyLeaf(SDL_Scancode key)
	: RealtimeNode()
	, mKey(key)
	{
	}

	bool RealtimeKeyLeaf::isRealtimeActive() const
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[mKey])
			return true; // is pressed
		else 
			return false;	
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	EventKeyLeaf::EventKeyLeaf(SDL_Scancode key, bool pressed)
	: EventNode()
	{
		mEvent.type = pressed ? SDL_KEYDOWN : SDL_KEYUP;
		mEvent.key.keysym.scancode = key;
	}

	bool EventKeyLeaf::isEventActive(const SDL_Event& event) const
	{
		return event.type == mEvent.type && event.key.keysym.scancode == mEvent.key.keysym.scancode;
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	RealtimeMouseLeaf::RealtimeMouseLeaf(MouseBottonID mouseButton)
	: RealtimeNode()
	, mMouseButton(mouseButton)
	{
	}

	bool RealtimeMouseLeaf::isRealtimeActive() const
	{
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(mMouseButton))
			return true;
		else
			return false;
	}

	// ---------------------------------------------------------------------------------------------------------------------------
	
	EventMouseLeaf::EventMouseLeaf(MouseBottonID mouseButton, bool pressed)
	: EventNode()
	{
		mEvent.type = pressed ? SDL_MOUSEBUTTONDOWN : SDL_MOUSEBUTTONUP;
		mEvent.button.button = mouseButton;
	}

	bool EventMouseLeaf::isEventActive(const SDL_Event& event) const
	{
		return event.type == mEvent.type && event.button.button == mEvent.button.button;
	}

	// ---------------------------------------------------------------------------------------------------------------------------

	EventMouseWheelLeaf::EventMouseWheelLeaf(MouseWheelEvt mouseWheel)
		: EventNode() 
	{
		mEvent.type = SDL_MOUSEWHEEL;
		switch (mouseWheel)
		{
		case thor::MW_UP: mEvent.wheel.y = 1;  break;
		case thor::MW_DOWN: mEvent.wheel.y = -1;  break;
		case thor::MW_LEFT: mEvent.wheel.x = -1;  break;
		case thor::MW_RIGHT: mEvent.wheel.x = 1;  break;
		}
	}

	bool EventMouseWheelLeaf::isEventActive(const SDL_Event& event) const {

		if (event.type == mEvent.type && event.wheel.y != 0)
		{
			if (event.wheel.y > 0 && mEvent.wheel.y == -1)
			{
				return true; //UP
			}
			else if (event.wheel.y < 0 && mEvent.wheel.y == 1)
			{
				return true; //DOWN
			}
		}
		else if (event.type == mEvent.type && event.wheel.x != 0)
		{	
			if (event.wheel.x > 0 && mEvent.wheel.x == -1)
			{
				return true; //RIGHT
			}
			else if (event.wheel.x < 0 && mEvent.wheel.x == 1)
			{
				return true; //LEFT
			}
		}

		return false; 
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	RealtimeJoystickButtonLeaf::RealtimeJoystickButtonLeaf(SDL_JoyButtonEvent joystick)
	: RealtimeNode()
	, mJoystick(joystick)
	{
	}

	bool RealtimeJoystickButtonLeaf::isRealtimeActive() const
	{
		return  mJoystick.type == SDL_JOYBUTTONDOWN;// sf::Joystick::isButtonPressed(mJoystick.which, mJoystick.button);
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	RealtimeJoystickAxisLeaf::RealtimeJoystickAxisLeaf(SDL_JoyAxisEvent joystick)
	: RealtimeNode()
	, mJoystick(joystick)
	{
	}

	bool RealtimeJoystickAxisLeaf::isRealtimeActive() const
	{
		//FIXME
		//float axisPos = mJoystick.value; //  sf::Joystick::getAxisPosition(mJoystick.joystickId, mJoystick.axis);

		//return mJoystick.type == SDL_Joy .above && axisPos > mJoystick.threshold
		//	|| !mJoystick.above && axisPos < mJoystick.threshold;
		return false;
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	EventJoystickLeaf::EventJoystickLeaf(SDL_JoyButtonEvent joystick, bool pressed)
	: EventNode()
	{
		mEvent.type = pressed ? SDL_JOYBUTTONDOWN : SDL_JOYBUTTONUP;
		//FIXME
		//mEvent.jbutton. = joystick.button;//.joy.joystickButton.joystickId = joystick.joystickId;
		//mEvent.joystickButton.button = joystick.button;
	}

	bool EventJoystickLeaf::isEventActive(const SDL_Event& event) const
	{
		return event.type == mEvent.type && event.jbutton.button == mEvent.jbutton.button;
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	MiscEventLeaf::MiscEventLeaf(SDL_EventType eventType)
	: EventNode()
	{
		mEvent.type = eventType;
	}

	bool MiscEventLeaf::isEventActive(const SDL_Event& event) const
	{
		return mEvent.type == event.type;
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	CustomEventLeaf::CustomEventLeaf(std::function<bool(const SDL_Event&)> filter)
	: mFilter(std::move(filter))
	{
	}

	bool CustomEventLeaf::isEventActive(const SDL_Event& event) const
	{
		return mFilter(event);
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	CustomRealtimeLeaf::CustomRealtimeLeaf(std::function<bool()> filter)
	: mFilter(std::move(filter))
	{
	}

	bool CustomRealtimeLeaf::isRealtimeActive() const
	{
		return mFilter();
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	OrNode::OrNode(ActionNode::CopiedPtr lhs, ActionNode::CopiedPtr rhs)
	: ActionNode()
	, mLhs(std::move(lhs))
	, mRhs(std::move(rhs))
	{
	}

	bool OrNode::isActionActive(const EventBuffer& buffer) const
	{
		return mLhs->isActionActive(buffer) || mRhs->isActionActive(buffer);
	}

	bool OrNode::isActionActive(const EventBuffer& buffer, ActionResult& out) const
	{
		// Prevent shortcut semantics of logical OR: If first operand is true, the second's vector isn't filled.
		bool lhsValue = mLhs->isActionActive(buffer, out);
		bool rhsValue = mRhs->isActionActive(buffer, out);

		return lhsValue || rhsValue;
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	AndNode::AndNode(ActionNode::CopiedPtr lhs, ActionNode::CopiedPtr rhs)
	: ActionNode()
	, mLhs(std::move(lhs))
	, mRhs(std::move(rhs))
	{
	}

	bool AndNode::isActionActive(const EventBuffer& buffer) const
	{
		return mLhs->isActionActive(buffer) && mRhs->isActionActive(buffer);
	}

	bool AndNode::isActionActive(const EventBuffer& buffer, ActionResult& out) const
	{
		// Don't modify out if whole logical AND expression is false -> use temporary result state
		ActionResult tmpResult;

		// If both calls return true, copy events and realtime counter
		if (mLhs->isActionActive(buffer, tmpResult) && mRhs->isActionActive(buffer, tmpResult))
		{
			out.eventContainer.insert(out.eventContainer.end(), tmpResult.eventContainer.begin(), tmpResult.eventContainer.end());
			out.nbRealtimeTriggers += tmpResult.nbRealtimeTriggers;
			return true;
		}
		else
		{
			return false;
		}
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	NotNode::NotNode(ActionNode::CopiedPtr action)
	: ActionNode()
	, mAction(std::move(action))
	{
	}

	bool NotNode::isActionActive(const EventBuffer& buffer) const
	{
		return !mAction->isActionActive(buffer);
	}

	bool NotNode::isActionActive(const EventBuffer& buffer, ActionResult& out) const
	{
		// Don't modify if action is active -> use temporary result state
		ActionResult tmpResult;

		if (!mAction->isActionActive(buffer, tmpResult))
		{
			out.eventContainer.insert(out.eventContainer.end(), tmpResult.eventContainer.begin(), tmpResult.eventContainer.end());
			out.nbRealtimeTriggers += tmpResult.nbRealtimeTriggers;
			return true;
		}
		else
		{
			return false;
		}
	}

} // namespace detail
} // namespace thor
