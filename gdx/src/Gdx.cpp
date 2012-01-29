#include "StdAfx.h"
#include "Gdx.h"

GdxClass::GdxClass()
	:app(NULL),
	graphics(NULL),
	audio(NULL),
	input(NULL),

	files(NULL),
	gl(NULL),
	gl10(NULL),
	gl11(NULL),
	gl20(NULL),
	glu(NULL)
{
	
}

bool GdxClass::isGL20Available()
{
	return gl20 != NULL;
}

bool GdxClass::isGL11Available()
{
	return gl11 != NULL;
}

GdxClass Gdx = GdxClass::getInstance();