//#ifndef XEUIMANAGER_H
//#define XEUIMANAGER_H
//
//#include <Ogre/OgreMain/include/OgreVector2.h>
////#include <Ogre/OgreMain/include/OgreFrameListener.h>
////#include <XEUI/Graphics/Gorilla.h>
////#include <XERenderer/GUI/ScreenRenderable.hpp>
////#include <XERenderer/GUI/Layer.hpp>
////#include <XERenderer/GUI/Screen.h>
//
//#include <XEUI/Export.hpp>
//#include <XEUI/Desktop.hpp>
//
////#include <XEUI/PanelColors.h> //todo 
//
//#include <map>
//#include <vector>
//
//
//namespace XE {
//
////	class UIPanel;
////	class Navigation;
//	class WScreenRenderable;
////	class WScreen;
////	class WLayer;
////	class GraphicsManager;
//
////	struct ElementStyle;
//	
////	enum StyleType;
//
//	/** \brief Internal use only. Used to keep track of all screens's layers
//	//*/
//	//typedef struct XEUIScreenRenderable XEUIScreenRenderable;
//
//	///** \brief Internal use only. Used to keep track of all screenRenderable's layers
//	//*/
//	//typedef struct XEUIScreen XEUIScreen;
//
//// TODO : Screens methods : implements something more ?
//
///*! class. XEUI
//    desc.
//        The main object to instanciate XEUI.
//*/
//class XEUI_API UIManager //: public Ogre::FrameListener
//{
//	typedef std::size_t ElementID; //!< Element ID type.
//
//	typedef std::vector<Desktop::Ptr> DesktopList;
//
//public:
//    /** \brief The PanelColors gave as argument will automatically be deleted in XEUI destructor, or
//    in the setPanelColors() method
//    */
//	UIManager(); //PanelColors*);
//    
//    ~UIManager();
//
//	void destroyStyles();
//
//    /** \brief /!\ Be careful when using this. Return the main OGRE_G object.
//    */
////    Silverback* getSilverback();
//
//    // ScreenRenderables methods (2D Screens rendered in 3D)
//
//	//WLayer* getLayer(const Ogre::String& screenRenderableName,
//	//	const Ogre::String& layerName);
//
// //   WLayer* getLayer(WScreenRenderable* screenRenderable,
//	//	const Ogre::String& layerName);
//
// //   WLayer* createLayer(WScreenRenderable* screenRenderable,
//	//	const Ogre::String& layerName);
//
//	//WLayer* createLayer(const Ogre::String& screenRenderableName,
//	//	const Ogre::String& layerName);
// //   
//	//WScreenRenderable* getScreenRenderable(const Ogre::String& name);
// //   
// //   WScreenRenderable* createScreenRenderable(const Ogre::Vector2& pos, 
//	//										const Ogre::String& atlasName,
//	//										const Ogre::String& name, 
//	//										Ogre::ObjectMemoryManager* objManager);
//
// //   // Screens methods (2D screen)
//	//WLayer* getLayerScreen(const Ogre::String& screenName,
//	//	const Ogre::String& layerName);
//
// //   WLayer* getLayerScreen(WScreen* screen,
//	//	const Ogre::String& layerName);
//
//	////Layer* getLayer(Screen* screen, Ogre::String layer);
// ////  	Layer* createLayer(Screen* screen, Ogre::String layer);
//
//	//WLayer* createLayerScreen(WScreen* screen,
//	//	const Ogre::String& layerName);
//
//	//WLayer* createLayerScreen(const Ogre::String& screenName,
//	//	const Ogre::String& layerName);
//
//	//WScreen* createScreen(Ogre::Viewport* vp,
//	//	const Ogre::String& atlasName, const Ogre::String& name);
//
//	//WScreen* getScreen(const Ogre::String& name);
//
//	void addDesktop(Desktop::Ptr desktop);
//	
//	void loadAtlas(const Ogre::String& name);
//
//	void destroyScreenRenderable(const Ogre::String& screenRenderableName);
//
//    void destroyScreenRenderable(WScreenRenderable* screenRenderable);
//
//	//ElementStyle* getStyle(StyleType type) ;
//	//ElementStyle* addStyle(StyleType type, ElementStyle* elementStyle);
//
//	/** \brief Give coordinates of the external mouse to all active Panels
//    */
//	bool injectMouseMoved(const Ogre::Real& x, const Ogre::Real& y, const Ogre::uint16& grp = 0);
//
//	bool pointSelectStart(Ogre::Vector2 point);
//	bool pointSelectEnd(Ogre::Vector2 point);
//
//	void selectOveredItem();
//	bool makeNextItemOver();
//	bool makePrevItemOver();
//
//	void update(const Ogre::Real& timeElapsed);
//
//
//	static ElementID GetGUID();
//
//protected:
//	Ogre::String mCurrentPanelName;
//
// //   Silverback* mSilverback;
//
//	//DesktopList m_DesktopList;
//	//std::map<Ogre::String, WScreenRenderable*> m_screenRenderables;
//	//std::map<Ogre::String, WScreen*> m_screens;
//	//Ogre::map<StyleType, ElementStyle*>::type mStyles;
//	
//	static ElementID m_last_guid;
//
//	//bool hasAtlas(const Ogre::String& name);
//};
//
//
//
//} //namespace XE
//
//#endif//XEUIMANAGER_H