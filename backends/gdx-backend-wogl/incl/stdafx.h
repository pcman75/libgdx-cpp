// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define NOMINMAX

// Windows Header Files:
#include <windows.h>
#include <mmsystem.h>

#define GL_GLEXT_PROTOTYPES
#include <glew.h>

#include <string>
#include <vector>
#include <set>

#include <sstream>
#include <iostream>
#include <cstring>

#include <process.h>                                // for _beginthreadex()

#include <io.h>
#include <fcntl.h>

#include <Shlobj.h> //special folders location

#include <direct.h> //_mkdir

#pragma warning( disable : 4251 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4275 )
