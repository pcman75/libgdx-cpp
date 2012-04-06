#include "stdafx.h"
#include "SuperJumper.h"
#include "GlfwApplication.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	GlfwApplication(SuperJumper(), "Super Jumper", 320, 480, false);
    return 0;
}

