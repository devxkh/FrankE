#pragma once

#include <string>
#include <memory>
#include <vector>

namespace XE
{
	struct FileResource {
		FileResource()
		: buffer(nullptr){}

		std::vector<char> bufferVec;
		void* buffer;
	};

	class ResourceManager
	{
	public:
		void _t_addLocationForRender(const std::string& location, const std::string& group, bool recursive = true, bool readOnly = true , const std::string& locType = "FileSystem");
		void _t_initResourceGroup(const std::string& nameOfResourceGroup);
		void _t_registerHLMSResources();

		void getBufferFromFile(const std::string& filePath, FileResource& res);
	};
}