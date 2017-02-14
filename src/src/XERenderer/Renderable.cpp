#include <XERenderer/Renderable.hpp>
#include <XERenderer/GraphicsManager.hpp>

#include <XEDAL/Objects/FBEngineTypes_generated.h>


#include <Ogre/OgreMain/include/OgreNode.h>
#include <Ogre/OgreMain/include/OgreMeshManager.h>
#include <Ogre/OgreMain/include/OgreMeshManager2.h>
#include <Ogre/OgreMain/include/OgreItem.h>
#include <Ogre/OgreMain/include/OgreMesh2.h>
#include <Ogre/OgreMain/include/OgreSceneManager.h>
#include <Ogre/OgreMain/include/Animation/OgreSkeletonInstance.h>
#include <Ogre/OgreMain/include/Animation/OgreSkeletonAnimationDef.h>

#include <Ogre/OgreMain/include//OgreHlmsManager.h>

#include <Ogre/OgreMain/include/OgreHlms.h>
#include <Ogre/OgreMain/include/OgreGpuProgramManager.h>

#include <XERenderer/OgreSceneManager.hpp>

#include <XERenderer/private/OgreHelper.hpp>

#include <XEngine/Components/AnimationComponent.hpp>
#include <ThirdParty/plog/Log.h>
#include <XEngine/Scene.hpp>

#include <Ogre/OgreMain/include/OgreBillboard.h>
#include <XEDAL/PhysFS/PhysFsStream.hpp>
#include <Ogre/Components/Hlms/Pbs/include/OgreHlmsPbs.h>

#include <Ogre/OgreMain/include/OgreHlmsTextureManager.h>
#include <Ogre/Components/Hlms/Pbs/include/OgreHlmsPbsDatablock.h>
#include <Ogre/Components/Hlms/Common/include/OgreHlmsBufferManager.h>
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlit.h>
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitDatablock.h>

#include <Ogre/OgreMain/include/OgrePredefinedControllers.h>
#include <Ogre/Components/Hlms/Unlit/include/OgreTextureAnimationController.h>

namespace XE
{
	Renderable::Renderable(GraphicsManager& gmanager, Scene& scene, const void* fbData)
		: m_GraphicsManager(gmanager)
		, m_Scene(scene)
		, m_ID(m_Scene.nextRenderableID())
		, _t_OgreEntitySceneNodePtr(0)
		, isDirty(false)
		//, m_worldPosition(0,0,0)
		, m_position(0, 0, 0)
		//, m_worldScale(1, 1, 1)
		//, m_scale(1, 1, 1)
		, _t_OgreItemPtr(0)
		, m_rotation(1, 0, 0, 0)
		, m_datablock(0)
		//, m_worldOrientation(1 , 0, 0, 0)*/
		//,m_transform(0, 0, 0)
		//,m_worldTransform(0, 0, 0)
		, _t_LastPosition(Ogre::Vector3::ZERO)
		, _t_CurrentPosition(Ogre::Vector3::ZERO)
	{
		m_GraphicsManager._t_Renderables.push_back(this);

		m_GraphicsManager.getIntoRendererQueue().push([this, fbData]()
		{
			Ogre::LogManager::getSingleton().logMessage("RQ -> Renderable::StaticRenderable");


			_t_OgreEntitySceneNodePtr = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->getRootSceneNode()->createChildSceneNode();

			_t_createItem(fbData);
		});
	}

	Renderable::~Renderable()
	{
		m_GraphicsManager.getIntoRendererQueue().push([this]()
		{
			m_GraphicsManager._t_Renderables.erase(std::find(m_GraphicsManager._t_Renderables.begin(), m_GraphicsManager._t_Renderables.end(), this));
		});
	}

	const double cFrametime = 1.0 / 50.0;

	void Renderable::_t_update()
	{
		//_t_LastPosition = _t_CurrentPosition;
		//_t_CurrentPosition = m_position;

		//float weight = m_GraphicsManager.getAccumTimeSinceLastLogicFrame() / cFrametime;
		//weight = std::min(1.0f, weight);

		//Ogre::Vector3 interpPosition = Ogre::Math::lerp(_t_LastPosition, _t_CurrentPosition, weight);
		
		_t_OgreEntitySceneNodePtr->setPosition(m_position);
		_t_OgreEntitySceneNodePtr->setOrientation(m_rotation);
		_t_OgreEntitySceneNodePtr->setVisible(m_isVisible);

		isDirty = false;
	}
	

	void Renderable::setWorldPosition(const Ogre::Vector3& pos)
	{
		m_position = pos;
		isDirty = true;
	}

	void Renderable::setOrientation(const Ogre::Quaternion& rot)
	{
		m_rotation = rot;
		isDirty = true;
	}

	void Renderable::setVisibility(const bool isVisible)
	{
		m_isVisible = isVisible;
		isDirty = true;
	}

	bool Renderable::isVisible()
	{
		return m_isVisible;
	}
	//void Renderable::setBlendmode()// Ogre::v1::Entity* _t_entity)
	//{
	//	m_GraphicsManager.getIntoRendererQueue().push([this]() {
	//		//	assert(_t_entity);

	//		//	m_t_animations = ogreEntity._t_getEntPtr()->getAllAnimationStates();

	//		bool entityIsAnimated = (_t_OgreItemPtr->getSkeletonInstance()->getAnimations() != NULL);
	//		assert(entityIsAnimated);

	//		Ogre::SkeletonInstance* skeleton = _t_OgreItemPtr->getSkeletonInstance();
	//		skeleton->setBlendMode(Ogre::v1::ANIMBLEND_CUMULATIVE);
	//	});
	//}

	void Renderable::_t_createItem(const void* fbData)
	{
		const XFBType::RenderableComponent* renderable = (const XFBType::RenderableComponent*)fbData;

		//	auto renderable = flatbuffers::GetRoot<XFBType::RenderableComponent>(fbData);
		auto meshes = renderable->meshes();

		//------------------------------------------------------------------------------
		//------------------- create all meshes for this entity -----------------------
		//------------------------------------------------------------------------------
		if (meshes)
		{
			for (auto var : *meshes)
			{
				Ogre::v1::MeshPtr meshV1;
				
				//std::cout << "meshes:" << var->Name()->c_str() << std::endl;
				LOG(plog::info) << "Renderable:_t_createItem";
				LOG(plog::info) << "mesh_type:" << EnumNameUMesh(var->mesh_type());

				if (var->mesh_type() == XFBType::UMesh::UMesh_MeshPlane)
				{
					//------------------- OGRE PLANE MESH -----------------------
					meshV1 = Ogre::v1::MeshManager::getSingleton().createPlane(
						std::to_string(m_ID),
						"General",
						Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 250, 250, 25, 25, true, 1, 15, 15, Ogre::Vector3::UNIT_Z,
						Ogre::v1::HardwareBuffer::HBU_STATIC,
						Ogre::v1::HardwareBuffer::HBU_STATIC); //without Ogre::v1::HardwareBuffer::HBU_STATIC crash in planeMesh->importV1???

															   // create a floor entity, give it a material, and place it at the origin
															   //--------------------------- todo import v2 directly
					Ogre::MeshPtr manual = Ogre::MeshManager::getSingleton().createManual(
						"Plane",//var->Name()->c_str(), //"Plane",
						Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
					manual->importV1(meshV1.get(), true, true, true);
					//We don't need the v1 mesh. Free CPU memory, get it out of the GPU.
					//Leave it loaded if you want to use athene with v1 Entity.
					meshV1->unload();

					_t_OgreItemPtr = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createItem(manual, (Ogre::SceneMemoryMgrTypes)Ogre::SCENE_DYNAMIC); //renderable->memType()); //Ogre::SCENE_DYNAMIC);

					Ogre::HlmsManager *hlmsManager = m_GraphicsManager.getRoot()->getHlmsManager();
					m_datablock = hlmsManager->getDatablock("StonesPbs");
					//_t_OgreItemPtr->setDatablock(datablock); //todo multiple materials per mesh	
												   //floor->setMaterialName("Examples/Rockwall", "General");
												   //floor->setCastShadows(false);
			

					//_t_OgreEntitySceneNodePtr->attachObject(_t_OgreItemPtr);
				}
				else if (var->mesh_type() == XFBType::UMesh::UMesh_MeshCube)
				{
					_t_OgreItemPtr = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createItem("Cube_d.mesh",
																							Ogre::ResourceGroupManager::
																							AUTODETECT_RESOURCE_GROUP_NAME,
																							Ogre::SCENE_DYNAMIC);

	
					//_t_OgreEntitySceneNodePtr->attachObject(_t_OgreItemPtr);


					auto bbs = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createBillboardSet();
					Ogre::v1::Billboard* sunBillboard = bbs->createBillboard(Ogre::Vector3(0, 0, 0));
					sunBillboard->setDimensions(25,25);
					//You need sets Billboard::mDirection to some value other than the default Vector3::ZERO to make BBT_ORIENTED_SELF / BBT_PERPENDICULAR_SELF work.
					sunBillboard->mDirection = Ogre::Vector3::UNIT_Y;
					bbs->setBillboardType(Ogre::v1::BillboardType::BBT_ORIENTED_SELF);
				
					//bbs->Ogre::Renderable::setDatablock("TestModel");
					bbs->setRenderQueueGroup(5);
					m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->getRenderQueue()->setRenderQueueMode(5, Ogre::RenderQueue::Modes::V1_FAST);

					Ogre::HlmsManager *hlmsManager = m_GraphicsManager.getRoot()->getHlmsManager();
					m_datablock = hlmsManager->getDatablock("BillBoardTest");
					bbs->setDatablock(m_datablock);

					Ogre::HlmsUnlitDatablock *datablockUnlit = (Ogre::HlmsUnlitDatablock*)m_datablock;
					//	assert(dynamic_cast<Ogre::HlmsUnlit*>(hlmsManager->getHlms(Ogre::HLMS_UNLIT)));
					/*	Ogre::HlmsUnlit *hlmsUnlit = static_cast<Ogre::HlmsUnlit*>(hlmsManager->getHlms(Ogre::HLMS_UNLIT));
					
						Ogre::HlmsUnlitDatablock *datablockUnlit = (Ogre::HlmsUnlitDatablock*)hlmsUnlit->createDatablock(
							"TestMat", "TestMat", Ogre::HlmsMacroblock(), Ogre::HlmsBlendblock(), Ogre::HlmsParamVec());
						datablockUnlit->setTexture(0, 0,
							Ogre::TextureManager::getSingleton().load("tornado.png",
								Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME), 0);*/
					//	Ogre::Matrix4 mat(Ogre::Matrix4::IDENTITY);
					//	//mat.setScale(Ogre::Vector3(1, 1, 1));
					////	mat.setTrans(Ogre::Vector3(0.5, 0.5, 0));
					//	Ogre::Matrix4 xform(Ogre::Matrix4::IDENTITY);
					//	mat[0][3] = 1.0;
					//	mat[1][3] = 0;

					//	xform = mat * xform;
						//datablockUnlit->setFlipbookAnim(2,3, 1); //x , y , speed
					//	datablockUnlit->setAnimationMatrix(0, xform);
						//auto tex = datablockUnlit->getTexture(0);
	
						//Ogre::ControllerManager::getSingleton().getElapsedTime();
			
					Ogre::HlmsSamplerblock samplerblock;
					samplerblock.setAddressingMode(Ogre::TAM_WRAP);
					datablockUnlit->setSamplerblock(0, samplerblock);

					datablockUnlit->setEnableAnimationMatrix(0, true);
					
					Ogre::Controller<Ogre::Real>* ret = 0;

					float speed = 1.0;
					Ogre::TextureAnimationControllerValue* ctrlVal = 0;

					if (speed != 0)
					{
						Ogre::SharedPtr< Ogre::ControllerValue<Ogre::Real> > val;
						Ogre::SharedPtr< Ogre::ControllerFunction<Ogre::Real> > func;

						val.bind(OGRE_NEW Ogre::TextureAnimationControllerValue(datablockUnlit, 0));
						ctrlVal = static_cast<Ogre::TextureAnimationControllerValue*>(val.get());

						// Create function: use -speed since we're altering texture coords so they have reverse effect
						func.bind(OGRE_NEW Ogre::ScaleControllerFunction(-speed, true));
						ret = Ogre::ControllerManager::getSingleton().createController(Ogre::ControllerManager::getSingleton().getFrameTimeSource(), val, func);
					}

						ctrlVal->tiledAnimation(4, 4);
					//ctrlVal->scrollAnimation(1, 1);
					//	ctrlVal->scrollAnimation(0, 1);
					//	ctrlVal->rotationAnimation(1);
					//	ctrlVal->scaleAnimation(1, 0);


					//	auto controller = Ogre::ControllerManager::getSingleton().createTextureUVScroller(? ? , 1.0f);
					
						//Ogre::MaterialPtr m = Ogre::MaterialManager::getSingleton().create(
						//	"MyOffsetMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
			
/*
						Ogre::Technique *technique = m->createTechnique();
						Ogre::Pass *pass_ambient = technique->createPass();*/

				//		auto controller = Ogre::ControllerManager::getSingleton().createTextureUVScroller(?? , 1.0f);
						//datablockUnlit->getTexture()->get
						//auto renderables = _t_OgreItemPtr->mRenderables[0];
						//auto text = datablockUnlit->getTexture(2);
					
						//renderables->setMaterial(m);
						//auto material = renderables->getMaterial();
						//auto pass = material->getTechnique(0)->getPass(0);
						//auto texUState = pass->createTextureUnitState("tornado.png", 0);
						//auto controller = Ogre::ControllerManager::getSingleton().createTextureUVScroller(texUState, 1.0f);
					/*	auto tech = renderables->get();
						auto pass = tech->getPass(0);

						 Ogre::TextureUnitState* t = pass->getTextureUnitState(0);*/
				
					_t_OgreEntitySceneNodePtr->attachObject(bbs);
				}

				else if (var->mesh_type() == XFBType::UMesh::UMesh_MeshFile)
				{
					const XFBType::MeshFile * meshFile = static_cast<const XFBType::MeshFile *>(var->mesh());

					
					if (!meshFile->file() || !meshFile->file()->fileName())
					{
						LOG(plog::error) << "mesh filename is empty! , Renderable.create";
						return;
					}

					auto test = meshFile->file()->fileName()->c_str();

					bool halfPosition = true;
					bool halfUVs = true;
					bool useQtangents = true;

					auto v2Mesh = Ogre::MeshManager::getSingleton().getByName(meshFile->file()->fileName()->c_str(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

					if (!v2Mesh)
					{
						auto v1Mesh = Ogre::v1::MeshManager::getSingleton().load(
							meshFile->file()->fileName()->c_str(), Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
							Ogre::v1::HardwareBuffer::HBU_STATIC, Ogre::v1::HardwareBuffer::HBU_STATIC);
						/*		auto v1Mesh = Ogre::v1::MeshManager::getSingleton().load(
								"Sinbad.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
								Ogre::v1::HardwareBuffer::HBU_STATIC, Ogre::v1::HardwareBuffer::HBU_STATIC);*/
								//Create a v2 mesh to import to, with a different name.

						v2Mesh = Ogre::MeshManager::getSingleton().createManual(meshFile->file()->fileName()->c_str(), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

						v2Mesh->importV1(v1Mesh.get(), halfPosition, halfUVs, useQtangents);
						v1Mesh->unload();
					}

					_t_OgreItemPtr = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createItem(v2Mesh, (Ogre::SceneMemoryMgrTypes)Ogre::SCENE_DYNAMIC);
				//	_t_OgreItemPtr->setVisibilityFlags(0x000000001);

					Ogre::HlmsManager *hlmsManager = m_GraphicsManager.getRoot()->getHlmsManager();
					
					/*Ogre::HlmsDatablock *datablockTest = hlmsManager->getDatablock("DefaultPbs");
					_t_OgreItemPtr->setDatablock(datablockTest);*/

					m_datablock = hlmsManager->getDatablock(meshFile->material()->name()->c_str());//"TestModel");
				//	_t_OgreItemPtr->setDatablock(datablock);

					


					//Ogre::HlmsManager *hlmsManager = m_GraphicsManager.getRoot()->getHlmsManager();
					//Ogre::HlmsDatablock *datablock = hlmsManager->getDatablock("HlmsUnlit1");
					//datablock->mShadowConstantBias = 0.001;
					//_t_OgreItemPtr->setDatablock(datablock);
					
					auto aabb = _t_OgreItemPtr->getLocalAabb();
					
					//_t_OgreItemPtr->setCastShadows(true);
					//	_t_OgreItemPtr->setDatablock("BaseWhite");
						//meshV1 = tmp->getMesh();
						//Ogre::MeshPtr manual = Ogre::MeshManager::getSingleton().createManual(
						//	"sindbad",//var->Name()->c_str(), //"Plane",
						//	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
						//manual->importV1(meshV1.get(), true, true, true);
						////We don't need the v1 mesh. Free CPU memory, get it out of the GPU.
						////Leave it loaded if you want to use athene with v1 Entity.
						//meshV1->unload();

					//	newItem = m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->createItem(manual, (Ogre::SceneMemoryMgrTypes)Ogre::SCENE_DYNAMIC); //renderable->memType()); //Ogre::SCENE_DYNAMIC);
					//	newItem->setDatablock("Marble"); //todo multiple materials per mesh	
														 //floor->setMaterialName("Examples/Rockwall", "General");
														 //floor->setCastShadows(false);

				//	_t_OgreEntitySceneNodePtr->setVisible(false);
	
				}

				/*_t_OgreItemPtr->setRenderQueueGroup(renderable->renderqueue());
				m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->getRenderQueue()->setRenderQueueMode(renderable->renderqueue(), Ogre::RenderQueue::Modes::V1_FAST);
*/
				m_isVisible = renderable->visible();
				_t_OgreItemPtr->setVisibilityFlags(renderable->visibilityFlags());
				_t_OgreEntitySceneNodePtr->attachObject(_t_OgreItemPtr);
				_t_OgreItemPtr->setVisibilityFlags(renderable->visibilityFlags()); // 0x000000001);
				_t_OgreItemPtr->setCastShadows(renderable->castShadows());
				_t_OgreEntitySceneNodePtr->setVisible(renderable->visible());
				if (m_datablock)
				{
					m_datablock->mShadowConstantBias = renderable->shadowconstBias();
					_t_OgreItemPtr->setDatablock(m_datablock);
				}
			}
		}

		//	m_ogreEntity._t_OgreEntitySceneNodePtr->setPosition(0, -50, 0); //done in scene gameEntity->setTransform(tvs);

	/*	if (deleteThisBuffer)
		{
			delete deleteThisBuffer;
			deleteThisBuffer = nullptr;
		}*/
	}

	void Renderable::createAnimations(AnimationComponent& animationComponent)
	{
		m_GraphicsManager.getIntoRendererQueue().push([this, &animationComponent]()
		{
			assert(_t_OgreItemPtr->hasSkeleton());

			auto animations = _t_OgreItemPtr->getSkeletonInstance()->getAnimations();

			Ogre::SkeletonAnimationVec::iterator it = animations.begin();
			while (it != animations.end())
			{
				//	auto animationPtr = &*it;
				float duration = it->getDuration();
				std::string name = it->getDefinition()->getNameStr();

				Ogre::SkeletonAnimation* skeletonAnimationPtr = &*it;
		
				//attention!! delete in mainthread 
				std::vector< float* >* boneWeightPtrs = new std::vector< float* >();
				std::vector< float >* boneWeightList = new std::vector< float >();

				for (int i = 0; i < skeletonAnimationPtr->mOwner->getNumBones(); i++)
				{
					Ogre::String boneName = skeletonAnimationPtr->mOwner->getBone(i)->getName();
					Ogre::Real* weight = skeletonAnimationPtr->getBoneWeightPtr(Ogre::IdString(boneName));
					if (weight != 0)
					{
						boneWeightPtrs->push_back(weight);
						boneWeightList->push_back(*boneWeightPtrs->back());
					}
					else
					{
						boneWeightPtrs->push_back(0);
						boneWeightList->push_back(0);
					}
				}
				//do not use the iterator, else crash in mainthread ?!! 
				//setloop only works with >getSkeletonInstance()->getAnimation returned _t_OgreItemPtr->getSkeletonInstance() instance???
				Ogre::SkeletonAnimation* test = _t_OgreItemPtr->getSkeletonInstance()->getAnimation(name);

				//		m_GraphicsManager.getFromRendererQueue().push([test, name, duration, &animationComponent, boneWeightPtrs, boneWeightList]() {

				animationComponent._MT_setAnimationStatePtr(test, name, duration, boneWeightPtrs, boneWeightList);

				//	m_t_animation = test;
		//		});
				it++;
			}
		});
	}

	void Renderable::destoyItems()
	{
		m_GraphicsManager.getIntoRendererQueue().push([this]()
		{
			_t_OgreEntitySceneNodePtr->detachAllObjects();

			auto objIt = _t_OgreEntitySceneNodePtr->getAttachedObjectIterator();
			while (objIt.hasMoreElements())
			{
				m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->destroyItem(static_cast<Ogre::Item*>(objIt.getNext()));
			}

			_t_OgreEntitySceneNodePtr->removeAndDestroyAllChildren();
		});
	}

	void Renderable::update(float delta)
	{

	}

	void Renderable::update(const void* fbData)
	{
	//	destoyItems(); //mainthread !
		
		//TODO http://www.ogre3d.org/forums/viewtopic.php?f=2&t=91995

		m_GraphicsManager.getIntoRendererQueue().push([this, fbData]()
		{
			const XFBType::RenderableComponent* renderable = (const XFBType::RenderableComponent*)fbData;

			//	auto renderable = flatbuffers::GetRoot<XFBType::RenderableComponent>(fbData);
			auto meshes = renderable->meshes();


			Ogre::LogManager::getSingleton().logMessage("RQ -> Renderable::update");

			Ogre::HlmsManager *hlmsManager = m_GraphicsManager.getRoot()->getHlmsManager();

			//https://github.com/spookyboo/HLMSEditor/blob/74e175352a6d794c0c0fe937ab7ce14134255e5e/source/src/hlms_utils_manager.cpp
			Ogre::HlmsJson hlmsJson(hlmsManager);

			if (meshes)
			{
				for (auto fbMesh : *meshes)
				{
					LOG(plog::info) << "Renderable:_t_createItem";

					LOG(plog::info) << "mesh_type:" << EnumNameUMesh(fbMesh->mesh_type());

					if (fbMesh->mesh_type() == XFBType::UMesh::UMesh_MeshFile)
					{
						const XFBType::MeshFile* mesh = (const XFBType::MeshFile*)fbMesh->mesh();
												
						auto textures = mesh->material()->textures();

						//----------------- destroy textures -----------------------------
						if (textures)
						{
							Ogre::HlmsTextureManager *hlmsTextureManager = hlmsManager->getTextureManager();

							for (auto fbTexture : *textures)
							{
								auto tex = fbTexture->c_str();

								hlmsTextureManager->destroyTexture(tex); // "outUV.png");
							}
						}
						
						//-------------- assign dummy material to free item material ----------------------
						m_datablock = hlmsManager->getDatablock("DefaultPbs");
						_t_OgreItemPtr->setDatablock(m_datablock);

						//-------------- destroy item material ------------------------------------
						if (mesh->material()->textureType() == XFBType::TextureType::TextureType_Pbs)
						{
							Ogre::HlmsPbs* hlmsPbs = static_cast<Ogre::HlmsPbs*>(hlmsManager->getHlms(Ogre::HLMS_PBS));
														
							auto matName = mesh->material()->name()->c_str();
							Ogre::HlmsDatablock *latestDatablock = hlmsPbs->getDatablock(matName); // "TestModel");//"TestModel");
						
							if (latestDatablock && latestDatablock != hlmsPbs->getDefaultDatablock())
							{
								hlmsPbs->destroyDatablock(mesh->material()->name()->c_str()); // "TestModel");
							}
						}

						std::string filename = mesh->material()->file()->filePath()->c_str();
						//filename += mesh->material()->file()->fileName()->c_str();

					//		filename = "assets/TestModel.material.json";		

						XE::PhysFsStream wonderfullStream;
						if (wonderfullStream.open(filename.c_str()))
						{
							// Make sure that the stream's reading position is at the beginning
							wonderfullStream.seek(0);

							std::vector<char> buffer(wonderfullStream.getSize());
							if (wonderfullStream.read(buffer.data(), wonderfullStream.getSize()))
							{
								buffer.push_back('\0'); //rapidjson needs to be null terminated
								hlmsJson.loadMaterials(mesh->material()->file()->fileName()->c_str(), "General", &buffer[0]);
							}
						}

						m_datablock = hlmsManager->getDatablock(mesh->material()->name()->c_str());// "TestModel");
					

								//------------ reload hlms template files ----------------
								//Hot reload of PBS shaders. We need to clear the microcode cache
								//to prevent using old compiled versions.
								//Ogre::Root *root = m_GraphicsManager.getRoot();
								////Ogre::HlmsManager *hlmsManager = root->getHlmsManager();

								//Ogre::Hlms *hlms = hlmsManager->getHlms(Ogre::HLMS_PBS);
								//Ogre::GpuProgramManager::getSingleton().clearMicrocodeCache();
								//hlms->reloadFrom(hlms->getDataFolder());

								////Hot reload of Unlit shaders.
								//Ogre::Hlms *hlmsUnlit = hlmsManager->getHlms(Ogre::HLMS_UNLIT);
								//Ogre::GpuProgramManager::getSingleton().clearMicrocodeCache();
								//hlmsUnlit->reloadFrom(hlmsUnlit->getDataFolder());
								//------------ reload hlms template files ----------------

							//	_t_createItem(fbData);
					}
				}
			}

			/*_t_OgreItemPtr->setRenderQueueGroup(renderable->renderqueue());
			m_Scene.getOgreSceneManager().__OgreSceneMgrPtr->getRenderQueue()->setRenderQueueMode(renderable->renderqueue(), Ogre::RenderQueue::Modes::V1_FAST);*/

			m_isVisible = renderable->visible();
			_t_OgreEntitySceneNodePtr->setVisible(renderable->visible());
			_t_OgreItemPtr->setVisibilityFlags(renderable->visibilityFlags());
			//_t_OgreEntitySceneNodePtr->attachObject(_t_OgreItemPtr);
			_t_OgreItemPtr->setVisibilityFlags(renderable->visibilityFlags()); // 0x000000001);
			_t_OgreItemPtr->setCastShadows(renderable->castShadows());
			if (m_datablock)
			{
				m_datablock->mShadowConstantBias = renderable->shadowconstBias();
				_t_OgreItemPtr->setDatablock(m_datablock);
			}
			//	delete deleteThisBuffer;
		});
	}

	/*void reloadHlmsResource(Ogre::Root* root, const std::string& resourceName)
	{
		const std::array<Ogre::HlmsTypes, 7> searchHlms = { Ogre::HLMS_PBS, Ogre::HLMS_TOON, Ogre::HLMS_UNLIT, Ogre::HLMS_USER0, Ogre::HLMS_USER1, Ogre::HLMS_USER2, Ogre::HLMS_USER3 };

		Ogre::Hlms* hlms = nullptr;
		Ogre::HlmsDatablock* datablockToReload = nullptr;
		for (auto searchHlmsIt = searchHlms.begin(); searchHlmsIt != searchHlms.end() && datablockToReload == nullptr; ++searchHlmsIt)
		{
			hlms = root->getHlmsManager()->getHlms(*searchHlmsIt);
			if (hlms)
				datablockToReload = hlms->getDatablock(resourceName);
		}

		if (datablockToReload == nullptr || datablockToReload == hlms->getDefaultDatablock())
			return;

		Ogre::String const *filenameTmp, *resourceGroupTmp;
		datablockToReload->getFilenameAndResourceGroup(&filenameTmp, &resourceGroupTmp);
		if (filenameTmp && resourceGroupTmp && !filenameTmp->empty() && !resourceGroupTmp->empty())
		{
			const Ogre::String filename(*filenameTmp), resourceGroup(*resourceGroupTmp);
			Ogre::vector<Ogre::Renderable*>::type lrlist = datablockToReload->getLinkedRenderables();
			for (auto it = lrlist.begin(); it != lrlist.end(); ++it)
				(*it)->_setNullDatablock();

			hlms->destroyDatablock(resourceName);

			hlms->getHlmsManager()->loadMaterials(filename, resourceGroup);

			Ogre::HlmsDatablock *datablockNew = hlms->getDatablock(resourceName);
			for (auto it = lrlist.begin(); it != lrlist.end(); ++it)
				(*it)->setDatablock(datablockNew);
		}
		else {}
	}*/

	//void Renderable::scale(const Ogre::Vector3& scale){
	//	m_scale = scale;
	//	m_GraphicsManager.getIntoRendererQueue().push([this, scale]()
	//	{
	//		_t_OgreEntitySceneNodePtr->setScale(scale);
	//	});
	//}	


	void Renderable::destroy()
	{
		//todo	//todo in renderthread
		//(*rIter)->getSceneNode()->detachAllObjects();
		//(*rIter)->getSceneNode()->removeAndDestroyAllChildren();
		//mScene->getSceneMgr()->destroyEntity((*rIter)->getEntity());
		//mScene->getSceneMgr()->destroySceneNode((*rIter)->getSceneNode());
	}

} // namespace XE