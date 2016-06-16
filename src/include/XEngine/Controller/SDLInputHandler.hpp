//Thanks to Jordan Milne and Scrawl for allowing to use their
//sdlinputwrapper files as base under the MIT license

#ifndef __SDL_INPUTHANDLER_HPP__
#define __SDL_INPUTHANDLER_HPP__

#include <XESystem/SystemConfig.hpp>
#include <Thor/Input/ActionMap.hpp>
#include <SDL.h>

namespace XE {

	typedef thor::ActionContext<std::size_t> ActionContext;

	class SDLInputHandler
	{
	public:

		SDLInputHandler();

		/// Locks the pointer to the window
		void setGrabMousePointer(bool grab, SDL_Window* window);

		/// Set the mouse to relative positioning mode (when not supported
		/// by hardware, we emulate the behavior).
		/// From the SDL docs: While the mouse is in relative mode, the
		/// cursor is hidden, and the driver will try to report continuous
		/// motion in the current window. Only relative motion events will
		/// be delivered, the mouse position will not change.
		void setMouseRelative(bool relative, SDL_Window* window);

		/// Shows or hides the mouse cursor.
		void setMouseVisible(bool visible, SDL_Window* window);

	protected:

		void onWindowEvent(XE::ActionContext& context);

		/// Moves the mouse to the specified point within the viewport
		void warpMouse(int x, int y, SDL_Window* window);

		/// Prevents the mouse cursor from leaving the window.
		void wrapMousePointer(const SDL_MouseMotionEvent& evt, SDL_Window* window);

		/// Internal method for ignoring relative
		/// motions as a side effect of warpMouse()
		bool handleWarpMotion(const SDL_MouseMotionEvent& evt);

		void updateMouseSettings(SDL_Window* window);


		// User settings
		/// User setting. From the SDL docs: While the mouse is in relative mode, the
		/// cursor is hidden, and the driver will try to report continuous motion in
		/// the current window. Only relative motion events will be delivered, the
		/// mouse position will not change.
		bool        m_wantRelative;
		/// Locks the pointer to remain inside the window.
		bool        m_wantMouseGrab;
		/// Whether to show the mouse.
		bool        m_wantMouseVisible;

		// Describes internal state.
		bool        m_isMouseRelative;
		/// Used when driver doesn't support relative mode.
		bool        m_wrapPointerManually;
		bool        m_grabPointer;
		bool        m_mouseInWindow;
		bool        m_windowHasFocus;

		Uint16      m_warpX;
		Uint16      m_warpY;
		bool        m_warpCompensate;
	};

} // ns XE

#endif // __SDL_INPUTHANDLER_HPP__