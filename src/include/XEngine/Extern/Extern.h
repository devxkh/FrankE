#ifndef XEXTERN_H
#define XEXTERN_H

#include <XEngine.hpp>

#define XE_EDITOR_EXPORTS

//works not with c++ projects
#define EDITOR_API_EXPORT extern "C" __declspec(dllexport)//extern c important for c# and c++ compatibility
#define EDITOR_API_IMPORT  extern "C" __declspec(dllimport) //extern c important for c# and c++ compatibility
//__declspec(dllimport)

////////////////////////////////////////////////////////////
// Define portable import / export macros
////////////////////////////////////////////////////////////
#if defined(XE_EDITOR_EXPORTS)

#define XE_EDITOR_API EDITOR_API_EXPORT

#else

#define XE_EDITOR_API EDITOR_API_IMPORT

#endif

XE_EDITOR_API bool  xEngine_test(bool test);
XE_EDITOR_API XE::XEngine* xEngine_create(const char* title, const char* resourceFile);
XE_EDITOR_API void xEngine_destroy(XE::XEngine* ptr);


#endif