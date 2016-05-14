
#include <XEUI/Widgets/MICheckBox.hpp>

namespace XE {


MICheckBox::MICheckBox( const Ogre::String& name,
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
	
	mCaption = mPanelContainer->getGUILayer()->createCaption(14, 0, 0, "X");
	
	_actualize();
}
    
MICheckBox::~MICheckBox()
{

}



void MICheckBox::pointSelectStart(const Ogre::Vector2& point)
{
	if (!mIsActive)
		return;

	mIsClicked = true;

	_actualize();

	if(hasSubMenu())
		MenuItem::pointSelectStart(point);
}


void MICheckBox::pointSelectEnd(const Ogre::Vector2& point)
{
	mIsClicked = false;

	if (!mIsActive)
		return;

	//setFocus(false);
	callCallback(); 
}
    

void MICheckBox::resetState()
{
    mIsClicked = false;
    mIsActive = true;

    PanelElement::resetState();
}


void MICheckBox::_inactive()
{
	ElementStyle* style = getStyle(S_MenuItem);

	styleRectangle(mDesign,style,ES_Disabled);
	styleCaption(mCaption,style,ES_Disabled);
}


void MICheckBox::_over()
{
	ElementStyle* style = getStyle(S_MenuItem);

	styleRectangle(mDesign,style,ES_Over);
	styleCaption(mCaption,style,ES_Over);
}


void MICheckBox::_unOver()
{
   	ElementStyle* style = getStyle(S_MenuItem);

	styleRectangle(mDesign,style,ES_Default);
	styleCaption(mCaption,style,ES_Default);
}


void MICheckBox::_clicked()
{
    ElementStyle* style = getStyle(S_MenuItem);

	styleRectangle(mDesign,style,ES_Selected);
	styleCaption(mCaption,style,ES_Selected);
}


bool MICheckBox::isOver(const Ogre::Vector2& pos)
{
    if (!mIsActive)
        return false;

    mOvered = mCaption->intersects(pos);
    _actualize();
    return mOvered;
}

void MICheckBox::_actualize()
{
    if (mIsActive)
    {
        if (mIsClicked)
            _clicked();
        else
            mOvered ? _over() : _unOver();
    }
    else
        _inactive();
}
    



} //namespace XE