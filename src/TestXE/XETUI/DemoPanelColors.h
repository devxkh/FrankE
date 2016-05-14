#ifndef MySimpleDemoPanelColors_H
#define MySimpleDemoPanelColors_H

#include <XEUI/PanelColors.h>

/*! struct. MySimpleDemoPanelColors
    desc.
        Example of customisation of Gui3D colors
*/
struct MySimpleDemoPanelColors : public XE::UI::PanelColors
{
    MySimpleDemoPanelColors();
};


MySimpleDemoPanelColors::MySimpleDemoPanelColors()
    : XE::UI::PanelColors()
{
    // General
    transparent = XE::XE_G::rgb(0, 0, 0, 0);

    // Panel
    panelBackgroundSpriteName = "panelBackground";
    panelCursorSpriteName = "mousepointer";
    panelCursorSpriteSizeX = 12;
    panelCursorSpriteSizeY = 18;

    // Button
    // In the demo, sprites are used for the "click me!" button
    buttonInactiveSpriteName = "buttonInactive";
    buttonOveredSpriteName = "buttonOvered";
    buttonNotOveredSpriteName = "buttonNotOvered";
    buttonClickedSpriteName = "buttonClicked";

    // In the demo, those are used by the combobox previous and next buttons
    buttonBackgroundClickedGradientType = XE::XE_G::Gradient_NorthSouth;
    buttonBackgroundClickedGradientStart = XE::XE_G::rgb(255, 255, 255, 200);
    buttonBackgroundClickedGradientEnd = XE::XE_G::rgb(255, 255, 255, 170);

    buttonBackgroundOveredGradientType = XE::XE_G::Gradient_NorthSouth;
    buttonBackgroundOveredGradientStart = XE::XE_G::rgb(255, 255, 255, 128);
    buttonBackgroundOveredGradientEnd = XE::XE_G::rgb(255, 255, 255, 100);

    buttonBackgroundNotOveredGradientType = XE::XE_G::Gradient_NorthSouth;
    buttonBackgroundNotOveredGradientStart = XE::XE_G::rgb(255, 255, 255, 80);
    buttonBackgroundNotOveredGradientEnd = XE::XE_G::rgb(255, 255, 255, 50);

    buttonBackgroundInactiveGradientType = XE::XE_G::Gradient_NorthSouth;
    buttonBackgroundInactiveGradientStart = XE::XE_G::rgb(255, 255, 255, 15);
    buttonBackgroundInactiveGradientEnd = XE::XE_G::rgb(255, 255, 255, 5);

    buttonText = XE::XE_G::rgb(255, 255, 255, 255);
    buttonTextInactive = XE::XE_G::rgb(255, 255, 255, 70);
    buttonTextSize = 14;

    buttonBorder = XE::XE_G::rgb(70, 70, 70, 50);
    buttonBorderHighlight = XE::XE_G::rgb(255, 100, 100, 170);
    buttonBorderInactive = XE::XE_G::rgb(70, 70, 70, 15);
    buttonBorderSize = 1;

    // Checkbox
    checkboxOveredBackgroundSpriteName = "checkboxOvered";
    checkboxNotOveredBackgroundSpriteName = "checkboxNotOvered";
    checkboxCheckedNotOveredBackgroundSpriteName = "checkboxCheckedNotOvered";
    checkboxCheckedOveredBackgroundSpriteName = "checkboxCheckedOvered"; 

    // Combobox
    comboboxButtonPreviousOveredSpriteName = "comboboxpreviouselementbuttonovered";
    comboboxButtonPreviousNotOveredSpriteName = "comboboxpreviouselementbuttonnotovered";
    comboboxButtonPreviousInactiveSpriteName = "comboboxpreviouselementbuttoninactive";

    comboboxButtonNextOveredSpriteName = "comboboxnextelementbuttonovered";
    comboboxButtonNextNotOveredSpriteName = "comboboxnextelementbuttonnotovered";
    comboboxButtonNextInactiveSpriteName = "comboboxnextelementbuttoninactive";

    comboboxBackgroundGradientType = XE::XE_G::Gradient_NorthSouth;
    comboboxBackgroundGradientStart = XE::XE_G::rgb(255, 255, 255, 0);
    comboboxBackgroundGradientEnd = XE::XE_G::rgb(255, 255, 255, 0);

    comboboxOveredElement = XE::XE_G::rgb(255, 255, 255, 100);
    comboboxNotOveredElement = XE::XE_G::rgb(255, 255, 255, 30);
    comboboxSelectedElement = XE::XE_G::rgb(120, 20, 120, 200);

    comboboxText = XE::XE_G::ColourValue::White;
    comboboxTextSize = 14;

    comboboxBorder = XE::XE_G::rgb(70, 70, 70, 50);
    comboboxBorderHighlight = XE::XE_G::rgb(255, 100, 100, 170);
    comboboxBorderSize = 0;

	  // Listbox
    // same value as the combobox
    listboxButtonPreviousOveredSpriteName = comboboxButtonPreviousOveredSpriteName;
    listboxButtonPreviousNotOveredSpriteName = comboboxButtonPreviousNotOveredSpriteName;
    listboxButtonPreviousInactiveSpriteName = comboboxButtonPreviousInactiveSpriteName;

    listboxButtonNextOveredSpriteName = comboboxButtonNextOveredSpriteName;
    listboxButtonNextNotOveredSpriteName = comboboxButtonNextNotOveredSpriteName;
    listboxButtonNextInactiveSpriteName = comboboxButtonNextInactiveSpriteName;

    listboxBackgroundGradientType = comboboxBackgroundGradientType;
    listboxBackgroundGradientStart = comboboxBackgroundGradientStart;
    listboxBackgroundGradientEnd = comboboxBackgroundGradientEnd;

    listboxOveredElement = comboboxOveredElement;
    listboxNotOveredElement = comboboxNotOveredElement;
    listboxOveredSelectedElement = comboboxSelectedElement;
    listboxNotOveredSelectedElement = comboboxSelectedElement + XE::XE_G::rgb(0, 0, 0, -50);

    listboxText = comboboxText;
    listboxTextSize = 14;

    listboxBorder = comboboxBorder;
    listboxBorderHighlight = comboboxBorderHighlight;
    listboxBorderSize = comboboxBorderSize;


    // Caption
    captionBackgroundGradientType = XE::XE_G::Gradient_NorthSouth;
    captionBackgroundGradientStart = transparent;
    captionBackgroundGradientEnd = transparent;

    captionBorder = transparent;
    captionText = XE::XE_G::ColourValue::White;
    captionTextSize = 14;
    captionBorderSize = 0;
}

#endif