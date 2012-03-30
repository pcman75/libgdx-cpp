// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#if defined (WIN32)
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define NOMINMAX
// Windows Header Files:
#include <windows.h>
#include <mmsystem.h>
#include <direct.h> //_mkdir

#include <io.h>
#include <fcntl.h>

#include <Shlobj.h> //special folders location

#endif

#define GL_GLEXT_PROTOTYPES

#include <glew.h>
#include <GL/glfw.h>

#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <iostream>
#include <cstring>


#include <stdlib.h>
#include <stdio.h>