
#ifndef __XESETTINGS_HPP__
#define __XESETTINGS_HPP__

#include <string>

#include <XEDAL/Objects/FB_Settings_generated.h>
#include <vector>

namespace XE {

	/// Settings as Meyers Singleton http://www.codeproject.com/Articles/4750/Singleton-Pattern-A-review-and-analysis-of-existin
	class Settings {

	public:

		Settings();

		~Settings();

		//// Diese statische Methode erzeugt die einzige Instanz.
		//// Nur über diese Methode erhalten Anwender den Zugriff auf
		//// die Instanz.
		//static Settings& Instance() {
		//	// Die Instanz wird erst beim ersten Aufruf erzeugt.
		//	// Endet das Programm, wird Instanz vernichtet.
		//	static Settings S;
		//	return S;
		//}

		///Path to the data folder
		std::string dataRootFolder;

		bool fullscreen;

		////dbData searchpath for physfs -> "F:/Projekte/coop/XGame/data/dbData"
		//std::string dbDataFolder;

		////assets searchpath for physfs -> "F:/Projekte/coop/XGame/data/assets"
		//std::string assetsFolder;

		/////sqllitedb -> "F:\\Projekte\\coop\\XGame\\data\\dbData.s3db"
		//std::string dbFileName;

		//std::string windowTitle;
	
		//std::string hlmsDataFolder;

		const FBSettings::Settings * FBSettings();

		void load(const std::string& dataRootFolder);

	private:
		
		std::vector<char> m_buffer;
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