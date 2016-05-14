
#ifndef Gui3DPanelColors_H
#define Gui3DPanelColors_H


//#include <OGRE\Ogre.h>
#include <XEGraphics/Gorilla.h>
//#include "Gorilla.h"

namespace XE {


/*! class. PanelColors
    desc.
        Interface for colors of the Gui3D elements.
    note.
        By default, an element will use its gradients, colors and borders definitions.
        To use sprites, you have to set ALL the sprite names (each has to be different of "" or "none"), and
            thoses sprites have to be defined in the .gorilla file, otherwise, an OGRE EXCEPTION will 
            be throwned by Gorilla (with the sprite name or sprite informations)
*/
struct PanelColors
{
    /** \brief Init all the colour values
    */
    PanelColors()
    {
        transparent = rgb(0, 0, 0, 0);

        // NorthSouth gradient by default
        panelGradientType = Gradient_NorthSouth;

        buttonBackgroundClickedGradientType = panelGradientType;
        buttonBackgroundOveredGradientType = panelGradientType;
        buttonBackgroundNotOveredGradientType = panelGradientType;
        buttonBackgroundInactiveGradientType = panelGradientType;

        checkboxOveredGradientType = panelGradientType;
        checkboxNotOveredGradientType = panelGradientType;

        comboboxBackgroundGradientType = panelGradientType;

        inlineselectorBackgroundGradientType = panelGradientType;

        listboxBackgroundGradientType = panelGradientType;

        scrollbarBackgroundGradientType = panelGradientType;
        scrollbarProgressbarGradientType = panelGradientType;
        scrollbarCursorOveredGradientType = panelGradientType;
        scrollbarCursorNotOveredGradientType = panelGradientType;
        scrollbarCursorSelectedGradientType = panelGradientType;

        textzoneBackgroundOveredGradientType = panelGradientType;
        textzoneBackgroundNotOveredGradientType = panelGradientType;
        textzoneBackgroundSelectedGradientType = panelGradientType;

        captionBackgroundGradientType = panelGradientType;

        progressbarBackgroundGradientType = panelGradientType;
        progressbarLoadingBarGradientType = panelGradientType;


        // Init border sizes
        size_t defaultBorderSize = 0;
        
        panelCursorSpriteSizeX = defaultBorderSize;
        panelCursorSpriteSizeY = defaultBorderSize;
        panelBorderSize = defaultBorderSize;

        buttonTextSize = defaultBorderSize;
        buttonBorderSize = defaultBorderSize;

        checkboxTextSize = defaultBorderSize;
        checkboxBorderSize = defaultBorderSize;

        comboboxTextSize = defaultBorderSize;
        comboboxBorderSize = defaultBorderSize;

        inlineselectorTextSize = defaultBorderSize;
        inlineselectorBorderSize = defaultBorderSize;

        listboxTextSize = defaultBorderSize;
        listboxBorderSize = defaultBorderSize;

        scrollbarTextSize = defaultBorderSize;
        scrollbarBorderSize = defaultBorderSize;
        scrollbarCursorBorderSize = defaultBorderSize;

        textzoneTextSize = defaultBorderSize;
        textzoneBorderSize = defaultBorderSize;

        captionTextSize = defaultBorderSize;
        captionBorderSize = defaultBorderSize;

        progressbarTextSize = defaultBorderSize;
        progressbarBorderSize = defaultBorderSize;
    }

    // General
    Ogre::ColourValue transparent;

    // Panel
    Ogre::String panelBackgroundSpriteName;

    Ogre::String panelCursorSpriteName;
    size_t panelCursorSpriteSizeX;
    size_t panelCursorSpriteSizeY;

    Gradient panelGradientType; //!< \brief The gradient type of a panel. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue panelGradientColorStart; 
    Ogre::ColourValue panelGradientColorEnd;
    
    Ogre::ColourValue panelBorder; //!< \brief The border colour of a panel.
    size_t panelBorderSize; //!< \brief The border size of a panel.


    /**
      *
     * Button configuration
    *
    */
    Ogre::String buttonOveredSpriteName;
    Ogre::String buttonNotOveredSpriteName;
    Ogre::String buttonInactiveSpriteName;
    Ogre::String buttonClickedSpriteName;

    Gradient buttonBackgroundClickedGradientType; //!< \brief The gradient type of an overed button. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue buttonBackgroundClickedGradientStart;
    Ogre::ColourValue buttonBackgroundClickedGradientEnd;

    Gradient buttonBackgroundOveredGradientType; //!< \brief The gradient type of an overed button. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue buttonBackgroundOveredGradientStart;
    Ogre::ColourValue buttonBackgroundOveredGradientEnd;

    Gradient buttonBackgroundNotOveredGradientType; //!< \brief The gradient type of a not overed button. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue buttonBackgroundNotOveredGradientStart;
    Ogre::ColourValue buttonBackgroundNotOveredGradientEnd;

    Gradient buttonBackgroundInactiveGradientType;
    Ogre::ColourValue buttonBackgroundInactiveGradientStart; //!< \brief The gradient type of an inactive hovered button. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue buttonBackgroundInactiveGradientEnd;
    
    Ogre::ColourValue buttonText; //!< \brief The text colour of a button.
    Ogre::ColourValue buttonTextInactive; //!< \brief The text colour of an inactive button.
    size_t buttonTextSize;

    Ogre::ColourValue buttonBorder; //!< \brief The border colour of a button.
    Ogre::ColourValue buttonBorderHighlight; //!< \brief The border colour of a highlight button.
    Ogre::ColourValue buttonBorderInactive; //!< \brief The border colour of an inactive button.
    size_t buttonBorderSize; //!< \brief The border size of a button.


    /**
      *
     * Checkbox configuration
    *
    */
    Ogre::String checkboxOveredBackgroundSpriteName;
    Ogre::String checkboxNotOveredBackgroundSpriteName;
    Ogre::String checkboxCheckedNotOveredBackgroundSpriteName;
    Ogre::String checkboxCheckedOveredBackgroundSpriteName;

    char checkboxCheckedSymbol;

    Gradient checkboxOveredGradientType; //!< \brief The gradient tye of an overed checkbox. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue checkboxOveredGradientStart;
    Ogre::ColourValue checkboxOveredGradientEnd;

    Gradient checkboxNotOveredGradientType; //!< \brief The gradient type of a not overed button. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue checkboxNotOveredGradientStart;
    Ogre::ColourValue checkboxNotOveredGradientEnd;

    Gradient checkboxSelectedOveredGradientType; //!< \brief The gradient tye of an overed checkbox. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue checkboxSelectedOveredGradientStart;
    Ogre::ColourValue checkboxSelectedOveredGradientEnd;

    Gradient checkboxSelectedNotOveredGradientType; //!< \brief The gradient type of a not overed button. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue checkboxSelectedNotOveredGradientStart;
    Ogre::ColourValue checkboxSelectedNotOveredGradientEnd;

    Ogre::ColourValue checkboxText; //!< \brief The text colour of a checked symbol of a checkbox.
    size_t checkboxTextSize;

    Ogre::ColourValue checkboxBorder; //!< \brief The border colour of a checkbox.
    Ogre::ColourValue checkboxBorderHighlight; //!< \brief The border colour of a highlight checkbox.
    size_t checkboxBorderSize; //!< The border size of a checkbox.


    /**
      *
     * Combobox configuration
    *
    */
    Ogre::String comboboxButtonPreviousOveredSpriteName;
    Ogre::String comboboxButtonPreviousNotOveredSpriteName;
    Ogre::String comboboxButtonPreviousInactiveSpriteName;
    Ogre::String comboboxButtonPreviousClickedSpriteName;

    Ogre::String comboboxButtonNextOveredSpriteName;
    Ogre::String comboboxButtonNextNotOveredSpriteName;
    Ogre::String comboboxButtonNextInactiveSpriteName;
    Ogre::String comboboxButtonNextClickedSpriteName;

    Gradient comboboxBackgroundGradientType; //!< \brief The gradient type of an overed combobox. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue comboboxBackgroundGradientStart;
    Ogre::ColourValue comboboxBackgroundGradientEnd;

    Ogre::ColourValue comboboxOveredElement;
    Ogre::ColourValue comboboxNotOveredElement;
    Ogre::ColourValue comboboxSelectedElement;

    Ogre::ColourValue comboboxText; //!< \brief The text colour of combobox elements
    size_t comboboxTextSize;

    Ogre::ColourValue comboboxBorder; //!< \brief The border colour of a combobox
    Ogre::ColourValue comboboxBorderHighlight; //!< \brief The border colour of a highlight combobox
    size_t comboboxBorderSize; //!< \brief The border size of a combobox


    /**
      *
     * InlineSelector configuration
    *
    */
    Ogre::String inlineselectorButtonPreviousOveredSpriteName;
    Ogre::String inlineselectorButtonPreviousNotOveredSpriteName;
    Ogre::String inlineselectorButtonPreviousInactiveSpriteName;
    Ogre::String inlineselectorButtonPreviousClickedSpriteName;

    Ogre::String inlineselectorButtonNextOveredSpriteName;
    Ogre::String inlineselectorButtonNextNotOveredSpriteName;
    Ogre::String inlineselectorButtonNextInactiveSpriteName;
    Ogre::String inlineselectorButtonNextClickedSpriteName;

    Gradient inlineselectorBackgroundGradientType; //!< \brief The gradient type of an inline selector. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue inlineselectorBackgroundGradientStart;
    Ogre::ColourValue inlineselectorBackgroundGradientEnd;
    
    Ogre::ColourValue inlineselectorText; //!< \brief The text colour of an inline selector
    size_t inlineselectorTextSize;

    Ogre::ColourValue inlineselectorBorder; //!< \brief The border colour of an inline selector
    Ogre::ColourValue inlineselectorBorderHighlight; //!< \brief The border colour of a highlight inline selector
    size_t inlineselectorBorderSize; //!< \brief The border size of an inline selector


    /**
      *
     * Listbox configuration
    *
    */
    Ogre::String listboxButtonPreviousOveredSpriteName;
    Ogre::String listboxButtonPreviousNotOveredSpriteName;
    Ogre::String listboxButtonPreviousInactiveSpriteName;
    Ogre::String listboxButtonPreviousClickedSpriteName;

    Ogre::String listboxButtonNextOveredSpriteName;
    Ogre::String listboxButtonNextNotOveredSpriteName;
    Ogre::String listboxButtonNextInactiveSpriteName;
    Ogre::String listboxButtonNextClickedSpriteName;

    Gradient listboxBackgroundGradientType; //!< \brief The gradient type of an overed combobox. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue listboxBackgroundGradientStart;
    Ogre::ColourValue listboxBackgroundGradientEnd;

    Ogre::ColourValue listboxOveredElement;
    Ogre::ColourValue listboxNotOveredElement;
    Ogre::ColourValue listboxOveredSelectedElement;
    Ogre::ColourValue listboxNotOveredSelectedElement;

    Ogre::ColourValue listboxText; //!< \brief The text colour of combobox elements
    size_t listboxTextSize;

    Ogre::ColourValue listboxBorder; //!< \brief The border colour of a combobox
    Ogre::ColourValue listboxBorderHighlight; //!< \brief The border colour of a highlight combobox
    size_t listboxBorderSize; //!< \brief The border size of a combobox

    /**
      *
     * Scrollbar configuration
    *
    */
    Ogre::String scrollbarCursorNotOveredSpriteName;
    Ogre::String scrollbarCursorOveredSpriteName;
    Ogre::String scrollbarCursorSelectedSpriteName;

    Gradient scrollbarBackgroundGradientType; //!< \brief The gradient type of a scrollbar background. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue scrollbarBackgroundGradientStart;
    Ogre::ColourValue scrollbarBackgroundGradientEnd;

    Gradient scrollbarProgressbarGradientType; //!< \brief The gradient type of a scrollbar bar. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue scrollbarProgressbarGradientStart;
    Ogre::ColourValue scrollbarProgressbarGradientEnd;

    Gradient scrollbarCursorOveredGradientType; //!< \brief The gradient type of a scrollbar overed cursor. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue scrollbarCursorOveredGradientStart;
    Ogre::ColourValue scrollbarCursorOveredGradientEnd;

    Gradient scrollbarCursorNotOveredGradientType; //!< \brief The gradient type of a scrollbar not overed cursor. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue scrollbarCursorNotOveredGradientStart;
    Ogre::ColourValue scrollbarCursorNotOveredGradientEnd;

    Gradient scrollbarCursorSelectedGradientType; //!< \brief The gradient type of a scrollbar selected cursor. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue scrollbarCursorSelectedGradientStart;
    Ogre::ColourValue scrollbarCursorSelectedGradientEnd;

    Ogre::ColourValue scrollbarText; //!< \brief The text colour of a scrollbar.
    size_t scrollbarTextSize;

    Ogre::ColourValue scrollbarBorder; //!< \brief The border colour of a scrollbar.
    Ogre::ColourValue scrollbarBorderHighlight; //!< \brief The border colour of a highlight scrollbar.
    Ogre::ColourValue scrollbarCursorBorder; //!< \brief The border colour of a scrollbar cursor.
    size_t scrollbarBorderSize; //!< \brief The border size of a scrollbar.
    size_t scrollbarCursorBorderSize; //!< \brief The border size of a cursor scrollbar.

    
    /**
      *
     * Textzone configuration
    *
    */
    Gradient textzoneBackgroundOveredGradientType; //!< \brief The gradient type of a overed textzone. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue textzoneBackgroundOveredGradientStart; 
    Ogre::ColourValue textzoneBackgroundOveredGradientEnd;

    Gradient textzoneBackgroundNotOveredGradientType; //!< \brief The gradient type of a not overed textzone. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue textzoneBackgroundNotOveredGradientStart;
    Ogre::ColourValue textzoneBackgroundNotOveredGradientEnd;
    
    Gradient textzoneBackgroundSelectedGradientType; //!< \brief The gradient type of a selected textzone. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue textzoneBackgroundSelectedGradientStart;
    Ogre::ColourValue textzoneBackgroundSelectedGradientEnd;

    Ogre::ColourValue textzoneText; //!< \brief The text colour of a textzone.
    size_t textzoneTextSize;

    Ogre::ColourValue textzoneBorder; //!< \brief The border colour of a textzone.
    Ogre::ColourValue textzoneBorderHighlight; //!< \brief The border colour of a highlight textzone.
    Ogre::ColourValue textzoneBorderSelected; //!< \brief The border colour of a selected textzone.
    size_t textzoneBorderSize; //!< \brief The border size of a textzone.

    
    /**
      *
     * Caption configuration
    *
    */
    Ogre::String captionBackgroundSpriteName;

    Gradient captionBackgroundGradientType; //!< \brief The gradient type of a caption. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue captionBackgroundGradientStart;
    Ogre::ColourValue captionBackgroundGradientEnd;

    Ogre::ColourValue captionText; //!< \brief The text colour of a caption.
    size_t captionTextSize;

    Ogre::ColourValue captionBorder; //!< \brief The border colour of a caption.
    size_t captionBorderSize; //!< \brief The border size of a caption.

    
    /**
      *
     * ProgressBar configuration
    *
    */
    Gradient progressbarBackgroundGradientType; //!< \brief The gradient type of a progressbar background. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue progressbarBackgroundGradientStart;
    Ogre::ColourValue progressbarBackgroundGradientEnd;

    Gradient progressbarLoadingBarGradientType; //!< \brief The gradient type of a progressbar loadingbar background. If you want a single color, set the gradient to whatever type you want and the same colors for gradientStart and gradientEnd.
    Ogre::ColourValue progressbarLoadingBarGradientStart;
    Ogre::ColourValue progressbarLoadingBarGradientEnd;

    Ogre::ColourValue progressbarText; //!< \brief The text colour of a progressbar.
    size_t progressbarTextSize; //!< \brief The text colour of a caption.

    Ogre::ColourValue progressbarBorder; //!< \brief The border colour of a progressbar.
    Ogre::ColourValue progressbarBorderHighlight; //!< \brief The border colour of a highlight progressbar.
    size_t progressbarBorderSize; //!< \brief The border size of a progressbar.
};


} // namespace XE

#endif