#pragma once

//#include <SFGUI/Config.hpp>
#include <XEUI/Signal.hpp>
#include <XEUI/NonCopyable.hpp>
//#include <XEUI/SharedPtr.hpp>

namespace XE {

	enum NavAction
	{
		NavAction_None,
		NavAction_NavUp,
		///< Menu NavigationDown 				
		NavAction_NavDown,
		///< Menu NavigationLeft 			
		NavAction_NavLeft,
		///< Menu NavigationRight 	
		NavAction_NavRight,
		///< Menu Navigation selection
		NavAction_NavSelect,
		NavAction_NavEnter,
	};

	/** Base class for all Widget, Adjustment and Tooltip objects.
	 */
	class Object : public NonCopyable
	{
	public:
		typedef  std::shared_ptr<Object> Ptr; //!< Shared pointer.
		typedef  std::shared_ptr<const Object> PtrConst; //!< Shared pointer.


		/** Ctor.
		*/
		Object() = default;

		/** Dtor.
		*/
		virtual ~Object() = default;

		/// @cond
			// Fix for VS2013 not supporting = default move members.
#if defined( _MSC_VER )
		/** Deleted Copy Ctor.
		*/
		Object(const Object&) = delete;

		/** Deleted Copy Assignment.
		*/
		Object& operator=(const Object&) = delete;
#else
		/** Move Ctor.
		*/
		Object(Object&&) = default;

		/** Move Assignment.
		*/
		Object& operator=(Object&&) = default;
#endif
		/// @endcond


		/** Request a reference to a specific signal for this object.
		 * @param id Requested signal id.
		 * @return Reference to requested signal.
		 */
		Signal& GetSignal(Signal::SignalID& id);

	protected:

		/** Get the signal container.
		 * @return Reference to the signal container.
		 */
		SignalContainer& GetSignals();

	private:
		// Signals.
		SignalContainer m_signals;
	};

} // namespace XE