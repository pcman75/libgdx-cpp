#include "StdAfx.h"
#include "WoglGraphics.h"
#include "WoglGL10.h"
#include "WoglGL11.h"
#include "WoglGL20.h"
#include "Gdx.h"
//#include <glew.h>

WoglGraphics::WoglGraphics(ApplicationListener& listener, bool useGL20)
	:m_listener(listener), m_useGL20(useGL20),
	m_major(-1), m_minor(0)
	//TODO: Temporary
	,mouseLeftDown(false), mouseRightDown(false),
	cameraAngleX(0), cameraAngleY(0), cameraDistance(5)
{
	m_pGL = NULL; 
	m_pGL10 = NULL;
	m_pGL11 = NULL;
	m_pGL20 = NULL;
}


WoglGraphics::~WoglGraphics(void)
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


void WoglGraphics::initializeGLInstances() 
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


bool WoglGraphics::isGL11Available ()
{
	return (m_pGL11 != NULL);
}


bool WoglGraphics::isGL20Available()
{
	return (m_pGL20 != NULL);
}


const GLCommon& WoglGraphics::getGLCommon ()
{
	return *m_pGL;
}

const GL10& WoglGraphics::getGL10 ()
{
	return *m_pGL10;
}

const GL11& WoglGraphics::getGL11 ()
{
	return *m_pGL11;
}	


const GL20& WoglGraphics::getGL20 ()
{
	return *m_pGL20;
}
const GLU& WoglGraphics::getGLU ()
{
	return *m_pGLU;
}
int WoglGraphics::getWidth ()
{
	return m_width;
}
int WoglGraphics::getHeight ()
{
	return m_height;
}
float WoglGraphics::getDeltaTime ()
{
	return 0;
}

int WoglGraphics::getFramesPerSecond ()
{
	//TODO:
	return 0;
}
Graphics::GraphicsType WoglGraphics::getType ()
{
	return WOGL;
}
float WoglGraphics::getPpiX ()
{
	//TODO:
	return 0;
}
float WoglGraphics::getPpiY ()
{
	//TODO:
	return 0;
}
float WoglGraphics::getPpcX ()
{
	//TODO:
	return 0;
}
float WoglGraphics::getPpcY ()
{
	//TODO:
	return 0;
}
float WoglGraphics::getDensity ()
{
	//TODO:
	return -1;
}
bool WoglGraphics::supportsDisplayModeChange ()
{
	//TODO:
	return false;
}
std::vector<Graphics::DisplayMode> WoglGraphics::getDisplayModes ()
{
	//TODO:
	return std::vector<Graphics::DisplayMode>();
}
Graphics::DisplayMode WoglGraphics::getDesktopDisplayMode ()
{
	//TODO:
	return DisplayMode(0, 0,0,0);
}
bool WoglGraphics::setDisplayMode (DisplayMode displayMode)
{
	//TODO:
	return false;
}
bool WoglGraphics::setDisplayMode (int width, int height, bool fullscreen)
{
	//TODO:
	return false;
}

void WoglGraphics::setTitle (std::string title)
{
}
//void WoglGraphics::setIcon (std::vector<Pixmap> pixmaps)
//{
//}
void WoglGraphics::setVSync (bool vsync)
{
}
Graphics::BufferFormat WoglGraphics::getBufferFormat ()
{
	return BufferFormat(0,0,0,0,0,0,0,false);
}
bool WoglGraphics::supportsExtension (std::string extension)
{
	return false;
}



///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL states and scene
///////////////////////////////////////////////////////////////////////////////
void WoglGraphics::init()
{
	
	glewInit();

	glShadeModel(GL_SMOOTH);                        // shading mathod: GL_SMOOTH or GL_FLAT
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);          // 4-byte pixel alignment

	// enable /disable features
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	// track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0, 0, 0, 0);                       // background color
	glClearStencil(0);                              // clear stencil buffer
	glClearDepth(1.0f);                             // 0 is near, 1 is far
	glDepthFunc(GL_LEQUAL);

	initLights();
	setCamera(0, 0, 10, 0, 0, 0);

	

	initializeGLInstances();
	m_listener.create();
}



///////////////////////////////////////////////////////////////////////////////
// initialize lights
///////////////////////////////////////////////////////////////////////////////
void WoglGraphics::initLights()
{
	// set up light colors (ambient, diffuse, specular)
	GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};      // ambient light
	GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};      // diffuse light
	GLfloat lightKs[] = {1, 1, 1, 1};               // specular light
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

	// position the light
	float lightPos[4] = {0, 0, 20, 1}; // positional light
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0);                            // MUST enable each light source after configuration
}



///////////////////////////////////////////////////////////////////////////////
// set camera position and lookat direction
///////////////////////////////////////////////////////////////////////////////
void WoglGraphics::setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}



///////////////////////////////////////////////////////////////////////////////
// configure projection and viewport
///////////////////////////////////////////////////////////////////////////////
void WoglGraphics::setViewport(int w, int h)
{
	m_width = w;
	m_height = h;

	// set viewport to be the entire window
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// set perspective viewing frustum
	float aspectRatio = (float)w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0f, (float)(w)/h, 0.1f, 20.0f); // FOV, AspectRatio, NearClip, FarClip

	// switch to modelview matrix in order to set scene
	glMatrixMode(GL_MODELVIEW);
}



///////////////////////////////////////////////////////////////////////////////
// draw 2D/3D scene
///////////////////////////////////////////////////////////////////////////////
void WoglGraphics::draw()
{
	// clear buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// save the initial ModelView matrix before modifying ModelView matrix
	glPushMatrix();

	// tramsform camera
	glTranslatef(0, 0, cameraDistance);
	glRotatef(cameraAngleX, 1, 0, 0);   // pitch
	glRotatef(cameraAngleY, 0, 1, 0);   // heading

	m_listener.render();

	glPopMatrix();
}



///////////////////////////////////////////////////////////////////////////////
// rotate the camera
///////////////////////////////////////////////////////////////////////////////
void WoglGraphics::rotateCamera(int x, int y)
{
	if(mouseLeftDown)
	{
		cameraAngleY += (x - mouseX);
		cameraAngleX += (y - mouseY);
		mouseX = x;
		mouseY = y;
	}
}



///////////////////////////////////////////////////////////////////////////////
// zoom the camera
///////////////////////////////////////////////////////////////////////////////
void WoglGraphics::zoomCamera(int delta)
{
	if(mouseRightDown)
	{
		cameraDistance += (delta - mouseY) * 0.05f;
		mouseY = delta;
	}
}



