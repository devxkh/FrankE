
#include <XEUI/Panel2D.hpp>
//#include "XEUIPanelColors.h"
#include <XEUI/Widget.hpp>
#include <XERenderer/GUI/WScreen.hpp>
#include <XERenderer/GUI/WCaption.hpp>
#include <XEUI/DAL/FB_UI_StateData_generated.h> //need to include ... else link error

#include <iostream>

namespace XE {

	Panel2D::Panel2D(UIManager& gui, Desktop::Ptr desktop) :
		UIPanel(gui, desktop, 0)
		, m_BGHead(nullptr)
		, m_CaptionHead(nullptr)
	{

		//ElementStyle* style = getStyle( S_Panel2D );

		//   mGUILayer = screen->createLayer();

		//_background = mGUILayer->createRectangle(_pos.x, _pos.y, _size.x, _size.y );

		//   // Create an empty mouse pointer which follow the mouse cursor
		//   _mousePointer = mGUILayer->createRectangle(0, 0, 0, 0);
		//   showInternalMousePointer();

		////PanelHead
		//if(showHead)
		//{
		//	mBGHead = mGUILayer->createRectangle(_pos.x + _size.x / 2, _pos.y - 25, 200, 40 );
		//	mBGHead->background_colour(Colours::Black);
		//	mCaptionHead = mGUILayer->createCaption(9, _pos.x + _size.x / 2, _pos.y - 25, name);
		//}

		//mOldScreenHeight = mScreen->getViewport()->getActualHeight();
		//mOldScreenWidth = mScreen->getViewport()->getActualWidth();
	}

	Panel2D::~Panel2D()
	{
		//mScreen->destroy(mGUILayer);

		/*for (WidgetVector::iterator it = mWidgets.begin(); it != mWidgets.end(); ++it)
		{
			OGRE_DELETE *it;
		}*/
	//	mWidgets.clear();

		//	mPanelContainer->getGUILayer()->destroyRectangle(_background);
	}



	void Panel2D::setPosition(const Ogre::Vector3& pos)
	{
		//automaticly called?   ElementBase::setPosition(Ogre::Vector3(pos.x, pos.y, 0));

		//PanelHead
		if (m_BGHead)
		{
			/*m_BGHead->setPosition(Ogre::Vector2(Widget::getPosition().x + Widget::getSize().x / 2 - m_BGHead->getPosition().x / 2, Widget::getPosition().y - 25));
			m_CaptionHead->setPosition(Ogre::Vector2(Widget::getPosition().x + Widget::getSize().x / 2 - m_BGHead->getPosition().x / 2, Widget::getPosition().y - 25));*/
		}
	}

	//void Panel2D::setStyle(ElementStyle* style, bool  resizedOnly)
	//{
	//	mStyle = style;
	//
	//	std::cout << "Panel2d resized! " << mScreen->getViewport()->getActualHeight() << std::endl;
	//
	//	if (style->align.unitvert == Unit_AlignBottom) // screen bottom
	//		_pos.y = mScreen->getViewport()->getActualHeight() - style->height;
	//	else if (style->align.unitvert == Unit_AlignCenter) // screen center
	//		_pos.y = mScreen->getViewport()->getActualHeight() / 2 - style->height / 2;
	//	else if (style->align.unitvert == Unit_VBottomPElement && mParent) // bottom of Parent Element
	//		_pos.y = mParent->_pos.y + mParent->_size.y;
	//	else //top
	//		_pos.y = 0;
	//
	//	if (style->align.unithorz == Unit_AlignRight) // screen right
	//		_pos.x = mScreen->getViewport()->getActualWidth() - style->width;
	//	else if (style->align.unithorz == Unit_AlignCenter) // screen center
	//		_pos.x = mScreen->getViewport()->getActualWidth() / 2 - style->width / 2;
	//	else if (style->align.unithorz == Unit_HCenterPElement && mParent) // center of parent element
	//		_pos.x = (mParent->_pos.x + mParent->_size.x / 2) - style->width / 2;
	//	else //left
	//		_pos.x = 0;
	//
	//	_background->position( Ogre::Vector2( _pos.x,_pos.y ) );
	//	_background->width(_size.x = style->width);
	//	_background->height(_size.y = style->height);
	//
	//	if (!resizedOnly)
	//		styleRectangle( _background, style, ES_Default );
	//
	//	//PanelHead
	//	if(mBGHead)
	//	{
	//		mBGHead->width( std::min(_pos.x / 2,mBGHead->width()));
	//		mBGHead->position(Ogre::Vector2( _pos.x + _size.x / 2 - mBGHead->width() / 2, _pos.y - 25 ));
	//		mCaptionHead->left( _pos.x + _size.x / 2 - mBGHead->width() / 2);
	//		mCaptionHead->top( _pos.y - 25 );
	//	}
	//}


	void Panel2D::HandleAlignmentChange(const sf::Vector2f& alignment)
	{
		
	}

/*
	void Panel2D::update(const Ogre::Real& timeElapsed)
	{
		for each (auto& var in GetChildren())
		{
			var->Update(timeElapsed);
		}
	}*/


	bool Panel2D::injectMouseMoved(const  Ogre::Real& x, const  Ogre::Real& y)
	{
	//	mInternalMousePos = Ogre::Vector2(x, y);
		// _mousePointer->position(mInternalMousePos);

		//if ((x >= Widget::getPosition().x && x <= Widget::getPosition().x + Widget::getSize().x) && (y >= Widget::getPosition().y && y <= Widget::getPosition().y + Widget::getSize().y))
		//{


		//	// Let's actualize the "over" for each elements
		//	for (WidgetVector::iterator it = mWidgets.begin(); it != mWidgets.end(); ++it)
		//		(*it)->isOver(mInternalMousePos);

		//}


		/*  for (size_t i=0; i < mPanelElements.size(); i++)
			  mPanelElements[i]->isOver(mInternalMousePos);*/

		return true;
	}

	void Panel2D::pointSelectStart(const Ogre::Vector2& point){ }
	void Panel2D::pointSelectEnd(const Ogre::Vector2& point){ }
	bool Panel2D::isOver(const Ogre::Vector2& pos){ return false; }

	/*void Panel2D::setSize(int width, int height)
	{
	
	}
*/
	void Panel2D::setPosition(int left, int top)
	{ 
	/*	for each (auto& var in m_widgets)
		{
			var.setPosition();
		}*/
	}

//	Ogre::Vector3& Panel2D::getPosition(){ return Widget::getPosition(); }

	void Panel2D::injectTimeAndMousePosition(double time, const Ogre::Vector2& pos){ }

	void Panel2D::highlight(){ }
	void Panel2D::_actualize(){ }

	void Panel2D::parentResized()
	{
		//change onyly position! no autoscale!
		//	setStyle(mStyle,true);

		//Ogre::Vector3 startPosition = _pos;


		//Ogre::Real deltay = mScreen->getViewport()->getActualHeight() - mOldScreenHeight;
		//Ogre::Real deltax = mScreen->getViewport()->getActualWidth() - mOldScreenWidth;

		//mOldScreenHeight = mScreen->getViewport()->getActualHeight();
		//mOldScreenWidth = mScreen->getViewport()->getActualWidth();
		////ElementStyle style = *this->getStyle(S_Panel2D);
		////style.width = mOldScreenWidth + deltax;
		////style.height = mOldScreenHeight + deltay;
		////setStyle(style);
		//_pos.x = std::max(std::min(_size.x, _pos.x + deltax) , 0.0f);
		//_pos.y = std::max(std::min(_size.y, _pos.y + deltay) , 0.0f);



		////change onyly pos and width!
		//_background->position(Ogre::Vector2(_pos.x, _pos.y));

		////PanelHead
		//if (mBGHead)
		//{
		//	mBGHead->position(Ogre::Vector2(_pos.x + _size.x / 2 - mBGHead->width() / 2, _pos.y - 25));
		//	mCaptionHead->left(_pos.x + _size.x / 2 - mBGHead->width() / 2);
		//	mCaptionHead->top(_pos.y - 25);
		//}
		////Ogre::Vector2 newPos( _pos.x + deltax,_pos.y + deltay );
		////_background->position( newPos );

		////reposition of Panel Elements
		//for each (auto& var in mWidgets)
		//{
		////	var->parentResized();
		//}
		//for (WidgetVector::iterator it = mWidgets.begin(); it != mWidgets.end(); ++it)
		//   {
		//	(*it)->parentResized();
		//      // Ogre::Vector2 oldPanelElementPosition = (*it)->getPosition();
		//      //(*it)->setPosition( oldPanelElementPosition.x + deltax,
		//      //                                oldPanelElementPosition.y + deltay );
		//   }

		//_pos = Ogre::Vector3( newPos.x, newPos.y, 0 );
	}


	//Button* Panel2D::makeButton(Uint32 id,
	//								 Ogre::Real x, 
	//								 Ogre::Real y, 
	//                                size_t width,
	//                                size_t height,
	//                                const Ogre::String& text)
	//{
	//    return PanelContainer::makeButton(id,mStartPosition.x + x, mStartPosition.y + y, 
	//                                      width, height, 
	//                                      text);
	//}
	//
	//
	//Caption* Panel2D::makeCaption(Uint32 id,
	//								   Ogre::Real x, 
	//								   Ogre::Real y,
	//                                  size_t width,
	//                                  size_t height,
	//                                  const Ogre::String& text,
	//                                  TextAlignment textAlign,
	//                                  VerticalAlignment verticalAlign)
	//{
	//    return PanelContainer::makeCaption(id,mStartPosition.x + x, mStartPosition.y + y, 
	//                                       width, height, 
	//                                       text, textAlign, verticalAlign);
	//}


	//Checkbox* Panel2D::makeCheckbox( Ogre::Real x, 
	//                                     Ogre::Real y,
	//                                    size_t width,
	//                                    size_t height)
	//{
	//    return PanelContainer::makeCheckbox(mStartPosition.x + x, mStartPosition.y + y, 
	//                                        width, height);
	//}


	//Combobox* Panel2D::makeCombobox(Uint32 id,
	//									 Ogre::Real x, 
	//									 Ogre::Real y,
	//                                    size_t width,
	//                                    size_t height,
	//                                    const vector<String>::type& items,
	//                                    unsigned int nbDisplayedElements)
	//{
	//    return PanelContainer::makeCombobox(id,mStartPosition.x + x, mStartPosition.y + y, 
	//                                        width, height, 
	//                                        items, nbDisplayedElements);
	//}

	//Menu* Panel2D::makeMenu( const Ogre::String& name,
	//							        Ogre::Real x, 
	//                                    Ogre::Real y,
	//                                   size_t width,
	//                                   size_t height,
	//                                   unsigned int nbDisplayedElements )
	//{
	//    return PanelContainer::makeMenu( name, _pos.x + x, _pos.y + y, 
	//                                        width, height, 
	//                                        nbDisplayedElements );
	//}
	//
	//Navigation* Panel2D::makeNavigation( const Ogre::String& name,
	//							        Ogre::Real x, 
	//                                    Ogre::Real y,
	//                                   size_t width,
	//                                   size_t height,
	//                                   unsigned int nbDisplayedElements )
	//{
	//    return PanelContainer::makeNavigation( name, _pos.x + x, _pos.y + y, 
	//                                        width, height, 
	//                                        nbDisplayedElements );
	//}
	//
	//OgreConsole* Panel2D::makeConsole(const Ogre::String& name,
	//	Ogre::Real x,
	//	Ogre::Real y,
	//	size_t width,
	//	size_t height,
	//	unsigned int nbDisplayedElements)
	//{
	//	return PanelContainer::makeConsole(name, _pos.x + x, _pos.y + y,
	//		width, height,
	//		nbDisplayedElements);
	//}


	//Listbox* Panel2D::makeListbox(Uint32 id,
	//								   Ogre::Real x, 
	//								   Ogre::Real y,
	//                                  size_t width,
	//                                  size_t height,
	//                                  const vector<String>::type& items,
	//                                  unsigned int nbDisplayedElements)
	//{
	//    return PanelContainer::makeListbox(id,mStartPosition.x + x, mStartPosition.y + y, 
	//                                       width, height, 
	//                                       items, nbDisplayedElements);
	//}


	//InlineSelector* Panel2D::makeInlineSelector( Ogre::Real x,
	//                                                 Ogre::Real y,
	//                                                size_t width,
	//                                                size_t height,
	//                                                const vector<String>& items)
	//{
	//    return PanelContainer::makeInlineSelector(mStartPosition.x + x, mStartPosition.y + y, 
	//                                              width, height, 
	//                                              items);
	//}
	//
	//
	//ScrollBar* Panel2D::makeScrollBar( Ogre::Real x, 
	//                                       Ogre::Real y,
	//                                      size_t width,
	//                                      size_t height,
	//                                       Ogre::Real minValue,
	//                                       Ogre::Real maxValue)
	//{
	//    return PanelContainer::makeScrollBar(mStartPosition.x + x, mStartPosition.y + y, 
	//                                         width, height, 
	//                                         minValue, maxValue);
	//}
	//
	//
	//ProgressBar* Panel2D::makeProgressBar( Ogre::Real x, 
	//                                           Ogre::Real y,
	//                                          size_t width,
	//                                          size_t height)
	//{
	//    return PanelContainer::makeProgressBar(mStartPosition.x + x, mStartPosition.y + y, 
	//                                           width, height);
	//}
	//
	//
	//TextZone* Panel2D::makeTextZone( Ogre::Real x,
	//                                     Ogre::Real y,
	//                                    size_t width,
	//                                    size_t height,
	//                                    const Ogre::String& text)
	//{
	//    return PanelContainer::makeTextZone(mStartPosition.x + x, mStartPosition.y + y, 
	//                                        width, height, 
	//                                        text);
	//}


} // namespace XE