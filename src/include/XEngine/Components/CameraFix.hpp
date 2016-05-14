#ifndef __CAMERAFIX_HPP__
#define __CAMERAFIX_HPP__

#include <sfml/Config.hpp>
#include <XESystem/TransportData.hpp>
//#include <XEDAL/Objects/FBEngineTypes_generated.h>

#include <XERenderer/CameraRenderable.hpp>

namespace entityx { class Entity; }

namespace XE
{
	class BodyComponent;
	class Scene;
	class GraphicsManager;

	struct CameraFixComponent {
	public:
		CameraFixComponent(CameraRenderable& cameraRenderable);


		CameraRenderable& getRenderable() { return _cameraRenderable; }

	private:
		CameraRenderable& _cameraRenderable;
	};
}

#endif