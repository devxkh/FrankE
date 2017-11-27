////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////

#pragma once

namespace XE {

	/// set used rendersystem -> 1 = "GLES3", 2 = D3D11
#define UseRenderSystem 1 
	///use renderthread
#define UseRenderThread
	/// compile editor functions 
#define CompileEditor


	////////////////////////////////////////////////////////////
	// Define helpers to create portable import / export macros for each module
	////////////////////////////////////////////////////////////
//#if !defined(XE_STATIC)
//
//#if defined(XE_SYSTEM_WINDOWS)
//
//	// Windows compilers need specific (and different) keywords for export and import
//#define XE_API_EXPORT __declspec(dllexport)
//#define XE_API_IMPORT __declspec(dllimport)
//
//	// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
//#ifdef _MSC_VER
//
//#pragma warning(disable: 4251)
//
//#endif
//
//#else // Linux, FreeBSD, Mac OS X
//
//#if __GNUC__ >= 4
//
//	// GCC 4 has special keywords for showing/hidding symbols,
//	// the same keyword is used for both importing and exporting
//#define XE_API_EXPORT __attribute__ ((__visibility__ ("default")))
//#define XE_API_IMPORT __attribute__ ((__visibility__ ("default")))
//
//#else
//
//	// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
#define XE_API_EXPORT
#define XE_API_IMPORT

//#endif
//
//#endif
//
//#else
//
//	// Static build doesn't need import/export macros
//#define XE_API_EXPORT
//#define XE_API_IMPORT
//
//#endif

////////////////////////////////////////////////////////////
// Define portable import / export macros
////////////////////////////////////////////////////////////
#if defined(XE_SYSTEM_EXPORTS)

#define XE_API XE_API_EXPORT

#else

#define XE_API XE_API_IMPORT

#endif

	// All "common" platforms use the same size for char, short and int
	// (basically there are 3 types for 3 sizes, so no other match is possible),
	// we can use them without doing any kind of check

	// 8 bits integer types
	typedef signed   char Int8;
	typedef unsigned char Uint8;

	// 16 bits integer types
	typedef signed   short Int16;
	typedef unsigned short Uint16;

	// 32 bits integer types
	typedef signed   int Int32;
	typedef unsigned int Uint32;

	// 64 bits integer types
#if defined(_MSC_VER)
	typedef signed   __int64 Int64;
	typedef unsigned __int64 Uint64;
#else
	typedef signed   long long Int64;
	typedef unsigned long long Uint64;
#endif

}