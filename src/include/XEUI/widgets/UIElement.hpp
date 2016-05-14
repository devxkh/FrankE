#ifndef UI_ELEMENT_HPP
#define UI_ELEMENT_HPP

#include <XEOSConfig.hpp>
#include <XEUI/Object.hpp>
#include <XESystem/XEMemory/XEMemoryPrerequisites.hpp>

namespace XE {
namespace UI {

class UIElement : public Object
{
public:
	UIElement(Uint32 id)
	{
		mID = id;
	}
	Uint32 getID(){ return mID; }
private:
	Uint32 mID;
	SYS::String mType; // Type button,submenu ..
	UIElement* mParent; //parent Element
};

} // namespace UI
} // namespace XE

#endif