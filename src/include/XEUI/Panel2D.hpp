//
//#ifndef XEUIPanel2D_H
//#define XEUIPanel2D_H
//
//
////-------------------------------------
////			2D  direct on Screen !!
////------------------------------------
//
//#include <vector>
////
////#include "OGRE_G.h"
////
////#include "XEUI.h"
//#include <XEUI/UIPanel.hpp>
//#include <XEUI/Desktop.hpp>
//
////namespace XFB_UI
////{
////	class Panel2D;
////	class Style;
////}
//
//namespace XE {
//
//	class WRectangle;
//	class WCaption;
//	class ListBox;
//	class PanelElementCallback;
////
//class Panel2D : public UIPanel
//{
//public:
//	typedef std::shared_ptr<Panel2D> Ptr; //!< Shared pointer.
//	typedef std::shared_ptr<const Panel2D> PtrConst; //!< Shared pointer.
//
//
//
//	~Panel2D();
//
//	/** Create caption.
//	* @param text Text.
//	* @return Label.
//	*/
//
//
//
//    /** \brief Give coordinates of the external mouse to this screen
//    */
//    bool injectMouseMoved(const  Ogre::Real& x, const  Ogre::Real& y);
//	bool injectMouseMoved(const Ogre::Ray& ray)  { return true; }
//    
//
//	//void setParent( PanelElementCallback* pElementCallback ){ mParent = pElementCallback;	}
//
//	/** \brief Change the position of this Panel2D
//    */
////	void setStyle(ElementStyle* style, bool  resizedOnly = false );
//
////	void windowResized(Ogre::RenderWindow* rw);
//	void parentResized();
//
//	 //void update(const Ogre::Real& timeElapsed);
//
//	void HandleAlignmentChange(const sf::Vector2f& alignment);
//
//	 void setPosition(const Ogre::Vector3& pos);
//
//	 void pointSelectStart(const Ogre::Vector2& point);
//	 void pointSelectEnd(const Ogre::Vector2& point);
//	 bool isOver(const Ogre::Vector2& pos);
//
//	 //void setSize(int width, int height);
//
//	 void setPosition(int left, int top);
//
//	 Ogre::Vector3& getPosition();
//
//	 void injectTimeAndMousePosition(double time, const Ogre::Vector2& pos);
//
//	 void highlight();
//	 void _actualize();
//
//protected:
//	Panel2D(UIManager& gui, Desktop::Ptr desktop);
//
//	//PanelElementCallback* mParent;
//	WRectangle* m_BGHead;
//	WCaption* m_CaptionHead;
//
//	Ogre::Real mOldScreenHeight;
//	Ogre::Real mOldScreenWidth; 
//
//private:
//	//ElementStyle* mStyle;
//};
//
//
//} //namespace XE
//
//#endif // Panel2D