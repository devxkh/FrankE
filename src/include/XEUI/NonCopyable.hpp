#pragma once

//#include <SFGUI/Config.hpp>

namespace XE {

/** NonCopyable interface.
 * Prevents derivates from being copied/assigned.
 */
class NonCopyable {
	protected:
		NonCopyable();
		~NonCopyable();

	private:
		NonCopyable( const NonCopyable& );
		const NonCopyable& operator=( const NonCopyable& );
};

} // namespace XE
