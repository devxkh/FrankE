#pragma once

#include <string>

namespace XE
{
	class ResourceManager
	{
	public:
		void _t_addLocationForRender(const std::string& location, const std::string& group, bool recursive = true, bool readOnly = true , const std::string& locType = "FileSystem");
		void _t_initResourceGroup(const std::string& nameOfResourceGroup);
		void _t_registerHLMSResources();
	};
}