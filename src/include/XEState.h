#ifndef XESTATE_HPP
#define XESTATE_HPP

#include <memory>

namespace XE
{
	class XEngine;

	class XEState
	{
	public:
		XEState(XEngine& engine, bool replace = true)
			: m_engine(engine),
			m_replacing(replace),
			m_breaked(false)
		{

		}

		virtual ~XEState() {};

		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual void update(float deltaTime) = 0;
		virtual void draw() = 0;

		std::unique_ptr<XEState> next()
		{
			return std::move(m_next);
		}

		bool isReplacing()
		{
			return m_replacing;
		}

		inline XEngine& getEngine() { return m_engine; }

		std::unique_ptr<XEState> m_next;

	protected:

		XEngine& m_engine;
		bool m_replacing;
		bool m_breaked; //State sleeping

	};

} // namespace XE

#endif // XESTATE_HPP
