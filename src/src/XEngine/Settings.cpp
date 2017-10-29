#include <XEngine/Settings.hpp>

#include <XEDAL/PhysFS/PhysFsStream.hpp>


#include <XEDAL/PhysFS/PhysFSArchive.h>

//#include <ThirdParty/google/flatbuffers/include/flatbuffers/util.h>
//#include <ThirdParty/google/flatbuffers/include/flatbuffers/idl.h>


#include <ThirdParty/cereal/archives/json.hpp>

#include <iostream>

namespace XE {
	
	XESettings::XESettings() {

	}

	XESettings::~XESettings() {

	}

	void XESettings::load(const std::string& settingsfilepath) {
	
		{
			//XESettings m;
			//ResourceData rd;
			//rd.assetsFolder = "c://assetsFolder";
			//rd.dbDataFolder = "c://dbDataFolder";
			//m.resourceData = rd;
			//m.dataRootFolder = "F:/Projekte/coop/FrankE/data";
			//std::ofstream os(settingsfilepath); // "F:/Projekte/coop/FrankE/data/settings.json");
			//cereal::JSONOutputArchive ar(os);// std::cout);
			//ar(m);
		}

		{
		//	XESettings m;
			std::ifstream is(settingsfilepath); // "F:/Projekte/coop/FrankE/data/settings.json");
			cereal::JSONInputArchive arRead(is);// std::cout);
			arRead(*this);
		}

		//this->dataRootFolder = dataRootFolder;

		PhysFS::addToSearchPath(dataRootFolder, true);
		

		//PhysFsStream wonderfullStream;
		//if (!wonderfullStream.open("settings.json"))
		//	return;

		//// Make sure that the stream's reading position is at the beginning
		//wonderfullStream.seek(0);

		//std::vector<char> m_buffer;
		//m_buffer.resize(wonderfullStream.getSize());
		//if (!wonderfullStream.read(m_buffer.data(), wonderfullStream.getSize()))
		//	return;

		/*std::string buf;
		flatbuffers::LoadFile("", false, &buf);
		flatbuffers::Parser parser;
		parser.Parse(buf.c_str());
		auto test = FBSettings::GetSettings(parser.builder_.GetBufferPointer());*/

		//	flatbuffers::GenerateJsonSchema(,,);

			//m_buffer = &buffer[0];

			//auto settings = FBSettings::GetSettings(&buffer[0]);
			//auto dbDataFolder = settings->resourceData()->dbDataFolder()->c_str();
			//auto assetsFolder = settings->resourceData()->assetsFolder()->c_str();
			//auto dbFileName = settings->resourceData()->dbFileName()->c_str();
			//auto hlmsDataFolder = settings->resourceData()->hlmsDataFolder()->c_str();
			//auto windowTitle = settings->windowTitle()->c_str();
	}

	/*const FBSettings::Settings* Settings::FBSettings()
	{
		return FBSettings::GetSettings(&m_buffer[0]);
	}*/


} //ns XE