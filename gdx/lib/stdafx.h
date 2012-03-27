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
#endif

#if defined(__APPLE_CC__)
    #include <OpenGL/gl.h>
    #include <OpenGL/glext.h>
    #include <libgen.h>
#else
    #include <GL/gl.h>
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



