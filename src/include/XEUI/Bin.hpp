#pragma once

//#include </*SFGUI*//Config.hpp>
#include <XEUI/Container.hpp>
#include <memory>

namespace XE {

	/** Base class for containers with only one child.
	 */
	class Bin : public Container {
	public:
		typedef std::shared_ptr<Bin> Ptr; //!< Shared pointer.
		typedef std::shared_ptr<const Bin> PtrConst; //!< Shared pointer.

													 /** Get child widget.
													 * @return Child widget.
													 */
		Widget::Ptr GetChild() const;

	protected:
	};


}
