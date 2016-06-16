/*
  Description:
   
   This is a port of the OgreConsole code presented by PixL in the Ogre Forums then later added
   to the Ogre Wiki.
   
   This is a straight port replacing all the Overlay code with Gorilla code, some changes have
   been added but they are minor and do not add to the actual functionality of the class.
   
   
*/

#include <XEUI/widgets/OgreConsoleForGorilla.hpp>
#include <XEUI/UIPanel.hpp>
#include <XEUI/Panel2D.hpp>
#include <XEUI/UIManager.hpp>

#include <XEUI/DAL/FB_UI_StateData_generated.h> //need to include ... else link error

namespace XE {

//#define CONSOLE_FONT_INDEX 9
//
#define CONSOLE_LINE_LENGTH 50	//todo from style
#define CONSOLE_LINE_COUNT 11	//todo from style

static const unsigned char legalchars[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890+!\"'#%&/()=?[]\\*-_.:,; ";

OgreConsole::OgreConsole( WLayer& parentLayer)
	: 
		mIsVisible(true), 
		mIsInitialised(false),
		mUpdateConsole(false),
		mUpdatePrompt(false),
		mStartline(0),
		mActive(false)
		,m_layer(parentLayer)
		, m_rectanglebg(parentLayer, 0, 0, 0, 0)
		 , m_consoleText(parentLayer)
		 , m_promptText(parentLayer)
		 , m_lineheight(15)
{
	Ogre::LogManager::getSingleton().getDefaultLog()->addListener(this);

	//todo from style
	SetStyle(nullptr,nullptr);
	Widget::setPosition(sf::Vector2f(300,200));
	m_consoleText.setSize(200,185);



	m_promptText.setText("> _");
}
 

OgreConsole::Ptr OgreConsole::Create(WLayer& parentLayer) {
	Ptr console(new OgreConsole(parentLayer));
	//console->RequestResize();
	return console;
}

OgreConsole::~OgreConsole()
{
 if (mIsInitialised)
  shutdown();
}

//
//void OgreConsole::HandleRequisitionChange() {
//
//	static auto calculate_y_requisition = false;
//
//	if (!calculate_y_requisition) {
//		calculate_y_requisition = true;
//		RequestResize();
//	}
//	else {
//		calculate_y_requisition = false;
//	}
//}
//
//void OgreConsole::HandleSizeChange() {
//	
//	static auto calculate_y_requisition = false;
//
//	if (!calculate_y_requisition) {
//		calculate_y_requisition = true;
//		RequestResize();
//	}
//	else {
//		calculate_y_requisition = false;
//	}
//}

//std::unique_ptr<RenderQueue>
void OgreConsole::draw() {

	/*sf::FloatRect req(GetAllocation());
	sf::FloatRect parentAllocation(GetParent()->GetAllocation());*/

	m_rectanglebg.setPosition(Widget::getPosition()); // sf::Vector2f(parentAllocation.left + req.left, parentAllocation.top + req.top));
	m_rectanglebg.setSize(sf::Vector2f(size.x, size.y));
	
	m_promptText.setPosition(sf::Vector2f(Widget::getPosition().x, Widget::getPosition().y + (size.y - m_lineheight)));
	m_consoleText.setPosition(Widget::getPosition());
	//return Context::Get().GetEngine().CreateLabelDrawable( std::dynamic_pointer_cast<const Label>( shared_from_this() ) );
}

sf::Vector2f OgreConsole::CalculateRequisition() {

	return m_rectanglebg.getSize(); // metrics;
}

const std::string& OgreConsole::GetName() const {
	static const std::string name("Label");
	return name;
}

void OgreConsole::SetStyle(const char* consoleElement, const char* consoleStyle)
{
	//load style from file

	if (consoleElement && consoleStyle)
	{
		auto ele = flatbuffers::GetRoot<XFB_UI::Console>(consoleElement);
		auto style = flatbuffers::GetRoot<XFB_UI::Style>(consoleStyle);
		//set widget size and position
		//setPosition(ele->base()->positon()->x(), ele->base()->positon()->y());
		//setSize(style->width(), style->height());

		//set renderered rectangle
		m_rectanglebg.setSize(sf::Vector2f(ele->base()->width(), ele->base()->height()));
		m_rectanglebg.setPosition(sf::Vector2f(ele->base()->positon()->x(), ele->base()->positon()->y()));

		m_rectanglebg.setBackground(ele->base()->style()->normalState()->bgColour());
	}
	else
	{
		m_rectanglebg.setBackground(Ogre::ColourValue::Black); //default test
	}
}

void OgreConsole::SetPrompt(Ogre::String& prompt)
{

	print("%3> " + prompt + "%R");


	//split the parameter list
	Ogre::StringVector params = Ogre::StringUtil::split(prompt, " ");

	if (params.size())
	{
		std::map<Ogre::String, OgreConsoleFunctionPtr>::iterator i;
		for (i = commands.begin(); i != commands.end(); i++){
			if ((*i).first == params[0]){
				if ((*i).second)
					(*i).second(params);
				break;
			}
		}
		prompt.clear();
		mUpdateConsole = true;
		mUpdatePrompt = true;
	}
}

void OgreConsole::shutdown()
{
 if(!mIsInitialised)
    return;
 
 mIsInitialised = false;
 
 //Ogre::Root::getSingletonPtr()->removeFrameListener(this);
 Ogre::LogManager::getSingleton().getDefaultLog()->removeListener(this);
 
 //todoXXX mScreen->destroy(mLayer);
 
}

void OgreConsole::HandleEvent(const SDL_Event& event)
{
	//Widget::HandleKeyEvent(event);

	//if (event.type == SDL_KEYDOWN) {
	//	onKeyPressed(event.key);
	//}
	//else if (event.type == SDL_KEYUP) {
	//	onTextEntered(event.key.keysym.scancode);
	//}
}

void OgreConsole::onTextEntered(const unsigned char &text)
{
	if (!mActive) return;

	for (unsigned int c = 0; c<sizeof(legalchars); c++){
		if (legalchars[c] == text){
			prompt += text;
			break;
		}
	}
	mUpdatePrompt = true;
}

void OgreConsole::onKeyPressed(const SDL_KeyboardEvent &arg)
{
	if (!mIsVisible) return;

	if (arg.keysym.scancode == SDL_SCANCODE_KP_ENTER) // || arg == sf::Keyboard::Key::)
	{
		if (!mActive)
		{
			mActive = true;
			return;
		}

		print("%3> " + prompt + "%R");

		//split the parameter list
		Ogre::StringVector params = Ogre::StringUtil::split(prompt, " ");

		if (params.size())
		{
			std::map<Ogre::String, OgreConsoleFunctionPtr>::iterator i;
			for (i = commands.begin(); i != commands.end(); i++){
				if ((*i).first == params[0]){
					if ((*i).second)
						(*i).second(params);
					break;
				}
			}
			prompt.clear();
			mUpdateConsole = true;
			mUpdatePrompt = true;
		}

		mActive = false;
	}

	if (!mActive) return;

	//if (arg == sf::Keyboard::Key::BackSpace)
	//{
	//	if (prompt.size())
	//	{
	//		prompt.erase(prompt.end() - 1); //=prompt.substr(0,prompt.length()-1);
	//		mUpdatePrompt = true;
	//	}
	//}

	//else if (arg == sf::Keyboard::Key::PageUp)
	//{
	//	if (mStartline > 0)
	//		mStartline--;
	//	mUpdateConsole = true;
	//}

	//else if (arg == sf::Keyboard::Key::PageDown)
	//{
	//	if (mStartline < lines.size())
	//		mStartline++;
	//	mUpdateConsole = true;
	//}
}

bool OgreConsole::update()
{
   if(mUpdateConsole)
    updateConsole();
    
   if (mUpdatePrompt)
    updatePrompt();
   
   return true;
}

void OgreConsole::updateConsole()
{
 
 mUpdateConsole = false;
 
 std::stringstream text;
 std::list<Ogre::String>::iterator i,start,end;

 //make sure is in range
 if(mStartline>lines.size())
  mStartline=lines.size();

 int lcount=0;
 start=lines.begin();
 for(unsigned int c=0;c<mStartline;c++)
    start++;
 end=start;
 for(unsigned int c=0;c<CONSOLE_LINE_COUNT;c++){
    if(end==lines.end())
       break;
    end++;
 }

 for(i=start;i!=end;i++)
 {
  lcount++;
  text << (*i) << "\n";
 }


 m_consoleText.SetText(text.str());


 // Move prompt downwards.
//	mPromptText->top(mPromptText->top() + (lcount * mGlyphData->mLineHeight));

 // Change background height so it covers the text and prompt
 //todoXXX mDecoration->height(((lcount+1) * mGlyphData->mLineHeight) + 4);

 
}

void OgreConsole::updatePrompt()
{
 mUpdatePrompt = false;
 std::stringstream text;
 text << "> " << prompt << "_";
 m_promptText.setText(text.str());
}

void OgreConsole::print(const Ogre::String &text)
{
   //subdivide it into lines
   const char *str=text.c_str();
   int len=text.length();
   Ogre::String line;
   for(int c=0;c<len;c++){
      if(str[c]=='\n'||line.length()>=CONSOLE_LINE_LENGTH){
         lines.push_back(line);
         line="";
      }
      if(str[c]!='\n')
         line+=str[c];
   }
   if(line.length())
      lines.push_back(line);
   if(lines.size()>CONSOLE_LINE_COUNT)
      mStartline=lines.size()-CONSOLE_LINE_COUNT;
   else
      mStartline=0;
   mUpdateConsole=true;
}

//bool OgreConsole::frameEnded(const Ogre::FrameEvent &evt)
//{
// return true;
//}

void OgreConsole::setVisible(bool isVisible)
{
 mIsVisible = isVisible;
 //todoXXX  mLayer->setVisible(mIsVisible);
}

void OgreConsole::addCommand(const Ogre::String &command, OgreConsoleFunctionPtr func)
{
 commands[command]=func;
}

void OgreConsole::removeCommand(const Ogre::String &command)
{
 commands.erase(commands.find(command));
}

#if OGRE_VERSION_MINOR < 8 && OGRE_VERSION_MAJOR < 2
void OgreConsole::messageLogged( const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName )
#else
    // "bool& skip" added in Ogre 1.8
void OgreConsole::messageLogged( const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool &skip )
#endif
{
 print(message);
}


} // ns XE