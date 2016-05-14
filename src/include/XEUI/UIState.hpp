#ifndef UISTATE_HPP
#define UISTATE_HPP

#include <XESystem/SystemConfig.hpp>

namespace XE {
	
	class UIState
	{
	public:
		
		UIState( const Uint16& id, bool replace = true ) : m_replacing( replace ), mId( id ) {}
		
		virtual  ~UIState() {}
		
		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual void update(float delta) = 0;
		virtual void draw() = 0;


		virtual void create(const char* fbdata) = 0;
		virtual void reload(const char* fbdata) = 0;

		bool isReplacing()
		{
			return m_replacing;
		}
			
		Uint16& getID() { return mId; }

	protected:

		Uint16 mId;

		bool m_replacing;
	};

} // namespace XE

#endif // UISTATE_HPP
