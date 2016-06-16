//improved Ogre::ConfigFile thomas {AT} thomasfischer {DOT} biz 3/2008
#ifndef INPUTCONFIGFILE_H_
#define INPUTCONFIGFILE_H_

//#include <OgrePrerequisites.h>
//#include <Ogre/OgreMain/include/OgreConfigFile.h>
//#include  <SFML/Window/Export.hpp>
//
//namespace XE {
//
//class SFML_WINDOW_API InputConfigFile : public Ogre::ConfigFile
//{
//public:
//	InputConfigFile();
//   
//	~InputConfigFile();
//    
//   // note: saving is only supported for direct loaded files atm!
//	void load(const Ogre::String& filename, const Ogre::String& separators, bool trimWhitespace);
//   
//	bool save();
//
//	void setSetting(Ogre::String &key, Ogre::String &value, Ogre::String section = "");
//
//   // type specific implementations
// //  ActionMap<ActionId> getSettingRadian(String key, String section = StringUtil::BLANK) { return "ddd";   }
//  // void setSetting(String key, String value, String section = StringUtil::BLANK) { setSetting(key, value, section);   }
//
//   /*Radian getSettingRadian(String key, String section = StringUtil::BLANK) { return StringConverter::parseAngle(getSetting(key, section));   }
//   void setSetting(String key, Radian value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section);   }
//
//   bool getSettingBool(String key, String section = StringUtil::BLANK) { return StringConverter::parseBool(getSetting(key, section)); }
//   void setSetting(String key, bool value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }
//
//   Real getSettingReal(String key, String section = StringUtil::BLANK) { return StringConverter::parseReal(getSetting(key, section)); }
//   void setSetting(String key, Real value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }
//
//   int getSettingInt(String key, String section = StringUtil::BLANK) { return StringConverter::parseInt(getSetting(key, section)); }
//   void setSetting(String key, int value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }
//
//   unsigned int getSettingUnsignedInt(String key, String section = StringUtil::BLANK) { return StringConverter::parseUnsignedInt(getSetting(key, section)); }
//   void setSetting(String key, unsigned int value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }
//
//   long getSettingLong(String key, String section = StringUtil::BLANK) { return StringConverter::parseLong(getSetting(key, section)); }
//   void setSetting(String key, long value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }
//
//   unsigned long getSettingUnsignedLong(String key, String section = StringUtil::BLANK) { return StringConverter::parseUnsignedLong(getSetting(key, section)); }
//   void setSetting(String key, unsigned long value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }
//
//   Vector3 getSettingVector3(String key, String section = StringUtil::BLANK) { return StringConverter::parseVector3(getSetting(key, section)); }
//   void setSetting(String key, Vector3 value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }
//
//   Matrix3 getSettingMatrix3(String key, String section = StringUtil::BLANK) { return StringConverter::parseMatrix3(getSetting(key, section)); }
//   void setSetting(String key, Matrix3 value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }
//
//   Matrix4 getSettingMatrix4(String key, String section = StringUtil::BLANK) { return StringConverter::parseMatrix4(getSetting(key, section)); }
//   void setSetting(String key, Matrix4 value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }
//
//   Quaternion getSettingQuaternion(String key, String section = StringUtil::BLANK) { return StringConverter::parseQuaternion(getSetting(key, section)); }
//   void setSetting(String key, Quaternion value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }
//
//   ColourValue getSettingColorValue(String key, String section = StringUtil::BLANK) { return StringConverter::parseColourValue(getSetting(key, section)); }
//   void setSetting(String key, ColourValue value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }
//
//   StringVector getSettingStringVector(String key, String section = StringUtil::BLANK) { return StringConverter::parseStringVector(getSetting(key, section)); }
//   void setSetting(String key, StringVector value, String section = StringUtil::BLANK) { setSetting(key, StringConverter::toString(value), section); }
//*/
//protected:
//	Ogre::String separators;
//	Ogre::String filename;
//};

//} // namespace XE

#endif // INPUTCONFIGFILE_H_