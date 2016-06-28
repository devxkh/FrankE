#pragma once

#include <XEDAL/IDAL.hpp>

namespace XE
{
	class XEngine;
}

namespace XET {
	class TestDAL : public XE::IDAL
	{
	public:

		TestDAL(XE::XEngine& engine);
		~TestDAL();

		const void* getState(const char* name, int namelen) override;
		void getSceneNodes(XE::Scene& scene, XE::Uint16 sceneID, XE::sceneNodes_callback xCallback) override;
		char*  getScene(XE::Uint16 id) override;
		char*  getEntity(XE::Uint16 id) override;
	};

} //NS XET
