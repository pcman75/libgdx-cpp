#include "stdafx.h"
#include "BitmapFont.h"

BitmapFont::Glyph::Glyph()
	:kerning(0)
{
}

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
	if(!kerning)
	{
		kerning = new char*[PAGES];
		memset(kerning, NULL, PAGES * sizeof(char*));
	}
	char* page = kerning[ch >> LOG2_PAGE_SIZE];
	if(!page)
	{
		kerning[ch >> LOG2_PAGE_SIZE] = page = new char[PAGE_SIZE];
		memset(page, 0, PAGE_SIZE * sizeof(char));
	}
	page[ch & PAGE_SIZE - 1] = (char)value;
}

BitmapFont::Glyph::~Glyph()
{
	if(kerning)
	{
		for(int i = 0; i < PAGES; i++)
		{
			char* page = kerning[i];		
			delete[] page;
		}

		delete[] kerning;
	}
}
