#include "StdAfx.h"
#include "WoglApplication.h"
#include "WoglGraphics.h"
#include "WindowsInput.h"
#include "WindowsFiles.h"
#include "WindowsAudio.h"

#include "WoglGraphics.h"
#include "ViewGL.h"
#include "ControllerGL.h"
#include "Window.h"
#include "Gdx.h"
#include "GdxRuntimeException.h"

#include "WindowsTimer.h"

///////////////////////////////////////////////////////////////////////////////
// main message loop
///////////////////////////////////////////////////////////////////////////////
void WoglApplication::mainMessageLoop(HACCEL hAccelTable)
{
    MSG msg;

    while(::GetMessage(&msg, 0, 0, 0) > 0)  // loop until WM_QUIT(0) received
    {
        // now, handle window messages
        if(!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
    }
}

WoglApplication::WoglApplication (ApplicationListener& listener, const char* title, int width, int height, bool useGL20IfAvailable)
{
	logLevel = LOG_INFO;
	m_pGraphics = new WoglGraphics(listener, useGL20IfAvailable);
	m_pInput = new WindowsInput();
	m_pFiles = new WindowsFiles();
	m_pAudio = new WindowsAudio();
	

	Gdx.app = this;
	Gdx.graphics = m_pGraphics;
	Gdx.audio = m_pAudio;
	Gdx.input = m_pInput;
	Gdx.files = m_pFiles;

	// instantiate model and view components, so "controller" component can reference them
    Win::ViewGL view;   // under "Win" namespace because it is Windows specific view component.

    // create "controller" component by specifying what are "model" and "view"
    Win::ControllerGL glCtrl((WoglGraphics*)m_pGraphics, (WindowsInput*)m_pInput, &view);

    // create window with given controller
    Win::Window glWin(::GetModuleHandle(NULL), title, 0, &glCtrl);
	DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    glWin.setWindowStyle(style);
    glWin.setClassStyle(CS_OWNDC);
    
	
	RECT rcWindow = {0, 0, width, height};
	AdjustWindowRectEx(&rcWindow,                // pointer to the RECT structure to use
                  style,     // window styles
                   FALSE,    // TRUE if the window has a menu, FALSE if not
                   style);  // extended window styles
	
	
	
	//glWin.setPosition(rcWindow.left, rcWindow.top);
	glWin.setWidth(rcWindow.right - rcWindow.left);
    glWin.setHeight(rcWindow.bottom - rcWindow.top);

    glWin.create();
    glWin.show();

	// main message loop
    mainMessageLoop(NULL);
}

WoglApplication::~WoglApplication(void)
{
	delete m_pGraphics;
	delete m_pInput;
	delete m_pFiles;
	delete m_pAudio;
}

Graphics* WoglApplication::getGraphics ()
{
	return m_pGraphics;
}



Audio* WoglApplication::getAudio ()
{
	return m_pAudio;
}


Input* WoglApplication::getInput ()
{
	return m_pInput;
}


Files* WoglApplication::getFiles ()
{
	return m_pFiles;
}

Timer* WoglApplication::createTimer()
{
	return new WindowsTimer();
}

void WoglApplication::log(const char* tag, const char* message)
{
	::OutputDebugString(tag);
	::OutputDebugString("\t");
	::OutputDebugString(message);
	::OutputDebugString("\n");
}

/* TODO imlement it only iof it's the case i.e u used C++ throw exceptions or gdx throws exceptions
void WoglApplication::log (const char* tag, const char* message, std::exception ex)
{
	if (logLevel >= LOG_INFO)
	{
		log(tag, message + ex.what());
	}
}
*/
void WoglApplication::error (const char* tag, const char* message)
{
}

//void WoglApplication::error (const char* tag, const char* message, std::exception ex)
//{
//}

void WoglApplication::debug (const char* tag, const char* message)
{
}

//void WoglApplication::debug (const char* tag, const char* message, std::exception ex)
//{
//}


void WoglApplication::setLogLevel (int logLevel)
{
}

 WoglApplication::ApplicationType WoglApplication::getType ()
{
	return Windows;
}


int WoglApplication::getVersion ()
{
	return 0;
}

//TODO: possible?
/** @return the heap memory use in bytes */
//long getHeap ();

//const Preferences& WoglApplication::getPreferences (const char* name)
//{
//	return 
//}

void WoglApplication::exit()
{
	//TODO: send WM_CLOSE
	exit();
}

Threading* WoglApplication::getThreading()
{
	throw GdxRuntimeException("not implemented");
}