#pragma once

#include <XEngine.hpp>

namespace XE
{
	class GraphicsManager;
	class XEngine;
}

namespace XET {

	class EditorControllerSystem : public entityx::System < EditorControllerSystem > 
	{
	public:

		EditorControllerSystem(XE::XEngine& engine);

		~EditorControllerSystem();

		void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

		inline XE::XEngine& getEngine() { return m_engine; }

	private:
	
		XE::XEngine& m_engine;
	};

} // namespace XET
