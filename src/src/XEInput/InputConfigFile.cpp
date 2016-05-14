#include <XEInput/InputConfigFile.hpp>


#include <Ogre/OgreMain/include/OgreException.h>
//#include <XEWindow/Input/ActionMap.hpp>
//
////todo --test
//#include <XESystem/XECore/XEStringConverter.hpp>
//
using namespace Ogre;

namespace XE {


		InputConfigFile::InputConfigFile() : separators(), filename()
		{
			ConfigFile::ConfigFile();
		}

		InputConfigFile::~InputConfigFile()
		{
		}

		// note: saving is only supported for direct loaded files atm!
		void InputConfigFile::load(const String& filename, const String& separators, bool trimWhitespace)
		{
			this->separators = separators;
			this->filename = filename;
			ConfigFile::load(filename, separators, trimWhitespace);
		}

		bool InputConfigFile::save()
		{
			if (!filename.length())
			{
				OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Saving of the configuration File is only allowed when the configuration was not loaded using the resource system!", "ImprovedConfigFile::save");
				return false;
			}
			FILE *f = fopen(filename.c_str(), "w");
			if (!f)
			{
				OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "Cannot open File '" + filename + "' for writing.", "ImprovedConfigFile::save");
				return false;
			}

			SettingsBySection::iterator secIt;
			for (secIt = mSettings.begin(); secIt != mSettings.end(); secIt++)
			{
				if (secIt->first.size() > 0)
					fprintf(f, "[%s]\n", secIt->first.c_str());
				SettingsMultiMap::iterator setIt;
				for (setIt = secIt->second->begin(); setIt != secIt->second->end(); setIt++)
				{
					fprintf(f, "%s%c%s\n", setIt->first.c_str(), separators[0], setIt->second.c_str());
				}

			}
			fclose(f);
			return true;
		}

		void InputConfigFile::setSetting(String &key, String &value, String section)
		{
			SettingsMultiMap *set = mSettings[section];
			if (!set)
			{
				// new section
				set = new SettingsMultiMap();
				mSettings[section] = set;
			}
			if (set->count(key))
				// known key, delete old first
				set->erase(key);
			// add key
			set->insert(std::multimap<String, String>::value_type(key, value));
		}


// type specific implementations
//  ActionMap<ActionId> getSettingRadian(String key, String section = StringUtil::BLANK) { return "ddd";   }
// void setSetting(String key, String value, String section = StringUtil::BLANK) { setSetting(key, value, section);   }

/*Radian getSettingRadian(String key, String section = StringUtil::BLANK) { return StringConverter::parseAngle(getSetting(key, section));   }
void setSetting(String key, Radian value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section);   }

bool getSettingBool(String key, String section = StringUtil::BLANK) { return StringConverter::parseBool(getSetting(key, section)); }
void setSetting(String key, bool value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }

Real getSettingReal(String key, String section = StringUtil::BLANK) { return StringConverter::parseReal(getSetting(key, section)); }
void setSetting(String key, Real value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }

int getSettingInt(String key, String section = StringUtil::BLANK) { return StringConverter::parseInt(getSetting(key, section)); }
void setSetting(String key, int value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }

unsigned int getSettingUnsignedInt(String key, String section = StringUtil::BLANK) { return StringConverter::parseUnsignedInt(getSetting(key, section)); }
void setSetting(String key, unsigned int value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }

long getSettingLong(String key, String section = StringUtil::BLANK) { return StringConverter::parseLong(getSetting(key, section)); }
void setSetting(String key, long value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }

unsigned long getSettingUnsignedLong(String key, String section = StringUtil::BLANK) { return StringConverter::parseUnsignedLong(getSetting(key, section)); }
void setSetting(String key, unsigned long value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }

Vector3 getSettingVector3(String key, String section = StringUtil::BLANK) { return StringConverter::parseVector3(getSetting(key, section)); }
void setSetting(String key, Vector3 value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }

Matrix3 getSettingMatrix3(String key, String section = StringUtil::BLANK) { return StringConverter::parseMatrix3(getSetting(key, section)); }
void setSetting(String key, Matrix3 value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }

Matrix4 getSettingMatrix4(String key, String section = StringUtil::BLANK) { return StringConverter::parseMatrix4(getSetting(key, section)); }
void setSetting(String key, Matrix4 value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }

Quaternion getSettingQuaternion(String key, String section = StringUtil::BLANK) { return StringConverter::parseQuaternion(getSetting(key, section)); }
void setSetting(String key, Quaternion value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }

ColourValue getSettingColorValue(String key, String section = StringUtil::BLANK) { return StringConverter::parseColourValue(getSetting(key, section)); }
void setSetting(String key, ColourValue value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }

StringVector getSettingStringVector(String key, String section = StringUtil::BLANK) { return StringConverter::parseStringVector(getSetting(key, section)); }
void setSetting(String key, StringVector value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }
*/

} // namespace XE