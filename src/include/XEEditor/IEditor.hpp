#ifndef INTERFACE_EDITOR_HPP
#define INTERFACE_EDITOR_HPP

//#include <sfml/Window/WindowHandle.hpp>

//#include <XEEditor/Editor.h>
//#include <XEngine.hpp>
#include <iostream>
//#include <d3dx9.h>

#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
#include <XEEditor/Event/Event.h>

namespace EI {
	////////////////////////////////////////////////////////////
	// Identify the operating system
	////////////////////////////////////////////////////////////
	//#if defined(_WIN32) || defined(__WIN32__)
	//
	//	// Windows
	//#define CSFML_SYSTEM_WINDOWS
	//
	//#elif defined(linux) || defined(__linux)
	//
	//	// Linux
	//#define CSFML_SYSTEM_LINUX
	//
	//#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
	//
	//	// MacOS
	//#define CSFML_SYSTEM_MACOS
	//
	//#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
	//
	//	// FreeBSD
	//#define CSFML_SYSTEM_FREEBSD
	//
	//#else
	//
	//	// Unsupported system
	//#error This operating system is not supported by SFML library
	//
	//#endif
	//
	//
	//	////////////////////////////////////////////////////////////
	//	// Define helpers to create portable import / export macros for each module
	//	////////////////////////////////////////////////////////////
	//#if defined(CSFML_SYSTEM_WINDOWS)
	//
	//	// Windows compilers need specific (and different) keywords for export and import
	//#define CSFML_API_EXPORT extern "C" __declspec(dllexport)
	//#define CSFML_API_IMPORT extern __declspec(dllimport)
	//
	//	// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
	//#ifdef _MSC_VER
	//
	//#pragma warning(disable : 4251)
	//
	//#endif
	//
	//#else // Linux, FreeBSD, Mac OS X
	//
	//#if __GNUC__ >= 4
	//
	//	// GCC 4 has special keywords for showing/hidding symbols,
	//	// the same keyword is used for both importing and exporting
	//#define CSFML_API_EXPORT extern "C" __attribute__ ((__visibility__ ("default")))
	//#define CSFML_API_IMPORT extern __attribute__ ((__visibility__ ("default")))
	//
	//#else
	//
	//	// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
	//#define CSFML_API_EXPORT extern "C"
	//#define CSFML_API_IMPORT extern
	//
	//#endif
	//
	//#endif
	//
	//
	//	////////////////////////////////////////////////////////////
	//	// Define portable import / export macros
	//	////////////////////////////////////////////////////////////
	//#if defined(CSFML_WINDOW_EXPORTS)
	//
	//#define CSFML_WINDOW_API CSFML_API_EXPORT
	//
	//#else
	//
	//#define CSFML_WINDOW_API CSFML_API_IMPORT
	//
	//#endif


#define SFML_SYSTEM_WINDOWS

	////////////////////////////////////////////////////////////
	// Define helpers to create portable import / export macros for each module
	////////////////////////////////////////////////////////////
#if !defined(XE_EDITOR_STATIC)

#if defined(SFML_SYSTEM_WINDOWS)

	//works not with c++ projects
#define EDITOR_API_EXPORT extern "C" __declspec(dllexport)//extern c important for c# and c++ compatibility
#define EDITOR_API_IMPORT  extern "C" __declspec(dllimport) //extern c important for c# and c++ compatibility
	//__declspec(dllimport)

	// Windows compilers need specific (and different) keywords for export and import
	//#define EDITOR_API_EXPORT __declspec(dllexport)
	//#define EDITOR_API_IMPORT __declspec(dllimport)

	// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
#ifdef _MSC_VER

#pragma warning(disable : 4251)

#endif

#else // Linux, FreeBSD, Mac OS X

#if __GNUC__ >= 4

	// GCC 4 has special keywords for showing/hidding symbols,
	// the same keyword is used for both importing and exporting
#define EDITOR_API_EXPORT __attribute__ ((__visibility__ ("default")))
#define EDITOR_API_IMPORT __attribute__ ((__visibility__ ("default")))

#else

	// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
#define EDITOR_API_EXPORT
#define EDITOR_API_IMPORT

#endif

#endif

#else

	// Static build doesn't need import/export macros
#define EDITOR_API_EXPORT
#define EDITOR_API_IMPORT

#endif
	////////////////////////////////////////////////////////////
	// Define portable import / export macros
	////////////////////////////////////////////////////////////
#if defined(XE_EDITOR_EXPORTS)

#define XE_EDITOR_API EDITOR_API_EXPORT

#else

#define XE_EDITOR_API EDITOR_API_IMPORT

#endif


	//class SelectionRectangle;
	//class Editor;
	//struct ImplData;
	//	ImplData g_data;

	//	void CreateResourceGroups();
	
	typedef struct _StatesInfo
	{
		const char* buffer[5];
		int  size;
	} StatesInfo;

	XE_EDITOR_API unsigned char* command(const char* command, unsigned char* data, int len);
	XE_EDITOR_API int pushEvent(sfEvent pushEvent);
	XE_EDITOR_API void renderTargetSize(const char* rtName, Ogre::Real x, Ogre::Real y);

	XE_EDITOR_API void getStates(char* statesinfo);
	XE_EDITOR_API void* stateInit(const char* stateName, int width, int height);
	XE_EDITOR_API void* renderOnceTexturePtr(const char* stateName, int width, int height);
	XE_EDITOR_API bool moveToState(const char* stateName);
	XE_EDITOR_API bool stateUpdate();
	XE_EDITOR_API void quit();

} //ns EI

#endif // INTERFACE_EDITOR_HPP