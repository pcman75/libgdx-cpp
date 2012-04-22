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
    #define GL_GLEXT_PROTOTYPES
    #include <glew.h>
    
    #define GL_GLEXT_PROTOTYPES
    #include <glew.h>
#endif

#if defined(__APPLE_CC__)
    #if defined (TARGET_IOS)
        #include <OpenGLES/ES1/gl.h>
        #include <OpenGLES/ES1/glext.h>
        #include <OpenGLES/ES2/gl.h>
        #include <OpenGLES/ES2/glext.h>
    #else
        #include <OpenGL/gl.h>
        #include <OpenGL/glext.h>
    #endif
    #include <libgen.h>
    #include <sys/stat.h> //mkdir
#endif



#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <math.h>

#include <fstream>