#pragma once
#include <XEUI/Container.hpp>
#include <XEUI/Misc.hpp>


#include <memory>
#include <list>
#include <cstdint>

namespace XE {

	class WLayer;
	class WRectangle;

/** Box sizer.
 * Widgets are arranged horizontally or vertically.
 */
class Box : public Container {
	public:
		typedef std::shared_ptr<Box> Ptr; //!< Shared pointer.
		typedef std::shared_ptr<const Box> PtrConst; //!< Shared pointer.

		~Box();

		/** Box orientation.
		 */
		enum class Orientation : std::uint8_t {
			HORIZONTAL = 0, //!< Arrange horizontally.
			VERTICAL //!< Arrange vertically.
		};

		/** Create box.
		 * @param orientation Orientation.
		 * @param spacing Spacing = space between widgets.
		 * @return Box.
		 */
		static Ptr Create(WLayer&  layer, Orientation orientation = Orientation::HORIZONTAL, float spacing = 0.f );

		virtual const std::string& GetName() const override;

		/** Add a widget to the end of the box.
		 * Alias to PackEnd(...) for backward compatibility.
		 * @param widget Widget.
		 * @param expand Expand widget to highest possible size.
		 * @param fill Fill calculated size.
		 */
		void Pack( Widget::Ptr widget, bool expand = true, bool fill = true );

		/** Add a widget to the start of the box.
		 * @param widget Widget.
		 * @param expand Expand widget to highest possible size.
		 * @param fill Fill calculated size.
		 */
		void PackStart( Widget::Ptr widget, bool expand = true, bool fill = true );

		/** Add a widget to the end of the box.
		 * @param widget Widget.
		 * @param expand Expand widget to highest possible size.
		 * @param fill Fill calculated size.
		 */
		void PackEnd( Widget::Ptr widget, bool expand = true, bool fill = true );

		/** Reorder a child to a new location within the box.
		 * @param widget Child to reorder.
		 * @param position Position to reorder to. 0 for the start, size - 1 or greater for the end.
		 */
		void ReorderChild( Widget::Ptr widget, std::size_t position );

		/** Set spacing.
		 * @param spacing Spacing.
		 */
		void SetSpacing( float spacing );

		/** Get spacing.
		 * @return Spacing.
		 */
		float GetSpacing() const;
		
		virtual void setPosition(const sf::Vector2f& pos) override;

		void draw();

	protected:
		/** Get requisition.
		 * @return Requisition.
		 */
	//	sf::Vector2f calculateSize();

	private:
		struct ChildInfo {
			Widget::Ptr widget;
			bool expand;
			bool fill;

			ChildInfo( Widget::Ptr widget_, bool expand_ = true, bool fill_ = true );
			bool operator==( const ChildInfo& rhs ) const;
		};

		typedef std::list<ChildInfo> ChildrenCont;

		Box(WLayer&  layer, Orientation orientation = Orientation::HORIZONTAL, float spacing = 0.f );

		void AllocateChildren() const;
		bool IsChildInteresting( Widget::PtrConst child ) const;

		ChildrenCont m_box_children;
		float m_spacing;
		Orientation m_orientation;

		WRectangle* m_DebugRectangle;
		WLayer& m_layer;
};

}
