#include "stdafx.h"
#include "BitmapFont.h"

///////////////////////////////////////////////////////////////
//TextBounds
BitmapFont::TextBounds::TextBounds()
{
}

BitmapFont::TextBounds::TextBounds(const TextBounds& bounds)
{
	set(bounds);
}

void BitmapFont::TextBounds::set(const TextBounds& bounds)
{
	width = bounds.width;
	height = bounds.height;
}
