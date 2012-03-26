#include "StdAfx.h"
#include "GlfwApplication.h"
#include "GlfwGraphics.h"
#include "GlfwInput.h"
#include "WoglFiles.h"
#include "GlfwThreading.h"

#include "WindowsAudio.h"

#include "GlfwGraphics.h"
#include "Gdx.h"

#include "GlfwTimer.h"
#include "GdxRuntimeException.h"

GlfwApplication::GlfwApplication (ApplicationListener& listener, const char* title, int width, int height, bool useGL20IfAvailable)
{
	logLevel = LOG_INFO;
	m_pGraphics = new GlfwGraphics(listener, useGL20IfAvailable);
	m_pInput = new GlfwInput();
	m_pFiles = new WoglFiles();
	m_pThreading = new GlfwThreading();
	m_pAudio = new WindowsAudio();
	
	Gdx.app = this;
	Gdx.graphics = m_pGraphics;
	Gdx.input = m_pInput;
	Gdx.audio = m_pAudio;
	Gdx.files = m_pFiles;
	Gdx.threading = m_pThreading;


	// Initialise GLFW
	if( !glfwInit() )
	{
		throw GdxRuntimeException("Failed to initialize GLFW");
	}
	
	/*
	if(useGL20IfAvailable)
		::glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	else
	{
		::glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 1);
		//TODO: need to set OpenGL minor version???
		//::glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3); 
	}*/

	createWindow(title, width, height);

	//setup input
	GlfwInput* input = ((GlfwInput*)Gdx.input);
	input->init();

	// Enable vertical sync (on cards that support it)
	//glfwSwapInterval(1);

	runOpenGLLoop();

	((GlfwGraphics*)m_pGraphics)->dispose();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

GlfwApplication::~GlfwApplication(void)
{
	delete m_pGraphics;
	delete m_pInput;
	delete m_pFiles;
	delete m_pThreading;
	delete m_pAudio;
}

Graphics* GlfwApplication::getGraphics ()
{
	return m_pGraphics;
}



Audio* GlfwApplication::getAudio ()
{
	return m_pAudio;
}


Input* GlfwApplication::getInput ()
{
	return m_pInput;
}


Files* GlfwApplication::getFiles ()
{
	return m_pFiles;
}

Timer* GlfwApplication::createTimer()
{
	return new GlfwTimer();
}

void GlfwApplication::log(const char* tag, const char* message)
{
	printDebugString(tag);
	printDebugString("\t");
	printDebugString(message);
	printDebugString("\n");
}

void GlfwApplication::printDebugString(const char* str)
{
#ifdef WIN32
    ::OutputDebugString(str);
#else
    printf(str);
#endif
}


/* TODO imlement it only if it's the case i.e u used C++ throw exceptions or gdx throws exceptions
void GlfwApplication::log (const char* tag, const char* message, std::exception ex)
{
	if (logLevel >= LOG_INFO)
	{
		log(tag, message + ex.what());
	}
}
*/
void GlfwApplication::error (const char* tag, const char* message)
{
}

//void GlfwApplication::error (const char* tag, const char* message, std::exception ex)
//{
//}

void GlfwApplication::debug (const char* tag, const char* message)
{
}

//void GlfwApplication::debug (const char* tag, const char* message, std::exception ex)
//{
//}


void GlfwApplication::setLogLevel (int logLevel)
{
}

 GlfwApplication::ApplicationType GlfwApplication::getType ()
{
	return Windows;
}


int GlfwApplication::getVersion ()
{
	return 0;
}

//TODO: possible?
/** @return the heap memory use in bytes */
//long getHeap ();

//const Preferences& GlfwApplication::getPreferences (const char* name)
//{
//	return 
//}

void GlfwApplication::exit()
{
	exit();
}

void GlfwApplication::createWindow(const char* title, int width, int height)
{
	((GlfwGraphics*)m_pGraphics)->createWindow(title, width, height);
}

void GlfwApplication::runOpenGLLoop()
{
	((GlfwGraphics*)m_pGraphics)->runOpenGLLoop();
}

/** @return the {@link Threading} instance */
Threading* GlfwApplication::getThreading()
{
	return m_pThreading;
}