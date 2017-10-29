
#ifndef __XESETTINGS_HPP__
#define __XESETTINGS_HPP__

#include <string>

//#include <XEDAL/Objects/FB_Settings_generated.h>


#include <ThirdParty/cereal/cereal.hpp>

#include <vector>


namespace XE {

	struct XESettings {

	public:

		enum FSAA
		{
			none = 0,
			x8 = 8,
			x16 = 16,
			x32 = 32
		};

		struct Graphics
		{
			bool fullscreen;

			FSAA fsaa;


			template <class Archive>
			void serialize(Archive & ar)
			{
				ar(CEREAL_NVP(fullscreen), CEREAL_NVP(fsaa));
			}
		};

		///resource folders
		struct ResourceData
		{
			std::string hlmsDataFolder;// folder for hlms shader script files
			std::string dbDataFolder;// folder contains lua scripts/flatbuffer files
			std::string assetsFolder;//folder contains 3d assets used in renderthread
			std::string dbFileName;//sqlite dbfilename contains scene, entity, node data

			template <class Archive>
			void serialize(Archive & ar)
			{
				ar(CEREAL_NVP(hlmsDataFolder) , CEREAL_NVP(dbDataFolder) , CEREAL_NVP(assetsFolder) , CEREAL_NVP(dbFileName));
			}
		};

		Graphics graphics;
		ResourceData resourceData;
		
		///Path to the data folder
		std::string dataRootFolder;
		std::string windowTitle; // window title 
		std::string inputMapFilename; //fb binary filepath with input mappings


		template<class Archive>
		void serialize(Archive & archive) 
		{
			archive(CEREAL_NVP(dataRootFolder)
				,CEREAL_NVP(graphics),
				CEREAL_NVP(resourceData),
				CEREAL_NVP(windowTitle),
				CEREAL_NVP(inputMapFilename)
			);
		}

		XESettings();

		~XESettings();

		//// Diese statische Methode erzeugt die einzige Instanz.
		//// Nur über diese Methode erhalten Anwender den Zugriff auf
		//// die Instanz.
		//static Settings& Instance() {
		//	// Die Instanz wird erst beim ersten Aufruf erzeugt.
		//	// Endet das Programm, wird Instanz vernichtet.
		//	static Settings S;
		//	return S;
		//}

		
	//	bool fullscreen;

		////dbData searchpath for physfs -> "F:/Projekte/coop/XGame/data/dbData"
		//std::string dbDataFolder;

		////assets searchpath for physfs -> "F:/Projekte/coop/XGame/data/assets"
		//std::string assetsFolder;

		/////sqllitedb -> "F:\\Projekte\\coop\\XGame\\data\\dbData.s3db"
		//std::string dbFileName;

		//std::string windowTitle;
	
		//std::string hlmsDataFolder;

//		const FBSettings::Settings * FBSettings();

		void load(const std::string& settingsfilepath);



	private:
		
	//	std::vector<char> m_buffer;
		// Standard- und Copykonstruktor sind private. 
		// Nur Methoden dieser Klasse können auf sie zugreifen.
	//	Settings();
	////	Settings(const Settings&);

	//	~Settings();

		// Es gibt nur eine Instanz. Jede Zuweisung wäre eine Selbstzuweisung.
		// Da Selbstzuweisungen selten Sinn machen, ist der op= privat
	//	Settings& operator=(const Settings&);
	};

} //ns XE

#endif