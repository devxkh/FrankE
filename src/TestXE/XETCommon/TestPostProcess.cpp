#include "TestPostProcess.hpp"

#include "OgreSceneManager.h"
#include "OgreItem.h"

#include "OgreMeshManager.h"
#include "OgreMeshManager2.h"
#include "OgreMesh2.h"

#include "OgreCamera.h"
#include "OgreRenderWindow.h"

//#include "OgreHlmsPbsDatablock.h"
#include "OgreHlmsSamplerblock.h"

#include "OgreRoot.h"
#include "OgreHlmsManager.h"
#include "OgreHlmsTextureManager.h"
//#include "OgreHlmsPbs.h"

#include "Compositor/OgreCompositorManager2.h"
#include "Compositor/OgreCompositorWorkspace.h"
#include "Compositor/OgreCompositorWorkspaceDef.h"
#include "Compositor/OgreCompositorNode.h"
#include "Compositor/OgreCompositorNodeDef.h"

#include "Compositor/Pass/PassQuad/OgreCompositorPassQuadDef.h"

#include "OgreTexture.h"
#include "OgreTextureManager.h"
#include "OgreHardwarePixelBuffer.h"


#include <XEngine.hpp>
#include <XERenderer/OgreWorkspace.hpp>


//#include "Compositor/OgreCompositorWorkspace.h"
//#include "Compositor/OgreCompositorNode.h"
#include "Compositor/OgreCompositorNodeDef.h"
//#include "Compositor/Pass/PassClear/OgreCompositorPassClear.h"
#include "Compositor/Pass/PassClear/OgreCompositorPassClearDef.h"


using namespace Ogre;

namespace XET
{
	TestPostProcess::TestPostProcess(XE::XEngine& engine, XE::CameraRenderable& cameraRenderable)
		: m_engine(engine)
		, m_cameraRenderable(cameraRenderable)
	{

		//Billboard texture animation test

		//auto bbs = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createBillboardSet();
		//Ogre::v1::Billboard* sunBillboard = bbs->createBillboard(Ogre::Vector3(0, 0, 0));
		//sunBillboard->setDimensions(25, 25);
		////You need sets Billboard::mDirection to some value other than the default Vector3::ZERO to make BBT_ORIENTED_SELF / BBT_PERPENDICULAR_SELF work.
		//sunBillboard->mDirection = Ogre::Vector3::UNIT_Y;
		//bbs->setBillboardType(Ogre::v1::BillboardType::BBT_ORIENTED_SELF);

		//bbs->setRenderQueueGroup(5);
		//m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->getRenderQueue()->setRenderQueueMode(5, Ogre::RenderQueue::Modes::V1_FAST);

		//Ogre::HlmsManager *hlmsManager = m_GraphicsManager.getRoot()->getHlmsManager();
		//m_datablock = hlmsManager->getDatablock("BillBoardTest");
		//bbs->setDatablock(m_datablock);

		//Ogre::HlmsUnlitDatablock *datablockUnlit = (Ogre::HlmsUnlitDatablock*)m_datablock;

		//Ogre::HlmsSamplerblock samplerblock;
		//samplerblock.setAddressingMode(Ogre::TAM_WRAP);
		//datablockUnlit->setSamplerblock(0, samplerblock);

		//datablockUnlit->setEnableAnimationMatrix(0, true);

		//Ogre::Controller<Ogre::Real>* ret = 0;

		//float speed = 1.0;
		//Ogre::TextureAnimationControllerValue* ctrlVal = 0;

		//if (speed != 0)
		//{
		//	Ogre::SharedPtr< Ogre::ControllerValue<Ogre::Real> > val;
		//	Ogre::SharedPtr< Ogre::ControllerFunction<Ogre::Real> > func;

		//	val.bind(OGRE_NEW Ogre::TextureAnimationControllerValue(datablockUnlit, 0));
		//	ctrlVal = static_cast<Ogre::TextureAnimationControllerValue*>(val.get());

		//	// Create function: use -speed since we're altering texture coords so they have reverse effect
		//	func.bind(OGRE_NEW Ogre::ScaleControllerFunction(-speed, true));
		//	ret = Ogre::ControllerManager::getSingleton().createController(Ogre::ControllerManager::getSingleton().getFrameTimeSource(), val, func);
		//}

		//ctrlVal->tiledAnimation(4, 4);
		////ctrlVal->scrollAnimation(1, 1);
		////	ctrlVal->scrollAnimation(0, 1);
		////	ctrlVal->rotationAnimation(1);
		////	ctrlVal->scaleAnimation(1, 0);


		//_t_OgreEntitySceneNodePtr->attachObject(bbs);
	}

	void TestPostProcess::createCustomTextures()
	{
		TexturePtr tex = TextureManager::getSingleton().createManual(
			"HalftoneVolume",
			"General",
			TEX_TYPE_3D,
			64, 64, 64,
			0,
			PF_L8,
			TU_DYNAMIC_WRITE_ONLY
		);

		if (!tex.isNull())
		{
			v1::HardwarePixelBufferSharedPtr ptr = tex->getBuffer(0, 0);
			ptr->lock(v1::HardwareBuffer::HBL_DISCARD);
			const PixelBox &pb = ptr->getCurrentLock();
			Ogre::uint8 *data = static_cast<Ogre::uint8*>(pb.data);

			size_t height = pb.getHeight();
			size_t width = pb.getWidth();
			size_t depth = pb.getDepth();
			size_t rowPitch = pb.rowPitch;
			size_t slicePitch = pb.slicePitch;

			for (size_t z = 0; z < depth; ++z)
			{
				for (size_t y = 0; y < height; ++y)
				{
					for (size_t x = 0; x < width; ++x)
					{
						float fx = 32 - (float)x + 0.5f;
						float fy = 32 - (float)y + 0.5f;
						float fz = 32 - ((float)z) / 3 + 0.5f;
						float distanceSquare = fx*fx + fy*fy + fz*fz;
						data[slicePitch*z + rowPitch*y + x] = 0x00;
						if (distanceSquare < 1024.0f)
							data[slicePitch*z + rowPitch*y + x] += 0xFF;
					}
				}
			}
			ptr->unlock();
		}
		

		Ogre::RenderWindow *renderWindow = m_engine.getGraphicsManager()._t_getRenderWindow(0);

		TexturePtr tex2 = TextureManager::getSingleton().createManual(
			"DitherTex",
			"General",
			TEX_TYPE_2D,
			renderWindow->getWidth(), renderWindow->getHeight(), 1,
			0,
			PF_L8,
			TU_DYNAMIC_WRITE_ONLY
		);

		v1::HardwarePixelBufferSharedPtr ptr2 = tex2->getBuffer(0, 0);
		ptr2->lock(v1::HardwareBuffer::HBL_DISCARD);
		const PixelBox &pb2 = ptr2->getCurrentLock();
		Ogre::uint8 *data2 = static_cast<Ogre::uint8*>(pb2.data);

		size_t height2 = pb2.getHeight();
		size_t width2 = pb2.getWidth();
		size_t rowPitch2 = pb2.rowPitch;

		for (size_t y = 0; y < height2; ++y)
		{
			for (size_t x = 0; x < width2; ++x)
			{
				data2[rowPitch2*y + x] = Ogre::Math::RangeRandom(64.0, 192);
			}
		}

		ptr2->unlock();
	}
	//-----------------------------------------------------------------------------------
	void TestPostProcess::togglePostprocess(IdString nodeName)
	{
		Root *root = m_engine.getGraphicsManager().getRoot();
		CompositorManager2 *compositorManager = root->getCompositorManager2();

		CompositorWorkspace *workspace = m_workspace;//m_cameraRenderable._t_OgreWorkspace->_t_compositorWorkspace;


		const IdString workspaceName("PostprocessingSampleWorkspace");

		//Disable/Enable the node (it was already instantiated in setupCompositor())
		CompositorNode *node = workspace->findNode(nodeName);
		node->setEnabled(!node->getEnabled());

		//The workspace instance can't return a non-const version of
		//its definition, so we perform the lookup this way.
		CompositorWorkspaceDef *workspaceDef =
			compositorManager->getWorkspaceDefinition(workspaceName);

		//Try both methods alternating them, just for the sake of testing and demonstrating them.
		//The 1st user 5 toggles will use method 1, the next 5 toggles will use method 2, and repeat
		static int g_methodCount = 0;

		if (g_methodCount < 5)
		{
			//-------------------------------------------------------------------------------------------
			//
			//  METHOD 1 (the masochist way, 'cos it's hard, prone to bugs, but very flexible):
			//      When enabling: Interleave the node between the 1st and 2nd node.
			//      When disabling: Manually disconnect the node in the middle, then fix broken
			//      connections.
			//      Normally this method is not recommended, but if you're looking to make a GUI node
			//      editor, the knowledge from this code is very useful.
			//
			//-------------------------------------------------------------------------------------------
			CompositorWorkspaceDef::ChannelRouteList &channelRouteList = workspaceDef->_getChannelRoutes();
			if (node->getEnabled())
			{
				//Enabling
				if (channelRouteList.size() == 1)
				{
					//No compositor node yet activated
					channelRouteList.pop_back();
					workspaceDef->connect("PostprocessingSampleStdRenderer", node->getName());
					workspaceDef->connect(node->getName(), 0, "FinalComposition", 1);
				}
				else
				{
					//There is at least one compositor active already, interleave

					const IdString firstNodeName("PostprocessingSampleStdRenderer");

					//Find the first node "PostprocessingSampleStdRenderer", and put the new compo
					//after that once (theoretically, we could put it anywhere we want in the chain)
					CompositorWorkspaceDef::ChannelRouteList::iterator it = channelRouteList.begin();
					CompositorWorkspaceDef::ChannelRouteList::iterator en = channelRouteList.end();

					CompositorWorkspaceDef::ChannelRoute *firstNodeChannel0 = 0;
					CompositorWorkspaceDef::ChannelRoute *firstNodeChannel1 = 0;

					while (it != en)
					{
						if (it->outNode == firstNodeName)
						{
							if (it->inChannel == 0)
								firstNodeChannel0 = &(*it);
							else
								firstNodeChannel1 = &(*it);
						}
						++it;
					}

					IdString old2ndNode = firstNodeChannel0->inNode; //Will now become the 3rd node

					firstNodeChannel0->inNode = node->getName();
					//firstNodeChannel0->inChannel= 0 //Channel stays the same
					firstNodeChannel1->inNode = node->getName();
					//firstNodeChannel1->inChannel= 1 //Channel stays the same

					workspaceDef->connect(node->getName(), old2ndNode);
				}
			}
			else
			{
				//Disabling
				if (channelRouteList.size() == 3)
				{
					//After disabling us, there will be no more compositors active
					channelRouteList.clear();
					workspaceDef->connect("PostprocessingSampleStdRenderer", 0, "FinalComposition", 1);
				}
				else
				{
					//Find our channel route
					CompositorWorkspaceDef::ChannelRouteList::iterator it = channelRouteList.begin();
					CompositorWorkspaceDef::ChannelRouteList::iterator en = channelRouteList.end();

					IdString currentNode = node->getName();
					IdString prevNode; //We assume all inputs are coming from the same node
					IdString nextNode; //We assume our node doesn't output to more than one node simultaneously

					while (it != en)
					{
						if (it->inNode == currentNode)
						{
							prevNode = it->outNode;
							it = channelRouteList.erase(it);
						}
						else if (it->outNode == currentNode)
						{
							nextNode = it->inNode;
							it = channelRouteList.erase(it);
						}
						else
						{
							++it;
						}
					}

					if (nextNode == "FinalComposition")
						workspaceDef->connect(prevNode, 0, nextNode, 1);
					else
						workspaceDef->connect(prevNode, nextNode);
				}
			}
		}
		else
		{
			//-------------------------------------------------------------------------------------------
			//
			//  METHOD 2 (the easy way):
			//      Reconstruct the whole connection from scratch based on a copy (be it a cloned,
			//      untouched workspace definition, a custom file, or the very own workspace instance)
			//      but leaving the node we're disabling unplugged.
			//      This method is much safer and easier, the **recommended** way for most usage
			//      scenarios involving toggling compositors on and off frequently. With a few tweaks,
			//      it can easily be adapted to complex compositors too.
			//
			//-------------------------------------------------------------------------------------------
			workspaceDef->clearAllInterNodeConnections();

			IdString finalCompositionId = "FinalComposition";
			const CompositorNodeVec &nodes = workspace->getNodeSequence();

			IdString lastInNode;
			CompositorNodeVec::const_iterator it = nodes.begin();
			CompositorNodeVec::const_iterator en = nodes.end();

			while (it != en)
			{
				CompositorNode *outNode = *it;

				if (outNode->getEnabled() && outNode->getName() != finalCompositionId)
				{
					//Look for the next enabled node we can connect to
					CompositorNodeVec::const_iterator it2 = it + 1;
					while (it2 != en && (!(*it2)->getEnabled() || (*it2)->getName() == finalCompositionId))
						++it2;

					if (it2 != en)
					{
						lastInNode = (*it2)->getName();
						workspaceDef->connect(outNode->getName(), lastInNode);
					}

					it = it2 - 1;
				}

				++it;
			}

			if (lastInNode == IdString())
				lastInNode = "PostprocessingSampleStdRenderer";

			workspaceDef->connect(lastInNode, 0, "FinalComposition", 1);

			//Not needed unless we'd called workspaceDef->clearOutputConnections
			//workspaceDef->connectOutput( "FinalComposition", 0 );
		}

		g_methodCount = (g_methodCount + 1) % 10;

		//Now that we're done, tell the instance to update itself.
		workspace->reconnectAllNodes();
	}

	void init(Ogre::uint8 fsaa)
	{
		if (fsaa <= 1)
			return;

		Ogre::String preprocessorDefines = "MSAA_INITIALIZED=1,";

		preprocessorDefines += "MSAA_SUBSAMPLE_WEIGHT=";
		preprocessorDefines += Ogre::StringConverter::toString(1.0f / (float)fsaa);
		preprocessorDefines += ",MSAA_NUM_SUBSAMPLES=";
		preprocessorDefines += Ogre::StringConverter::toString(fsaa);

		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().load(
			"HDR/Resolve_4xFP32_HDR_Box",
			Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME).
			staticCast<Ogre::Material>();

		Ogre::Pass *pass = material->getTechnique(0)->getPass(0);

		Ogre::GpuProgram *shader = 0;
		Ogre::GpuProgramParametersSharedPtr oldParams;

		//Save old manual & auto params
		oldParams = pass->getFragmentProgramParameters();
		//Retrieve the HLSL/GLSL/Metal shader and rebuild it with the right settings.
		shader = pass->getFragmentProgram()->_getBindingDelegate();
		shader->setParameter("preprocessor_defines", preprocessorDefines);
		pass->getFragmentProgram()->reload();
		//Restore manual & auto params to the newly compiled shader
		pass->getFragmentProgramParameters()->copyConstantsFrom(*oldParams);
	}
	//-----------------------------------------------------------------------------------
	void setSkyColour(const Ogre::ColourValue &colour,
		float multiplier)
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
	//-----------------------------------------------------------------------------------
	void setExposure(float exposure, float minAutoExposure, float maxAutoExposure)
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
	void setBloomThreshold(float minThreshold, float fullColourThreshold)
	{
		assert(minThreshold < fullColourThreshold);

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

	void switchPreset(Ogre::SceneManager *sceneManager)
	{
		struct Preset
		{
			const char *name;
			Ogre::ColourValue skyColour;
			Ogre::ColourValue ambUpperHemisphere;
			Ogre::ColourValue ambLowerHemisphere;
			float lightPower[3];
			float exposure;
			float minAutoExposure;
			float maxAutoExposure;
			float bloomThreshold;
			float envmapScale;
		};

		//Our HDR is calibrated to multiply by 1024 (-10 stops)
		//(this is due to limited range in 16-bit float RenderTargets).
		//Direct sunlight on a perpendicular surface is ~100.000 lumens
		//100.000 / 1024 = ~97.0f
		//
		//  1 lux = 1 lumen per square meter.
		//
		// According to http://lumennow.org/lumens-vs-watts/
		//  40-watt incandescent bulb = 450 lumens
		//  60-watt incandescent bulb = 800 lumens
		//  100-watt incandescent bulb = 1600 lumens
		//
		// According to http://www.greenbusinesslight.com/page/119/lux-lumens-and-watts
		//  Outdoor average sunlight ranges from 32 000 to 100 000 lux
		//  Warehouse aisles are lit to approx 100-200 lux
		//  A bright office requires about 400 lux of illumination
		//  At sunset and sunrise (with a clear sky), ambient outdoor light is also about 400 lux
		//  Building corridors can be lit adequately at around 100 lux
		//  Moonlight represents about 1 lux
		//
		//  A 400W Metal Halide lamp - used for high bay lighting in warehouses: 95 lumens/watt
		//  A 100W Incandescent bulb - used for general task lighting applications: 17 lumens/watt
		//  A 32W T5 or T8 Fluorescent tube - used for general office ceiling lighting - 50 lumens/watt
		//  A 150W High pressure sodium bulb - used for street and area - lighting 80 lumens/watt
		//
		// How we calculated the presets?
		//  Starting by kwnowing the sun's power in a bright day, we use the EV values from:
		//      https://en.wikipedia.org/wiki/Exposure_value#Tabulated_exposure_values
		//  We now know that at a bright day is between EV 14-16 A heavy overcast scene is EV 12.
		//  This means we take the 97.000 lumens from the sun and divide it by
		//  2^(16-12) = 2^4 = 16 => 97.000 / 16 = 6062.5 lumens.
		//  Now we know the sun in an overcast day is around 6062.5 lumens.
		//  6062.5 lumens / 1024 = 5.92. Note that the sample uses 6.0625, which is a little more.
		//  And we then apply the same process to all the parameters.
		//  Not all the parameters were scaled exactly the same because we're not
		//  really simulating Global Illumination but rather faking it.
		//  We hand-tweak a few adjustments based on obvervation. Furthermore note that
		//  "A bright day" is between EV 14-16; not a perfect EV 16. You may divide some parameters by
		//  16, some by 8 and some by 32... or 10 (not power of 2). This isn't an exact science, but it
		//  is very accurate. As long as you don't stray too much from the reference you will probably
		//  get very convincing results.
		//
		//  Exposure values were adjusted by hand based on observation.
		const Preset c_presets[] =
		{
			{
				"Bright, sunny day",
				Ogre::ColourValue(0.2f, 0.4f, 0.6f)  * 60.0f, //Sky
				Ogre::ColourValue(0.3f, 0.50f, 0.7f) * 4.5f,
				Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 2.925f,
				97.0f,              //Sun power
				1.5f, 1.5f,         //Lights
				0.0f, -1.0f, 2.5f,  //Exposure
				5.0f,               //Bloom
				16.0f               //Env. map scale
			},
			{
				"Average, slightly hazy day",
				Ogre::ColourValue(0.2f, 0.4f, 0.6f) * 32.0f, //Sky
				Ogre::ColourValue(0.3f, 0.50f, 0.7f) * 3.15f,
				Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 2.0475f,
				48.0f, //Sun power
				1.5f, 1.5f,         //Lights
				0.0f, -2.0f, 2.5f,  //Exposure
				5.0f,               //Bloom
				8.0f                //Env. map scale
			},
			{
				"Heavy overcast day",
				Ogre::ColourValue(0.4f, 0.4f, 0.4f) * 4.5f, //Sky
				Ogre::ColourValue(0.5f, 0.5f, 0.5f) * 0.4f,
				Ogre::ColourValue(0.5f, 0.5f, 0.5f) * 0.365625f,
				6.0625f,            //Sun power
				1.5f, 1.5f,         //Lights
				0.0f, -2.5f, 1.0f,  //Exposure
				5.0f,               //Bloom
				0.5f                //Env. map scale
			},
			{
				"Gibbous moon night",
				Ogre::ColourValue(0.27f, 0.3f, 0.6f) * 0.01831072f, //Sky
				Ogre::ColourValue(0.5f, 0.5f, 0.50f) * 0.003f,
				Ogre::ColourValue(0.4f, 0.5f, 0.65f) * 0.00274222f,
				0.0009251f,         //Sun power
				1.5f, 1.5f,         //Lights
				0.65f, -2.5f, 3.0f, //Exposure
				5.0f,               //Bloom
				0.0152587890625f    //Env. map scale
			},
			{
				"Gibbous moon night w/ powerful spotlights",
				Ogre::ColourValue(0.27f, 0.3f, 0.6f) * 0.01831072f, //Sky
				Ogre::ColourValue(0.5f, 0.5f, 0.50f) * 0.003f,
				Ogre::ColourValue(0.4f, 0.5f, 0.65f) * 0.00274222f,
				0.0009251f,         //Sun power
				6.5f, 6.5f,         //Lights
				0.65f, -2.5f, 3.0f, //Exposure
				5.0f,               //Bloom
				0.0152587890625f    //Env. map scale
			},
			{
				"JJ Abrams style",
				Ogre::ColourValue(0.2f, 0.4f, 0.6f)  * 6.0f, //Sky
				Ogre::ColourValue(0.3f, 0.50f, 0.7f) * 0.1125f,
				Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 0.073125f,
				4.0f,               //Sun power
				17.05f, 17.05f,     //Lights
				0.5f, 1.0f, 2.5f,   //Exposure
				3.0f,               //Bloom
				1.0f,               //Env. map scale
			},
		};

		{
		/*	const Ogre::uint32 numPresets = sizeof(c_presets) / sizeof(c_presets[0]);

			if (direction >= 0)
				mCurrentPreset = (mCurrentPreset + 1) % numPresets;
			else
				mCurrentPreset = (mCurrentPreset + numPresets - 1) % numPresets;*/
		}

		const Preset &preset = c_presets[4];

		/*mPresetName = preset.name;
		mExposure = preset.exposure;
		mMinAutoExposure = preset.minAutoExposure;
		mMaxAutoExposure = preset.maxAutoExposure;
		mBloomFullThreshold = preset.bloomThreshold;*/

		setSkyColour(preset.skyColour, 1.0f);


		setExposure(0.0f, 0.0f, 2.1f);
		//setExposure(preset.exposure, preset.minAutoExposure, preset.maxAutoExposure);
		setBloomThreshold(Ogre::max(preset.bloomThreshold - 2.0f, 0.0f),
			Ogre::max(preset.bloomThreshold, 0.01f));
		
		/*for (int i = 0; i<3; ++i)
		{
			assert(dynamic_cast<Ogre::Light*>(mLightNodes[i]->getAttachedObject(0)));
			Ogre::Light *light = static_cast<Ogre::Light*>(mLightNodes[i]->getAttachedObject(0));
			light->setPowerScale(preset.lightPower[i]);
		}*/

		//Ogre::SceneManager *sceneManager = mGraphicsSystem->getSceneManager();
		/*sceneManager->setAmbientLight(preset.ambLowerHemisphere,
			preset.ambUpperHemisphere,
			sceneManager->getAmbientLightHemisphereDir(),
			preset.envmapScale);*/
	}

	//-----------------------------------------------------------------------------------
	CompositorWorkspace* TestPostProcess::setupCompositor(void)
	{
		//mCompositorNames.clear();

		//createExtraEffectsFromCode();

		Root *root = m_engine.getGraphicsManager().getRoot();
		CompositorManager2 *compositorManager = root->getCompositorManager2();

		//const IdString workspaceName("PostprocessingSampleWorkspace");
		//CompositorWorkspaceDef *workspaceDef = compositorManager->getWorkspaceDefinition(workspaceName);

		////Ogre::CompositorWorkspaceDef *workspaceDef = compositorManager->addWorkspaceDefinition("PostprocessingSampleWorkspace");
		//
		////Clear the definition made with scripts as example
		//workspaceDef->clearAll();

		//CompositorManager2::CompositorNodeDefMap nodeDefs = compositorManager->getNodeDefinitions();

		////iterate through Compositor Managers resources and add name keys to menu
		//CompositorManager2::CompositorNodeDefMap::const_iterator itor = nodeDefs.begin();
		//CompositorManager2::CompositorNodeDefMap::const_iterator end = nodeDefs.end();

		//IdString compositorId = "Ogre/Postprocess";

		//// Add all compositor resources to the view container
		//while (itor != end)
		//{
		//	if (itor->second->mCustomIdentifier == compositorId)
		//	{
		//		mCompositorNames.push_back(itor->second->getNameStr());

		//		//Manually disable the node and add it to the workspace without any connection
		//		itor->second->setStartEnabled(false);
		//		workspaceDef->addNodeAlias(itor->first, itor->first);
		//	}

		//	++itor;
		//}

		//workspaceDef->connect("PostprocessingSampleStdRenderer", 0, "FinalComposition", 1);
		//workspaceDef->connectExternal(0, "FinalComposition", 0);

		SceneManager *sceneManager = m_engine.getScene().getOgreSceneManager().__OgreSceneMgrPtr;
		RenderWindow *renderWindow = m_engine.getGraphicsManager()._t_getRenderWindow(0);
		Camera *camera = m_cameraRenderable._t_OgreCameraPtr;
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

		compositorManager->addWorkspace(sceneManager, renderWindow, camera,	compositorName, true,1);

		switchPreset(sceneManager);

		return m_workspace;
	}


	//-----------------------------------------------------------------------------------
	void TestPostProcess::createExtraEffectsFromCode(void)
	{
		Root *root = m_engine.getGraphicsManager().getRoot();
		CompositorManager2 *compositorManager = root->getCompositorManager2();

		// Bloom compositor is loaded from script but here is the hard coded equivalent
		if (!compositorManager->hasNodeDefinition("Bloom"))
		{
			CompositorNodeDef *bloomDef = compositorManager->addNodeDefinition("Bloom");

			//Input channels
			bloomDef->addTextureSourceName("rt_input", 0, TextureDefinitionBase::TEXTURE_INPUT);
			bloomDef->addTextureSourceName("rt_output", 1, TextureDefinitionBase::TEXTURE_INPUT);

			bloomDef->mCustomIdentifier = "Ogre/Postprocess";

			//Local textures
			bloomDef->setNumLocalTextureDefinitions(2);
			{
				TextureDefinitionBase::TextureDefinition *texDef = bloomDef->addTextureDefinition("rt0");
				texDef->widthFactor = 0.25f;
				texDef->heightFactor = 0.25f;
				texDef->formatList.push_back(Ogre::PF_R8G8B8);

				texDef = bloomDef->addTextureDefinition("rt1");
				texDef->widthFactor = 0.25f;
				texDef->heightFactor = 0.25f;
				texDef->formatList.push_back(Ogre::PF_R8G8B8);
			}

			bloomDef->setNumTargetPass(4);

			{
				CompositorTargetDef *targetDef = bloomDef->addTargetPass("rt0");

				{
					CompositorPassQuadDef *passQuad;
					passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
					passQuad->mMaterialName = "Postprocess/BrightPass2";
					passQuad->addQuadTextureSource(0, "rt_input", 0);
				}
			}
			{
				CompositorTargetDef *targetDef = bloomDef->addTargetPass("rt1");

				{
					CompositorPassQuadDef *passQuad;
					passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
					passQuad->mMaterialName = "Postprocess/BlurV";
					passQuad->addQuadTextureSource(0, "rt0", 0);
				}
			}
			{
				CompositorTargetDef *targetDef = bloomDef->addTargetPass("rt0");

				{
					CompositorPassQuadDef *passQuad;
					passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
					passQuad->mMaterialName = "Postprocess/BluH";
					passQuad->addQuadTextureSource(0, "rt1", 0);
				}
			}
			{
				CompositorTargetDef *targetDef = bloomDef->addTargetPass("rt_output");

				{
					CompositorPassQuadDef *passQuad;
					passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
					passQuad->mMaterialName = "Postprocess/BloomBlend2";
					passQuad->addQuadTextureSource(0, "rt_input", 0);
					passQuad->addQuadTextureSource(1, "rt0", 0);
				}
			}

			//Output channels
			bloomDef->setNumOutputChannels(2);
			bloomDef->mapOutputChannel(0, "rt_output");
			bloomDef->mapOutputChannel(1, "rt_input");
		}

		//Glass compositor is loaded from script but here is the hard coded equivalent
		if (!compositorManager->hasNodeDefinition("Glass"))
		{
			CompositorNodeDef *glassDef = compositorManager->addNodeDefinition("Glass");

			//Input channels
			glassDef->addTextureSourceName("rt_input", 0, TextureDefinitionBase::TEXTURE_INPUT);
			glassDef->addTextureSourceName("rt_output", 1, TextureDefinitionBase::TEXTURE_INPUT);

			glassDef->mCustomIdentifier = "Ogre/Postprocess";

			glassDef->setNumTargetPass(1);

			{
				CompositorTargetDef *targetDef = glassDef->addTargetPass("rt_output");

				{
					CompositorPassQuadDef *passQuad;
					passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
					passQuad->mMaterialName = "Postprocess/Glass";
					passQuad->addQuadTextureSource(0, "rt_input", 0);
				}
			}

			//Output channels
			glassDef->setNumOutputChannels(2);
			glassDef->mapOutputChannel(0, "rt_output");
			glassDef->mapOutputChannel(1, "rt_input");
		}

		if (!compositorManager->hasNodeDefinition("Motion Blur"))
		{
			/// Motion blur effect
			CompositorNodeDef *motionBlurDef = compositorManager->addNodeDefinition("Motion Blur");

			//Input channels
			motionBlurDef->addTextureSourceName("rt_input", 0, TextureDefinitionBase::TEXTURE_INPUT);
			motionBlurDef->addTextureSourceName("rt_output", 1, TextureDefinitionBase::TEXTURE_INPUT);

			motionBlurDef->mCustomIdentifier = "Ogre/Postprocess";

			//Local textures
			motionBlurDef->setNumLocalTextureDefinitions(1);
			{
				TextureDefinitionBase::TextureDefinition *texDef =
					motionBlurDef->addTextureDefinition("sum");
				texDef->width = 0;
				texDef->height = 0;
				texDef->formatList.push_back(Ogre::PF_R8G8B8);
			}

			motionBlurDef->setNumTargetPass(3);

			/// Initialisation pass for sum texture
			{
				CompositorTargetDef *targetDef = motionBlurDef->addTargetPass("sum");
				{
					CompositorPassQuadDef *passQuad;
					passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
					passQuad->mNumInitialPasses = 1;
					passQuad->mMaterialName = "Ogre/Copy/4xFP32";
					passQuad->addQuadTextureSource(0, "rt_input", 0);
				}
			}
			/// Do the motion blur
			{
				CompositorTargetDef *targetDef = motionBlurDef->addTargetPass("rt_output");

				{
					CompositorPassQuadDef *passQuad;
					passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
					passQuad->mMaterialName = "Postprocess/Combine";
					passQuad->addQuadTextureSource(0, "rt_input", 0);
					passQuad->addQuadTextureSource(1, "sum", 0);
				}
			}
			/// Copy back sum texture for the next frame
			{
				CompositorTargetDef *targetDef = motionBlurDef->addTargetPass("sum");

				{
					CompositorPassQuadDef *passQuad;
					passQuad = static_cast<CompositorPassQuadDef*>(targetDef->addPass(PASS_QUAD));
					passQuad->mMaterialName = "Ogre/Copy/4xFP32";
					passQuad->addQuadTextureSource(0, "rt_output", 0);
				}
			}

			//Output channels
			motionBlurDef->setNumOutputChannels(2);
			motionBlurDef->mapOutputChannel(0, "rt_output");
			motionBlurDef->mapOutputChannel(1, "rt_input");
		}
	}

}