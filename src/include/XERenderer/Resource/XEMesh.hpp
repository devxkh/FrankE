#pragma once

#include <Ogre/OgreMain/include/OgreMesh2.h>
#include <string>

namespace gltf {

	struct Asset;
}

namespace Ogre {

	class SceneManager;
	class HlmsPbsDatablock;
//	class Mesh;
//	class SharedPtr;

//	typedef SharedPtr<Mesh> MeshPtr;

}

namespace XE
{
	class GraphicsManager;

	class XEMesh {
	public:
		XEMesh();

		void buildMesh(const gltf::Asset& asset, const std::string& meshName, GraphicsManager& gMgr, Ogre::SceneManager* sceneMgr);

		Ogre::MeshPtr m_ogreMesh;
		Ogre::HlmsPbsDatablock *m_datablock;
	};

}