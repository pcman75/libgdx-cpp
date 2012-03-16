#include "StdAfx.h"
#include "GlfwApplication.h"
#include "GlfwGraphics.h"
#include "GlfwInput.h"
#include "WoglFiles.h"
#include "WindowsAudio.h"

#include "GlfwGraphics.h"
#include "Gdx.h"

#include "WindowsTimer.h"
#include "GdxRuntimeException.h"

GlfwApplication::GlfwApplication (ApplicationListener& listener, const char* title, int width, int height, bool useGL20IfAvailable)
{
	logLevel = LOG_INFO;
	m_pGraphics = new GlfwGraphics(listener, useGL20IfAvailable);
	m_pInput = new GlfwInput();
	m_pFiles = new WoglFiles();
	m_pAudio = new WindowsAudio();
	
	Gdx.app = this;
	Gdx.graphics = m_pGraphics;
	Gdx.input = m_pInput;
	Gdx.audio = m_pAudio;
	Gdx.files = m_pFiles;


	// Initialise GLFW
	if( !glfwInit() )
	{
		throw GdxRuntimeException("Failed to initialize GLFW");
	}
	
	// Initialise GLEW
	glewInit();

	if(useGL20IfAvailable)
		::glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	else
	{
		::glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 1);
		//TODO: need to set OpenGL minor version???
		//::glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3); 
	}
	
	createWindow(title, width, height);
}

GlfwApplication::~GlfwApplication(void)
{
	delete m_pGraphics;
	delete m_pInput;
	delete m_pFiles;
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
	return new WindowsTimer();
}

void GlfwApplication::log(const char* tag, const char* message)
{
	::OutputDebugString(tag);
	::OutputDebugString("\t");
	::OutputDebugString(message);
	::OutputDebugString("\n");
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

int GlfwApplication::createWindow(const char* title, int width, int height)
{
	return ((GlfwGraphics*)m_pGraphics)->createWindow(title, width, height);
}