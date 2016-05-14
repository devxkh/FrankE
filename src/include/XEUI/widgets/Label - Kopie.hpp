#ifndef Gui3DCaption_H
#define Gui3DCaption_H



#include <vector>

#include <Ogre/OgreMain/include/OgreVector2.h>
#include <sfml/System/String.hpp>
#include <XERenderer/GUI/WCaption.hpp>
#include <XEUI/Widget.hpp>

namespace XE {

	class WLayer;
	class UIManager;

	/*! class. Caption
		desc.
		A simple Caption
		*/
	class Label : public Widget//, public RectangleDesigned, public Captioned
	{
	public:
		Label(UIManager* uiManager, WLayer* parentLayer, const sf::String& text);

		~Label();

		typedef std::shared_ptr<Label> Ptr; //!< Shared pointer.
		typedef std::shared_ptr<const Label> PtrConst; //!< Shared pointer.

		/** Create caption.
		* @param text Text.
		* @return Label.
		*/
		static Ptr Create(UIManager* uiManager, WLayer* parentLayer = nullptr, const sf::String& text = L"");

		/** Set text.
		* @param text New text.
		*/
		void SetText(const sf::String& text);

		void SetStyle(const char* labelElement, const  char* labelStyle);

		void pointSelectStart(const Ogre::Vector2& point);
		void pointSelectEnd(const Ogre::Vector2& point);
		void parentResized();

		/** Get text.
		* @return Text.
		*/
		//const sf::String& GetText() const;

		//void injectKeyPressed(const OIS::KeyEvent& evt);
		//
		//void injectKeyReleased(const OIS::KeyEvent& evt);

		//void injectKeys(std::vector<OIS::KeyCode>& keys);

		//void injectMousePressed(const OIS::MouseEvent& evt, 
		//                        OIS::MouseButtonID id);

		//void injectMouseReleased(const OIS::MouseEvent& evt, 
		//                         OIS::MouseButtonID id);
		//void pointSelectStart(const Math::Vector2f& point){};
		//void pointSelectEnd(const Math::Vector2f& point){};

		bool isOver(const Ogre::Vector2& pos);

		void setSize(int width, int height);

		void setPosition(int left, int top);

		Ogre::Vector3& getPosition();

		void injectTimeAndMousePosition(double time, const Ogre::Vector2& pos);

		void highlight();

		void text(sf::String s);

		sf::String text();

		/** \brief Set the background to a sprite from the texture atlas.
			note.
			To remove the images pass on "none" or a empty string to the sprite name.
			*/
		// void setBackgroundImage(const SYS::String& backgroundSpriteName);

	protected:
		//  SYS::String mBackgroundSpriteName;
		WCaption m_Label;

		void _actualize();
	};

} // namespace XE

#endif