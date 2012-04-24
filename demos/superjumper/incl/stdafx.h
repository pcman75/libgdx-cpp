// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#if defined (WIN32)
    #include "targetver.h"

    #define NOMINMAX

    #define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
    // Windows Header Files:
    #include <windows.h>
    #include <GL/GL.h>
	#include <tchar.h>
#endif

#if defined(__APPLE_CC__)
    #include <OpenGL/gl.h>
    #include <OpenGL/glext.h>
#endif

// C RunTime Header Files
#include <stdlib.h>
#include <memory.h>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <sstream>
#include <fstream>


