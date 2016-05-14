#ifndef UIELEMENTSTYLE_HPP
#define UIELEMENTSTYLE_HPP

//#include <XERenderer/GUI/Gorilla.h>

namespace XE {


	//enum StyleType
	//{
	//	S_Default,
	//	
	//	S_ListBox,
	//	S_ComboBox,
	//	S_Caption,
	//	S_Button,
	//	S_Panel2D,
	//	S_Panel3D,
	//	S_Menu,
	//	S_MenuItem,
	//	S_Mouse,
	//	S_Navigation,
	//	S_NavItem,
	//	S_Console,

	//	S_Count
	//};

	//enum Unit
	//{
	//	Unit_Pixel,
	//	Unit_Percent,
	//	Unit_Fill,
	//	Unit_Auto,
	//	Unit_AlignLeft,
	//	Unit_AlignRight,
	//	Unit_AlignCenter,
	//	Unit_AlignTop,
	//	Unit_AlignBottom,

	//	Unit_VBottomPElement,
	//	Unit_VCenterPElement,
	//	Unit_VTopPElement,
	//	Unit_HCenterPElement,
	//	Unit_HLeftPElement,
	//	Unit_HRightPElement,
	//};

	//enum ElementState
	//{
	//	ES_Disabled,
	//	ES_Over,
	//	ES_Default,
	//	ES_Selected
	//};

	//enum ElementType
	//{
	//	ET_Block,
	//	ET_Button,
	//	ET_TextBox,
	//	ET_OSK_BEGIN,
	//	ET_OSKContainer,
	//	ET_OSKTitle,
	//	ET_OSKInput,
	//	ET_OSKSubmit,
	//	ET_OSKCancel,
	//	ET_OSK_END
	//};

	//enum BackgroundType
	//{
	//	BT_Transparent,
	//	BT_Sprite,
	//	BT_Colour,
	//	BT_Gradient
	//};
	//	
	//struct Margin
	//{
	//public:
	//	Ogre::uint16 left;
	//	Ogre::uint16 top;
	//	Ogre::uint16 right;
	//	Ogre::uint16 bottom;
	//};

	//struct Padding
	//{
	//public:
	//	Ogre::uint16 all;
	//	Ogre::uint16 left;
	//	Ogre::uint16 top;
	//	Ogre::uint16 right;
	//	Ogre::uint16 bottom;
	//};

	//struct StateStyle
	//{
	//	struct Background
	//	{
	//		BackgroundType type;

	//		Gradient gradientType;
	//		Ogre::ColourValue colour;
	//		Ogre::ColourValue gradientStart;
	//		Ogre::ColourValue gradientEnd;
	//		Ogre::String sprite;
	//		bool set;
	//	} background;

	//	struct Border
	//	{
	//		Padding padding;
	//		Ogre::uint16 thickness;
	//		Ogre::ColourValue brush;
	//		Ogre::ColourValue top, left, right, bottom;
	//		bool top_set, left_set, right_set, bottom_set;
	//	} border;

	//	Ogre::ColourValue colour;
	//	bool colour_set;
	//};

	//struct Aligment
	//{
	//		Margin margin;
	//		Unit unithorz;
	//		Unit unitvert;
	//		
	//		float left;
	//		bool left_set;
	//		float top;
	//		bool top_set;
	//};

	//struct ElementStyle : public Ogre::GeneralAllocatedObject
	//{			
	//public:
	//	size_t font;
	//	bool font_set;
	//	
	//	Aligment align;
	//	Aligment textAlign;

	//	float width;
	//	Unit width_unit;
	//	bool width_set;
	//	float height;
	//	Unit height_unit;
	//	bool height_set;

	//	ElementStyle()
	//	{
	//		//Default Style for all Elements
	//		width_unit = Unit::Unit_Auto;
	//		height_unit = Unit::Unit_Auto;
	//		height = 0;
	//		width = 0;
	//		font = 14;
	//				
	//		align.unithorz = Unit_AlignLeft;
	//		align.unitvert = Unit_AlignTop;
	//		
	//		textAlign.unithorz = Unit_AlignLeft;
	//		textAlign.unitvert = Unit_AlignTop;

	//		StateStyle sDefault;
	//		sDefault.background.colour = Ogre::ColourValue::Black;
	//		sDefault.background.type	  =	BT_Colour;
	//		sDefault.background.gradientType = Gradient_NorthSouth;

	//		sDefault.border.thickness	  =	4;
	//		sDefault.border.brush	  = Ogre::ColourValue::Blue;
	//		sDefault.colour			  = Ogre::ColourValue::Green;

	//		StateStyle sDisabled;
	//		sDisabled.background.colour = Ogre::ColourValue::White;
	//		sDisabled.background.type	= BT_Colour;
	//		sDisabled.background.gradientType = Gradient_NorthSouth;
	//		sDisabled.border.thickness		= 4;
	//		sDisabled.border.brush		= Ogre::ColourValue::Black;
	//		sDisabled.colour			= Ogre::ColourValue::White;

	//		add( ES_Default, sDefault );
	//		add( ES_Disabled, sDisabled );
	//	};

	//	~ElementStyle()
	//	{
	//		esMap.clear();
	//	}

	//	std::map< ElementState, StateStyle > esMap;
	//	void add( ElementState es, StateStyle ss ) { esMap[es] = ss; } //leak? alten style löschen?
	//};

 //   struct MenuStyle : public ElementStyle
	//{
	//	float item_width;
	//	Unit item_width_unit;
	//	bool item_width_set;
	//	float item_height;
	//	Unit item_height_unit;
	//	bool item_height_set;

	//public:
	//	/*MenuStyle()
	//	{
	//	
	//	};*/
	//};

	//struct MenuItemStyle : public ElementStyle
	//{
	//public:
	//	MenuItemStyle()
	//	{
	//		//Default Style for Menu Items
	//		StateStyle sOver;
	//		sOver.background.colour	= Ogre::ColourValue::White;
	//		sOver.background.type	= BT_Colour;
	//		sOver.border.thickness		= 4;
	//		sOver.border.brush		= Ogre::ColourValue::Blue;
	//		sOver.colour			= Ogre::ColourValue::Black;

	//		StateStyle sSelected;
	//		sSelected.background.gradientStart	= Ogre::ColourValue::White;
	//		sSelected.background.gradientEnd	= Ogre::ColourValue::Black;
	//		sSelected.background.type			= BT_Gradient;
	//		sSelected.border.thickness				= 4;
	//		sSelected.border.brush				= Ogre::ColourValue::White;
	//		sSelected.colour					= Ogre::ColourValue::Blue;

	//		add(ES_Over,sOver);
	//		add(ES_Selected,sSelected);
	//	};
	//};
 //  
	//struct ConsoleStyle : public ElementStyle
	//{
	//	//float item_width;
	//	//Unit item_width_unit;
	//	//bool item_width_set;
	//	//float item_height;
	//	Unit height_unit;
	//	bool height_set;

	//public:
	//	/*MenuStyle()
	//	{
	//	
	//	};*/
	//};

	//struct NavStyle : public ElementStyle
	//{
	//	float item_width;
	//	Unit item_width_unit;
	//	bool item_width_set;
	//	float item_height;
	//	Unit height_unit;
	//	bool height_set;

	//public:
	//	/*MenuStyle()
	//	{
	//	
	//	};*/
	//};

	//struct NavItemStyle : public ElementStyle
	//{

	//public:
	//	NavItemStyle()
	//	{
	//		//Default Style for Menu Items
	//		StateStyle sOver;
	//		sOver.background.colour	= Ogre::ColourValue::White;
	//		sOver.background.type	= BT_Colour;
	//		sOver.border.thickness		= 4;
	//		sOver.border.brush		= Ogre::ColourValue::Blue;
	//		sOver.colour			= Ogre::ColourValue::Black;

	//		StateStyle sSelected;
	//		sSelected.background.gradientStart	= Ogre::ColourValue::White;
	//		sSelected.background.gradientEnd	= Ogre::ColourValue::Black;
	//		sSelected.background.type			= BT_Gradient;
	//		sSelected.border.thickness				= 4;
	//		sSelected.border.brush				= Ogre::ColourValue::White;
	//		sSelected.colour					= Ogre::ColourValue::Blue;

	//		add(ES_Over,sOver);
	//		add(ES_Selected,sSelected);
	//	};
	//};

	//struct ListBoxStyle : public ElementStyle
	//{

	//};
	//
	//void styleRectangle(Rectangle* mDesign, ElementStyle* style, ElementState state);

	//void styleCaption(Caption* mCaption, ElementStyle* style, ElementState state);


} // namespace XE

#endif //UIELEMENTSTYLE_HPP