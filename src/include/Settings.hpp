
#ifndef __XESETTINGS_HPP__
#define __XESETTINGS_HPP__

#include <string>

namespace XE {

	/// Settings as Singleton
	class Settings {
	public:
		static Settings& Instance() {
			static Settings S;
			return S;
		}

		///Path to the data folder
		std::string dataFolder;

		///load settings from lua File
		void load();

	private:
		Settings();
		~Settings();
	};

} //ns XE

#endif