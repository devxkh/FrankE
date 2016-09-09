#include <XEUI/widgets/Label.hpp>

#include <XEUI/Container.hpp>

#include <XERenderer/GUI/GUIRenderer.hpp>
#include <XERenderer/GUI/WLayer.hpp>

namespace XE {

	Label::Label(WLayer& parentLayer, Uint16 fontId, const sf::String& text) :
		m_text(text)
		, m_wrap(false)
		, m_wcaption(parentLayer,fontId)
		
		, m_DebugRectangle(parentLayer, 0, 0, 0, 0)

	{
		SetAlignment(sf::Vector2f(.5f, .5f));
		draw();
	}

	Label::Ptr Label::Create(WLayer& parentLayer, const sf::String& text, Uint16 fontsize) {
		Ptr label(new Label(parentLayer, fontsize, text));
		//label->RequestResize();
		return label;
	}

	void Label::SetText(const sf::String& text) {
		m_text = text;

		if (m_wrap) {
			WrapText();
		}

	//	RequestResize();
		draw();
	}

	const sf::String& Label::GetText() const {
		return m_text;
	}

	void Label::SetLineWrap(bool wrap) {
		if (wrap == m_wrap) {
			return;
		}

		m_wrap = wrap;

		//RequestResize();

		if (wrap) {
			WrapText();
		}
		else {
			m_wrapped_text = L"";
		}

		draw();
	}

	bool Label::GetLineWrap() const {
		return m_wrap;
	}

	sf::String Label::GetWrappedText() const {
		if (!m_wrap) {
			return m_text;
		}

		return m_wrapped_text;
	}

	void Label::WrapText() {
		//const std::string& font_name( Context::Get().GetEngine().GetProperty<std::string>( "FontName", shared_from_this() ) );
		//unsigned int font_size( Context::Get().GetEngine().GetProperty<unsigned int>( "FontSize", shared_from_this() ) );
		//const sf::Font& font( *Context::Get().GetEngine().GetResourceManager().GetFont( font_name ) );

		//std::basic_string<sf::Uint32> wrapped_text;
		//std::basic_string<sf::Uint32> text( m_text.begin(), m_text.end() );

		//std::basic_string<sf::Uint32> line;

		//while( !text.empty() ) {
		//	auto next_newline = text.find( L'\n' );

		//	line = text.substr( 0, next_newline );

		//	if( next_newline != std::basic_string<sf::Uint32>::npos ) {
		//		text = text.substr( next_newline + 1 );
		//	}
		//	else {
		//		text.clear();
		//	}

		//	if( !wrapped_text.empty() ) {
		//		wrapped_text += L'\n';
		//	}

		//	// Check if line needs to be wrapped.
		//	if( Context::Get().GetEngine().GetTextMetrics( line, font, font_size ).x <= GetAllocation().width ) {
		//		wrapped_text += line;
		//	}
		//	else {
		//		// Line needs to be wrapped.
		//		while( !line.empty() ) {
		//			auto last_space = line.size();

		//			while( Context::Get().GetEngine().GetTextMetrics( line.substr( 0, last_space ), font, font_size ).x > GetAllocation().width ) {
		//				last_space = line.find_last_of( L' ', last_space - 1 );

		//				if( last_space == std::basic_string<sf::Uint32>::npos ) {
		//					wrapped_text += line;
		//					line.clear();
		//					break;
		//				}
		//			}

		//			if( last_space != std::basic_string<sf::Uint32>::npos ) {
		//				wrapped_text += line.substr( 0, last_space );
		//				line = line.substr( last_space );
		//			}

		//			if( !line.empty() ) {
		//				wrapped_text += L'\n';

		//				// If this is a new line remove the leading space.
		//				if( line[0] == L' ' ) {
		//					line = line.substr( 1 );
		//				}
		//			}
		//		}
		//	}
		//}

		//m_wrapped_text = wrapped_text;
	}

	void Label::UpdateAlignment() {
		
		sf::Vector2i textSize = m_wcaption.GetTextStringMetrics(m_text);

		/*--------
		xxxx*/
		auto offsetx = GetAlignment().x == 0 ? 0 : (size.x * GetAlignment().x) - (textSize.x / 2);
		auto posx = Widget::getPosition().x;
		
		auto posy = Widget::getPosition().y;
		auto offsety = (size.y * 0.5f);// -(textSize.y / 2);
		auto middley = posy - offsety;

		sf::Vector2f textPos(posx + offsetx, middley + (textSize.y / 2));

		m_wcaption.setPosition(textPos);

		m_DebugRectangle.setBackground(Ogre::ColourValue::White);
		m_DebugRectangle.setPosition(Widget::getPosition());
		m_DebugRectangle.setSize(size);
	}


	//std::unique_ptr<RenderQueue>
	void Label::draw() {

		//sf::FloatRect req(GetAllocation());
		//sf::FloatRect parentAllocation(GetParent()->GetAllocation());
		/*
		m_alignment.x
		*/
		//sf::Vector2i textSize = m_wcaption.GetTextStringMetrics(m_text);
		///*--------
		//xxxx*/
		//auto offsetx = (size.x * GetAlignment().x) - (textSize.x / 2);
		//
		//auto posx = Widget::getPosition().x;

		//sf::Vector2f textPos(posx + offsetx, Widget::getPosition().y);

		m_wcaption.setSize(size.x, size.y);
		m_wcaption.setText(GetText());

		//m_wcaption.setPosition(textPos);//  sf::Vector2f(parentAllocation.left + req.left, parentAllocation.top + req.top));
		UpdateAlignment();

		//return Context::Get().GetEngine().CreateLabelDrawable( std::dynamic_pointer_cast<const Label>( shared_from_this() ) );
	}

	sf::Vector2f Label::CalculateRequisition() {
		/*const std::string& font_name( Context::Get().GetEngine().GetProperty<std::string>( "FontName", shared_from_this() ) );
		unsigned int font_size( Context::Get().GetEngine().GetProperty<unsigned int>( "FontSize", shared_from_this() ) );
		const sf::Font& font( *Context::Get().GetEngine().GetResourceManager().GetFont( font_name ) );

		auto metrics = Context::Get().GetEngine().GetTextMetrics( GetWrappedText(), font, font_size );
		metrics.y = Context::Get().GetEngine().GetFontLineHeight( font, font_size );

		sf::String wrapped_text( GetWrappedText() );
		std::basic_string<sf::Uint32> text( wrapped_text.begin(), wrapped_text.end() );

		std::size_t lines = 1;

		do {
		auto next_newline = text.find( L'\n' );

		if( next_newline != std::basic_string<sf::Uint32>::npos ) {
		text = text.substr( next_newline + 1 );
		}
		else {
		break;
		}

		if( !text.empty() ) {
		lines++;
		}
		} while( !text.empty() );

		metrics.y *= static_cast<float>( lines );

		if( m_wrap ) {
		metrics.x = 0.f;
		}*/

		return m_wcaption.getSize(); // metrics;
	}

	const std::string& Label::GetName() const {
		static const std::string name("Label");
		return name;
	}

}
