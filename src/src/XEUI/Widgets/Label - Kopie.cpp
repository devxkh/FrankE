#include <XEUI/Widgets/Label.hpp>

#include <XEUI/UIManager.hpp>
#include <XERenderer/GUI/WLayer.hpp>
#include <XEUI/DAL/FB_UI_StateData_generated.h> 

namespace XE {

	Label::Label(UIManager* uiManager, WLayer* parentLayer, const sf::String& text) :
		Widget(parentLayer, "")
		, m_Label(&uiManager->getGUIRenderer(), parentLayer)
	{

	}

	Label::~Label()
	{
		//mPanelContainer->getGUILayer()->destroyCaption(mCaption);
		//mPanelContainer->getGUILayer()->destroyRectangle(mDesign);
	}


	Label::Ptr Label::Create(UIManager* uiManager, WLayer* parentLayer, const sf::String& text) {
		Ptr caption(new Label(uiManager, parentLayer, text));
		//label->RequestResize();
		return caption;
	}

	void Label::SetText(const sf::String& text) {

		m_Label.SetText(text);
		//m_text = text;

		//if (m_wrap) {
		//	WrapText();
		//}

		//RequestResize();
		//Invalidate();
	}

	void  Label::SetStyle(const char* labelElement,const char* styleAll)
	{
		//load style from file
		if (labelElement && styleAll)
		{
			//auto ele = flatbuffers::GetRoot<XFB_UI::Label>(labelElement);
			//auto style = flatbuffers::GetRoot<XFB_UI::Style>(styleAll);
			////set widget size and position
			//setPosition(ele->base()->positon()->x(), ele->base()->positon()->y());
			//setSize(style->width(), style->height());

			////set renderered rectangle
			//m_Label.setSize(style->width(), style->height());
			//m_Label.setPosition(Ogre::Vector2(ele->base()->positon()->x(), ele->base()->positon()->y()));
			//m_Label.setBackground(style->defaultState()->bgColour());
		}
		else
		{
			//m_Label.setBackground(Ogre::ColourValue::White); //default test
		}
	}

	void Label::pointSelectStart(const Ogre::Vector2& point){}
	void Label::pointSelectEnd(const Ogre::Vector2& point){}
	void Label::parentResized()
	{
	

		//Widget::_parent->getScreen()->
	}

	//const sf::String& Caption::GetText() const {
	//	return m_text;
	//}

	bool Label::isOver(const Ogre::Vector2& pos)
	{
		//mOvered = mCaption->intersects(pos);
		return mOvered;
	}


	void Label::setSize(int width, int height)
	{
		m_Label.setSize(width, height);
	}
	
	void Label::setPosition(int left, int top)
	{
		m_Label.setPosition(Ogre::Vector2(left, top));
	}
	
	Ogre::Vector3& Label::getPosition()
	{
		Ogre::Vector3 redo;
		return redo;// mDesign->position();
	}
		
	void Label::injectTimeAndMousePosition(double time, const Ogre::Vector2& pos)
	{
	}


	void Label::highlight()
	{
	}


	void Label::text(sf::String s)
	{
		/// mCaption->text(s);
	}


	sf::String Label::text()
	{
		return "";// mCaption->text();
	}


	void Label::_actualize()
	{
		//if (!mBackgroundSpriteName.empty())
		//    mDesign->background_image(mBackgroundSpriteName);
		//else
		//{
		//    mDesign->background_gradient(getColors()->captionBackgroundGradientType,
		//                                 getColors()->captionBackgroundGradientStart,
		//                                 getColors()->captionBackgroundGradientEnd);
		//    mDesign->border(getColors()->captionBorderSize, getColors()->captionBorder);
		//}
	}
} // namespace XE