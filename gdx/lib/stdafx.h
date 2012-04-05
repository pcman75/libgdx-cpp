// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#if defined (WIN32)
	#define _USE_MATH_DEFINES //for M_PI
	#include "targetver.h"
	#define NOMINMAX
	#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
	// Windows Header Files:
	#include <windows.h>
	#include <direct.h> //rmdir
    #include <io.h> //access
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
#else
    #define GL_GLEXT_PROTOTYPES
	#include <glew.h>
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <iterator>

#include <fstream>

#include <time.h> //for random

#include <stdint.h> //for uint64_t

#include <float.h>

#include <math.h>
#include <limits.h>
#include <stdio.h>

#include <sys/types.h> //stat() (get the file size)
#include <sys/stat.h>



