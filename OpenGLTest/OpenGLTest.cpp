// OpenGLTest.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "OpenGLTest.h"
#include "OpenGLTestApp.h"
#include "WoglApplication.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	WoglApplication(OpenGLTestApp(), L"OpenGL Test", 800, 600, true);
	return 0;
}

