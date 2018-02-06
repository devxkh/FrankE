#include <XERenderer/Compositor/Compositor.hpp>

#include <Ogre/OgreMain/include/OgreMaterialManager.h>
#include <Ogre/OgreMain/include/OgreMaterial.h>
#include <Ogre/OgreMain/include/OgreTechnique.h>
#include <Ogre/OgreMain/include/OgreRoot.h>
#include <Ogre/OgreMain/include/OgreRenderWindow.h>

#include "Compositor/OgreCompositorManager2.h"
#include "Compositor/OgreCompositorWorkspace.h"
#include "Compositor/OgreCompositorWorkspaceDef.h"
#include "Compositor/OgreCompositorNode.h"
#include "Compositor/OgreCompositorNodeDef.h"

#include "Compositor/Pass/PassClear/OgreCompositorPassClearDef.h"
#include "Compositor/Pass/PassQuad/OgreCompositorPassQuadDef.h"

#include <XERenderer/CameraRenderable.hpp>
#include <XERenderer/GraphicsManager.hpp>
#include <XERenderer/OgreWorkspace.hpp>

namespace XE {

	XECompositor::XECompositor(GraphicsManager &graphicsMgr, CameraRenderable& cameraRenderable)
		: m_graphicsMgr(graphicsMgr)
		, m_cameraRenderable(cameraRenderable)
		, _t_OgreWorkspace(nullptr)
	{

	}

	//-----------------------------------------------------------------------------------
	void XECompositor::setSkyColour(const Ogre::ColourValue &colour, float multiplier)
	{
		/*Ogre::CompositorNode *node = workspace->findNode( "HdrRenderingNode" );

		if( !node )
		{
		OGRE_EXCEPT( Ogre::Exception::ERR_INVALIDPARAMS,
		"No node 'HdrRenderingNode' in provided workspace ",
		"HdrUtils::setSkyColour" );
		}

		const Ogre::CompositorPassVec passes = node->_getPasses();

		assert( passes.size() >= 1 );
		Ogre::CompositorPass *pass = passes[0];

		assert( pass->getType() == Ogre::PASS_CLEAR &&
		dynamic_cast<Ogre::CompositorPassClear*>(pass) );

		Ogre::CompositorPassClear *passClear = static_cast<Ogre::CompositorPassClear*>( pass );*/
		Ogre::CompositorManager2 *compositorManager = Ogre::Root::getSingleton().getCompositorManager2();
		Ogre::CompositorNodeDef *nodeDef =
			compositorManager->getNodeDefinitionNonConst("HdrRenderingNode");

		assert(nodeDef->getNumTargetPasses() >= 1);

		Ogre::CompositorTargetDef *targetDef = nodeDef->getTargetPass(0);
		const Ogre::CompositorPassDefVec &passDefs = targetDef->getCompositorPasses();

		assert(passDefs.size() >= 1);
		Ogre::CompositorPassDef *passDef = passDefs[0];

		assert(passDef->getType() == Ogre::PASS_CLEAR &&
			dynamic_cast<Ogre::CompositorPassClearDef*>(passDef));

		Ogre::CompositorPassClearDef *clearDef = static_cast<Ogre::CompositorPassClearDef*>(passDef);
		clearDef->mColourValue = colour * multiplier;
	}

	void XECompositor::setExposure(float exposure, float minAutoExposure, float maxAutoExposure)
	{
		assert(minAutoExposure <= maxAutoExposure);

		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().load(
			"HDR/DownScale03_SumLumEnd",
			Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME).
			staticCast<Ogre::Material>();

		Ogre::Pass *pass = material->getTechnique(0)->getPass(0);
		Ogre::GpuProgramParametersSharedPtr psParams = pass->getFragmentProgramParameters();

		const Ogre::Vector3 exposureParams(1024.0f * expf(exposure - 2.0f),
			7.5f - maxAutoExposure,
			7.5f - minAutoExposure);

		psParams = pass->getFragmentProgramParameters();
		psParams->setNamedConstant("exposure", exposureParams);
	}
	//-----------------------------------------------------------------------------------
	void XECompositor::setBloomThreshold(float minThreshold, float fullColourThreshold)
	{
	//	assert(minThreshold < fullColourThreshold);

		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().load(
			"HDR/BrightPass_Start",
			Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME).
			staticCast<Ogre::Material>();

		Ogre::Pass *pass = material->getTechnique(0)->getPass(0);

		Ogre::GpuProgramParametersSharedPtr psParams = pass->getFragmentProgramParameters();
		psParams->setNamedConstant("brightThreshold",
			Ogre::Vector4(
				minThreshold,
				1.0f / (fullColourThreshold - minThreshold),
				0, 0));
	}

	void XECompositor::setup() {

		Ogre::Root *root = m_graphicsMgr.getRoot();
		Ogre::CompositorManager2 *compositorManager = root->getCompositorManager2();

		Ogre::SceneManager *sceneManager = _t_OgreWorkspace->_t_sceneMgr;
		Ogre::RenderWindow *renderWindow = m_graphicsMgr._t_getRenderWindow(0);
		Ogre::Camera *camera = m_cameraRenderable._t_OgreCameraPtr;
		//m_workspace = compositorManager->addWorkspace(sceneManager,
		//	renderWindow,
		//	camera,
		//	workspaceName, true,1);

		//workspace->setListener( &mWorkspaceListener );


		//HDR workspace
		Ogre::RenderSystem *renderSystem = root->getRenderSystem();

		const Ogre::RenderSystemCapabilities *caps = renderSystem->getCapabilities();

		Ogre::String compositorName = "HdrWorkspace";
		if (renderWindow->getFSAA() > 1u && caps->hasCapability(Ogre::RSC_EXPLICIT_FSAA_RESOLVE))
			compositorName = "HdrWorkspaceMsaa";

		compositorManager->addWorkspace(sceneManager, renderWindow, camera, compositorName, true, 1);


		setSkyColour(m_CompositorProperties.skyColour, 1.0f);


		setExposure(0.0f, 0.0f, 2.1f);
		//setExposure(preset.exposure, preset.minAutoExposure, preset.maxAutoExposure);
		setBloomThreshold(Ogre::max(m_CompositorProperties.bloomThreshold - 2.0f, 0.0f), Ogre::max(m_CompositorProperties.bloomThreshold, 0.01f));

	
		setAmbientLight(m_CompositorProperties.ambLowerHemisphere, m_CompositorProperties.ambUpperHemisphere, sceneManager->getAmbientLightHemisphereDir(), m_CompositorProperties.envmapScale);

	}

	void XECompositor::setAmbientLight(const Ogre::ColourValue& upperHemisphere, const Ogre::ColourValue& lowerHemisphere, const Ogre::Vector3 &hemisphereDir, Ogre::Real envmapScale)
	{
		_t_OgreWorkspace->_t_sceneMgr->setAmbientLight(
			lowerHemisphere,
			upperHemisphere,
			hemisphereDir,
			envmapScale);

	}


}