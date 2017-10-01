#ifndef glTFAsset_H_INC
#define glTFAsset_H_INC

#include <map>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <exception>
#include <unordered_map>


namespace gltf
{
	class MisformattedException : public std::exception {
	public:
		explicit MisformattedException(const char* key, const char* what) {
			_what = std::string("Misformated file: '") + key + "' " + what;
		}
		explicit MisformattedException(const std::string& key, const std::string& what) {
			_what = "Misformated file: '" + key + "' " + what;
		}
		virtual ~MisformattedException() throw() {}

		virtual const char* what() const throw() {
			return _what.c_str();
		}

	protected:
		std::string _what;
	};


	class MisformattedExceptionNotNumber : public MisformattedException {
	public:
		explicit MisformattedExceptionNotNumber(const char* key) : MisformattedException(key, "is not a number") {}
		explicit MisformattedExceptionNotNumber(const std::string& key) : MisformattedException(key, "is not a number") {}
		virtual ~MisformattedExceptionNotNumber() throw() {}
	};

	class MisformattedExceptionNotBoolean : public MisformattedException {
	public:
		explicit MisformattedExceptionNotBoolean(const char* key) : MisformattedException(key, "is not a boolean") {}
		explicit MisformattedExceptionNotBoolean(const std::string& key) : MisformattedException(key, "is not a boolean") {}
		virtual ~MisformattedExceptionNotBoolean() throw() {}
	};

	class MisformattedExceptionNotString : public MisformattedException {
	public:
		explicit MisformattedExceptionNotString(const char* key) : MisformattedException(key, "is not a string") {}
		explicit MisformattedExceptionNotString(const std::string& key) : MisformattedException(key, "is not a string") {}
		virtual ~MisformattedExceptionNotString() throw() {}
	};

	class MisformattedExceptionNotArray : public MisformattedException {
	public:
		explicit MisformattedExceptionNotArray(const char* key) : MisformattedException(key, "is not an array") {}
		explicit MisformattedExceptionNotArray(const std::string& key) : MisformattedException(key, "is not an array") {}
		virtual ~MisformattedExceptionNotArray() throw() {}
	};

	class MisformattedExceptionNotGoodSizeArray : public MisformattedException {
	public:
		explicit MisformattedExceptionNotGoodSizeArray(const char* key) : MisformattedException(key, "is not the good size") {}
		explicit MisformattedExceptionNotGoodSizeArray(const std::string& key) : MisformattedException(key, "is not the good size") {}
		virtual ~MisformattedExceptionNotGoodSizeArray() throw() {}
	};

	class MisformattedExceptionNotObject : public MisformattedException {
	public:
		explicit MisformattedExceptionNotObject(const char* key) : MisformattedException(key, "is not an array") {}
		explicit MisformattedExceptionNotObject(const std::string& key) : MisformattedException(key, "is not an array") {}
		virtual ~MisformattedExceptionNotObject() throw() {}
	};

	class MisformattedExceptionIsRequired : public MisformattedException {
	public:
		explicit MisformattedExceptionIsRequired(const char* key) : MisformattedException(key, "is required") {}
		explicit MisformattedExceptionIsRequired(const std::string& key) : MisformattedException(key, "is required") {}
		virtual ~MisformattedExceptionIsRequired() throw() {}
	};


	using Attributes = std::unordered_map<std::string, std::uint32_t>;

	struct SceneGLTF {
		std::string name;

		std::vector<std::uint32_t> nodes;

		// extensions / extras
	};

	struct Primitive {
		int32_t indices = -1; // Index to accessor containing the indices
		int32_t material = -1; // Index to the material

		enum class Mode : uint8_t {
			Points = 0,
			Lines = 1,
			LineLoop = 2,
			LineStrip = 3,
			Triangles = 4,
			TriangleStrip = 5,
			TriangleFan = 6
		} mode = Mode::Triangles; // primitive type

		Attributes attributes; // Each attribute is mapped with his name and accessor index to the data
		std::vector<Attributes> targets;

		// extensions / extras
	};

	/**
	* @brief      Describes part of a Mesh.
	*/
	struct PrimitiveSet {
		struct Attribute {
			enum class Type : uint8_t {
				Indice,     ///< Indices (UNSIGNED_SHORT)
				Position,   ///< Position (VEC3<FLOAT>)
				Normal,     ///< Normal (VEC3<FLOAT>)
				TexCoord,   ///< UV (VEC2<FLOAT>)
				Tangent,    ///< Tangent (VEC4<FLOAT> w component is a sign value (-1 or +1) indicating handedness of the tangent basis)
				Color,      ///< Color (VEC4<FLOAT>)
			} type;

			/**
			* @brief      Access to the data of the attribute.
			*/
			struct Buffer {
				char* data{ nullptr };        ///< The data of the buffer.
				uint32_t size{ 0 };           ///< The size of the above data buffer, in bytes.
				uint32_t elementsCount{ 0 };  ///< The number of elements (indices, vertices, normals)
			} buffer;

			void* _data{ nullptr }; // Specific to each Renderer
		};

		/**
		* @brief      Type of the primitive set, defaults to Triangles.
		*/
		enum class Mode : uint8_t {
			Points = 0,         ///< Each vertex defines a separate point
			Lines = 1,          ///< The first two vertices define the first segment, with subsequent pairs of vertices each defining one more segment
			LineStrip = 3,      ///< The first vertex specifies the first segment’s start point while the second vertex specifies the first segment’s endpoint and the second segment’s start point
			Triangles = 4,      ///<
			TriangleStrip = 5,  ///<
			TriangleFan = 6     ///<
		} mode{ Mode::Triangles };

		std::vector<Attribute> attributes{};

		Attribute* indices{ nullptr };
		Attribute* position{ nullptr };
		Attribute* normal{ nullptr };
		std::vector<Attribute*> texCoords{};
		std::vector<Attribute*> colors{};
		Attribute* tangent{ nullptr };

		//TODO Resource::SharedPtr<Material> material{ nullptr };

		void* _data{ nullptr }; // Specific to each Renderer
	};

	struct Mesh {
		std::string name;

		std::vector<float> weights;
		std::vector<Primitive> primitives;

		// extensions / extras
		std::vector<PrimitiveSet> primitiveSets;

	};

	struct Buffer {
		std::string name;

		std::string uri;
		std::uint32_t byteLength = 0;

		char* data = nullptr;

		// content

		// extensions / extras
	};

	struct BufferView {
		std::string name;

		std::uint32_t buffer; // Index to the buffer
		std::uint32_t byteOffset = 0;
		std::uint32_t byteLength = 0;
		std::uint32_t byteStride = 0; // The stride, in bytes

		enum class TargetType : uint16_t {
			None = 0,
			ArrayBuffer = 34962,
			ElementArrayBuffer = 34963
		} target; // The target that the GPU buffer should be bound to.

				  // extensions / extras
	};

	struct Texture {
		std::string name;

		int32_t sampler{ -1 };
		int32_t source{ -1 };
	};

	struct Sampler {
		std::string name;

		enum class MagFilter : uint16_t {
			None,
			Nearest = 9728,
			Linear = 9729
		} magFilter{ MagFilter::None };

		enum class MinFilter : uint16_t {
			None,
			Nearest = 9728,
			Linear = 9729,
			NearestMipMapNearest = 9984,
			LinearMipMapNearest = 9985,
			NearestMipMapLinear = 9986,
			LinearMipMapLinear = 9987
		} minFilter{ MinFilter::None };

		enum class WrappingMode : uint16_t {
			ClampToEdge = 33071,
			MirroredRepeat = 33648,
			Repeat = 10497
		};

		WrappingMode wrapS{ WrappingMode::Repeat };
		WrappingMode wrapT{ WrappingMode::Repeat };
	};

	struct ImageGLTF {
		std::string name;

		std::string uri;

		std::string mimeType;
		int32_t bufferView{ -1 };
	};

	struct Material {
		std::string name;

		struct Texture {
			int32_t index{ -1 };
			std::uint32_t texCoord{ 0 };
		};

		struct Pbr {
			float baseColorFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			Texture baseColorTexture;

			float metallicFactor{ 1.0f };
			float roughnessFactor{ 1.0f };
			Texture metallicRoughnessTexture;
		} pbr;

		struct NormalTexture : Texture {
			float scale{ 1.0f };
		} normalTexture;

		struct OcclusionTexture : Texture {
			float strength{ 1.0f };
		} occlusionTexture;

		Texture emissiveTexture;

		float emissiveFactor[3] = { 0.0f, 0.0f, 0.0f };

		enum class AlphaMode : uint8_t {
			Opaque,
			Mask,
			Blend
		} alphaMode{ AlphaMode::Opaque };

		float alphaCutoff{ 0.5f };
		bool doubleSided{ false };
	};

	struct NodeGLTF {
		std::string name;

		int32_t camera = -1;
		int32_t mesh = -1;
		int32_t skin = -1;

		std::vector<int> children;

		float matrix[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		float rotation[4] = { 0, 0, 0, 1 };
		float scale[3] = { 1, 1, 1 };
		float translation[3] = { 0, 0, 0 };

		std::vector<float> weights;

		// extensions / extras
	};

	struct Accessor {
		std::string name;

		int32_t bufferView = -1;
		std::uint32_t byteOffset = 0;

		enum class ComponentType : uint16_t {
			Byte = 5120,
			UnsignedByte = 5121,
			Short = 5122,
			UnsignedShort = 5123,
			UnsignedInt = 5125,
			Float = 5126
		} componentType;

		bool normalized = false;

		std::uint32_t count;

		enum class Type : uint8_t {
			Scalar,
			Vec2,
			Vec3,
			Vec4,
			Mat2,
			Mat3,
			Mat4
		} type;

		// max / min / sparse
		// extensions / extras
	};

	struct Asset {
		struct Metadata {
			std::string copyright;
			std::string generator;
			std::string version;
			std::string minVersion;

			// extensions / extras
		} metadata;

		std::vector<std::string> extensionsUsed;
		std::vector<std::string> extensionRequired;

		std::vector<Accessor> accessors;
		// std::vector<Animation> animations;
		std::vector<Buffer> buffers;
		std::vector<BufferView> bufferViews;
		// std::vector<Camera> cameras;
		std::vector<ImageGLTF> images;
		std::vector<Material> materials;
		std::vector<Mesh> meshes;
		std::vector<NodeGLTF> nodes;
		std::vector<Sampler> samplers;
		int32_t scene = -1; // Index to the default scene
		std::vector<SceneGLTF> scenes;
		// std::vector<Skin> skins;
		std::vector<Texture> textures;

		// extensions / extras

		std::string dirName;

		SceneGLTF* getDefaultScene() const;
	};

	/**
	* @brief      Load a glTF v2.0 asset from a file
	*
	* @param[in]  fileName  The file name
	*
	* @return     The asset
	*/
	void load(std::string fileName, Asset& asset);


	uint32_t getAttributeSize(const Accessor& accessor);

	void* getBufferViewData(const Asset& asset, const Accessor& accessor);

	void* generateNormals(float* positions, uint32_t accessorCount);
}

#endif
