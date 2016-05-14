//#ifndef Gui3DPanel_H
//#define Gui3DPanel_H
//
//
//
////#include <XEGraphics/Gorilla.h>
//
////#include <XEUI/UIManager.hpp>
//#include <XEUI/UIPanel.hpp>
//
//namespace XE {
//
//	class XEUI;
//	class WScreenRenderable;
////
//class Panel3D : public UIPanel
//{
//public:
//    Panel3D(UIManager* gui, 
//		Ogre::SceneManager* sceneMgr,
//		 Ogre::ObjectMemoryManager* objManager,
//			 Ogre::Real distanceFromPanelToInteractWith,
//			const Ogre::String& atlasName,
//			const Ogre::String& name,
//			const Ogre::uint16& grp = 0 );
//
//    ~Panel3D();
//    
//    /** \brief Set the distance the user can interact with the panel
//    */
//    void setDistanceFromPanelToInteractWith( Ogre::Real distanceFromPanelToInteractWith);
//
//    /** \brief Send a ray from a part of the screen to this panel to
//    actualize the internal mouse position on the panel.
//    Return if the ray intersects with the panel. 
//    */
//    bool injectMouseMoved(const Ogre::Ray& ray);
//	bool injectMouseMoved(const  Ogre::Real& x, const  Ogre::Real& y) { return true; }
//
//	void windowResized(Ogre::RenderWindow* rw);
//
//	Ogre::SceneNode* mNode; //!< \brief The panel node
//	Ogre::SceneNode* mPanelCameraNode; //!< \brief The node the camera should be attached to and look at mNode for this panel
//
//protected:
//     WScreenRenderable* mScreenRenderable;
//     Ogre::Real mDistanceFromPanelToInteractWith; //!< \brief The distance the origin of a ray can be to interact with the panel.
//};
//
//
//} // namespace XE
//
//#endif