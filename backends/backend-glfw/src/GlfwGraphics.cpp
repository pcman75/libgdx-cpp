#include "StdAfx.h"
#include "GlfwGraphics.h"
#include "Gdx.h"
#include "GdxRuntimeException.h"
#include "GlfwInput.h"

GlfwGraphics::GlfwGraphics(ApplicationListener& listener, bool useGL20)
	:m_listener(listener), m_useGL20(useGL20),
	m_major(-1), m_minor(0)
{
	m_deltaTime = 0;
}


GlfwGraphics::~GlfwGraphics(void)
{
}


bool GlfwGraphics::isGL11Available ()
{
	return Gdx.isGL11Available();
}


bool GlfwGraphics::isGL20Available()
{
	return Gdx.isGL20Available();
}

int GlfwGraphics::getWidth ()
{
	return m_width;
}
int GlfwGraphics::getHeight ()
{
	return m_height;
}
float GlfwGraphics::getDeltaTime ()
{
	return m_deltaTime;
}

int GlfwGraphics::getFramesPerSecond ()
{
	return m_fps;
}
Graphics::GraphicsType GlfwGraphics::getType ()
{
	return WOGL;
}
float GlfwGraphics::getPpiX ()
{
	//TODO:
	return 0;
}
float GlfwGraphics::getPpiY ()
{
	//TODO:
	return 0;
}
float GlfwGraphics::getPpcX ()
{
	//TODO:
	return 0;
}
float GlfwGraphics::getPpcY ()
{
	//TODO:
	return 0;
}
float GlfwGraphics::getDensity ()
{
	//TODO:
	return -1;
}
bool GlfwGraphics::supportsDisplayModeChange ()
{
	//TODO:
	return false;
}
std::vector<Graphics::DisplayMode> GlfwGraphics::getDisplayModes ()
{
	//TODO:
	return std::vector<Graphics::DisplayMode>();
}
Graphics::DisplayMode GlfwGraphics::getDesktopDisplayMode ()
{
	//TODO:
	return DisplayMode(0, 0,0,0);
}
bool GlfwGraphics::setDisplayMode (DisplayMode displayMode)
{
	//TODO:
	return false;
}
bool GlfwGraphics::setDisplayMode (int width, int height, bool fullscreen)
{
	//TODO:
	return false;
}

void GlfwGraphics::setTitle (std::string title)
{
}

//void GlfwGraphics::setIcon (std::vector<Pixmap> pixmaps)
//{
//}

void GlfwGraphics::setVSync (bool vsync)
{
}
Graphics::BufferFormat GlfwGraphics::getBufferFormat ()
{
	return BufferFormat(0,0,0,0,0,0,0,false);
}
bool GlfwGraphics::supportsExtension (std::string extension)
{
	return false;
}


void GlfwGraphics::createWindow(const char* title, int width, int height)
{
	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( width, height, 0, 0, 0, 0, 0, 0, GLFW_WINDOW ) )
	{
		::glfwTerminate();
		throw GdxRuntimeException("Failed to open GLFW window");
	}
	::glfwSetWindowTitle(title);
	
	//initializa glew
	glewInit();

	updateSize();

	//TODO: implement also window resize
	//setup a callback?

	m_listener.create();

	m_frameStart = m_timer.systemNanoSeconds();
	m_lastFrameTime = m_frameStart;
	m_deltaTime = 0;
}

void GlfwGraphics::runOpenGLLoop()
{
	do
	{
		updateSize();
		updateTimes();

		m_listener.render();

		// Swap buffers
		::glfwSwapBuffers();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		::glfwGetWindowParam( GLFW_OPENED ) );
}

void GlfwGraphics::updateSize()
{
	::glfwGetWindowSize( &m_width, &m_height );
	m_height = m_height > 0 ? m_height : 1;
}

void GlfwGraphics::dispose()
{
	m_listener.dispose();
}

void GlfwGraphics::updateTimes() 
{
	m_deltaTime = (m_timer.systemNanoSeconds() - m_lastFrameTime) / 10.0E9f;
	m_lastFrameTime = m_timer.systemNanoSeconds();

	if(m_timer.systemNanoSeconds() - m_frameStart > 10E9) 
	{
		m_fps = m_frames;
		m_frames = 0;
		m_frameStart = m_timer.systemNanoSeconds();
	}
	m_frames++;
}


