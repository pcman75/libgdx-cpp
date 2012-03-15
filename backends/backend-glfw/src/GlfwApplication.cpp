#include "StdAfx.h"
#include "GlfwApplication.h"
#include "WoglGraphics.h"
#include "WindowsInput.h"
#include "WoglFiles.h"
#include "WindowsAudio.h"

#include "WoglGraphics.h"
#include "Gdx.h"

#include "WindowsTimer.h"

GlfwApplication::GlfwApplication (ApplicationListener& listener, const char* title, int width, int height, bool useGL20IfAvailable)
{
	logLevel = LOG_INFO;
	m_pGraphics = new WoglGraphics(listener, useGL20IfAvailable);
	m_pInput = new WindowsInput();
	m_pFiles = new WoglFiles();
	m_pAudio = new WindowsAudio();
	

	Gdx.app = this;
	Gdx.graphics = m_pGraphics;
	Gdx.audio = m_pAudio;
	Gdx.input = m_pInput;
	Gdx.files = m_pFiles;
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
	int running = GL_TRUE;
	
	// Initialize GLFW
	if( !glfwInit() )
	{
		return EXIT_FAILURE;
	}
	
	// Open an OpenGL window
	if( !glfwOpenWindow(width, height,0,0,0,0,0,0, GLFW_WINDOW) )
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSetWindowTitle(title);

	// Main loop
	while( running )
	{
		// OpenGL rendering goes here...
		//glClear( GL_COLOR_BUFFER_BIT );
		
		// Swap front and back rendering buffers
		glfwSwapBuffers();
		// Check if ESC key was pressed or window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
			glfwGetWindowParam( GLFW_OPENED );
	}
	// Close window and terminate GLFW
	glfwTerminate();
	
	return EXIT_SUCCESS;
}