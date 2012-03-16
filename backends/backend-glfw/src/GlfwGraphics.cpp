#include "StdAfx.h"
#include "GlfwGraphics.h"
#include "WoglGL10.h"
#include "WoglGL11.h"
#include "WoglGL20.h"
#include "Gdx.h"
#include "WindowsTimer.h"
#include "GdxRuntimeException.h"
#include "GlfwInput.h"

GlfwGraphics::GlfwGraphics(ApplicationListener& listener, bool useGL20)
	:m_listener(listener), m_useGL20(useGL20),
	m_major(-1), m_minor(0)
{
	m_pGL = NULL; 
	m_pGL10 = NULL;
	m_pGL11 = NULL;
	m_pGL20 = NULL;

	m_deltaTime = 0;
}


GlfwGraphics::~GlfwGraphics(void)
{
	//delete only m_pGL the other GL pointers are casts of pointers of the same object
	if(m_pGL)
	{
		delete m_pGL;
		m_pGL = NULL; 
		m_pGL10 = NULL;
		m_pGL11 = NULL;
		m_pGL20 = NULL;
		Gdx.gl = NULL;
		Gdx.gl10 = NULL;
		Gdx.gl11 = NULL;
		Gdx.gl20 = NULL;
	}
}


void GlfwGraphics::initializeGLInstances() 
{
	WoglGLCommon ogl;

	std::string version = ogl.glGetString(GL10::GDX_GL_VERSION);
	std::string renderer = ogl.glGetString(GL10::GDX_GL_RENDERER);

	const char* szVersion = version.c_str();
	m_major = atoi(szVersion);
	m_minor = atoi(szVersion + 2);

	if (m_useGL20 && m_major >= 2)
	{
		m_pGL20 = new WoglGL20();
		m_pGL = m_pGL20;	
	} 
	else 
	{
		if (m_major == 1 && m_minor < 5 || renderer == "Mirage Graphics3") 
		{
			m_pGL10 = new WoglGL10();
		} 
		else 
		{
			m_pGL11 = new WoglGL11();
			m_pGL10 = m_pGL11;
		}
		m_pGL = m_pGL10;
	}

	Gdx.gl = m_pGL;
	Gdx.gl10 = m_pGL10;
	Gdx.gl11 = m_pGL11;
	Gdx.gl20 = m_pGL20;
}


bool GlfwGraphics::isGL11Available ()
{
	return (m_pGL11 != NULL);
}


bool GlfwGraphics::isGL20Available()
{
	return (m_pGL20 != NULL);
}


GLCommon* GlfwGraphics::getGLCommon ()
{
	return m_pGL;
}

GL10* GlfwGraphics::getGL10()
{
	return m_pGL10;
}

GL11* GlfwGraphics::getGL11 ()
{
	return m_pGL11;
}	


GL20* GlfwGraphics::getGL20()
{
	return m_pGL20;
}
GLU* GlfwGraphics::getGLU()
{
	return m_pGLU;
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
	if( !glfwOpenWindow( width, height, 0,0,0,0, 0,0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		throw GdxRuntimeException("Failed to open GLFW window");
	}
	glfwSetWindowTitle(title);
	
	initializeGLInstances();
	m_listener.create();

	m_frameStart = m_timer.systemNanoSeconds();
	m_lastFrameTime = m_frameStart;
	m_deltaTime = 0;
}

void GlfwGraphics::runOpenGLLoop()
{
	do
	{
		// Get window size (may be different than the requested size)
		glfwGetWindowSize( &m_width, &m_height );
		
		// Special case: avoid division by zero below
		m_height = m_height > 0 ? m_height : 1;

		updateTimes();
		m_listener.render();

		// Swap buffers
		glfwSwapBuffers();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		glfwGetWindowParam( GLFW_OPENED ) );
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


