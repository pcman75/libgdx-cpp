// GdxInvaders.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GdxInvadersDesktop.h"
#include "GlfwApplication.h"
#include "GdxInvaders.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	GlfwApplication(GdxInvaders(), "Gdx Invaders", 800, 480, false);
    return 0;
}

