///////////////////////////////////////////////////////////////////////////////
// ControllerGL.cpp
// ================
// Derived Controller class for OpenGL window
// It is the controller of OpenGL rendering window. It initializes DC and RC,
// when WM_CREATE called, then, start new thread for OpenGL rendering loop.
//
// When this class is constructed, it gets the pointers to model and view
// components.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gamil.com)
// CREATED: 2006-07-09
// UPDATED: 2007-07-21
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "ControllerGL.h"
using namespace Win;



///////////////////////////////////////////////////////////////////////////////
// default contructor
///////////////////////////////////////////////////////////////////////////////
ControllerGL::ControllerGL(WoglGraphics* graphics, WindowsInput* input, ViewGL* view) 
	: m_pGraphics(graphics), m_pInput(input), viewGL(view),
    threadHandle(0), threadId(0),
    loopFlag(false), resizeFlag(false),
    clientWidth(0), clientHeight(0)
{
}



///////////////////////////////////////////////////////////////////////////////
// handle WM_CLOSE
///////////////////////////////////////////////////////////////////////////////
int ControllerGL::close()
{
    loopFlag = false;
    ::WaitForSingleObject(threadHandle, INFINITE);  // wait for rendering thread is terminated

    // close OpenGL Rendering context
    viewGL->closeContext(handle);

    ::DestroyWindow(handle);
    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// handle WM_CREATE
///////////////////////////////////////////////////////////////////////////////
int ControllerGL::create()
{
    // create a OpenGL rendering context
    if(!viewGL->createContext(handle, 32, 24, 8))
    {
        //Win::log(L"[ERROR] Failed to create OpenGL rendering context from ControllerGL::create().");
        return -1;
    }

    // create a thread for OpenGL rendering
    // The params of _beginthreadex() are security, stackSize, functionPtr, argPtr, initFlag, threadId.
    threadHandle = (HANDLE)_beginthreadex(0, 0, (unsigned (__stdcall *)(void *))threadFunction, this, 0, &threadId);
    if(threadHandle)
    {
        loopFlag = true;
        //Win::log(L"Created a rendering thread for OpenGL.");
    }
    else
    {
        ;//Win::log(L"[ERROR] Failed to create rendering thread from ControllerGL::create().");
    }

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// handle WM_PAINT
///////////////////////////////////////////////////////////////////////////////
int ControllerGL::paint()
{
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// handle WM_COMMAND
///////////////////////////////////////////////////////////////////////////////
int ControllerGL::command(int id, int cmd, LPARAM msg)
{
    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// route to worker thread
// The function prototype is:
// unsigned int (__stdcall *)(void *)
///////////////////////////////////////////////////////////////////////////////
void ControllerGL::threadFunction(void* param)
{
    ((ControllerGL*)param)->runThread();
}



///////////////////////////////////////////////////////////////////////////////
// rendering thread
// initialize OpenGL states and start rendering loop
///////////////////////////////////////////////////////////////////////////////
void ControllerGL::runThread()
{
    // set the current RC in this thread
    ::wglMakeCurrent(viewGL->getDC(), viewGL->getRC());

    // initialize OpenGL states
    m_pGraphics->init();

    // cofigure projection matrix
    RECT rect;
    ::GetClientRect(handle, &rect);
    m_pGraphics->setViewport(rect.right, rect.bottom, false);

	m_pGraphics->create();

    // rendering loop
    while(loopFlag)
    {
        ::Sleep(10);                    // yield to other processes or threads

        if(resizeFlag)
        {
            m_pGraphics->setViewport(clientWidth, clientHeight, true);
            resizeFlag = false;
        }

        m_pGraphics->draw();
        viewGL->swapBuffers();
    }

	m_pGraphics->dispose();

    // terminate rendering thread
    ::wglMakeCurrent(0, 0);             // unset RC
    ::CloseHandle(threadHandle);
}



///////////////////////////////////////////////////////////////////////////////
// handle Left mouse down
///////////////////////////////////////////////////////////////////////////////
int ControllerGL::lButtonDown(WPARAM state, int x, int y)
{
	m_pInput->buttonDown(state, x, y);
    // update mouse position
    m_pGraphics->setMousePosition(x, y);

    if(state == MK_LBUTTON)
    {
        m_pGraphics->setMouseLeft(true);
    }

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// handle Left mouse up
///////////////////////////////////////////////////////////////////////////////
int ControllerGL::lButtonUp(WPARAM state, int x, int y)
{
	m_pInput->buttonUp(state, x, y);

    // update mouse position
    m_pGraphics->setMousePosition(x, y);

    m_pGraphics->setMouseLeft(false);

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// handle reft mouse down
///////////////////////////////////////////////////////////////////////////////
int ControllerGL::rButtonDown(WPARAM state, int x, int y)
{
    // update mouse position
    m_pGraphics->setMousePosition(x, y);

    if(state == MK_RBUTTON)
    {
        m_pGraphics->setMouseRight(true);
    }

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// handle reft mouse up
///////////////////////////////////////////////////////////////////////////////
int ControllerGL::rButtonUp(WPARAM state, int x, int y)
{
    // update mouse position
    m_pGraphics->setMousePosition(x, y);

    m_pGraphics->setMouseRight(false);

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// handle WM_MOUSEMOVE
///////////////////////////////////////////////////////////////////////////////
int ControllerGL::mouseMove(WPARAM state, int x, int y)
{
    if(state == MK_LBUTTON)
    {
        m_pGraphics->rotateCamera(x, y);
    }
    if(state == MK_RBUTTON)
    {
        m_pGraphics->zoomCamera(y);
    }

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// handle WM_KEYDOWN
///////////////////////////////////////////////////////////////////////////////
int ControllerGL::keyDown(int key, LPARAM lParam)
{
	/* TODO: need this?
    if(key == VK_ESCAPE)
    {
        ::PostMessage(handle, WM_CLOSE, 0, 0);
    }
	*/
	m_pInput->keyDown(key, lParam);
    return 0;
}

int ControllerGL::keyUp(int key, LPARAM lParam)
{
	m_pInput->keyUp(key, lParam);
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
// handle WM_SIZE notification
// Note that the input param, width and height is for client area only.
// It excludes non-client area.
///////////////////////////////////////////////////////////////////////////////
int ControllerGL::size(int width, int height, WPARAM type)
{
    resizeFlag = true;
    clientWidth = width;
    clientHeight = height;

    return 0;
}
