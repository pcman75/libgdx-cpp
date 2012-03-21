// GdxInvaders.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GdxInvadersDesktop.h"
#include "WoglApplication.h"
#include "GlfwApplication.h"
#include "GdxInvaders.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    //WoglApplication(GdxInvaders(), "Gdx Invaders", 800, 480, false);
	GlfwApplication(GdxInvaders(), "Gdx Invaders", 800, 480, false);
    return 0;
}

