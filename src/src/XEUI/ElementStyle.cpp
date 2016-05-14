#include <XEUI/ElementStyle.hpp>


namespace XE {


	void styleRectangle(Rectangle* mDesign, ElementStyle* style, ElementState state)
	{
		if (!style) return;

		std::map<ElementState, StateStyle>::iterator it = style->esMap.find(state);

		if(it != style->esMap.end())
		{
			if(it->second.background.type == BackgroundType::BT_Colour)
				mDesign->background_colour(it->second.background.colour);
			else if(it->second.background.type == BackgroundType::BT_Sprite)
				mDesign->background_image(it->second.background.sprite);
			else if(it->second.background.type == BackgroundType::BT_Transparent)
				mDesign->no_background();
			else if(it->second.background.type == BackgroundType::BT_Gradient)
			{
				mDesign->background_gradient(it->second.background.gradientType,
					it->second.background.gradientStart,
					it->second.background.gradientEnd);
			}
			
			mDesign->border(it->second.border.thickness, it->second.border.brush);
		}
	};

	void styleCaption(Caption* mCaption, ElementStyle* style, ElementState state)
	{
		std::map<ElementState, StateStyle>::iterator it = style->esMap.find(state);

		mCaption->font(style->font);
	//	
		if (style->align.unithorz == Unit_AlignCenter)
			mCaption->vertical_align(VerticalAlign_Middle);
		else if (style->align.unithorz == Unit_AlignTop)
			mCaption->vertical_align(VerticalAlign_Top);
		else if (style->align.unithorz == Unit_AlignBottom)
			mCaption->vertical_align(VerticalAlign_Bottom);

		if (style->align.unitvert == Unit_AlignCenter)
			mCaption->align(TextAlign_Centre);
		else if (style->align.unitvert == Unit_AlignLeft)
			mCaption->align(TextAlign_Left);
		else if (style->align.unitvert == Unit_AlignRight)
			mCaption->align(TextAlign_Right);


		if (it != style->esMap.end())
		{
			mCaption->colour(it->second.colour);
		//	mCaption = mPanelContainer->getGUILayer()->createCaption(style->font, x, y, "MenuItemText");

			mCaption->no_background(); //background(Colours::Aqua); ; // background(getColors()->transparent);
			mCaption->colour(style->esMap[state].colour);
		}
	}


} // namespace XE