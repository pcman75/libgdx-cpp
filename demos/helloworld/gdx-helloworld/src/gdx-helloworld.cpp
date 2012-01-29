// gdx-helloworld.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "gdx-helloworld.h"

#include "WoglApplication.h"
#include "HelloWorldApp.h"

#include <string>

/*
class GLCommon
{
public:
	virtual void f() = 0;
};

class GL10 : virtual public GLCommon
{
	virtual void f10() = 0;
};

class WoglGLCommon : virtual public GLCommon
{
public:
	virtual void f() {};
};

class WoglGL10 : public WoglGLCommon, public GL10
{
public:
	virtual void f10() {};
};
*/
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	WoglApplication(HelloWorldApp(), L"OpenGL Test", 400, 300, true);
    return 0;
}



