#include "StdAfx.h"
#include "Gdx.h"

GdxClass::GdxClass()
	:app(NULL),
	graphics(NULL),
	audio(NULL),
	input(NULL),
	files(NULL)
{
	
};


bool GdxClass::isGL20Available()
{
    return (graphics != NULL && graphics->getGlVersion() == GL_VERSION_20);
}

bool GdxClass::isGL11Available()
{
    return (graphics != NULL 
            && (graphics->getGlVersion() == GL_VERSION_11 
             || graphics->getGlVersion() == GL_VERSION_10));
}
bool GdxClass::isGLInitialised()
{
    return graphics != NULL;
}

GlVersion GdxClass::getGlVersion()
{
    if (graphics == NULL)
        return GL_VERSION_0;
    return graphics->getGlVersion();
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