#include "StdAfx.h"
#include "WoglApplication.h"
#include "WoglGraphics.h"
#include "WoglInput.h"
#include "WoglFiles.h"

#include "WoglGraphics.h"
#include "ViewGL.h"
#include "ControllerGL.h"
#include "Window.h"
#include "Gdx.h"

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

WoglApplication::WoglApplication (ApplicationListener& listener, const wchar_t* title, int width, int height, bool useGL20IfAvailable)
{
	logLevel = LOG_INFO;
	m_pGraphics = new WoglGraphics(listener, useGL20IfAvailable);
	m_pInput = new WoglInput();
	m_pFiles = new WoglFiles();


	Gdx.app = this;
	Gdx.graphics = m_pGraphics;
	//Gdx.audio = 
	//Gdx.input = *m_pInput;
	//Gdx.files = *m_pFiles;

	// instantiate model and view components, so "controller" component can reference them
    Win::ViewGL view;   // under "Win" namespace because it is Windows specific view component.

    // create "controller" component by specifying what are "model" and "view"
    Win::ControllerGL glCtrl((WoglGraphics*)m_pGraphics, &view);

    // create window with given controller
    Win::Window glWin(::GetModuleHandle(NULL), title, 0, &glCtrl);
    glWin.setWindowStyle(WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    glWin.setClassStyle(CS_OWNDC);
    glWin.setWidth(width);
    glWin.setHeight(height);

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
	//delete m_pAudio;
}

const Graphics& WoglApplication::getGraphics ()
{
	return *m_pGraphics;
}


/*
const Audio& WoglApplication::getAudio ()
{
	return *m_pAudio;
}
*/

const Input& WoglApplication::getInput ()
{
	return *m_pInput;
}


const Files& WoglApplication::getFiles ()
{
	return *m_pFiles;
}


void WoglApplication::log(const wchar_t* tag, const wchar_t* message)
{
}

/* TODO imlement it only iof it's the case i.e u used C++ throw exceptions or gdx throws exceptions
void WoglApplication::log (const wchar_t* tag, const wchar_t* message, std::exception ex)
{
	if (logLevel >= LOG_INFO)
	{
		log(tag, message + ex.what());
	}
}
*/
void WoglApplication::error (const wchar_t* tag, const wchar_t* message)
{
}

//void WoglApplication::error (const wchar_t* tag, const wchar_t* message, std::exception ex)
//{
//}

void WoglApplication::debug (const wchar_t* tag, const wchar_t* message)
{
}

//void WoglApplication::debug (const wchar_t* tag, const wchar_t* message, std::exception ex)
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

//const Preferences& WoglApplication::getPreferences (const wchar_t* name)
//{
//	return 
//}

void WoglApplication::exit()
{
	//TODO: send WM_CLOSE
	exit();
}
