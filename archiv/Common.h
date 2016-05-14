/*
TecnoFreak Animation System
http://sourceforge.net/projects/tecnofreakanima/

Copyright (c) 2008 Pau Novau Lebrato

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.
*/

#ifndef __TECNOFREAK__COMMON__H__
#define __TECNOFREAK__COMMON__H__

#pragma warning( disable : 4251 )

#define TECNOFREAK_PLATFORM_WIN32 1
#define TECNOFREAK_PLATFORM_LINUX 2
#define TECNOFREAK_PLATFORM_APPLE 3

// Determine current platform.
#if defined( __WIN32__ ) || defined( _WIN32 )
#   define TECNOFREAK_PLATFORM TECNOFREAK_PLATFORM_WIN32
#elif defined( __APPLE_CC__)
#   define TECNOFREAK_PLATFORM TECNOFREAK_PLATFORM_APPLE
#else
#   define TECNOFREAK_PLATFORM TECNOFREAK_PLATFORM_LINUX
#endif

#if SFML_STATIC
#       define TecnoFreakDllExport
#       define TecnoFreakDllPrivate
#       define TecnoFreakThisCall

#else
#if TECNOFREAK_PLATFORM == TECNOFREAK_PLATFORM_WIN32
#       define TecnoFreakDllExport __declspec( dllexport )
#       define TecnoFreakDllPrivate __declspec( dllexport )
#       define TecnoFreakThisCall __thiscall
#elif TECNOFREAK_PLATFORM == TECNOFREAK_PLATFORM_APPLE || TECNOFREAK_PLATFORM == TECNOFREAK_PLATFORM_LINUX
#       define TecnoFreakDllExport
#       define TecnoFreakDllPrivate
#       define TecnoFreakThisCall
#endif
#endif



#undef min
#undef max

#include <stdexcept>

#endif