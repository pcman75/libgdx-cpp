#include "stdafx.h"
#include "BitmapFont.h"


///////////////////////////////////////////////////////////////
//Glyph
int BitmapFont::Glyph::getKerning(char ch)
{
	if(kerning)
	{
		char* page = kerning[ch >> LOG2_PAGE_SIZE];
		if(page) 
			return page[ch & PAGE_SIZE - 1];
	}
	return 0;
}

void BitmapFont::Glyph::setKerning(int ch, int value)
{
	if(kerning) 
		kerning = new char*[PAGES];
	char* page = kerning[ch >> LOG2_PAGE_SIZE];
	if(!page) 
		kerning[ch >> LOG2_PAGE_SIZE] = page = new char[PAGE_SIZE];
	page[ch & PAGE_SIZE - 1] = (char)value;
}
