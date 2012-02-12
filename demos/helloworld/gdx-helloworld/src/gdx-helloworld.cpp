// gdx-helloworld.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "gdx-helloworld.h"

#include "WoglApplication.h"
#include "HelloWorldApp.h"
#include "PixmapTest.h"
#include "MatrixTest.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	//WoglApplication(HelloWorldApp(), L"OpenGL Test", 400, 300, false);
	//WoglApplication(PixmapTest(), L"Pixmap Test", 400, 300, false);
	WoglApplication(MatrixTest(), L"Matrix Test", 400, 300, false);
    return 0;
}



