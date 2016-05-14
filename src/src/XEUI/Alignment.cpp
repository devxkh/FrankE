#include <XEUI/Alignment.hpp>
//#include <SFGUI/Engine.hpp>

namespace XE {

Alignment::Alignment() :
	m_scale( sf::Vector2f( 1.f, 1.f ) )
{
}

Alignment::Ptr Alignment::Create() {
	return Ptr( new Alignment );
}

void Alignment::SetScale( const sf::Vector2f& scale ) {
	m_scale = scale;
	UpdateChild();
}

const sf::Vector2f& Alignment::GetScale() const {
	return m_scale;
}

const std::string& Alignment::GetName() const {
	static const std::string name( "Alignment" );
	return name;
}

void Alignment::ParentPositionChanged() {
	UpdateChild();
}


void Alignment::HandleAlignmentChange( const sf::Vector2f& /*old_alignment*/ ) {
	UpdateChild();
}

void Alignment::UpdateChild() {
	auto child = GetChild();

	if( !child ) {
		return;
	}

	auto parent = GetParent();

	if (!parent) {
		return;
	}

	sf::Vector2f newChildPos(child->getPosition());
	sf::Vector2f spare_space(parent->size);
	spare_space -= child->size;
	spare_space.x *= 1.f - GetScale().x;
	spare_space.y *= 1.f - GetScale().y;

	if( ( spare_space.x < 0 ) || ( spare_space.y < 0 ) ) {
#if defined( SFGUI_DEBUG )
		std::cerr << "SFGUI warning: Alignment got a smaller allocation than it requested.\n";
		return;
#endif
	}

	newChildPos.x = spare_space.x * GetAlignment().x;
	newChildPos.y = spare_space.y * GetAlignment().y;
	//allocation.width -= spare_space.x;
	//allocation.height -= spare_space.y;

	child->setPosition(newChildPos);
}

}
