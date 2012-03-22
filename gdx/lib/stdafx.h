// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _USE_MATH_DEFINES //for M_PI

#include "targetver.h"

#define NOMINMAX

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#ifdef WIN32
#include <windows.h>
#endif

#include <GL\gl.h>

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

#pragma warning( disable : 4251 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4275 )

