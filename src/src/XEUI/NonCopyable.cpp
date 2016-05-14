#include <XEUI/NonCopyable.hpp>

namespace XE {

NonCopyable::NonCopyable() {
}

NonCopyable::~NonCopyable() {

}

NonCopyable::NonCopyable( const NonCopyable& ) {
}

const NonCopyable& NonCopyable::operator=( const NonCopyable& ) {
	return *this;
}

} // namespace XE