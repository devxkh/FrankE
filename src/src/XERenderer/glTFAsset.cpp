
#include "gltfAsset.h"


#include <XESystem/SystemConfig.hpp>

// Define these only in *one* .cc file.
#define TINYGLTF_LOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <ThirdParty/tinygltfloader/tiny_gltf_loader.h>
#include <XERenderer/private/gltf_loader.h>
#include <unordered_map>

#ifdef ASSIMP_IMPORTER_GLTF_USE_OPEN3DGC
// Header files, Open3DGC.
#	include <Open3DGC/o3dgcSC3DMCDecoder.h>
#endif

#include <Ogre/OgreMain/include/OgreVector2.h>

#include <XERenderer/private/gltf_loader.h>

namespace XE {


	typedef uint64_t VkDeviceSize;

	typedef enum VkFormat {
		VK_FORMAT_UNDEFINED = 0
	} VkFormat;

	typedef enum VkSampleCountFlagBits {
		VK_SAMPLE_COUNT_1_BIT = 0x00000001,
		VK_SAMPLE_COUNT_2_BIT = 0x00000002,
		VK_SAMPLE_COUNT_4_BIT = 0x00000004,
		VK_SAMPLE_COUNT_8_BIT = 0x00000008,
		VK_SAMPLE_COUNT_16_BIT = 0x00000010,
		VK_SAMPLE_COUNT_32_BIT = 0x00000020,
		VK_SAMPLE_COUNT_64_BIT = 0x00000040,
	} VkSampleCountFlagBits;

	struct ImageWrapper
	{
		uint32_t image;
		std::vector<uint32_t> imageViews;
		std::vector<uint32_t> samplers;

		VkFormat format;
		uint32_t width, height, depth = 1;
		uint32_t mipLevelCount = 1;
		uint32_t layerCount = 1;
		VkSampleCountFlagBits sampleCount = VK_SAMPLE_COUNT_1_BIT;
	};

	struct BufferWrapper
	{
		uint32_t buffer;
		VkDeviceSize offset;
		VkDeviceSize size;
	};
	struct Vertex
	{
		Ogre::Vector3 pos;
		Ogre::Vector3 normal;
		Ogre::Vector2 texCoord;

		bool operator==(const Vertex& other) const
		{
			return pos == other.pos &&
				normal == other.normal &&
				texCoord == other.texCoord;
		}

		/*static VkVertexInputBindingDescription getBindingDescription()
		{
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
		}

		static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions()
		{
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions(3, {});

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, normal);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

		return attributeDescriptions;
		}*/
	};

	struct BBox
	{
		Ogre::Vector3 min;
		Ogre::Vector3 max;

		/*BBox() : min(std::numeric_limits<float>::max()), max(-std::numeric_limits<float>::max()) {}

		BBox(const Ogre::Vector3 &_min, const Ogre::Vector3 &_max)
		: min(_min), max(_max) {}

		BBox getTransformedAABB(const glm::mat4 &T) const;*/
	};



	class VMesh
	{
	public:

		const static uint32_t numMapsPerMesh = 6;

		BufferWrapper vertexBuffer;
		BufferWrapper indexBuffer;

		ImageWrapper albedoMap;
		ImageWrapper normalMap;
		ImageWrapper roughnessMap;
		ImageWrapper metalnessMap;
		ImageWrapper aoMap;
		ImageWrapper emissiveMap;

		BBox bounds;
		float scale;
	};


	typedef struct { Uint32 vb; } GLBufferState;

	typedef struct {
		std::vector<Uint32> diffuseTex;  // for each primitive in mesh
	} GLMeshState;


	inline std::string getFileExtension(const std::string &fn)
	{
		size_t pos = fn.find_last_of('.');
		if (pos == std::string::npos) return ""; else return fn.substr(pos + 1);
	}

	static void loadFromGLTF(std::vector<VMesh> &retMeshes, const std::string &gltfFileName,
		const std::string &version = "1.0")
	{
		if (version == "1.0")
		{
			// Parse glTF
			tinygltf::Scene scene;
			tinygltf::TinyGLTFLoader loader;
			std::string err;
			bool status;

			std::string ext = getFileExtension(gltfFileName);
			if (ext == "gltf")
			{
				status = loader.LoadASCIIFromFile(&scene, &err, gltfFileName);
			}
			else if (ext == "glb")
			{
				status = loader.LoadBinaryFromFile(&scene, &err, gltfFileName);
			}
			else
			{
				throw std::invalid_argument("invalid input file name");
			}

			if (!status)
			{
				throw std::runtime_error("failed to parse glTF: " + err);
			}

			// Meshes
			std::unordered_map<std::string, std::vector<const tinygltf::Primitive *>> mat2meshes;
			const auto &meshes = scene.meshes;
			const auto &materials = scene.materials;
			const auto &textures = scene.textures;
			const auto &images = scene.images;

			for (const auto &nameMeshPair : meshes)
			{
				const auto &name = nameMeshPair.first;
				const auto &mesh = nameMeshPair.second;

				for (const auto &prim : mesh.primitives)
				{
					const auto &matName = prim.material;
					mat2meshes[matName].emplace_back(&prim);
				}
			}

			for (const auto &matMeshes : mat2meshes)
			{
				VMesh newMesh;
				retMeshes.emplace_back(newMesh);
				auto &retMesh = retMeshes.back();

				// Textures
				const auto &material = materials.at(matMeshes.first);
				{
					const auto &texName = material.values.at("baseColorTexture").string_value;
					const auto &tex = textures.at(texName);
					const auto &image = images.at(tex.source);

					/*	auto gliFormat = chooseFormat(tex.type, image.component);
					loadTexture2DFromBinaryData(&retMesh.albedoMap, pManager, image.image.data(), image.width, image.height, gliFormat, image.levelCount);*/
				}
				{
					const auto &texName = material.values.at("normalTexture").string_value;
					const auto &tex = textures.at(texName);
					const auto &image = images.at(tex.source);

					/*auto gliFormat = chooseFormat(tex.type, image.component);
					loadTexture2DFromBinaryData(&retMesh.normalMap, pManager, image.image.data(), image.width, image.height, gliFormat, image.levelCount);*/
				}
				{
					const auto &texName = material.values.at("roughnessTexture").string_value;
					const auto &tex = textures.at(texName);
					const auto &image = images.at(tex.source);

					/*auto gliFormat = chooseFormat(tex.type, image.component);
					loadTexture2DFromBinaryData(&retMesh.roughnessMap, pManager, image.image.data(), image.width, image.height, gliFormat, image.levelCount);*/
				}
				{
					const auto &texName = material.values.at("metallicTexture").string_value;
					const auto &tex = textures.at(texName);
					const auto &image = images.at(tex.source);

					/*auto gliFormat = chooseFormat(tex.type, image.component);
					loadTexture2DFromBinaryData(&retMesh.metalnessMap, pManager, image.image.data(), image.width, image.height, gliFormat, image.levelCount);*/
				}
				if (material.values.find("aoTexture") != material.values.end())
				{
					const auto &texName = material.values.at("aoTexture").string_value;
					const auto &tex = textures.at(texName);
					const auto &image = images.at(tex.source);

					/*auto gliFormat = chooseFormat(tex.type, image.component);
					loadTexture2DFromBinaryData(&retMesh.aoMap, pManager, image.image.data(), image.width, image.height, gliFormat, image.levelCount);*/
				}
				if (material.values.find("emissiveTexture") != material.values.end())
				{
					const auto &texName = material.values.at("emissiveTexture").string_value;
					const auto &tex = textures.at(texName);
					const auto &image = images.at(tex.source);

					/*auto gliFormat = chooseFormat(tex.type, image.component);
					loadTexture2DFromBinaryData(&retMesh.emissiveMap, pManager, image.image.data(), image.width, image.height, gliFormat, image.levelCount);*/
				}

				// Geometry
				std::vector<Vertex> hostVertices;
				std::vector<uint32_t> hostIndices;
				uint32_t vertOffset = 0;
				uint32_t indexOffset = 0;
				const auto &accessors = scene.accessors;
				const auto &bufferViews = scene.bufferViews;
				const auto &buffers = scene.buffers;

				for (const auto &pMeshPrim : matMeshes.second)
				{
					const auto &mesh = *pMeshPrim;
					const auto &posAccessor = accessors.at(mesh.attributes.at("POSITION"));
					const auto &nrmAccessor = accessors.at(mesh.attributes.at("NORMAL"));
					const auto &uvAccessor = accessors.at(mesh.attributes.at("TEXCOORD_0"));
					const auto &idxAccessor = accessors.at(mesh.indices);
					uint32_t numVertices = static_cast<uint32_t>(posAccessor.count);
					hostVertices.resize(hostVertices.size() + numVertices);
					uint32_t numIndices = static_cast<uint32_t>(idxAccessor.count);
					hostIndices.resize(hostIndices.size() + numIndices);

					// Postions
					{
						const auto &bufferView = bufferViews.at(posAccessor.bufferView);
						const auto &buffer = buffers.at(bufferView.buffer);
						size_t offset = bufferView.byteOffset + posAccessor.byteOffset;
						size_t stride = posAccessor.byteStride;
						assert(stride >= 12);
						assert(posAccessor.count == numVertices);
						const auto *data = &buffer.data[offset];

						for (uint32_t i = 0; i < numVertices; ++i)
						{
							const float *pos = reinterpret_cast<const float *>(&data[stride * i]);
							hostVertices[vertOffset + i].pos = Ogre::Vector3(pos[0], pos[1], pos[2]);

							retMesh.bounds.max = std::max(retMesh.bounds.max, hostVertices[vertOffset + i].pos);
							retMesh.bounds.min = std::min(retMesh.bounds.min, hostVertices[vertOffset + i].pos);
						}
					}
					// Normal
					{
						const auto &bufferView = bufferViews.at(nrmAccessor.bufferView);
						const auto &buffer = buffers.at(bufferView.buffer);
						size_t offset = bufferView.byteOffset + nrmAccessor.byteOffset;
						size_t stride = nrmAccessor.byteStride;
						assert(stride >= 12);
						assert(nrmAccessor.count == numVertices);
						const auto *data = &buffer.data[offset];

						for (uint32_t i = 0; i < numVertices; ++i)
						{
							const float *nrm = reinterpret_cast<const float *>(&data[stride * i]);
							hostVertices[vertOffset + i].normal = Ogre::Vector3(nrm[0], nrm[1], nrm[2]);
						}
					}
					// Texture coordinates
					{
						const auto &bufferView = bufferViews.at(uvAccessor.bufferView);
						const auto &buffer = buffers.at(bufferView.buffer);
						size_t offset = bufferView.byteOffset + uvAccessor.byteOffset;
						size_t stride = uvAccessor.byteStride;
						assert(stride >= 8);
						assert(uvAccessor.count == numVertices);
						const auto *data = &buffer.data[offset];

						for (uint32_t i = 0; i < numVertices; ++i)
						{
							const float *uv = reinterpret_cast<const float *>(&data[stride * i]);
							hostVertices[vertOffset + i].texCoord = Ogre::Vector2(uv[0], 1.f - uv[1]);
						}
					}
					// Indices
					{
						const auto &bufferView = bufferViews.at(idxAccessor.bufferView);
						const auto &buffer = buffers.at(bufferView.buffer);
						size_t offset = bufferView.byteOffset + idxAccessor.byteOffset;
						const uint16_t *data = reinterpret_cast<const uint16_t *>(&buffer.data[offset]);

						for (uint32_t i = 0; i < numIndices; ++i)
						{
							hostIndices[indexOffset + i] = vertOffset + static_cast<uint32_t>(data[i]);
						}
					}

					vertOffset += numVertices;
					indexOffset += numIndices;
				}

				// create vertex buffer
				retMesh.vertexBuffer = {};
				retMesh.vertexBuffer.size = sizeof(hostVertices[0]) * hostVertices.size();
				//	retMesh.vertexBuffer.buffer = pManager->createBuffer(retMesh.vertexBuffer.size,
				//###			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

				//###		pManager->transferHostDataToBuffer(retMesh.vertexBuffer.buffer, retMesh.vertexBuffer.size, hostVertices.data());

				// create index buffer
				retMesh.indexBuffer = {};
				retMesh.indexBuffer.size = sizeof(hostIndices[0]) * hostIndices.size();
				//###		retMesh.indexBuffer.buffer = pManager->createBuffer(retMesh.indexBuffer.size,
				//###			VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

				//###	pManager->transferHostDataToBuffer(retMesh.indexBuffer.buffer, retMesh.indexBuffer.size, hostIndices.data());
			}
		}
		else
		{
			rj::GLTFScene scene;
			rj::GLTFLoader loader;
			loader.load(&scene, gltfFileName);

			for (const auto &mesh : scene.meshes)
			{
				//###retMeshes.emplace_back(pManager);
				auto &retMesh = retMeshes.back();
				//	auto gliFormat = gli::FORMAT_RGBA8_UNORM_PACK8;

				// Textures
				/*loadTexture2DFromBinaryData(&retMesh.albedoMap, pManager, mesh.albedoMap.pixels.data(),
				mesh.albedoMap.width, mesh.albedoMap.height, gliFormat, mesh.albedoMap.levelCount);

				loadTexture2DFromBinaryData(&retMesh.normalMap, pManager, mesh.normalMap.pixels.data(),
				mesh.normalMap.width, mesh.normalMap.height, gliFormat, mesh.normalMap.levelCount);

				loadTexture2DFromBinaryData(&retMesh.roughnessMap, pManager, mesh.roughnessMap.pixels.data(),
				mesh.roughnessMap.width, mesh.roughnessMap.height, gliFormat, mesh.roughnessMap.levelCount);

				loadTexture2DFromBinaryData(&retMesh.metalnessMap, pManager, mesh.metallicMap.pixels.data(),
				mesh.metallicMap.width, mesh.metallicMap.height, gliFormat, mesh.metallicMap.levelCount);

				if (!mesh.aoMap.pixels.empty())
				{
				loadTexture2DFromBinaryData(&retMesh.aoMap, pManager, mesh.aoMap.pixels.data(),
				mesh.aoMap.width, mesh.aoMap.height, gliFormat, mesh.aoMap.levelCount);
				}

				if (!mesh.emissiveMap.pixels.empty())
				{
				loadTexture2DFromBinaryData(&retMesh.emissiveMap, pManager, mesh.emissiveMap.pixels.data(),
				mesh.emissiveMap.width, mesh.emissiveMap.height, gliFormat, mesh.emissiveMap.levelCount);
				}*/

				// Geometry
				uint32_t vertCount = static_cast<uint32_t>(mesh.positions.size() / 3);
				std::vector<Vertex> hostVertices(vertCount);

				for (int i = 0; i < vertCount; ++i)
				{
					Vertex &vert = hostVertices[i];
					vert.pos = Ogre::Vector3(mesh.positions[3 * i], mesh.positions[3 * i + 1], mesh.positions[3 * i + 2]);
					vert.normal = Ogre::Vector3(mesh.normals[3 * i], mesh.normals[3 * i + 1], mesh.normals[3 * i + 2]);
					vert.texCoord = Ogre::Vector2(mesh.texCoords[i << 1], mesh.texCoords[(i << 1) + 1]);

					retMesh.bounds.max = std::max(retMesh.bounds.max, vert.pos);
					retMesh.bounds.min = std::min(retMesh.bounds.min, vert.pos);
				}

				// create vertex buffer
				retMesh.vertexBuffer = {};
				retMesh.vertexBuffer.size = sizeof(hostVertices[0]) * hostVertices.size();
				//###retMesh.vertexBuffer.buffer = pManager->createBuffer(retMesh.vertexBuffer.size,
				//###	VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

				//###pManager->transferHostDataToBuffer(retMesh.vertexBuffer.buffer, retMesh.vertexBuffer.size, hostVertices.data());

				// create index buffer
				retMesh.indexBuffer = {};
				retMesh.indexBuffer.size = sizeof(mesh.indices[0]) * mesh.indices.size();
				//###	retMesh.indexBuffer.buffer = pManager->createBuffer(retMesh.indexBuffer.size,
				//###	VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

				//###pManager->transferHostDataToBuffer(retMesh.indexBuffer.buffer, retMesh.indexBuffer.size, mesh.indices.data());
			}
		}
	}

	void Asset::load(const std::string& input_filename) {
		
		std::vector<VMesh> meshes;
		/*loadFromGLTF(meshes, input_filename);

		return;*/
		//rj::GLTFLoader rfLoader; // aus einer anderen engine zum test
		//rj::GLTFScene testScene;
		//rfLoader.load(&testScene, "F:/Projekte/coop/obj2gltf/1.gltf");


		std::map<std::string, GLBufferState> gBufferState;
		std::map<std::string, GLMeshState> gMeshState;

		tinygltf::Scene scene;
		tinygltf::TinyGLTFLoader loader;
		std::string err;
		//std::string input_filename = "F:/Projekte/coop/obj2gltf/1.glb"; // (argv[1]);
		//std::string ext = GetFilePathExtension(input_filename);

		bool ret = false;
		//if (ext.compare("glb") == 0) {
			// assume binary glTF.
			ret = loader.LoadBinaryFromFile(&scene, &err, input_filename.c_str());
		//}
		//else {
		//	// assume ascii glTF.
		//	ret = loader.LoadASCIIFromFile(&scene, &err, input_filename.c_str());
		//}

			if (!err.empty()) {
				printf("Err: %s\n", err.c_str());
			}

			if (!ret) {
				printf("Failed to parse glTF\n");
				//return -1;
			}

			std::map<std::string, tinygltf::BufferView>::const_iterator it(
				scene.bufferViews.begin());
			std::map<std::string, tinygltf::BufferView>::const_iterator itEnd(
				scene.bufferViews.end());

			for (; it != itEnd; it++) {
				const tinygltf::BufferView &bufferView = it->second;
				if (bufferView.target == 0) {
					std::cout << "WARN: bufferView.target is zero" << std::endl;
					continue;  // Unsupported bufferView.
				}

				const tinygltf::Buffer &buffer = scene.buffers[bufferView.buffer];

				/*glBufferData(bufferView.target, bufferView.byteLength,
					&buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);*/

				GLBufferState state;
				/*const tinygltf::Buffer &buffer = scene.buffers[bufferView.buffer];
				std::cout << "buffer.size= " << buffer.data.size()
					<< ", byteOffset = " << bufferView.byteOffset << std::endl;
				
				gBufferState[it->first] = state;*/
			}

			std::vector<Vertex> hostVertices;
			std::vector<uint32_t> hostIndices;
			uint32_t vertOffset = 0;
			uint32_t indexOffset = 0;
			const auto &accessors = scene.accessors;
			const auto &bufferViews = scene.bufferViews;
			const auto &buffers = scene.buffers;

			for each (auto& mesh in scene.meshes)
			{
				for each (auto& primitive in mesh.second.primitives)
				{
					
					const auto &posAccessor = scene.accessors.at(primitive.attributes.at("POSITION"));
					const auto &nrmAccessor = scene.accessors.at(primitive.attributes.at("NORMAL"));
					const auto &uvAccessor = scene.accessors.at(primitive.attributes.at("TEXCOORD_0"));
					const auto &idxAccessor = scene.accessors.at(primitive.indices);
					uint32_t numVertices = static_cast<uint32_t>(posAccessor.count);
					hostVertices.resize(hostVertices.size() + numVertices);
					uint32_t numIndices = static_cast<uint32_t>(idxAccessor.count);
					hostIndices.resize(hostIndices.size() + numIndices);

					// Postions
					{
						const auto &bufferView = bufferViews.at(posAccessor.bufferView);
						const auto &buffer = buffers.at(bufferView.buffer);
						size_t offset = bufferView.byteOffset + posAccessor.byteOffset;
						size_t stride = posAccessor.byteStride;
						assert(stride >= 12);
						assert(posAccessor.count == numVertices);
						const auto *data = &buffer.data[offset];

						for (uint32_t i = 0; i < numVertices; ++i)
						{
							const float *pos = reinterpret_cast<const float *>(&data[stride * i]);
							hostVertices[vertOffset + i].pos = Ogre::Vector3(pos[0], pos[1], pos[2]);

					//		retMesh.bounds.max = std::max(retMesh.bounds.max, hostVertices[vertOffset + i].pos);
					//		retMesh.bounds.min = std::min(retMesh.bounds.min, hostVertices[vertOffset + i].pos);
						}
					}
					// Normal
					{
						const auto &bufferView = bufferViews.at(nrmAccessor.bufferView);
						const auto &buffer = buffers.at(bufferView.buffer);
						size_t offset = bufferView.byteOffset + nrmAccessor.byteOffset;
						size_t stride = nrmAccessor.byteStride;
						assert(stride >= 12);
						assert(nrmAccessor.count == numVertices);
						const auto *data = &buffer.data[offset];

						for (uint32_t i = 0; i < numVertices; ++i)
						{
							const float *nrm = reinterpret_cast<const float *>(&data[stride * i]);
							hostVertices[vertOffset + i].normal = Ogre::Vector3(nrm[0], nrm[1], nrm[2]);
						}
					}
					// Texture coordinates
					{
						const auto &bufferView = bufferViews.at(uvAccessor.bufferView);
						const auto &buffer = buffers.at(bufferView.buffer);
						size_t offset = bufferView.byteOffset + uvAccessor.byteOffset;
						size_t stride = uvAccessor.byteStride;
						assert(stride >= 8);
						assert(uvAccessor.count == numVertices);
						const auto *data = &buffer.data[offset];

						for (uint32_t i = 0; i < numVertices; ++i)
						{
							const float *uv = reinterpret_cast<const float *>(&data[stride * i]);
							hostVertices[vertOffset + i].texCoord = Ogre::Vector2(uv[0], 1.f - uv[1]);
						}
					}
					// Indices
					{
						const auto &bufferView = bufferViews.at(idxAccessor.bufferView);
						const auto &buffer = buffers.at(bufferView.buffer);
						size_t offset = bufferView.byteOffset + idxAccessor.byteOffset;
						const uint16_t *data = reinterpret_cast<const uint16_t *>(&buffer.data[offset]);

						for (uint32_t i = 0; i < numIndices; ++i)
						{
							hostIndices[indexOffset + i] = vertOffset + static_cast<uint32_t>(data[i]);
						}
					}

					vertOffset += numVertices;
					indexOffset += numIndices;



					// create vertex buffer
					//______________  retMesh.vertexBuffer = {};
					//______________  retMesh.vertexBuffer.size = sizeof(hostVertices[0]) * hostVertices.size();
					//	retMesh.vertexBuffer.buffer = pManager->createBuffer(retMesh.vertexBuffer.size,
					//###			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

					//###		pManager->transferHostDataToBuffer(retMesh.vertexBuffer.buffer, retMesh.vertexBuffer.size, hostVertices.data());

					// create index buffer
					//______________  retMesh.indexBuffer = {};
					//______________  retMesh.indexBuffer.size = sizeof(hostIndices[0]) * hostIndices.size();
					//###		retMesh.indexBuffer.buffer = pManager->createBuffer(retMesh.indexBuffer.size,
					//###			VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

					//###	pManager->transferHostDataToBuffer(retMesh.indexBuffer.buffer, retMesh.indexBuffer.size, hostIndices.data());


					//-----------------------------------------------------------
					//if (primitive.indices.empty()) return;
				std::map<std::string, std::string>::const_iterator it(
					primitive.attributes.begin());
				std::map<std::string, std::string>::const_iterator itEnd(
					primitive.attributes.end());

				// Assume TEXTURE_2D target for the texture object.
			//	glBindTexture(GL_TEXTURE_2D, gMeshState[mesh.name].diffuseTex[i]);

				for (; it != itEnd; it++) {
					assert(scene.accessors.find(it->second) != scene.accessors.end());
					const tinygltf::Accessor &accessor = scene.accessors[it->second];
				//	glBindBuffer(GL_ARRAY_BUFFER, gBufferState[accessor.bufferView].vb);
			//		CheckErrors("bind buffer");
					int count = 1;
					if (accessor.type == TINYGLTF_TYPE_SCALAR) {
						count = 1;
					}
					else if (accessor.type == TINYGLTF_TYPE_VEC2) {
						count = 2;
					}
					else if (accessor.type == TINYGLTF_TYPE_VEC3) {
						count = 3;
					}
					else if (accessor.type == TINYGLTF_TYPE_VEC4) {
						count = 4;
					}
					else {
						assert(0);
					}

					// it->first would be "POSITION", "NORMAL", "TEXCOORD_0", ...
					if ((it->first.compare("POSITION") == 0) ||
						(it->first.compare("NORMAL") == 0) ||
						(it->first.compare("TEXCOORD_0") == 0)) {

					//	if (gGLProgramState.attribs[it->first] >= 0) {
					//		glVertexAttribPointer(gGLProgramState.attribs[it->first], count,
					//			accessor.componentType, GL_FALSE,
					//			accessor.byteStride,
					//			BUFFER_OFFSET(accessor.byteOffset));
					//	//	CheckErrors("vertex attrib pointer");
					////		glEnableVertexAttribArray(gGLProgramState.attribs[it->first]);
					////		CheckErrors("enable vertex attrib array");
					//	}
					}
				}

			}
			
		}


		//scene.meshes[""].primitives[0].
		//auto data = scene.buffers[""].data;
	}

//	MaterialType_t materialType = MATERIAL_TYPE_FSCHLICK_DGGX_GSMITH;
	
} // ns glTF
