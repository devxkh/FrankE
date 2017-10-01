#pragma once

namespace gltf {

	struct Asset;
}

namespace Ogre {
	class SceneManager;
}

namespace XE
{
	class GraphicsManager;

	class XEMesh {
	public:
		void buildMesh(const gltf::Asset& asset, GraphicsManager& gMgr, Ogre::SceneManager* sceneMgr);
	};

}