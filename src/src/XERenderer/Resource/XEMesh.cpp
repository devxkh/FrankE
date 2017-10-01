
#include <XERenderer/Resource/XEMesh.hpp>
#include <XERenderer/Resource/gltfAsset.h>

#include <XERenderer/GraphicsManager.hpp>


#include <Ogre/OgreMain/include/OgreMatrix4.h>
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitDatablock.h>
#include <Ogre/Components/Hlms/Pbs/include/OgreHlmsPbsDatablock.h>
#include <Ogre/OgreMain/include/OgreRoot.h>
#include <Ogre/OgreMain/include/OgreMeshManager2.h>
#include <Ogre/OgreMain/include/OgreMesh2.h>
#include <Ogre/OgreMain/include/OgreHlmsManager.h>
#include <Ogre/OgreMain/include/OgreHlms.h>
#include <Ogre/OgreMain/include/OgreSubMesh2.h>
#include <Ogre/OgreMain/include/OgreItem.h>
#include <Ogre/OgreMain/include/OgreColourValue.h>
#include <Ogre/OgreMain/include/OgreTextureManager.h>


#include <XERenderer/Resource/XEMaterial.hpp>

namespace XE {


	struct PrimitiveInformation
	{
		struct AttributeInformation
		{
			/**
			* @brief      Access to the data of the attribute.
			*/
			struct Buffer {
				void* data{ nullptr };        ///< The data of the buffer.
				uint32_t size{ 0 };           ///< The size of the above data buffer, in bytes.
				uint32_t elementsCount{ 0 };  ///< The number of elements (indices, vertices, normals)
			} buffer;
		};

		//AttributeInformation* indices{ nullptr };
		AttributeInformation position;
		AttributeInformation normal;
		//	AttributeInformation colour;
		AttributeInformation texCoords;
		/*std::vector<AttributeInformation*> texCoords{};
		std::vector<AttributeInformation*> colors{};*/
	};

	void XEMesh::buildMesh(const gltf::Asset& asset, GraphicsManager& gMgr, Ogre::SceneManager* sceneMgr) {

		Ogre::Item* item{nullptr};

		//Ogre::String datablockName = "DebugLineMat";

		//Ogre::HlmsUnlitDatablock *datablock = static_cast<Ogre::HlmsUnlitDatablock*>(gMgr.getRoot()->getHlmsManager()->getDatablock("BillBoardTest"));
		//Ogre::HlmsPbsDatablock *datablock = static_cast<Ogre::HlmsPbsDatablock*>(gMgr.getRoot()->getHlmsManager()->getDatablock(""));

		//	Ogre::HlmsUnlitDatablock *datablock = static_cast<Ogre::HlmsUnlitDatablock*>(gMgr.getRoot()->getHlmsManager()->getHlms(Ogre::HlmsTypes::HLMS_UNLIT)->createDatablock(datablockName,
			//	datablockName,
			//	Ogre::HlmsMacroblock(),
			//	Ogre::HlmsBlendblock(),
			//	Ogre::HlmsParamVec()));

			//Ogre::Root *root = Ogre::Root::getSingletonPtr();
		Ogre::RenderSystem *renderSystem = gMgr.getRoot()->getRenderSystem();
		Ogre::VaoManager *vaoManager = renderSystem->getVaoManager();

		Ogre::MeshPtr ogreMesh = Ogre::MeshManager::getSingleton().createManual("PhysicsDebuggingMesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		//https://github.com/Lugdunum3D/Lugdunum/blob/dev/src/lug/Graphics/GltfLoader.cpp
		// Load the scene
		if (asset.scene == -1) { // No scene to load
								 //return nullptr;
		}

		//	const SceneGLTF& gltfScene = asset.scenes[asset.scene];

			//for (uint32_t nodeIdx : gltfScene.nodes) {
		for (auto& mesh : asset.meshes) {
			//const NodeGLTF& gltfNode = asset.nodes[nodeIdx];

			//Scene::Node* node = parent.createSceneNode(gltfNode.name);
			//parent.attachChild(*node);

			//if (gltfNode.mesh != -1) {

			//Mesh& gltfMesh = asset.meshes[gltfNode.mesh];

			for (const gltf::Primitive& gltfPrimitive : mesh.primitives) {

				Ogre::SubMesh *subMesh = ogreMesh->createSubMesh();
				Ogre::IndexBufferPacked* m_indexBuffer;

				//	PrimitiveSet primitiveSet; //TODO = meshBuilder.addPrimitiveSet();
				PrimitiveInformation primitiveInf;

				// Mode
				switch (gltfPrimitive.mode) {
					//case gltf::Primitive::Mode::Points:
				case gltf::Primitive::Mode::Triangles:
					//	primitiveSet.mode = PrimitiveSet::Mode::Triangles;

					break;
					/*case Primitive::Mode::TriangleStrip:
						primitiveSet.mode = PrimitiveSet::Mode::TriangleStrip;
						break;
					case Primitive::Mode::TriangleFan:
						primitiveSet.mode = PrimitiveSet::Mode::TriangleFan;
						break;*/
				}

				// Attributes
				struct {
					void* data{ nullptr };
					uint32_t accessorCount{ 0 };
				} positions; // Store positions for normals generation
				bool hasNormals = false;

				// index buffer
				//	if (gltfPrimitive.indices != -1) 
				{
					const gltf::Accessor& accessor = asset.accessors[gltfPrimitive.indices]; // Get the accessor from its index (directly from indices)

					uint32_t componentSize = gltf::getAttributeSize(accessor);
					void* data = getBufferViewData(asset, accessor);
					if (!data) {
						//	return nullptr;
					}

					m_indexBuffer = vaoManager->createIndexBuffer(Ogre::IndexBufferPacked::IT_16BIT, accessor.count, Ogre::BT_DYNAMIC_PERSISTENT, NULL, false);

					auto idx_dst = m_indexBuffer->map(0, accessor.count);

					memcpy(idx_dst, static_cast<const char*>(data), componentSize * accessor.count);

					m_indexBuffer->unmap(Ogre::UO_UNMAP_ALL);
				}


				for (auto& attribute : gltfPrimitive.attributes) {
					gltf::PrimitiveSet::Attribute::Type type;
					if (attribute.first == "POSITION") {
						type = gltf::PrimitiveSet::Attribute::Type::Position;
					}
					else if (attribute.first == "NORMAL") {
						type = gltf::PrimitiveSet::Attribute::Type::Normal;
						hasNormals = true;
					}
					else if (attribute.first == "TANGENT") {
						type = gltf::PrimitiveSet::Attribute::Type::Tangent;
					}
					else if (attribute.first.find("TEXCOORD_") != std::string::npos) {
						type = gltf::PrimitiveSet::Attribute::Type::TexCoord;
					}
					else if (attribute.first.find("COLOR_") != std::string::npos) {
						type = gltf::PrimitiveSet::Attribute::Type::Color;
					}
					else {
						//	LUG_LOG.warn("GltfLoader::createMesh Unsupported attribute {}", attribute.first);
						continue;
					}

					// TODO(nokitoo): See if we can use COLOR_0 or if we just discard it
					const gltf::Accessor& accessor = asset.accessors[attribute.second]; // Get the accessor from its index (second in the pair)

					uint32_t componentSize = getAttributeSize(accessor);
					void* data = getBufferViewData(asset, accessor);
					if (!data) {
						//	return nullptr;
					}
					if (type == gltf::PrimitiveSet::Attribute::Type::Position) { // Store positions in case we need to generate the normals later
						positions.data = data;
						positions.accessorCount = accessor.count;
					}

					//	primitiveSet->addAttributeBuffer(data, componentSize, accessor.count, type);

					//------- not needed !!!
					//gltf::PrimitiveSet::Attribute attribute;

					//attribute.type = type;
					//attribute.buffer.size = componentSize * accessor.count; //elementSize * elementsCount;
					//attribute.buffer.data = new char[attribute.buffer.size];
					//attribute.buffer.elementsCount = accessor.count;

					//std::memcpy(attribute.buffer.data, static_cast<const char*>(data), attribute.buffer.size);
					//------- not needed !!!

					PrimitiveInformation::AttributeInformation attributeInf;
					attributeInf.buffer.data = data;
					attributeInf.buffer.size = componentSize * accessor.count;
					attributeInf.buffer.elementsCount = accessor.count;

					//primitiveSet.attributes.push_back(std::move(attribute));
					if (type == gltf::PrimitiveSet::Attribute::Type::Normal)
					{
						primitiveInf.normal = std::move(attributeInf);
					}
					else if (type == gltf::PrimitiveSet::Attribute::Type::Position)
					{
						primitiveInf.position = std::move(attributeInf);
					}
					else if (type == gltf::PrimitiveSet::Attribute::Type::TexCoord)
					{
						primitiveInf.texCoords = std::move(attributeInf);
					}
				}

				//vertexbuffer
				{
					Ogre::VertexElement2Vec vertexElements;
					vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT3, Ogre::VES_POSITION));
					vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT4, Ogre::VES_DIFFUSE));
					vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT3, Ogre::VES_NORMAL));
					vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES));

					size_t vertexSize = vaoManager->calculateVertexSize(vertexElements);

					Ogre::Real* vertexData = static_cast<Ogre::Real*>(OGRE_MALLOC_SIMD(vertexSize * primitiveInf.position.buffer.elementsCount, Ogre::MEMCATEGORY_GEOMETRY));

					Ogre::VertexBufferPackedVec vertexBuffers;

					auto pVertexBuffer = vaoManager->createVertexBuffer(vertexElements, primitiveInf.position.buffer.elementsCount, Ogre::BT_DYNAMIC_PERSISTENT, vertexData, false);
					vertexBuffers.push_back(pVertexBuffer);

					auto vao = vaoManager->createVertexArrayObject(vertexBuffers, m_indexBuffer, Ogre::OperationType::OT_TRIANGLE_LIST);

					subMesh->mVao[0].push_back(vao);
					subMesh->mVao[1].push_back(vao);

					ogreMesh->_setBounds(Ogre::Aabb::BOX_INFINITE);

					item = sceneMgr->createItem(ogreMesh, Ogre::SCENE_DYNAMIC);
					
					Ogre::SceneNode *sceneNode = sceneMgr->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
					sceneNode->attachObject(item);
					sceneNode->setPosition(0, 10, -20);
					sceneNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(180));


					//char* vtx_dst = reinterpret_cast<char*>(pVertexBuffer->map(0, accessor.count));
					float* vtx_dst = reinterpret_cast<float*>(pVertexBuffer->map(0, primitiveInf.position.buffer.elementsCount));

					auto positions = reinterpret_cast<float*>(primitiveInf.position.buffer.data);
					auto normals = reinterpret_cast<float*>(primitiveInf.normal.buffer.data);
					auto texCoords = reinterpret_cast<float*>(primitiveInf.texCoords.buffer.data);

					Ogre::ColourValue colour(0, 1, 0, 1);

					for (uint32_t i = 0; i < primitiveInf.position.buffer.elementsCount; ++i)
					{
						*vtx_dst++ = *positions++;
						*vtx_dst++ = *positions++;
						*vtx_dst++ = *positions++;

						//color
						*vtx_dst++ = colour.r;
						*vtx_dst++ = colour.g;
						*vtx_dst++ = colour.b;
						*vtx_dst++ = colour.a;

						*vtx_dst++ = *normals++;
						*vtx_dst++ = *normals++;
						*vtx_dst++ = *normals++;

						//texture
						*vtx_dst++ = *texCoords++;//vertex.uv.x;
						*vtx_dst++ = *texCoords++; // vertex.uv.y;
					}

					//	memcpy(vtx_dst, static_cast<const char*>(data), componentSize * accessor.count); // vtxCount * sizeof(char*));

					if (pVertexBuffer->isCurrentlyMapped()) pVertexBuffer->unmap(Ogre::UO_KEEP_PERSISTENT);
				}

				// Generate flat normals if there is not any
				//if (!hasNormals) {
				//	void* data = gltf::generateNormals((float*)positions.data, positions.accessorCount);
				//	if (!data) {
				//		//return nullptr;
				//	}
				//	//primitiveSet->addAttributeBuffer(
				//	//	data, sizeof(Ogre::Vector3), positions.accessorCount,
				//	//	PrimitiveSet::Attribute::Type::Normal
				//	//);

				//	gltf::PrimitiveSet::Attribute attribute;

				//	attribute.type = gltf::PrimitiveSet::Attribute::Type::Normal;
				//	attribute.buffer.size = sizeof(Ogre::Vector3) * positions.accessorCount; //elementSize * elementsCount;
				//	attribute.buffer.data = new char[attribute.buffer.size];
				//	attribute.buffer.elementsCount = positions.accessorCount;

				//	std::memcpy(attribute.buffer.data, static_cast<const char*>(data), attribute.buffer.size);

				//	//primitiveSet.attributes.push_back(std::move(attribute));

				//}

				// Material
				{
					const gltf::Material& gltfMaterial = asset.materials[gltfPrimitive.material];

					Ogre::HlmsPbsDatablock *datablock = static_cast<Ogre::HlmsPbsDatablock*>(gMgr.getRoot()->getHlmsManager()->getHlms(Ogre::HlmsTypes::HLMS_PBS)->createDatablock(gltfMaterial.name,
						gltfMaterial.name,
						Ogre::HlmsMacroblock(),
						Ogre::HlmsBlendblock(),
						Ogre::HlmsParamVec()));

				//	Ogre::HlmsPbsDatablock *datablock = static_cast<Ogre::HlmsPbsDatablock*>(gMgr.getRoot()->getHlmsManager()->getDatablock("StonesPbs"));
				

					auto r = gltfMaterial.pbr.baseColorFactor[0];
					auto g = gltfMaterial.pbr.baseColorFactor[1];
					auto b = gltfMaterial.pbr.baseColorFactor[2];
					auto a = gltfMaterial.pbr.baseColorFactor[3];

					//gltfMaterial.emissiveFactor[0],
					//	gltfMaterial.emissiveFactor[1],
					//	gltfMaterial.emissiveFactor[2]

					if (gltfMaterial.pbr.baseColorTexture.index != -1) {
						
						const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.pbr.baseColorTexture.index];		
						auto path = asset.images[gltfTexture.source].uri;
						auto texCoord = gltfMaterial.pbr.baseColorTexture.texCoord;

						//---------------------------------------
						Ogre::HlmsManager *hlmsManager = gMgr.getRoot()->getHlmsManager();
						Ogre::HlmsTextureManager *hlmsTextureManager = hlmsManager->getTextureManager();

						Ogre::TexturePtr myTexture = Ogre::TextureManager::getSingletonPtr()->createManual(
							"MyTexture",
							Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
							Ogre::TEX_TYPE_2D_ARRAY, 1024, 768, 0, Ogre::PF_A8R8G8B8, Ogre::TU_DYNAMIC_WRITE_ONLY);

						Ogre::HlmsTextureManager::TextureLocation texLocation =
							hlmsTextureManager->createOrRetrieveTexture("DamagedHelmet/textures/Default_albedo.jpg", "MyTexture", Ogre::HlmsTextureManager::TEXTURE_TYPE_DIFFUSE);

						texLocation.texture = myTexture;
					
						////datablock->setTexture(0, texLocation.xIdx, texLocation.texture);
						datablock->setTexture(Ogre::PBSM_DETAIL0, 0, myTexture);//Ogre::PBSM_DIFFUSE, texLocation.xIdx, texLocation.texture);

					/*	Ogre::TexturePtr myTexture = Ogre::TextureManager::getSingletonPtr()->createManual(
							"Default_albedo",
							Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
							Ogre::TEX_TYPE_2D_ARRAY, 1024, 768, 1, 0, Ogre::PF_A8R8G8B8, Ogre::TU_DYNAMIC_WRITE_ONLY);
					*/
					//	datablock->setTexture(Ogre::PBSM_DIFFUSE, 0, myTexture);

						//---------------------------------------

						if (gltfTexture.sampler != -1) {
							const gltf::Sampler& sampler = asset.samplers[gltfTexture.sampler];

							switch (sampler.magFilter) {
							/*case gltf::Sampler::MagFilter::None:
								break;
							case gltf::Sampler::MagFilter::Nearest:
								textureBuilder.setMagFilter(Render::Texture::Filter::Nearest);
								break;
							case gltf::Sampler::MagFilter::Linear:
								textureBuilder.setMagFilter(Render::Texture::Filter::Linear);
								break;*/
							}

							switch (sampler.minFilter) {
						/*	case gltf::Sampler::MinFilter::None:
								break;
							case gltf::Sampler::MinFilter::Nearest:
								textureBuilder.setMinFilter(Render::Texture::Filter::Nearest);
								break;
							case gltf::Sampler::MinFilter::Linear:
								textureBuilder.setMinFilter(Render::Texture::Filter::Linear);
								break;
							case gltf::Sampler::MinFilter::NearestMipMapNearest:
								textureBuilder.setMinFilter(Render::Texture::Filter::Nearest);
								textureBuilder.setMipMapFilter(Render::Texture::Filter::Nearest);
								break;
							case gltf::Sampler::MinFilter::LinearMipMapNearest:
								textureBuilder.setMinFilter(Render::Texture::Filter::Linear);
								textureBuilder.setMipMapFilter(Render::Texture::Filter::Nearest);
								break;
							case gltf::Sampler::MinFilter::NearestMipMapLinear:
								textureBuilder.setMinFilter(Render::Texture::Filter::Nearest);
								textureBuilder.setMipMapFilter(Render::Texture::Filter::Linear);
								break;
							case gltf::Sampler::MinFilter::LinearMipMapLinear:
								textureBuilder.setMinFilter(Render::Texture::Filter::Linear);
								textureBuilder.setMipMapFilter(Render::Texture::Filter::Linear);
								break;*/
							}

							switch (sampler.wrapS) {
							/*case gltf::Sampler::WrappingMode::ClampToEdge:
								textureBuilder.setWrapS(Render::Texture::WrappingMode::ClampToEdge);
								break;
							case gltf::Sampler::WrappingMode::MirroredRepeat:
								textureBuilder.setWrapS(Render::Texture::WrappingMode::MirroredRepeat);
								break;
							case gltf::Sampler::WrappingMode::Repeat:
								textureBuilder.setWrapS(Render::Texture::WrappingMode::Repeat);
								break;*/
							}

							switch (sampler.wrapT) {
							/*case gltf::Sampler::WrappingMode::ClampToEdge:
								textureBuilder.setWrapT(Render::Texture::WrappingMode::ClampToEdge);
								break;
							case gltf::Sampler::WrappingMode::MirroredRepeat:
								textureBuilder.setWrapT(Render::Texture::WrappingMode::MirroredRepeat);
								break;
							case gltf::Sampler::WrappingMode::Repeat:
								textureBuilder.setWrapT(Render::Texture::WrappingMode::Repeat);
								break;*/
							}
						}

						/*Resource::SharedPtr<Render::Texture> texture = createTexture(renderer, asset, loadedAssets, gltfMaterial.pbr.baseColorTexture.index);
						if (!texture) {
							LUG_LOG.error("GltfLoader::createMaterial Can't create the texture resource");
							return nullptr;
						}

						materialBuilder.setBaseColorTexture(texture, gltfMaterial.pbr.baseColorTexture.texCoord);*/
					}


					item->setDatablock(datablock);
					item->setCastShadows(true);
					//datablock->setTexture(0, 0, mFontTex);
					//datablock->setTexture("Default_albedo", Ogre::PbsTextureTypes::PBSM_DIFFUSE);

					if (gltfMaterial.pbr.metallicRoughnessTexture.index != -1) {
						
						const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.pbr.metallicRoughnessTexture.index];
						auto path = asset.images[gltfTexture.source].uri;
						auto texCoord = gltfMaterial.pbr.metallicRoughnessTexture.texCoord;

						/*Resource::SharedPtr<Render::Texture> texture = createTexture(renderer, asset, loadedAssets, gltfMaterial.pbr.metallicRoughnessTexture.index);
						if (!texture) {
							LUG_LOG.error("GltfLoader::createMaterial Can't create the texture resource");
							return nullptr;
						}

						materialBuilder.setMetallicRoughnessTexture(texture, gltfMaterial.pbr.metallicRoughnessTexture.texCoord);*/
					}

					if (gltfMaterial.normalTexture.index != -1) {

						const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.normalTexture.index];
						auto path = asset.images[gltfTexture.source].uri;
						auto texCoord = gltfMaterial.normalTexture.texCoord;

					/*	Resource::SharedPtr<Render::Texture> texture = createTexture(renderer, asset, loadedAssets, gltfMaterial.normalTexture.index);
						if (!texture) {
							LUG_LOG.error("GltfLoader::createMaterial Can't create the texture resource");
							return nullptr;
						}

						materialBuilder.setNormalTexture(texture, gltfMaterial.normalTexture.texCoord);*/
					}

					if (gltfMaterial.occlusionTexture.index != -1) {

						const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.occlusionTexture.index];
						auto path = asset.images[gltfTexture.source].uri;
						auto texCoord = gltfMaterial.occlusionTexture.texCoord;

						/*Resource::SharedPtr<Render::Texture> texture = createTexture(renderer, asset, loadedAssets, gltfMaterial.occlusionTexture.index);
						if (!texture) {
							LUG_LOG.error("GltfLoader::createMaterial Can't create the texture resource");
							return nullptr;
						}

						materialBuilder.setOcclusionTexture(texture, gltfMaterial.occlusionTexture.texCoord);*/
					}

					if (gltfMaterial.emissiveTexture.index != -1) {


						const gltf::Texture& gltfTexture = asset.textures[gltfMaterial.emissiveTexture.index];
						auto path = asset.images[gltfTexture.source].uri;
						auto texCoord = gltfMaterial.emissiveTexture.texCoord;

					/*	Resource::SharedPtr<Render::Texture> texture = createTexture(renderer, asset, loadedAssets, gltfMaterial.emissiveTexture.index);
						if (!texture) {
							LUG_LOG.error("GltfLoader::createMaterial Can't create the texture resource");
							return nullptr;
						}

						materialBuilder.setEmissiveTexture(texture, gltfMaterial.emissiveTexture.texCoord);*/
					}
					gltfMaterial.pbr.metallicFactor;
					gltfMaterial.pbr.roughnessFactor;

					/*for each (auto& tex in asset.textures[index])
						{

						};*/


					XE::XEMaterial material(gMgr.getRoot()->getHlmsManager());
					material.loadMaterial(asset, gltfMaterial,datablock);
				}
				/*Resource::SharedPtr<Render::Material> material = createMaterial(renderer, asset, loadedAssets, gltfPrimitive.material);
				if (!material) {
				LUG_LOG.error("GltfLoader::createMesh Can't create the material resource");
				return nullptr;
				}

				primitiveSet->setMaterial(material);*/


				//	mesh.primitiveSets.push_back(std::move(primitiveSet));



					/*if (loadedAssets.meshes[index]) {
					return loadedAssets.meshes[index];
					}*/
					//auto mesh = createMesh(renderer, asset, loadedAssets, gltfNode.mesh);
					//if (!mesh) {
					//	LUG_LOG.error("GltfLoader::createNode Can't create the mesh resource");
					//	return false;
					//}
					//node->attachMeshInstance(mesh);
			}
		}
	}
}