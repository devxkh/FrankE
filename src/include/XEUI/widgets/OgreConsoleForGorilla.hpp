#ifndef _OGRECONSOLE_HPP
#define _OGRECONSOLE_HPP

/* Description:   This is a port of the OgreConsole code presented by PixL in the Ogre Forums then later added
   to the Ogre Wiki[1].
   This is a straight port replacing all the Overlay code with Gorilla code, some changes have
   been added but they are minor and do not add to the actual functionality of the class.
  
  Port Author: Betajaen.
     
  References: [1] http://www.ogre3d.org/tikiwiki/OgreConsole&structure=Cookbook   
*/

#include <Ogre/OgreMain/include/Ogre.h>
//#include <sfml/Window/Keyboard.hpp>
#include <SDL.h>
#include <XEUI/Widget.hpp>
#include <XERenderer/GUI/WRectangle.hpp>
#include <XERenderer/GUI/WMarkup.hpp>
#include <XERenderer/GUI/WCaption.hpp>

#include <XEUI/Box.hpp>

typedef void (*OgreConsoleFunctionPtr)(Ogre::StringVector&);

namespace XE {

class OgreConsole : public Widget, Ogre::LogListener
{
public:

	typedef std::shared_ptr<OgreConsole> Ptr; //!< Shared pointer.
	typedef std::shared_ptr<const OgreConsole> PtrConst; //!< Shared pointer.

	~OgreConsole();

	static Ptr Create(WLayer& parentLayer, Uint16 fontId = 14);

	virtual const std::string& GetName() const override;

   void SetStyle(const char* consoleElement, const char* consoleStyle);

    void   shutdown();
    
    void   setVisible(bool mIsVisible);
    bool   isVisible(){return mIsVisible;}
    
    void   print(const Ogre::String &text);
	
	void SetPrompt(Ogre::String& prompt);

	bool update();
   
    void addCommand(const Ogre::String &command, OgreConsoleFunctionPtr);
    void removeCommand(const Ogre::String &command);

    //log
#if OGRE_VERSION_MINOR < 8 && OGRE_VERSION_MAJOR < 2
    void messageLogged( const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName );
#else
    // "bool& skip" added in Ogre 1.8
    void messageLogged( const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool &skip );
#endif
protected:
	OgreConsole( WLayer& parentLayer, Uint16 fontId);


	void draw() override;
	sf::Vector2f CalculateRequisition();
	//virtual void HandleRequisitionChange() override;
	//virtual void HandleSizeChange() override;

	virtual void HandleEvent(const SDL_Event& event);

	void _actualize();

 private:

	 void onTextEntered(const  unsigned char  &text);
	 void onKeyPressed(const SDL_KeyboardEvent &arg);

    
    void  updateConsole();
    void  updatePrompt();
    
	WLayer&      m_layer;
	WRectangle  m_rectanglebg;
	WMarkup  m_consoleText;
	WCaption  m_promptText;
	sf::Uint16 m_lineheight;

	bool			mActive;
	bool            mIsVisible;
    bool            mIsInitialised;

    bool                 mUpdateConsole;
    bool                 mUpdatePrompt;

    unsigned int         mStartline;
    std::list<Ogre::String>      lines;
    Ogre::String            prompt;
    std::map<Ogre::String, OgreConsoleFunctionPtr>  commands;
	
 
};

} // ns XE


#endif // _OGRECONSOLE_HPP

