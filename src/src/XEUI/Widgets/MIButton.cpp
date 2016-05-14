
#include <XEUI/Widgets/MIButton.hpp>

namespace XE {


MIButton::MIButton( const Ogre::String& name,
			 Ogre::uint16 idx, 
			 const Ogre::String text,
			  Menu* owner)
			 : /*Button(
			 id,
		   0, 
          0, 
           10,
           10,
           "",
           parentContainer)
		   ,*/
		   MenuItem( name,
			  idx, 
			  text,
			  owner),
			 mIsActive(true), mIsClicked(false)
{


	_actualize();


}
    
MIButton::~MIButton()
{

}



void MIButton::pointSelectStart(const Ogre::Vector2& point)
{
	if (!mIsActive)
		return;

	mIsClicked = true;

	_actualize();

	if(hasSubMenu())
		MenuItem::pointSelectStart(point);
}


void MIButton::pointSelectEnd(const Ogre::Vector2& point)
{
	mIsClicked = false;

	if (!mIsActive)
		return;

	//setFocus(false);
//	callCallback(); 
}
    

void MIButton::resetState()
{
    mIsClicked = false;
    mIsActive = true;

  //  PanelElement::resetState();
}


void MIButton::_inactive()
{
	//ElementStyle* style = getStyle(S_MenuItem);

	//styleRectangle(mDesign,style,ES_Disabled);
	//styleCaption(mCaption,style,ES_Disabled);
}


void MIButton::_over()
{
	//ElementStyle* style = getStyle(S_MenuItem);

	//styleRectangle(mDesign,style,ES_Over);
	//styleCaption(mCaption,style,ES_Over);
}


void MIButton::_unOver()
{
 //  	ElementStyle* style = getStyle(S_MenuItem);

	//styleRectangle(mDesign,style,ES_Default);
	//styleCaption(mCaption,style,ES_Default);
}


void MIButton::_clicked()
{
 //   ElementStyle* style = getStyle(S_MenuItem);

	//styleRectangle(mDesign,style,ES_Selected);
	//styleCaption(mCaption,style,ES_Selected);
}


bool MIButton::isOver(const Ogre::Vector2& pos)
{
    if (!mIsActive)
        return false;

	//if (mSplitButton != nullptr)
	//{
	//	//test!!
	//	if (mSplitButton->intersects(pos))
	//		mSplitButton->background_colour(XE::Colours::ForestGreen);
	//	else
	//		mSplitButton->background_colour(XE::Colours::Blue);
	//}

	//mOvered = mCaption->intersects(pos);

    _actualize();
	return false;// mOvered;
}

void MIButton::_actualize()
{
    //if (mIsActive)
    //{
    //    if (mIsClicked)
    //        _clicked();
    //    else
    //        mOvered ? _over() : _unOver();
    //}
    //else
    //    _inactive();
}
    



} //namespace XE