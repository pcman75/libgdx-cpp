// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

//opengl
//#include <gl/gl.h>
//#include <gl/glu.h>

#define GL_GLEXT_PROTOTYPES

//#include <glext.h>
//#include <wglext.h>

#include <glew.h>

#include <string>
#include <vector>

#include <sstream>
#include <iostream>
#include <cstring>

#include <process.h>                                // for _beginthreadex()

#include <io.h>
#include <fcntl.h>

#pragma warning( disable : 4251 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4275 )
