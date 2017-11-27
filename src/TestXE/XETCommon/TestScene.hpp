#ifndef __TESTSCENE_HPP__
#define __TESTSCENE_HPP__

#include <XEngine/Scene.hpp>

namespace XET {

	class TestScene : public XE::Scene
	{

	public:
		TestScene(XE::XEngine& engine);

		virtual bool createEntityType(entityx::Entity entity, void* entityData) override;

		virtual void update(float deltaTime) override;

		virtual void loadRendererResources() override;

	private:
		XE::XEngine& m_engine;
	};

} // namespace XET

#endif // __SCENE_HPP__