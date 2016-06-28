#include <XEngine.hpp>


class TestScene : public XE::Scene
{

public:

	TestScene( XE::XEngine& engine)
		: XE::Scene(engine, engine.getDAL(), engine.getGraphicsManager())
		, m_engine(engine)
	{

	}

	void create(XE::Uint16 sceneID, char* fbData = nullptr)
	{
		XE::Scene::create(sceneID, fbData);

	
	}

	void update(float deltaTime)
	{
		XE::Scene::update(deltaTime);
		//Scene::getSystems().update<XE::ControllerSystem>(deltaTime);
		//Scene::getSystems().update<XE::PhysicsSystem>(deltaTime);
	}

private :
	XE::XEngine& m_engine;

};