#include <XEUI/Box.hpp>

#include <XERenderer/GUI/WLayer.hpp>
#include <XERenderer/GUI/WRectangle.hpp>
#include <iterator>

namespace XE {

Box::Box(WLayer&  layer, Orientation orientation, float spacing ) :
	m_spacing( spacing ),
	m_orientation( orientation )
	,m_layer(layer)
{
	m_shapesContainer.shapes.emplace_back(std::move(std::unique_ptr<WRectangle>(new WRectangle(layer, 0, 0, 0, 0))));
	m_DebugRectangle = static_cast<WRectangle*>(m_shapesContainer.shapes.back().get());
}


Box::~Box()
{

}

Box::Ptr Box::Create(WLayer&  layer, Orientation orientation, float spacing ) {
	return Ptr( new Box( layer, orientation, spacing ) );
}


void Box::draw() {

	//m_DebugRectangle.setBackgroundImage("item_ball_hover.png");
	m_DebugRectangle->setBackground(Ogre::ColourValue::Blue);

	m_DebugRectangle->setPosition(Widget::getPosition());
	m_DebugRectangle->setSize(size);
	//sf::FloatRect req(GetAllocation());
	//sf::FloatRect parentAllocation(GetParent()->GetAllocation());

	//m_Label.setPosition(sf::Vector2f(parentAllocation.left + req.left, parentAllocation.top + req.top));
	//m_Label.setSize(req.width, req.height);
	//m_Label.SetText(GetText());
	//return Context::Get().GetEngine().CreateLabelDrawable( std::dynamic_pointer_cast<const Label>( shared_from_this() ) );
}

const std::string& Box::GetName() const {
	static const std::string name( "Box" );
	return name;
}

void Box::PackEnd( Widget::Ptr widget, bool expand, bool fill ) {
	if( IsChild( widget ) ) {
		return;
	}

	// It's important to create the ChildInfo object first, so that the
	// HandleAdd() method recognized the widget as a correctly packed one.
	m_box_children.push_back( ChildInfo( widget, expand, fill ) );
	Add( widget );

	size.x = std::max(size.x, widget->size.x);
	size.y += widget->size.y;

	AllocateChildren();
}

void Box::PackStart( Widget::Ptr widget, bool expand, bool fill ) {
	if( IsChild( widget ) ) {
		return;
	}

	// It's important to create the ChildInfo object first, so that the
	// HandleAdd() method recognized the widget as a correctly packed one.
	m_box_children.push_front( ChildInfo( widget, expand, fill ) );
	Add( widget );
}

void Box::Pack( Widget::Ptr widget, bool expand, bool fill ) {
	PackEnd( widget, expand, fill );
}

void Box::ReorderChild( Widget::Ptr widget, std::size_t position ) {
	ChildrenCont::iterator iter( std::find( m_box_children.begin(), m_box_children.end(), widget ) );

	if( iter == m_box_children.end() ) {
		return;
	}

	position = std::min( position, m_box_children.size() - 1 );

	ChildrenCont::iterator insertion_point( m_box_children.begin() );
	std::advance( insertion_point, position );
	m_box_children.insert( insertion_point, *iter );
	m_box_children.erase( iter );

	Refresh();
	AllocateChildren();
}

//void Box::HandleRemove( Widget::Ptr child ) {
//	ChildrenCont::iterator iter( std::find( m_box_children.begin(), m_box_children.end(), child ) );
//
//	if( iter != m_box_children.end() ) {
//		m_box_children.erase( iter );
//	}
//
//	Refresh();
//	AllocateChildren();
//}


Box::ChildInfo::ChildInfo( Widget::Ptr widget_, bool expand_, bool fill_ ) :
	widget( widget_ ),
	expand( expand_ ),
	fill( fill_ )
{
}

bool Box::ChildInfo::operator==( const ChildInfo& rhs ) const {
	return widget == rhs.widget;
}

void Box::SetSpacing( float spacing ) {
	m_spacing = spacing;
}

float Box::GetSpacing() const {
	return m_spacing;
}


void Box::setPosition(const sf::Vector2f& pos) {

	Widget::setPosition(pos);

	AllocateChildren();
}

void Box::AllocateChildren() const {
	unsigned int num_expand( 0 );
	unsigned int num_visible( 0 );

	// Count number of visible and expanded children.
	for( const auto& child : m_box_children ) {
		if( !IsChildInteresting( child.widget ) ) {
			continue;
		}

		++num_visible;

		if( child.expand ) {
			++num_expand;
		}
	}

	// Calculate extra width pre expanded widget.
	float extra( 0.f );

	if( num_expand > 0 ) {
		if( m_orientation == Orientation::HORIZONTAL ) {
			extra = std::max( 0.f, size.x - Widget::getPosition().x ) / static_cast<float>( num_expand );
		}
		else {
			extra = std::max( 0.f, size.y - Widget::getPosition().y ) / static_cast<float>( num_expand );
		}
	}

	// Allocate children.
	float gap(0); //KH Context::Get().GetEngine().GetProperty<float>("Gap", shared_from_this()) );
	sf::Vector2f allocation( 0.f, 0.f );
	sf::Vector2f tmpPosition(Widget::getPosition()); // gap, gap );

	for( const auto& child : m_box_children ) {
		if( !IsChildInteresting( child.widget ) ) {
			continue;
		}

		if( m_orientation == Orientation::HORIZONTAL ) {

		/*	allocation.x = child.widget->getPosition().x + ( child.expand ? extra : 0.f );
			allocation.y = size.y - 2 * gap;
*/
			child.widget->setPosition(tmpPosition);
			//child.widget->size(sf::FloatRect(position.x, position.y, allocation.x - (child.expand && !child.fill ? extra : 0.f), allocation.y));
		//	tmpPosition.x += allocation.x + GetSpacing();
			tmpPosition.x += child.widget->size.x + GetSpacing();
		}
		else {
			child.widget->setPosition(tmpPosition);
			tmpPosition.y += child.widget->size.y + GetSpacing();
		}

		--num_visible;
	}
}

bool Box::IsChildInteresting( Widget::PtrConst child ) const {
	return 	child->IsLocallyVisible() &&
		(child->getPosition().x > 0.f || child->size.x > 0.0f) &&
		(child->getPosition().y > 0.f || child->size.y > 0.0f)
	;
}

}
