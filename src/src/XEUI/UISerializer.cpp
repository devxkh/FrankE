#include <XEUI/UISerializer.hpp>

#include "OgreStringConverter.h"

#include "OgreVector3.h"
#include "OgreColourValue.h"

//#include <XEResource/XML/tinyxml.h>

#include "OgreDataStream.h"
#include "OgreResourceManager.h"
//#include <XEObjects/XEProperty.hpp>

#include <XEUI/UIStateManager.hpp>
//#include <XEUI/UIScreen.hpp>
#include <XEUI/Panel2D.hpp>
#include <XEUI/Panel3D.hpp>
#include <XEUI/UIManager.hpp>
#include <XEUI/Widgets/MIButton.hpp>
#include <XEUI/Widgets/Menu.hpp>
#include <XEUI/Widgets/Navigation.hpp>
#include <XEUI/Widgets/NavItem.hpp>

#include <XEUI/OgreConsoleForGorilla.h>

#include <XEUI/PanelElementCallback.hpp>

#include <iostream>

//#include <XEUI/Widgets/UIItemBar.hpp>
//#include <XEUI/Widgets/UIItemBox.hpp>

namespace XE {

	using namespace Ogre;


	Margin& parseMargin(const std::string& marginStr)
	{

		Margin margin;
		VerticalAlignment val = VerticalAlign_Top; //default

		// Split on space
		Ogre::vector<Ogre::String>::type vec = Ogre::StringUtil::split(marginStr);
		margin.left = Ogre::StringConverter::parseUnsignedInt(vec[0]);
		margin.top = Ogre::StringConverter::parseUnsignedInt(vec[1]);
		margin.right = Ogre::StringConverter::parseUnsignedInt(vec[2]);
		margin.bottom = Ogre::StringConverter::parseUnsignedInt(vec[3]);

		return margin;
	}

Unit& parseVertiAlign(const std::string& vertAlign)
{
	Unit val = Unit_AlignTop; //default
	
	if(vertAlign == "bottom")	
		val = Unit_AlignBottom;
	else if(vertAlign == "center")	
		val = Unit_AlignCenter;
	else if(vertAlign == "bottomParentElement")	
		val = Unit_VBottomPElement;
	else if(vertAlign == "centerParentElement")	
		val = Unit_VCenterPElement;
	else if(vertAlign == "topParentElement")	
		val = Unit_VTopPElement;

	// vertAlign="bottomParentElement"
				

	return val;
}

Unit& parseHorizAlign(const std::string& horizAlign)
{
	Unit val = Unit_AlignLeft; //default
	
	if(horizAlign == "right")	
		val = Unit_AlignRight;
	else if(horizAlign == "center")	
		val = Unit_AlignCenter;

	else if(horizAlign == "centerParentElement")	
		val = Unit_HCenterPElement;
	else if(horizAlign == "leftParentElement")	
		val = Unit_HLeftPElement;	
	else if(horizAlign == "rightParentElement")	
		val = Unit_HRightPElement;


	//horzAlign="centerParentElement"

	return val;
}
//----------------------------------------------------------------------------
Ogre::ColourValue& parseColourValue(const std::string& colourVal)
	{
	Ogre::ColourValue val = Ogre::ColourValue(0, 0, 0, 1);

		//without prefix
		if(colourVal == "green")
			val = Ogre::ColourValue::Green;
		else if(colourVal == "red")
			val = Ogre::ColourValue::Red;
		else if(colourVal == "blue")
			val = Ogre::ColourValue::Blue;
		else if(colourVal == "white")
			val = Ogre::ColourValue::White;
		else 
		{
			  // Split on space
			Ogre::vector<Ogre::String>::type vec = Ogre::StringUtil::split(colourVal);

			val = rgb( Ogre::StringConverter::parseReal(vec[0]), Ogre::StringConverter::parseReal(vec[1]), Ogre::StringConverter::parseReal(vec[2]),  Ogre::StringConverter::parseReal(vec[3]));
		}	//val = Ogre::ColourValue::White;
		
		//Prefix wc:
		//webcolour(Colours::BlueViolet)

		//Prefix #:
		//webcolour(Colours::BlueViolet)


		/*if(XMLNode->first_attribute("r")->value())
			val.r = Ogre::StringConverter::parseReal(XMLNode->first_attribute("r")->value());

		if(XMLNode->first_attribute("g")->value())
			val.g = Ogre::StringConverter::parseReal(XMLNode->first_attribute("g")->value());

		if(XMLNode->first_attribute("b")->value())
			val.b = Ogre::StringConverter::parseReal(XMLNode->first_attribute("b")->value());

		if(XMLNode->first_attribute("a")->value())
			val.a = Ogre::StringConverter::parseReal(XMLNode->first_attribute("a")->value());*/

		return val;
	}
	//----------------------------------------------------------------------------
	const Ogre::Vector3 parseVector3(const Ogre::String& vector3String)
	{
		Ogre::Vector3 val = Ogre::Vector3(0,0,0);

		Ogre::StringVector res = Ogre::StringUtil::split(vector3String, ",");

			val.x = Ogre::StringConverter::parseReal(res[0]);

			val.y = Ogre::StringConverter::parseReal(res[1]);

			val.z = Ogre::StringConverter::parseReal(res[2]);

		return val;
	}

	const Ogre::Vector2 parseVector2(const Ogre::String& vector2String, const Ogre::String& delimiter = " ")
    {
		 Ogre::Vector2 val = Ogre::Vector2(0,0);
	  
		 Ogre::StringVector res = Ogre::StringUtil::split(vector2String, delimiter);
	
		val.x = Ogre::StringConverter::parseReal(res[0]);
		val.y = Ogre::StringConverter::parseReal(res[1]);

		return val;
    }

	//----------------------------------------------------------------------------
	UISerializer::UISerializer( UIManager* xeui, UIStateManager* uiStateMgr,  const Ogre::uint16& grp )
		//: CBaseSerializer("UI Serializer", CAN_EXPORT | CAN_IMPORT),
		: mUIStateMgr( uiStateMgr ),
		mGroup(grp),
		mAttachToElement( nullptr )
	{
		mXEUI = xeui;

		//screen Elements
		mScreenEleMap.insert( std::make_pair( "atlas", &UISerializer::atlas ));
		mScreenEleMap.insert( std::make_pair( "resourceLocations", &UISerializer::resourceLocations ));
		mScreenEleMap.insert( std::make_pair( "style", &UISerializer::style ));
		mScreenEleMap.insert( std::make_pair( "panel3D", &UISerializer::panel ));
		mScreenEleMap.insert( std::make_pair( "panel2D", &UISerializer::screenPanel ));
		
		//Panel Elements
		mPanelEleMap.insert( std::make_pair( "menu", &UISerializer::menu ));
		mPanelEleMap.insert( std::make_pair( "navigation", &UISerializer::navigation ));
		mPanelEleMap.insert(std::make_pair("console", &UISerializer::console));

		//Menu Elements
		mMenuEleMap.insert( std::make_pair( "menuItem", &UISerializer::menuItem ));

		//Navigation Elements
		mNavEleMap.insert( std::make_pair( "navItem", &UISerializer::navItem ));
	}
	
	UISerializer::~UISerializer()
	{
			/*for(std::map<std::string, FunctorBase*>::iterator it = mCallbackMap.begin();
				it != mCallbackMap.end(); it++){
					delete (*it).second;
			}
*/
	//		mCallbackMap.clear();
	 }

	Screen* UISerializer::loadScreenTheme(Ogre::Viewport* vp, const Ogre::String &fileName, const Ogre::String &groupName)
	{
		rapidxml::xml_document<> doc;
		//doc.LoadFile( fileName.c_str );
		Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(fileName, groupName);
		char* scene = _strdup(stream->getAsString().c_str());
	
		doc.parse<0>(scene);

		//std::cout << "loadXMLErr: " << doc.ErrorID() << std::endl;

		rapidxml::xml_node<>* screenNode = doc.first_node();


		if(screenNode)
		{
			//Screen Objekt erstellen
			mScreenName = screenNode->first_attribute("name")->value();
			mUIScreen = mXEUI->createScreen( vp ,
											screenNode->first_attribute("atlas")->value() , 
											mScreenName);
			std::cout << "----screenElement:" << screenNode->name() << std::endl;

			rapidxml::xml_node<>* screenElement = screenNode->first_node();
			if(screenElement)
			{
				do
				{
					CallScreenElement( screenElement->name() ,  screenElement, mUIScreen);
					screenElement = screenElement->next_sibling();
				}while(screenElement);
			}
		}

		return mUIScreen;
	}

	bool UISerializer::loadScreenElements(const Ogre::String &fileName, const Ogre::String &groupName)
	{
		rapidxml::xml_document<> doc;
		//doc.LoadFile( fileName.c_str );
		Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(fileName, groupName);
		char* scene = _strdup(stream->getAsString().c_str());
	
		doc.parse<0>(scene);

		//std::cout << "loadXMLErr: " << doc.ErrorID() << std::endl;

		rapidxml::xml_node<>* screenNode = doc.first_node();

		if(screenNode)
		{
			rapidxml::xml_node<>* screenElement = screenNode->first_node();
			if(screenElement)
			{
				do
				{
					CallScreenElement( screenElement->name() ,  screenElement, mUIScreen);
					screenElement = screenElement->next_sibling();
				}while(screenElement);
			}
		}

		return true;
	}

	bool UISerializer::loadPanel3D()
	{
		return true;
	}

	ScreenPanel* UISerializer::loadPanel2D(const Ogre::String &panelName, const Ogre::String &groupName, PanelElementCallback* attachToElement )
	{
		rapidxml::xml_document<> doc;
		//doc.LoadFile( fileName.c_str );
	    DataStreamPtr stream = ResourceGroupManager::getSingleton().openResource(panelName + ".xml", groupName );
		char* scene = _strdup(stream->getAsString().c_str());
	
		doc.parse<0>(scene);

		//std::cout << "loadXMLErr: " << doc.ErrorID() << std::endl;

		rapidxml::xml_node<>* panel2DNode = doc.first_node();

		if(panel2DNode)
		{
			if (attachToElement)
				mAttachToElement = attachToElement;

			if (screenPanel(panel2DNode, mUIScreen) == 0)
				return static_cast<ScreenPanel*> ( mXEUI->getUIPanel(panelName) );
		}

		OGRE_EXCEPT( Exception::ERR_ITEM_NOT_FOUND,
				"Could not find the panel2DNode ", "UISerializer::loadPanel2D" );
	}

	int UISerializer::CallScreenElement( const std::string & s, rapidxml::xml_node<>* x, Screen* parentElement ) {
		ScreenMFP fp = mScreenEleMap[s];
		if(fp)
			return (this->*fp)(x,parentElement);
		else 
			return 0;
	}

	int UISerializer::CallPanelElement( const std::string & s, rapidxml::xml_node<>* x, UIPanel* parentElement ) {
		UIPanelMFP fp = mPanelEleMap[s];
		if(fp)
			return (this->*fp)(x,parentElement);
		else 
			return 0;
	}

	int UISerializer::CallMenuElement( const std::string & s, rapidxml::xml_node<>* x, Menu* parentElement ) {
		MenuMFP fp = mMenuEleMap[s];
		if(fp)
			return (this->*fp)(x,parentElement);
		else 
			return 0;
	}

	int UISerializer::CallNavElement( const std::string & s, rapidxml::xml_node<>* x, Navigation* parentElement ) {
		NavMFP fp = mNavEleMap[s];
		if(fp)
			return (this->*fp)(x,parentElement);
		else 
			return 0;
	}

	int UISerializer::CallConsoleElement(const std::string & s, rapidxml::xml_node<>* x, OgreConsole* parentElement) {
		ConsoleMFP fp = mConsoleEleMap[s];
		if(fp)
			return (this->*fp)(x,parentElement);
		else 
			return 0;
	}

	int UISerializer::screenPanel(rapidxml::xml_node<>* pElement, Screen* parentElement )
	{ 
		std::cout << "screenPanel" << std::endl;

		ScreenPanel* mPanel = NULL;

		rapidxml::xml_node<>* screenPanelElement = pElement->first_node();
		
			do
			{
				Ogre::uint16 width = 0;
				Ogre::uint16 height = 0;

				if(pElement->first_attribute("width"))
					width =  Ogre::StringConverter::parseUnsignedInt(pElement->first_attribute("width")->value());

				if(pElement->first_attribute("height"))
					height =  Ogre::StringConverter::parseUnsignedInt(pElement->first_attribute("height")->value());

				ScreenPanel* mPanel = OGRE_NEW  ScreenPanel(
										mXEUI, 
										mUIScreen,
										"notUsed", 
										pElement->first_attribute("name")->value(),
										mGroup );
				
				//attach to parent element
				if (mAttachToElement)
					mPanel->setParent (mAttachToElement);
				
				ElementStyle* style = mPanel->getStyle( S_Panel2D ); // use copied Version of found style! else all panels will be the same
				style->width = width;
				style->height = height;

				if( pElement->first_attribute( "vertAlign" ) )	
					style->align.unitvert = parseVertiAlign(pElement->first_attribute("vertAlign")->value());
				if( pElement->first_attribute( "horzAlign" ) )	
					style->align.unithorz = parseHorizAlign(pElement->first_attribute("horzAlign")->value());

				if( pElement->first_attribute( "margin" ) )	
					style->align.margin = parseMargin(pElement->first_attribute("margin")->value());

				mPanel->setStyle( style );

				mXEUI->addUIPanel(mPanel);

				if(screenPanelElement)
				{	
					std::cout << "----screenPanelElement:" << screenPanelElement->name() << std::endl;

					CallPanelElement( screenPanelElement->name() ,  screenPanelElement, mPanel);
					screenPanelElement = screenPanelElement->next_sibling();
				}

			}while(screenPanelElement);

		return 0; 
	}

	int UISerializer::style( rapidxml::xml_node<>* pElement, Screen* parentElement) 
	{ 
		std::cout << "Element:" << pElement->name() << ",type:" << pElement->first_attribute("type") << std::endl;
	
		//neuer Elementstyle

		ElementStyle* newStyleElement;
		//StyleType styleType = S_Default;

		std::string sStyleType = pElement->first_attribute( "type" )->value();

		if (sStyleType == "panel2D")
		{
			newStyleElement = mXEUI->addStyle(S_Panel2D, OGRE_NEW ElementStyle());
		}
		else if( sStyleType == "menuItem" )
			newStyleElement = mXEUI->addStyle(S_MenuItem, OGRE_NEW MenuItemStyle());
		else if( sStyleType == "menu" )
		{
			MenuStyle* menuStyleElement = OGRE_NEW MenuStyle();
			newStyleElement = mXEUI->addStyle(S_Menu, menuStyleElement);
			if( pElement->first_attribute( "itemWidth" ) )	
				menuStyleElement->item_width = Ogre::StringConverter::parseReal(pElement->first_attribute("itemWidth")->value());
			if( pElement->first_attribute("itemHeight" ) )	
				menuStyleElement->item_height = Ogre::StringConverter::parseReal(pElement->first_attribute("itemHeight")->value());

			MenuStyle* test = static_cast<MenuStyle*> (newStyleElement);
		}
		else if( sStyleType == "navItem" )
			newStyleElement = mXEUI->addStyle(S_NavItem, OGRE_NEW NavItemStyle());
		else if( sStyleType == "navigation" )
		{
			NavStyle* navStyle = OGRE_NEW NavStyle();
			newStyleElement = mXEUI->addStyle(S_Navigation, navStyle);

			if( pElement->first_attribute( "itemWidth" ) )	
				navStyle->item_width = Ogre::StringConverter::parseReal(pElement->first_attribute("itemWidth")->value());
			if( pElement->first_attribute("itemHeight" ) )	
				navStyle->item_height = Ogre::StringConverter::parseReal(pElement->first_attribute("itemHeight")->value());
		}
		else if( sStyleType == "console" )
		{
			newStyleElement = mXEUI->addStyle(S_Console, OGRE_NEW ConsoleStyle());

		/*	if( pElement->first_attribute( "itemWidth" ) )	
				static_cast<NavStyle*>( newStyleEle )->item_width = Ogre::StringConverter::parseReal( pElement->first_attribute("itemWidth")->value() );
			if( pElement->first_attribute("itemHeight" ) )	
				static_cast<NavStyle*>( newStyleEle )->item_height = Ogre::StringConverter::parseReal( pElement->first_attribute("itemHeight")->value() );
		*/
		}
		else // Default
		{
			newStyleElement = mXEUI->addStyle(S_Default, OGRE_NEW ElementStyle());
		}
	 
		if (!newStyleElement)
			return 0;

		//----------------------------------------------------------------------
		// Alle Style setter
		//----------------------------------------------------------------------
		rapidxml::xml_node<>* setterElement = pElement->first_node( "setter" );

		if (setterElement  )
		{
			//Setters
			do
			{
				std::string propertyName = setterElement->first_attribute( "property" )->value();
				std::string propertyValue = setterElement->first_attribute( "value" )->value();
				
				if (propertyName == "height")		newStyleElement->height = Ogre::StringConverter::parseReal(propertyValue);
				else if (propertyName == "width")	newStyleElement->width = Ogre::StringConverter::parseReal(propertyValue);

				std::cout << "-------setterElement:" << setterElement->name() << ",property:" << setterElement->first_attribute("property")  << ",value:" << setterElement->first_attribute("value")<< std::endl;
				setterElement = setterElement->next_sibling("setter");
			}while( setterElement );

		}

		//----------------------------------------------------------------------
		// States Style
		//----------------------------------------------------------------------
		rapidxml::xml_node<>* statesElement = pElement->first_node("states");
		if(statesElement)
		{
			rapidxml::xml_node<>* stateElement = statesElement->first_node();
			if(stateElement)
			{
				do
				{
					std::string stateName = stateElement->name();
					if(stateName == "default")
						getStateStyle(ES_Default, stateElement, *newStyleElement);
					else if(stateName == "over")
						getStateStyle(ES_Over, stateElement, *newStyleElement);
					else if(stateName == "selected")
						getStateStyle(ES_Selected, stateElement, *newStyleElement);
					else
					{
						std::cout << "Error: Unknown ElementState" << std::endl;
					}

					stateElement = stateElement->next_sibling();
				}while( stateElement );
			}
		}

		//----------------------------------------------------------------------

		return 0; 
	}

	int UISerializer::getStateStyle( ElementState eleState, rapidxml::xml_node<>* pElement, ElementStyle& styleEle)
	{
		//Default, Over, or Selected ...	
		StateStyle& stateStyle = styleEle.esMap[eleState];

		rapidxml::xml_node<>* setterElement = pElement->first_node( "setter" );

		if( setterElement )
		{
			//Setters
			do
			{
				std::string propertyName = setterElement->first_attribute( "property" )->value();
				std::string propertyValue = setterElement->first_attribute( "value" )->value();
				
				if( propertyName == "colour" )		
					stateStyle.colour		= parseColourValue(propertyValue);
				
				std::cout << "-------setterElement:" << setterElement->name() << ",property:" << setterElement->first_attribute("property")  << ",value:" << setterElement->first_attribute("value")<< std::endl;
				setterElement = setterElement->next_sibling("setter");
			}while( setterElement );
		}

		//----------------------------------------------------------------------
		// Style background
		//----------------------------------------------------------------------
		rapidxml::xml_node<>* backgroundElement = pElement->first_node("background");
		if(backgroundElement)
		{
			std::string sBGType = backgroundElement->first_attribute("type")->value();

			if(sBGType == "sprite")
			{
				std::string imageSrc = backgroundElement->value();
				stateStyle.background.sprite = imageSrc;
				stateStyle.background.type	  =	BT_Sprite;
			}
			else if(sBGType == "none")
			{
				stateStyle.background.type	  =	BT_Transparent;
			}
			else if(sBGType == "gradient")
			{
				stateStyle.background.type	  =	BT_Gradient;
				stateStyle.background.gradientType = XE::Gradient_NorthSouth;
				stateStyle.background.gradientStart = parseColourValue(backgroundElement->first_node("gradientSart")->first_attribute("color")->value());
				stateStyle.background.gradientEnd   = parseColourValue(backgroundElement->first_node("gradientStop")->first_attribute("color")->value());
			}
			else if(sBGType == "colour")
			{
				stateStyle.background.type	  =	BT_Colour;
				stateStyle.background.colour  = parseColourValue(backgroundElement->value());
			}
			else
			{
				stateStyle.background.type	  =	BT_Transparent;
			}
		}

		//----------------------------------------------------------------------
		// Style border
		//----------------------------------------------------------------------
		rapidxml::xml_node<>* borderElement = pElement->first_node("border");
		if(borderElement)
		{
			rapidxml::xml_node<>* setterElement = borderElement->first_node("setter");
			if(setterElement)
			{
				do
				{

					std::string propertyName = setterElement->first_attribute( "property" )->value();
					std::string propertyValue = setterElement->first_attribute( "value" )->value();

					if( propertyName == "padding" )	
						stateStyle.border.padding.all = Ogre::StringConverter::parseUnsignedInt(propertyValue);
					if( propertyName == "thickness" )	
						stateStyle.border.thickness 	= Ogre::StringConverter::parseInt(propertyValue);
					if( propertyName == "brush" )	
						stateStyle.border.brush		= parseColourValue(propertyValue);

					std::cout << "-------//////bordersetterElement:" << setterElement->name() << ",property:" << setterElement->first_attribute("property")  << ",value:" << setterElement->first_attribute("value")<< std::endl;
					setterElement = setterElement->next_sibling("setter");
				}while(setterElement);
			}
		}
	
		return 0;
	}

	int UISerializer::atlas( rapidxml::xml_node<>* x ,  Screen* parentElement) 
	{ 
		std::cout << "atlas" << std::endl;

		//	//<screen  name="WorldState">
		//	String resName = ValidAttr(eleUIScreen->first_attribute("name"));
		//	
		//	//<atlas>completeGUIDemo.gorilla</atlas>

		return 0; 
	}

	int UISerializer::resourceLocations( rapidxml::xml_node<>* x , Screen* parentElement) 
	{ 
		std::cout << "resourceLocations" << std::endl;
		return 0; 
	}

	int UISerializer::panel( rapidxml::xml_node<>* pElement , Screen* parentElement) 
	{ 
		std::cout << "panel" << std::endl;

		rapidxml::xml_node<>* panelElement = pElement->first_node();
		if(panelElement)
		{
			do
			{
				Panel3D* panel3D = OGRE_NEW  Panel3D(mXEUI
												, mSceneMgr
												, mObjManager
												, 10
												, "completeGUIDemo.gorilla"
												, "panelResolution");
				// nur bei 3D !!! 
				panel3D->mNode->setPosition(0, 0, -5);

				std::cout << "----panelElement:" << panelElement->name() << std::endl;
				CallPanelElement( panelElement->name() ,  panelElement, panel3D);
				panelElement = panelElement->next_sibling();
			}while(panelElement);
		}
		return 0; 
	}

	//PanelElements
	int UISerializer::navigation( rapidxml::xml_node<>* pElement ,UIPanel* parentElement) 
	{ 
		std::cout << "navigation" << std::endl;

		Ogre::Vector2 pos;
		int width = parentElement->_size.x;
		int	height = parentElement->_size.y;

		if(pElement->first_attribute("position"))
			pos = parseVector2(pElement->first_attribute("position")->value(),","); 
		if(pElement->first_attribute("width"))
			width = Ogre::StringConverter::parseInt(pElement->first_attribute("width")->value()); 
		if(pElement->first_attribute("height"))
			height =  Ogre::StringConverter::parseInt(pElement->first_attribute("height")->value()); 
		String name = "";
		if( pElement->first_attribute( "name" ) )
			name = pElement->first_attribute( "name" )->value();

		Navigation* navigation = parentElement->makeNavigation( name, pos.x, pos.y, width, height, 10);
	//	mXEUI->setNavigation(navigation);

		//---------------------------------------------
		// Callback
		if(pElement->first_attribute("callback"))
		{
			String callBack = pElement->first_attribute("callback")->value();

			std::map<std::string, FunctorBase*>::iterator it = mCallbackMap.find(callBack);
			navigation->setValueChangedCallback(it->second);

			std::cout << "----______navItemonItemChanged:" << callBack << std::endl;
		}
		//---------------------------------------------
	
		rapidxml::xml_node<>* navItemElement = pElement->first_node();
		if(navItemElement)
		{
			do
			{
				std::cout << "----_______navItemElement:" << navItemElement->name() << std::endl;

				std::cout << "----_______navItemElement___Panel:" << navItemElement->first_attribute("panel") << std::endl;
				std::cout << "----_______navItemElement___LoadOnStart:" << navItemElement->first_attribute("loadOnStart") << std::endl;
				//Call( navItemElement->name() ,  navItemElement);
				CallNavElement( navItemElement->name() ,  navItemElement , navigation);

				navItemElement = navItemElement->next_sibling();
			}while(navItemElement);
		}

		//mUIStateMgr->addNav( navigation );

		return 0; 
	}
	
	int UISerializer::console(rapidxml::xml_node<>* pElement, UIPanel* parentElement)
	{ 
		std::cout << "console" << std::endl;

		Ogre::Vector2 pos;
		int width = parentElement->_size.x;
		int	height = parentElement->_size.y;

		if(pElement->first_attribute("position"))
			pos = parseVector2(pElement->first_attribute("position")->value(),","); 
		if(pElement->first_attribute("width"))
			width = Ogre::StringConverter::parseInt(pElement->first_attribute("width")->value()); 
		if(pElement->first_attribute("height"))
			height =  Ogre::StringConverter::parseInt(pElement->first_attribute("height")->value()); 
		String name = "";
		if( pElement->first_attribute( "name" ) )
			name = pElement->first_attribute( "name" )->value();

		OgreConsole* console = parentElement->makeConsole(name, pos.x, pos.y, width, height, 10);
	//	mXEUI->setNavigation(navigation);

		//---------------------------------------------
		// Callback
		if(pElement->first_attribute("callback"))
		{
			String callBack = pElement->first_attribute("callback")->value();

			std::map<std::string, FunctorBase*>::iterator it = mCallbackMap.find(callBack);
		//#	console->setValueChangedCallback(it->second);

			std::cout << "----______navItemonItemChanged:" << callBack << std::endl;
		}
		//---------------------------------------------
	
		//rapidxml::xml_node<>* navItemElement = pElement->first_node();
		//if(navItemElement)
		//{
		//	do
		//	{
		//		std::cout << "----_______navItemElement:" << navItemElement->name() << std::endl;

		//		std::cout << "----_______navItemElement___Panel:" << navItemElement->first_attribute("panel") << std::endl;
		//		std::cout << "----_______navItemElement___LoadOnStart:" << navItemElement->first_attribute("loadOnStart") << std::endl;
		//		//Call( navItemElement->name() ,  navItemElement);
		//		CallNavElement( navItemElement->name() ,  navItemElement , navigation);

		//		navItemElement = navItemElement->next_sibling();
		//	}while(navItemElement);
		//}

		//mUIStateMgr->addNav( navigation );

		return 0; 
	}

	int UISerializer::menu( rapidxml::xml_node<>* pElement , UIPanel* parentElement) 
	{ 
		std::cout << "menu" << std::endl;
	
		Ogre::uint16 id = 0;
		String name = "NotF";

		if(pElement->first_attribute("id"))
			id = Ogre::StringConverter::parseUnsignedInt( pElement->first_attribute("id")->value() );

		if(pElement->first_attribute("name"))
			name =  pElement->first_attribute("name")->value();

		Ogre::Vector2 pos;
		Ogre::uint16 width = parentElement->_size.x;
		Ogre::uint16 height = parentElement->_size.y;

		if(pElement->first_attribute("position"))
			pos = parseVector2(pElement->first_attribute("position")->value(),","); 
		if(pElement->first_attribute("width"))
			width = Ogre::StringConverter::parseInt(pElement->first_attribute("width")->value()); 
		if(pElement->first_attribute("height"))
			height =  Ogre::StringConverter::parseInt(pElement->first_attribute("height")->value()); 

		Menu* menuTest = parentElement->makeMenu( name, pos.x, pos.y, width, height, 4);

		//---------------------------------------------
		// Callback
		if(pElement->first_attribute("callBack"))
		{
			String callBack = pElement->first_attribute("callBack")->value();

			std::map<std::string, FunctorBase*>::iterator it = mCallbackMap.find(callBack);
			if(it != mCallbackMap.end())
				menuTest->setValueChangedCallback(it->second);
			else
				OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Callback not found",
					"UISerliazer::menu");

			std::cout << "----_______menuItemonSelect:" << callBack << std::endl;
		}
		//---------------------------------------------


		rapidxml::xml_node<>* menuElement = pElement->first_node();
		if(menuElement)
		{
			do
			{
				std::cout << "----_______menuElement:" << menuElement->name() << std::endl;
				CallMenuElement( menuElement->name() ,  menuElement, menuTest);
				menuElement = menuElement->next_sibling();
			}while(menuElement);
		}

		return 0; 
	}

	int UISerializer::menuItem( rapidxml::xml_node<>* pElement , Menu* parentElement ) 
	{ 
		std::cout << "menuItem" << std::endl;
		
		String caption = "NotF";
		if( pElement->first_attribute( "caption" ) )
			caption = pElement->first_attribute( "caption" )->value();

		String name = "";
		if( pElement->first_attribute( "name" ) )
			name = pElement->first_attribute( "name" )->value();

		
		//Typen list(MIButton),Combo(MenuItem)
		//XE::UI::MIButton* menuItem = parentElement->getPanelContainer()->makeMenu(2, 10, 10, 280, 280, 4);
		XE::MIButton* menuItem = OGRE_NEW  MIButton( name, 0, caption, parentElement );
		
		if( pElement->first_attribute( "id" ) )
			menuItem->setID(Ogre::StringConverter::parseUnsignedInt(pElement->first_attribute("id")->value()));

		//---------------------------------------------
		// Submenu
		if( pElement->first_attribute( "subMenu" ) )
		{
			String subMenu = pElement->first_attribute( "subMenu" )->value();

			menuItem->setSubMenu( subMenu );

			std::cout << "----_______menuItemsubMenu:" << subMenu << std::endl;
		}
		//---------------------------------------------
	

		//---------------------------------------------
		// Callback
		if(pElement->first_attribute("callBack"))
		{
			String callBack = pElement->first_attribute("callBack")->value();

			std::map<std::string, FunctorBase*>::iterator it = mCallbackMap.find(callBack);
			menuItem->setPressedCallback(it->second);

			std::cout << "----_______menuItemonSelect:" << callBack << std::endl;
		}
		//---------------------------------------------
		
		//---------------------------------------------
		// Style
		if( pElement->first_attribute("style"))
			std::cout << "----_______menuItemstyle:" << pElement->first_attribute("style") << std::endl;
		//---------------------------------------------
	

		//---------------------------------------------
		// Menu Item Elements
		rapidxml::xml_node<>* menuItemElement = pElement->first_node();
		if(menuItemElement)
		{
			do
			{
				std::cout << "----_______menuItemElement:" << menuItemElement->name() << std::endl;

				std::string test = menuItemElement->name();
				//if(menuItemElement->name() == "image")
				if(test == "caption")
					menuItem->setText(menuItemElement->value());

				std::cout << "----_______--------------Text:" << menuItemElement->value() << std::endl;


				menuItemElement = menuItemElement->next_sibling();
			}while(menuItemElement);
		}
		//---------------------------------------------
		
		parentElement->addItem(menuItem);

		return 0; 
	}


	int UISerializer::navItem( rapidxml::xml_node<>* pElement , Navigation* parentElement ) 
	{ 
		std::cout << "navItem" << std::endl;
		
		String caption = "NotF";
		if( pElement->first_attribute( "caption" ) )
			caption = pElement->first_attribute( "caption" )->value();

		String name = "";
		if( pElement->first_attribute( "name" ) )
			name = pElement->first_attribute( "name" )->value();

		Ogre::uint16 idx;
		if (pElement->first_attribute("idx"))
			idx = Ogre::StringConverter::parseUnsignedInt( pElement->first_attribute("idx")->value() );

		//Typen list(MIButton),Combo(MenuItem)
		//XE::UI::MIButton* navItem = parentElement->getPanelContainer()->makeMenu(2, 10, 10, 280, 280, 4);
		NavItem* navItem = OGRE_NEW  NavItem(name, idx, caption, parentElement);
		
		//---------------------------------------------
		// Subnav
		if (pElement->first_attribute( "subMenu" ) )
		{
			String subMenu = pElement->first_attribute("subMenu")->value();

		//	navItem->setSubMenu(subMenu);

			std::cout << "----_______navItemsubMenu:" << subMenu << std::endl;
		}
		//---------------------------------------------
	

		//---------------------------------------------
		// Callback
		if(pElement->first_attribute("callBack"))
		{
			String callBack = pElement->first_attribute("callBack")->value();

			std::map<std::string, FunctorBase*>::iterator it = mCallbackMap.find(callBack);
			navItem->setPressedCallback(it->second);

			std::cout << "----_______navItemonSelect:" << callBack << std::endl;
		}
		//---------------------------------------------
		
		//---------------------------------------------
		// Style
		if( pElement->first_attribute("style"))
			std::cout << "----_______navItemstyle:" << pElement->first_attribute("style") << std::endl;
		//---------------------------------------------
	

		//---------------------------------------------
		// Menu Item Elements
		rapidxml::xml_node<>* navItemElement = pElement->first_node();
		if(navItemElement)
		{
			do
			{
				std::cout << "----_______navItemElement:" << navItemElement->name() << std::endl;

				std::string test = navItemElement->name();
				//if(navItemElement->name() == "image")
				if(test == "caption")
					navItem->text(navItemElement->value());

				std::cout << "----_______--------------Text:" << navItemElement->value() << std::endl;


				navItemElement = navItemElement->next_sibling();
			}while(navItemElement);
		}
		//---------------------------------------------
		
		parentElement->addItem(navItem);

		return 0; 
	}

	//void UISerializer::load(rapidxml::xml_node<>* XMLNode)
	//{
	//	//Alle Elemente durchlaufen
	//	rapidxml::xml_node<>* pElement = XMLNode->first_node(); 
	//	if(pElement)
	//	{
	//		do
	//		{
	//			if(pElement->name() == "screen")
	//				loadScreen(Viewport* vp,const Ogre::String &fileName, const Ogre::String &groupName);
	//			else if(pElement->name() == "panel2D")

	//			else if(pElement->name() == "panel3D")
	//			
	//			pElement = pElement->next_sibling();
	//		}while(pElement);
	//	}
	//}
	//----------------------------------------------------------------------------
	//int UISerializer::ImportScreen(Viewport* vp,const Ogre::String &UIName, const Ogre::String &groupName)
	//{
	//	DataStreamPtr stream = ResourceGroupManager::getSingleton().openResource(UIName, groupName );
	//	char* scene = strdup(stream->getAsString().c_str());
	//
	//	TiXmlDocument docImport;//("MenuInit.xml");
	//	docImport.Parse((const char*)scene, 0, TIXML_ENCODING_UTF8);
	//	//   if(!docImport.LoadFile()) return SCF_ERRFILE;
	//
	//	//<screen  name="WorldState">
	//	TiXmlElement* eleUIScreen = docImport.first_node("screen");
	//
	//
	//	m["foo"] = &UISerializer::EleAtlas; //( std::make_pair( "dd", std::bind( &UISerializer::EleAtlas, eleUIScreen ) ));
	//	m["foo"];
	//
	//	if(!eleUIScreen)
	//		return SCF_ERRFILE;
	//	std::cout << "Element:" << eleUIScreen->ValueStr() << std::endl;
	//	
	//	//<atlas>completeGUIDemo.gorilla</atlas>
	//	TiXmlElement* eleAtlas = eleUIScreen->first_node("atlas");
	//	if(!eleAtlas)
	//		return SCF_ERRFILE;
	//	/* pOpt->SceneManagerName = "OctreeSceneManager";
	//
	//	pOpt->ResourceDirectories.push_back("/");*/
	//	TiXmlElement* resLoc = eleUIScreen->first_node("resourceLocations");
	//	if(resLoc)
	//	{
	//		resLoc = resLoc->first_node();
	//		while(resLoc)
	//		{
	//			String resType = ValidAttr(resLoc->first_attribute("type"));
	//			String resName = ValidAttr(resLoc->first_attribute("name"));
	//			if(resType == "FileSystem")
	//			{
	//				//todo  UIUtils::CleanPath(resName);
	//
	//				if(resName[0] == '.')
	//					resName.erase(0, 1);
	//
	//				//todo    pOpt->ResourceDirectories.push_back(resName);
	//			}
	//
	//			resLoc = resLoc->next_sibling();
	//		}
	//	}
	//
	//	//<screen  name="WorldState">
	//	String resName = ValidAttr(eleUIScreen->first_attribute("name"));
	//	
	//	//<atlas>completeGUIDemo.gorilla</atlas>
	//	String atlasName = eleAtlas->GetText();
	//	mUIScreen = mXEUI->createScreen(vp,atlasName , resName);
	//
	//	////<screen  name="WorldState">
	//	RecurseReadObjects(eleUIScreen); //, mngred);
	//   
	//	//ogRoot->AfterLoadScene();
	//    //ogRoot->GetViewport()->getCameraEditor()->setClipDistance(vClipping);
	//    return SCF_OK;
	//}
	////----------------------------------------------------------------------------
	//int UISerializer::RecurseReadObjects(TiXmlElement *parentelement) //,CBaseEditor* parentobject)
	//{
	//   // CBaseEditor *newobj;
	//    TiXmlElement* element = 0;
	//    Ogre::String eType;
	//    element = parentelement->first_node();
	//   
	//	std::cout << "Element:" << element->ValueStr() << std::endl;
	//    if(!element) return SCF_OK;
	//
	//    do
	//    {
	//     //   newobj = 0;
	//        eType = element->Value();
	//		//-------------------------------------------------------------------------------------
	//		if(eType == "style") 
	//		{
	//
	//		}  
	//		else if(eType == "screenpanel") 
	//		{
	//			/*mPanel = OGRE_NEW  XE::UI::ScreenPanel(
	//			&mXEUI, mXEUI.getScreen("WorldState"), 
	//							XE::Ogre::Vector2(400, 240),
	//							XE::Ogre::Vector2(300, 300),
	//							"completeGUIDemo.gorilla", 
	//							"panelResolution");*/
	//		} 
	//		else if(eType == "button") 
	//		{
	//
	//		}
	//		else if(eType == "panel") 
	//		{
	//
	//		}
	//        else if(eType == "menu") 
	//        {
	//            ReadUINode(element); //, parentobject, &newobj);
	//			std::cout << "---------------------------------------------------" << std::endl;
	//			int ret = RecurseReadObjects(element);//, newobj);
	//            
	//            if(ret != SCF_OK) 
	//                return ret;          
	//        }
	//	    else if(eType == "submenu") ReadSubMenu(element); //, parentobject, &newobj);
	//		  else 
	//            continue;
	//
	//      //-------------------------------------------------------------------------------------
	//        /*else if(eType == "entity") ReadEntity(element, parentobject, &newobj);
	//        else if(eType == "light") ReadLight(element, parentobject, &newobj);
	//        else if(eType == "camera") ReadCamera(element, parentobject, &newobj);
	//        else if(eType == "particle") ReadParticle(element, parentobject, &newobj);
	//        else if(eType == "plane") ReadPlane(element, parentobject, &newobj);*/
	//      
	//    } while(element = element->next_sibling());
	//    return SCF_OK;
	//}
	////----------------------------------------------------------------------------
	//int UISerializer::ReadUINode(TiXmlElement *element) //, CBaseEditor *parent, CBaseEditor **ret)
	//{
	//   /* UIPropertyValueMap params;
	//    UIPropertyValue propValue;
	// 
	//    propValue.propType = PROP_STRING;*/
	//    Ogre::String name = ValidAttr(element->first_attribute("id"));
	//    /*if(UI::UIRoot::getSingletonPtr()->FindObject(name))
	//        propValue.val = Any(String("Node") + UI::UIRoot::getSingletonPtr()->CreateUniqueID("Node",""));
	//    else*/
	//     //   propValue.val = Any(name);
	//
	//   // params["name"] = propValue;
	//
	//
	//
	//
	//    TiXmlElement* menuItem = 0;
	//   
	//	//element = Menu
	//    menuItem = element->first_node();
	//    if(!menuItem) return SCF_OK;
	//
	//	//XE::UI::ItemBar* itemBar = ReadMenu(element);
	//
	//	//--------------------
	//	//MENU Items
	//	//-------------------
	//	do
	//	{
	//	//	ReadMenuItem(menuItem,itemBar);
	//		
	//
	//		/*if(eType == "scale")
	//		params["scale"] = parseVector3(subs);
	//		else if(eType == "position")
	//		params["position"] = parseVector3(subs);*/
	//		/*else if(eType == "rotation")
	//		params["orientation"] = parseQuaternion(subs);*/
	//    } while(menuItem = menuItem->next_sibling());
	//    
	//		
	//
	//  //  *ret = UI::UIRoot::getSingletonPtr()->CreateEditorObject(parent, "Node", params, false, false);
	//
	//
	//    return SCF_OK;
	//}
	////----------------------------------------------------------------------------
	////XE::UI::ItemBar* UISerializer::ReadMenu(TiXmlElement *element) //, CBaseEditor *parent, CBaseEditor **ret)
	////{
	////   /* if(UI::UIRoot::getSingletonPtr()->FindObject(name))
	////        propValue.val = Any(String("Entity") + UI::UIRoot::getSingletonPtr()->CreateUniqueID("Entity",""));
	////    else*/
	////      //  propValue.val = Any(name);
	////
	////  //  params["name"] = propValue;
	////
	////    int id = Ogre::StringConverter::parseInt(ValidAttr(element->first_attribute("id")));
	////	String text = ValidAttr(element->first_attribute("text"));
	////  
	////	//Menu Attribute
	////	int itemOffset = Ogre::StringConverter::parseInt(ValidAttr(element->first_attribute("itemoffset")));
	////    float px = Ogre::StringConverter::parseReal(ValidAttr(element->first_attribute("px")));
	////	float py = Ogre::StringConverter::parseReal(ValidAttr(element->first_attribute("py")));
	////	float pz = Ogre::StringConverter::parseReal(ValidAttr(element->first_attribute("pz"))); 
	////
	////	std::cout << "menu:" << element->ValueStr() << ",text:" << text << ",id: " << id << ",offset: " << itemOffset << ",px: " << px << std::endl;
	////	
	////		//-------------------------------
	////	// Menu erstellen
	////	//Uint32 id = Ogre::StringConverter::parseUnsignedInt(ValidAttr(element->first_attribute("id")));
	////	//ItemBar* itemBar = OGRE_NEW  XE::UI::ItemBar(mXEUI,id,XE::Ogre::Vector2(px,py));
	////	//mXEUI->addUIElement(itemBar); 
	////	//----------------------------------
	////
	////    /*propValue.val = Ogre::String(ValidAttr(element->first_attribute("materialFile")));
	////    params["material"] = propValue;
	////    propValue.propType = PROP_BOOL;
	////    propValue.val = Any(StringConverter::parseBool(ValidAttr(element->first_attribute("castShadows"))));
	////    params["castshadows"] = propValue;
	////    propValue.val = Any(StringConverter::parseBool(ValidAttr(element->first_attribute("receiveShadows"))));
	////    params["receiveshadows"] = propValue;*/
	////    
	//////todo    XE::UI::ItemBox* iBoxSub = OGRE_NEW  XE::UI::ItemBox(mGui3D,  XE::UI::ITEM_ID::BALL, "Exit", "item_ball", "item_ball_hover");
	////		
	////   //*ret = UI::UIRoot::getSingletonPtr()->CreateEditorObject(parent, "Entity", params, false, false);
	////    return itemBar;
	////}
	//
	//int UISerializer::ReadMenuItem(TiXmlElement *element,XE::UI::ItemBar* itemBar) //, CBaseEditor *parent, CBaseEditor **ret)
	//{
	//   /* if(UI::UIRoot::getSingletonPtr()->FindObject(name))
	//        propValue.val = Any(String("Entity") + UI::UIRoot::getSingletonPtr()->CreateUniqueID("Entity",""));
	//    else*/
	//      //  propValue.val = Any(name);
	//
	//  //  params["name"] = propValue;
	//
	//    int id = Ogre::StringConverter::parseInt(ValidAttr(element->first_attribute("id")));
	//	String text = ValidAttr(element->first_attribute("text"));
	//  
	//	//Menu Attribute
	//	int itemOffset = Ogre::StringConverter::parseInt(ValidAttr(element->first_attribute("itemoffset")));
	//    float px = Ogre::StringConverter::parseReal(ValidAttr(element->first_attribute("px")));
	//	float py = Ogre::StringConverter::parseReal(ValidAttr(element->first_attribute("py")));
	//	float pz = Ogre::StringConverter::parseReal(ValidAttr(element->first_attribute("pz"))); 
	//
	//	std::cout << "menuItem:" << element->ValueStr() << ",text:" << text << ",id: " << id << ",offset: " << itemOffset << ",px: " << px << std::endl;
	//	
	//	TiXmlElement * miContentElement = element->first_node();
	//	if(miContentElement)
	//	{
	//		String menuItemContentType = miContentElement->ValueStr();
	//		std::cout << "menuItemContentType:" << menuItemContentType << std::endl;
	//		if(menuItemContentType == "button") 
	//		{
	//			String py = (ValidAttr(miContentElement->first_attribute("text")));
	//			std::cout << "menuItemContent_TExt:" << py << std::endl;
	//			int pz = Ogre::StringConverter::parseInt(ValidAttr(miContentElement->first_attribute("menuid"))); 
	//			std::cout << "menuItemContent_MenuID:" << pz << std::endl;
	//		}
	//		else if(menuItemContentType == "submenu") 
	//			ReadSubMenu(miContentElement);
	//
	//		//itemBar->addItem(OGRE_NEW  ItemBox(mXEUI,  XE::UI::ITEM_ID::BALL, text, "item_ball", "item_ball_hover"));
	//		//mXEUI->addUIElement();
	//	}
	//    /*propValue.val = Ogre::String(ValidAttr(element->first_attribute("materialFile")));
	//    params["material"] = propValue;
	//    propValue.propType = PROP_BOOL;
	//    propValue.val = Any(StringConverter::parseBool(ValidAttr(element->first_attribute("castShadows"))));
	//    params["castshadows"] = propValue;
	//    propValue.val = Any(StringConverter::parseBool(ValidAttr(element->first_attribute("receiveShadows"))));
	//    params["receiveshadows"] = propValue;*/
	//    
	////todo    XE::UI::ItemBox* iBoxSub = OGRE_NEW  XE::UI::ItemBox(mGui3D,  XE::UI::ITEM_ID::BALL, "Exit", "item_ball", "item_ball_hover");
	//		
	//   //*ret = UI::UIRoot::getSingletonPtr()->CreateEditorObject(parent, "Entity", params, false, false);
	//    return SCF_OK;
	//}
	////----------------------------------------------------------------------------
	//int UISerializer::ReadSubMenu(TiXmlElement *element) //, CBaseEditor *parent, CBaseEditor **ret)
	//{
	//   /* UIPropertyValueMap params;
	//    UIPropertyValue propValue;
	// 
	//    propValue.propType = PROP_STRING;
	//*/
	//    Ogre::String eType;
	//    if(!element) return SCF_OK;
	//
	//           Ogre::String text = ValidAttr(element->first_attribute("text"));
	//           int id = Ogre::StringConverter::parseInt(ValidAttr(element->first_attribute("menuid")));
	//        std::cout << "ReadSubMenu:" << eType << ",text: " << text << ",menuid: " << id << std::endl;
	//	   /* Ogre::String matname = ValidAttr(subs->first_attribute("materialName"));
	//            propValue.val = Any(matname);
	//            params["subentity" + idx + "::material"] = propValue;*/
	//        
	// 
	//
	//   // parent->getProperties()->initValueMap(params);
	//
	//    return SCF_OK;
	//}
	//
	////----------------------------------------------------------------------------
	//UISerializer *UISerializer = 0;

	//bool dllStartPlugin(void *identifier, Ogre::String& name)
	//{
	//    name = "Dot Scene Serializer Plugin";
	//    UISerializer = OGRE_NEW UISerializer();
	//    UIRoot::getSingletonPtr()->RegisterSerializer(identifier, UISerializer);
	//    return true;
	//}
	////----------------------------------------------------------------------------
	//bool dllGetPluginName(String& name)
	//{
	//    name = "Dot Scene Serializer Plugin";
	//    return true;
	//}
	////----------------------------------------------------------------------------
	//bool dllStopPlugin(void)
	//{
	//    OGRE_DELETE UISerializer;
	//    UISerializer = 0;
	//    return true;
	//}
	//----------------------------------------------------------------------------


} //namespace XE