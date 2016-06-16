#include <XEngine/Controller/SDLInputHandler.hpp>

namespace XE {

	SDLInputHandler::SDLInputHandler():
		m_wantRelative(false),
		m_wantMouseGrab(false),
		m_wantMouseVisible(true),
		m_isMouseRelative(!m_wantRelative),
		m_wrapPointerManually(false),
		m_grabPointer(false),
		m_mouseInWindow(true),
		m_windowHasFocus(true),
		m_warpX(0),
		m_warpY(0),
		m_warpCompensate(false)
	{


		 
	}

	void SDLInputHandler::onWindowEvent(XE::ActionContext& context)
	{
		switch (context.event->window.event)
		{
		case SDL_WINDOWEVENT_ENTER:
			m_mouseInWindow = true;
			updateMouseSettings(context.window);
			break;
		case SDL_WINDOWEVENT_LEAVE:
			m_mouseInWindow = false;
			updateMouseSettings(context.window);
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			m_windowHasFocus = true;
			updateMouseSettings(context.window);
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			m_windowHasFocus = false;
			updateMouseSettings(context.window);
			break;
		}
	}

	//-----------------------------------------------------------------------------------
	void SDLInputHandler::setGrabMousePointer(bool grab, SDL_Window* window)
	{
		m_wantMouseGrab = grab;
		updateMouseSettings(window);
	}
	//-----------------------------------------------------------------------------------
	void SDLInputHandler::setMouseRelative(bool relative, SDL_Window* window)
	{
		m_wantRelative = relative;
		updateMouseSettings(window);
	}
	//-----------------------------------------------------------------------------------
	void SDLInputHandler::setMouseVisible(bool visible, SDL_Window* window)
	{
		m_wantMouseVisible = visible;
		updateMouseSettings(window);
	}

	//-----------------------------------------------------------------------------------
	void SDLInputHandler::warpMouse(int x, int y, SDL_Window* window)
	{
		SDL_WarpMouseInWindow(window, x, y);
		m_warpCompensate = true;
		m_warpX = x;
		m_warpY = y;
	}
	//-----------------------------------------------------------------------------------
	void SDLInputHandler::wrapMousePointer(const SDL_MouseMotionEvent& evt, SDL_Window* window)
	{
		//Don't wrap if we don't want relative movements, support
		//relative movements natively, or aren't grabbing anyways
		if (m_isMouseRelative || !m_wrapPointerManually || !m_grabPointer)
			return;

		int width = 0;
		int height = 0;

		SDL_GetWindowSize(window, &width, &height);

		const int FUDGE_FACTOR_X = width;
		const int FUDGE_FACTOR_Y = height;

		//Warp the mouse if it's about to go outside the window
		if (evt.x - FUDGE_FACTOR_X < 0 || evt.x + FUDGE_FACTOR_X > width ||
			evt.y - FUDGE_FACTOR_Y < 0 || evt.y + FUDGE_FACTOR_Y > height)
		{
			warpMouse(width / 2, height / 2, window);
		}
	}
	//-----------------------------------------------------------------------------------
	bool SDLInputHandler::handleWarpMotion(const SDL_MouseMotionEvent& evt)
	{
		if (!m_warpCompensate)
			return false;

		//This was a warp event, signal the caller to eat it.
		if (evt.x == m_warpX && evt.y == m_warpY)
		{
			m_warpCompensate = false;
			return true;
		}

		return false;
	}

	void SDLInputHandler::updateMouseSettings(SDL_Window* window)
	{
		m_grabPointer = m_wantMouseGrab && m_mouseInWindow && m_windowHasFocus;
		SDL_SetWindowGrab(window, m_grabPointer ? SDL_TRUE : SDL_FALSE);

		SDL_ShowCursor(m_wantMouseVisible || !m_windowHasFocus);

		bool relative = m_wantRelative && m_mouseInWindow && m_windowHasFocus;
		if (m_isMouseRelative == relative)
			return;

		m_isMouseRelative = relative;

		m_wrapPointerManually = false;

		//Input driver doesn't support relative positioning. Do it manually.
		int success = SDL_SetRelativeMouseMode(relative ? SDL_TRUE : SDL_FALSE);
		if (!relative || (relative && success != 0))
			m_wrapPointerManually = true;

		//Remove all pending mouse events that were queued with the old settings.
		SDL_PumpEvents();
		SDL_FlushEvent(SDL_MOUSEMOTION);
	}

} // ns XE