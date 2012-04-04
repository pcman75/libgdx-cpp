// gdx-helloworld.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "gdx-helloworld.h"

#include "HelloWorldApp.h"
#include "GlfwApplication.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	GlfwApplication(HelloWorldApp(), "OpenGL Test", 400, 300, false);
	return 0;
}



