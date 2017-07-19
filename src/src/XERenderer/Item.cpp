#include <Ogre/OgreMain/include/OgreSubMesh2.h>
#include <Ogre/OgreMain/include/OgreMeshManager2.h>
#include <Ogre/OgreMain/include/OgreMesh2.h>
#include <Ogre/OgreMain/include/Vao/OgreVaoManager.h>
#include <Ogre/OgreMain/include/OgreSceneManager.h>

#include <Ogre/Components/Hlms/Common/include/OgreHlmsBufferManager.h>
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlit.h>
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitDatablock.h>

#include <Ogre/OgreMain/include/OgreItem.h>
#include <Ogre/OgreMain/include/OgreRoot.h>

#include <XERenderer\gltfAsset.h>

namespace XE
{ 
	

	class Item {

	public:
		void load();

	private:
		Ogre::SceneManager* sceneManager;
		
		Ogre::VertexBufferPacked *pVertexBuffer;
		int vertexCount;
		Ogre::Item *item;
		int vertIndex;
		Ogre::VertexArrayObject *vao;
	};

	
//
//
//	void Item::ImportglTFMesh(glTF::Asset& r)
//	{
//		std::vector<aiMesh*> meshes;
//
//		unsigned int k = 0;
//
//		for (unsigned int m = 0; m < r.meshes.Size(); ++m) {
//			Mesh& mesh = r.meshes[m];
//
//			// Check if mesh extensions is used
//			if (mesh.Extension.size() > 0)
//			{
//				for (Mesh::SExtension* cur_ext : mesh.Extension)
//				{
//#ifdef ASSIMP_IMPORTER_GLTF_USE_OPEN3DGC
//					if (cur_ext->Type == Mesh::SExtension::EType::Compression_Open3DGC)
//					{
//						// Limitations for meshes when using Open3DGC-compression.
//						// It's a current limitation of sp... Specification have not this part still - about mesh compression. Why only one primitive?
//						// Because glTF is very flexibly. But in fact it ugly flexible. Every primitive can has own set of accessors and accessors can
//						// point to a-a-a-a-any part of buffer (through bufferview of course) and even to another buffer. We know that "Open3DGC-compression"
//						// is applicable only to part of buffer. As we can't guaranty continuity of the data for decoder, we will limit quantity of primitives.
//						// Yes indices, coordinates etc. still can br stored in different buffers, but with current specification it's a exporter problem.
//						// Also primitive can has only one of "POSITION", "NORMAL" and less then "AI_MAX_NUMBER_OF_TEXTURECOORDS" of "TEXCOORD". All accessor
//						// of primitive must point to one continuous region of the buffer.
//						if (mesh.primitives.size() > 2) throw DeadlyImportError("GLTF: When using Open3DGC compression then only one primitive per mesh are allowed.");
//
//						Mesh::SCompression_Open3DGC* o3dgc_ext = (Mesh::SCompression_Open3DGC*)cur_ext;
//						Ref<Buffer> buf = r.buffers.Get(o3dgc_ext->Buffer);
//
//						buf->EncodedRegion_SetCurrent(mesh.id);
//					}
//					else
//#endif
//					{
//						throw DeadlyImportError("GLTF: Can not import mesh: unknown mesh extension (code: \"" + to_string(cur_ext->Type) +
//							"\"), only Open3DGC is supported.");
//					}
//				}
//			}// if(mesh.Extension.size() > 0)
//
//			meshOffsets.push_back(k);
//			k += unsigned(mesh.primitives.size());
//
//			for (unsigned int p = 0; p < mesh.primitives.size(); ++p) {
//				Mesh::Primitive& prim = mesh.primitives[p];
//
//				aiMesh* aim = new aiMesh();
//				meshes.push_back(aim);
//
//				aim->mName = mesh.id;
//				if (mesh.primitives.size() > 1) {
//					size_t& len = aim->mName.length;
//					aim->mName.data[len] = '-';
//					len += 1 + ASSIMP_itoa10(aim->mName.data + len + 1, unsigned(MAXLEN - len - 1), p);
//				}
//
//				switch (prim.mode) {
//				case PrimitiveMode_POINTS:
//					aim->mPrimitiveTypes |= aiPrimitiveType_POINT;
//					break;
//
//				case PrimitiveMode_LINES:
//				case PrimitiveMode_LINE_LOOP:
//				case PrimitiveMode_LINE_STRIP:
//					aim->mPrimitiveTypes |= aiPrimitiveType_LINE;
//					break;
//
//				case PrimitiveMode_TRIANGLES:
//				case PrimitiveMode_TRIANGLE_STRIP:
//				case PrimitiveMode_TRIANGLE_FAN:
//					aim->mPrimitiveTypes |= aiPrimitiveType_TRIANGLE;
//					break;
//				}
//
//				Mesh::Primitive::Attributes& attr = prim.attributes;
//
//				if (attr.position.size() > 0 && attr.position[0]) {
//					aim->mNumVertices = attr.position[0]->count;
//					attr.position[0]->ExtractData(aim->mVertices);
//				}
//
//				if (attr.normal.size() > 0 && attr.normal[0]) attr.normal[0]->ExtractData(aim->mNormals);
//
//				for (size_t tc = 0; tc < attr.texcoord.size() && tc < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++tc) {
//					attr.texcoord[tc]->ExtractData(aim->mTextureCoords[tc]);
//					aim->mNumUVComponents[tc] = attr.texcoord[tc]->GetNumComponents();
//
//					aiVector3D* values = aim->mTextureCoords[tc];
//					for (unsigned int i = 0; i < aim->mNumVertices; ++i) {
//						values[i].y = 1 - values[i].y; // Flip Y coords
//					}
//				}
//
//
//				if (prim.indices) {
//					aiFace* faces = 0;
//					unsigned int nFaces = 0;
//
//					unsigned int count = prim.indices->count;
//
//					Accessor::Indexer data = prim.indices->GetIndexer();
//					ai_assert(data.IsValid());
//
//					switch (prim.mode) {
//					case PrimitiveMode_POINTS: {
//						nFaces = count;
//						faces = new aiFace[nFaces];
//						for (unsigned int i = 0; i < count; ++i) {
//							SetFace(faces[i], data.GetUInt(i));
//						}
//						break;
//					}
//
//					case PrimitiveMode_LINES: {
//						nFaces = count / 2;
//						faces = new aiFace[nFaces];
//						for (unsigned int i = 0; i < count; i += 2) {
//							SetFace(faces[i / 2], data.GetUInt(i), data.GetUInt(i + 1));
//						}
//						break;
//					}
//
//					case PrimitiveMode_LINE_LOOP:
//					case PrimitiveMode_LINE_STRIP: {
//						nFaces = count - ((prim.mode == PrimitiveMode_LINE_STRIP) ? 1 : 0);
//						faces = new aiFace[nFaces];
//						SetFace(faces[0], data.GetUInt(0), data.GetUInt(1));
//						for (unsigned int i = 2; i < count; ++i) {
//							SetFace(faces[i - 1], faces[i - 2].mIndices[1], data.GetUInt(i));
//						}
//						if (prim.mode == PrimitiveMode_LINE_LOOP) { // close the loop
//							SetFace(faces[count - 1], faces[count - 2].mIndices[1], faces[0].mIndices[0]);
//						}
//						break;
//					}
//
//					case PrimitiveMode_TRIANGLES: {
//						nFaces = count / 3;
//						faces = new aiFace[nFaces];
//						for (unsigned int i = 0; i < count; i += 3) {
//							SetFace(faces[i / 3], data.GetUInt(i), data.GetUInt(i + 1), data.GetUInt(i + 2));
//						}
//						break;
//					}
//					case PrimitiveMode_TRIANGLE_STRIP: {
//						nFaces = count - 2;
//						faces = new aiFace[nFaces];
//						SetFace(faces[0], data.GetUInt(0), data.GetUInt(1), data.GetUInt(2));
//						for (unsigned int i = 3; i < count; ++i) {
//							SetFace(faces[i - 2], faces[i - 1].mIndices[1], faces[i - 1].mIndices[2], data.GetUInt(i));
//						}
//						break;
//					}
//					case PrimitiveMode_TRIANGLE_FAN:
//						nFaces = count - 2;
//						faces = new aiFace[nFaces];
//						SetFace(faces[0], data.GetUInt(0), data.GetUInt(1), data.GetUInt(2));
//						for (unsigned int i = 3; i < count; ++i) {
//							SetFace(faces[i - 2], faces[0].mIndices[0], faces[i - 1].mIndices[2], data.GetUInt(i));
//						}
//						break;
//					}
//
//					if (faces) {
//						aim->mFaces = faces;
//						aim->mNumFaces = nFaces;
//						ai_assert(CheckValidFacesIndices(faces, nFaces, aim->mNumVertices));
//					}
//				}
//
//
//				if (prim.material) {
//					aim->mMaterialIndex = prim.material.GetIndex();
//				}
//			}
//		}
//
//		meshOffsets.push_back(k);
//
//		CopyVector(meshes, mScene->mMeshes, mScene->mNumMeshes);
//	}
//
//
	void Item::load() {

		//glTF::IOStream * pIOHandler;

	//	glTF::IOSystem* pIOHandler;

		// read the asset file
	//	glTF::Asset asset(pIOHandler);
	//	asset.Load("", true);// GetExtension(pFile) == "glb");

//
//		vertIndex = 0;
//		vertexCount = 0;
//		sceneManager = Ogre::Root::getSingletonPtr()->getSceneManager("SceneManager");
//
//		Ogre::String datablockName = "DebugLineMat";
//		Ogre::HlmsUnlitDatablock *datablock = static_cast<Ogre::HlmsUnlitDatablock*>(yGraphicsSystem::getSingleton().getHlmsUnlit()->createDatablock(datablockName,
//			datablockName,
//			Ogre::HlmsMacroblock(),
//			Ogre::HlmsBlendblock(),
//			Ogre::HlmsParamVec()));
//
//		vertexCount = 0;
//		int maxVertexCount = 10000000;
//
//
//		Ogre::Root *root = Ogre::Root::getSingletonPtr();
//		Ogre::RenderSystem *renderSystem = root->getRenderSystem();
//		Ogre::VaoManager *vaoManager = renderSystem->getVaoManager();
//
//		Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual("PhysicsDebuggingMesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//
//		Ogre::SubMesh *subMesh = mesh->createSubMesh();
//
//		Ogre::VertexElement2Vec vertexElements;
//		vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT3, Ogre::VES_POSITION));
//		vertexElements.push_back(Ogre::VertexElement2(Ogre::VET_FLOAT3, Ogre::VES_DIFFUSE));
//
//		size_t vertexSize = vaoManager->calculateVertexSize(vertexElements);
//
//		Ogre::Real* vertexData = static_cast<Ogre::Real*>(OGRE_MALLOC_SIMD(vertexSize * maxVertexCount, Ogre::MEMCATEGORY_GEOMETRY));
//
//		Ogre::VertexBufferPackedVec vertexBuffers;
//
//		pVertexBuffer = vaoManager->createVertexBuffer(vertexElements, maxVertexCount, Ogre::BT_DYNAMIC_PERSISTENT, vertexData, false);
//		vertexBuffers.push_back(pVertexBuffer);
//
//
//		vao = vaoManager->createVertexArrayObject(
//			vertexBuffers, 0, Ogre::OperationType::OT_LINE_LIST);
//
//		subMesh->mVao[0].push_back(vao);
//		subMesh->mVao[1].push_back(vao);
//
//
//		mesh->_setBounds(Ogre::Aabb::BOX_INFINITE);
//
//
//		item = sceneManager->createItem(mesh, Ogre::SCENE_DYNAMIC);
//		item->setDatablock(datablock);
//		item->setCastShadows(false);
//		Ogre::SceneNode *sceneNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
//		sceneNode->attachObject(item);
//
//		Ogre::Real* vertexBufferCursor = reinterpret_cast<Ogre::Real*>(pVertexBuffer->map(0, pVertexBuffer->getNumElements()));
//
//
//		if (pVertexBuffer->isCurrentlyMapped()) {
//
//			//position
//			*vertexBufferCursor++ = vertex.position.x;
//			*vertexBufferCursor++ = vertex.position.y;
//			*vertexBufferCursor++ = vertex.position.z;
//
//			aabb.merge(vertex.position);
//
//			//color
//			*vertexBufferCursor++ = vertex.colour.r;
//			*vertexBufferCursor++ = vertex.colour.g;
//			*vertexBufferCursor++ = vertex.colour.b;
//			*vertexBufferCursor++ = vertex.colour.a;
//
//			//texture
//			*vertexBufferCursor++ = vertex.uv.x;
//			*vertexBufferCursor++ = vertex.uv.y;
//
//			vertexCount += 2;
//
//			vao->setPrimitiveRange(0, vertexCount);
//		}
//
//		if (pVertexBuffer->isCurrentlyMapped()) pVertexBuffer->unmap(Ogre::UO_KEEP_PERSISTENT);
//
//
	}

//#ifndef ASSIMP_IMPORTER_GLTF_USE_OPEN3DGC
//	inline void Item::Decode_O3DGC(const SCompression_Open3DGC& pCompression_Open3DGC, Asset& pAsset_Root)
//	{
//		typedef unsigned short IndicesType;///< \sa glTFExporter::ExportMeshes.
//
//		o3dgc::SC3DMCDecoder<IndicesType> decoder;
//		o3dgc::IndexedFaceSet<IndicesType> ifs;
//		o3dgc::BinaryStream bstream;
//		uint8_t* decoded_data;
//		size_t decoded_data_size = 0;
//		Ref<Buffer> buf = pAsset_Root.buffers.Get(pCompression_Open3DGC.Buffer);
//
//		// Read data from buffer and place it in BinaryStream for decoder.
//		// Just "Count" because always is used type equivalent to uint8_t.
//		bstream.LoadFromBuffer(&buf->GetPointer()[pCompression_Open3DGC.Offset], static_cast<unsigned long>(pCompression_Open3DGC.Count));
//
//		// After decoding header we can get size of primitives.
//		if (decoder.DecodeHeader(ifs, bstream) != o3dgc::O3DGC_OK) throw DeadlyImportError("GLTF: can not decode Open3DGC header.");
//
//		/****************** Get sizes of arrays and check sizes ******************/
//		// Note. See "Limitations for meshes when using Open3DGC-compression".
//
//		// Indices
//		size_t size_coordindex = ifs.GetNCoordIndex() * 3;// See float attributes note.
//
//		if (primitives[0].indices->count != size_coordindex)
//			throw DeadlyImportError("GLTF: Open3DGC. Compressed indices count (" + std::to_string(size_coordindex) +
//				") not equal to uncompressed (" + std::to_string(primitives[0].indices->count) + ").");
//
//		size_coordindex *= sizeof(IndicesType);
//		// Coordinates
//		size_t size_coord = ifs.GetNCoord();// See float attributes note.
//
//		if (primitives[0].attributes.position[0]->count != size_coord)
//			throw DeadlyImportError("GLTF: Open3DGC. Compressed positions count (" + std::to_string(size_coord) +
//				") not equal to uncompressed (" + std::to_string(primitives[0].attributes.position[0]->count) + ").");
//
//		size_coord *= 3 * sizeof(float);
//		// Normals
//		size_t size_normal = ifs.GetNNormal();// See float attributes note.
//
//		if (primitives[0].attributes.normal[0]->count != size_normal)
//			throw DeadlyImportError("GLTF: Open3DGC. Compressed normals count (" + std::to_string(size_normal) +
//				") not equal to uncompressed (" + std::to_string(primitives[0].attributes.normal[0]->count) + ").");
//
//		size_normal *= 3 * sizeof(float);
//		// Additional attributes.
//		std::vector<size_t> size_floatattr;
//		std::vector<size_t> size_intattr;
//
//		size_floatattr.resize(ifs.GetNumFloatAttributes());
//		size_intattr.resize(ifs.GetNumIntAttributes());
//
//		decoded_data_size = size_coordindex + size_coord + size_normal;
//		for (size_t idx = 0, idx_end = size_floatattr.size(), idx_texcoord = 0; idx < idx_end; idx++)
//		{
//			// size = number_of_elements * components_per_element * size_of_component.
//			// Note. But as you can see above, at first we are use this variable in meaning "count". After checking count of objects...
//			size_t tval = ifs.GetNFloatAttribute(static_cast<unsigned long>(idx));
//
//			switch (ifs.GetFloatAttributeType(static_cast<unsigned long>(idx)))
//			{
//			case o3dgc::O3DGC_IFS_FLOAT_ATTRIBUTE_TYPE_TEXCOORD:
//				// Check situation when encoded data contain texture coordinates but primitive not.
//				if (idx_texcoord < primitives[0].attributes.texcoord.size())
//				{
//					if (primitives[0].attributes.texcoord[idx]->count != tval)
//						throw DeadlyImportError("GLTF: Open3DGC. Compressed texture coordinates count (" + std::to_string(tval) +
//							") not equal to uncompressed (" + std::to_string(primitives[0].attributes.texcoord[idx]->count) + ").");
//
//					idx_texcoord++;
//				}
//				else
//				{
//					ifs.SetNFloatAttribute(static_cast<unsigned long>(idx), 0ul);// Disable decoding this attribute.
//				}
//
//				break;
//			default:
//				throw DeadlyImportError("GLTF: Open3DGC. Unsupported type of float attribute: " + to_string(ifs.GetFloatAttributeType(static_cast<unsigned long>(idx))));
//			}
//
//			tval *= ifs.GetFloatAttributeDim(static_cast<unsigned long>(idx)) * sizeof(o3dgc::Real);// After checking count of objects we can get size of array.
//			size_floatattr[idx] = tval;
//			decoded_data_size += tval;
//		}
//
//		for (size_t idx = 0, idx_end = size_intattr.size(); idx < idx_end; idx++)
//		{
//			// size = number_of_elements * components_per_element * size_of_component. See float attributes note.
//			size_t tval = ifs.GetNIntAttribute(static_cast<unsigned long>(idx));
//			switch (ifs.GetIntAttributeType(static_cast<unsigned long>(idx)))
//			{
//			case o3dgc::O3DGC_IFS_INT_ATTRIBUTE_TYPE_UNKOWN:
//			case o3dgc::O3DGC_IFS_INT_ATTRIBUTE_TYPE_INDEX:
//			case o3dgc::O3DGC_IFS_INT_ATTRIBUTE_TYPE_JOINT_ID:
//			case o3dgc::O3DGC_IFS_INT_ATTRIBUTE_TYPE_INDEX_BUFFER_ID:
//				break;
//
//			default:
//				throw DeadlyImportError("GLTF: Open3DGC. Unsupported type of int attribute: " + to_string(ifs.GetIntAttributeType(static_cast<unsigned long>(idx))));
//			}
//
//			tval *= ifs.GetIntAttributeDim(static_cast<unsigned long>(idx)) * sizeof(long);// See float attributes note.
//			size_intattr[idx] = tval;
//			decoded_data_size += tval;
//		}
//
//		// Create array for decoded data.
//		decoded_data = new uint8_t[decoded_data_size];
//
//		/****************** Set right array regions for decoder ******************/
//
//		auto get_buf_offset = [](Ref<Accessor>& pAccessor) -> size_t { return pAccessor->byteOffset + pAccessor->bufferView->byteOffset; };
//
//		// Indices
//		ifs.SetCoordIndex((IndicesType* const)(decoded_data + get_buf_offset(primitives[0].indices)));
//		// Coordinates
//		ifs.SetCoord((o3dgc::Real* const)(decoded_data + get_buf_offset(primitives[0].attributes.position[0])));
//		// Normals
//		if (size_normal)
//		{
//			ifs.SetNormal((o3dgc::Real* const)(decoded_data + get_buf_offset(primitives[0].attributes.normal[0])));
//		}
//
//		for (size_t idx = 0, idx_end = size_floatattr.size(), idx_texcoord = 0; idx < idx_end; idx++)
//		{
//			switch (ifs.GetFloatAttributeType(static_cast<unsigned long>(idx)))
//			{
//			case o3dgc::O3DGC_IFS_FLOAT_ATTRIBUTE_TYPE_TEXCOORD:
//				if (idx_texcoord < primitives[0].attributes.texcoord.size())
//				{
//					// See above about absent attributes.
//					ifs.SetFloatAttribute(static_cast<unsigned long>(idx), (o3dgc::Real* const)(decoded_data + get_buf_offset(primitives[0].attributes.texcoord[idx])));
//					idx_texcoord++;
//				}
//
//				break;
//			default:
//				throw DeadlyImportError("GLTF: Open3DGC. Unsupported type of float attribute: " + to_string(ifs.GetFloatAttributeType(static_cast<unsigned long>(idx))));
//			}
//		}
//
//		for (size_t idx = 0, idx_end = size_intattr.size(); idx < idx_end; idx++) {
//			switch (ifs.GetIntAttributeType(static_cast<unsigned int>(idx))) {
//			case o3dgc::O3DGC_IFS_INT_ATTRIBUTE_TYPE_UNKOWN:
//			case o3dgc::O3DGC_IFS_INT_ATTRIBUTE_TYPE_INDEX:
//			case o3dgc::O3DGC_IFS_INT_ATTRIBUTE_TYPE_JOINT_ID:
//			case o3dgc::O3DGC_IFS_INT_ATTRIBUTE_TYPE_INDEX_BUFFER_ID:
//				break;
//
//				// ifs.SetIntAttribute(idx, (long* const)(decoded_data + get_buf_offset(primitives[0].attributes.joint)));
//			default:
//				throw DeadlyImportError("GLTF: Open3DGC. Unsupported type of int attribute: " + to_string(ifs.GetIntAttributeType(static_cast<unsigned long>(idx))));
//			}
//		}
//
//		//
//		// Decode data
//		//
//		if (decoder.DecodePayload(ifs, bstream) != o3dgc::O3DGC_OK) {
//			throw DeadlyImportError("GLTF: can not decode Open3DGC data.");
//		}
//
//		// Set encoded region for "buffer".
//		buf->EncodedRegion_Mark(pCompression_Open3DGC.Offset, pCompression_Open3DGC.Count, decoded_data, decoded_data_size, id);
//		// No. Do not delete "output_data". After calling "EncodedRegion_Mark" bufferView is owner of "output_data".
//		// "delete [] output_data;"
//	}
//#endif

}