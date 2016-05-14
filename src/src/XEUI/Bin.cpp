#include <XEUI/Bin.hpp>

namespace XE {

Widget::Ptr Bin::GetChild() const {
	if( GetChildren().size() < 1 ) {
		return Widget::Ptr();
	}

	return *GetChildren().begin();
}

//bool Bin::HandleAdd( Widget::Ptr child ) {
//	if (!GetChildren().empty()) {
//#if defined( SFGUI_DEBUG )
//		std::cerr << "SFGUI warning: Only one widget can be added to a Bin.\n";
//#endif
//
//		return false;
//	}
//
//	if (!Container::HandleAdd(child)) {
//		return false;
//	}
//
//	return true;
//}

}
