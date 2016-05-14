#pragma once

//#include <SFGUI/Config.hpp>
#include <XEUI/Widget.hpp>
#include <memory>
#include <vector>

namespace XE {

/**
 * Base class for container-like widgets.
 */
class Container : public Widget {
public:
	typedef std::shared_ptr<Container> Ptr; //!< Shared pointer.
	typedef std::shared_ptr<const Container> PtrConst; //!< Shared pointer.
	typedef std::vector<Widget::Ptr> WidgetsList;

	/** Dtor.
	*/
	//virtual ~Container() = default;
	virtual ~Container()
	{

	}

	/** Add child.
	* @param widget Widget to add.
	*/
	virtual void Add(Widget::Ptr widget);

	/** Remove child (from container).
	* @param widget Widget to remove.
	*/
	virtual void Remove(Widget::Ptr widget);

	/** Remove all children from container.
	*/
	void RemoveAll();

	/** Check if a widget is a child of this container.
	* @param widget Widget to search for.
	*/
	bool IsChild(Widget::Ptr widget) const;

	/** Get children.
	* @return std::list with children.
	*/
	const WidgetsList& GetChildren() const;

	void Refresh() override;

	void HandleEvent(const sf::Event& event) override;

	/** Used to inform parent that a child has been invalidated
	* @param child Widget that was invalidated.
	*/
	virtual void HandleChildInvalidate(Widget::PtrConst child) const;


protected:

	/** Handle visibility change.
	*/
	void HandleGlobalVisibilityChange() override;
	

	WidgetsList m_children;

private:
};

}