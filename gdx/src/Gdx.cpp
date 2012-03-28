#include "StdAfx.h"
#include "Gdx.h"

GdxClass::GdxClass()
	:app(NULL),
	graphics(NULL),
	audio(NULL),
	input(NULL),
	files(NULL),
    glVersion(GL_VERSION_0)
{
	
};


bool GdxClass::isGL20Available()
{
//	return gl20 != NULL;
	return true;
}

bool GdxClass::isGL11Available()
{
//	return gl11 != NULL;
	return false;
}
bool GdxClass::isGLInitialised()
{
    return graphics != NULL;
}

GLversion GdxClass::getGLVersion()
{
    return glVersion;
}

GdxClass::~GdxClass()
{
	app = NULL;
	graphics = NULL;
	audio = NULL;
	input = NULL;

	files = NULL;
}

GdxClass Gdx = GdxClass::getInstance();