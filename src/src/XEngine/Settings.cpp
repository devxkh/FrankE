#include <XEngine/Settings.hpp>

#include <XEDAL/PhysFS/PhysFsStream.hpp>


#include <XEDAL/PhysFS/PhysFSArchive.h>

namespace XE {
	

	Settings::Settings()  {
		
	}

	Settings::~Settings() {

	}

	void Settings::load(const std::string& dataRootFolder) {

		this->dataRootFolder = dataRootFolder;

		PhysFS::addToSearchPath(dataRootFolder, true);
		
		PhysFsStream wonderfullStream;
		if (!wonderfullStream.open("settings.fbbin"))
			return;

		// Make sure that the stream's reading position is at the beginning
		wonderfullStream.seek(0);

		m_buffer.resize(wonderfullStream.getSize());
		if (!wonderfullStream.read(m_buffer.data(), wonderfullStream.getSize()))
			return;

		//m_buffer = &buffer[0];

		//auto settings = FBSettings::GetSettings(&buffer[0]);
		//auto dbDataFolder = settings->resourceData()->dbDataFolder()->c_str();
		//auto assetsFolder = settings->resourceData()->assetsFolder()->c_str();
		//auto dbFileName = settings->resourceData()->dbFileName()->c_str();
		//auto hlmsDataFolder = settings->resourceData()->hlmsDataFolder()->c_str();
		//auto windowTitle = settings->windowTitle()->c_str();
	}
	
	const FBSettings::Settings* Settings::FBSettings()
	{
		return FBSettings::GetSettings(&m_buffer[0]);
	}


} //ns XE