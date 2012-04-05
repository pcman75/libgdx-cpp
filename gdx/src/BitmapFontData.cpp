#include "stdafx.h"
#include "BitmapFont.h"
#include "StringTokenizer.h"
#include "StringUtils.h"

using namespace std;

BitmapFont::BitmapFontData::~BitmapFontData()
{
	for(int i = 0; i < PAGES; i++)
	{
		Glyph** page = this->glyphs[i];
		if(page)
		{
			for(int j = 0; j < PAGE_SIZE; j++)
			{
				//delete the glyph
				delete page[j];
			}
			delete[] page;
		}
	}
	delete[] glyphs;
}

BitmapFont::BitmapFontData::BitmapFontData(const FileHandle* fontFile, bool flip)
	:capHeight(1), scaleX(1), scaleY(1),
	m_lineHeight(0.f), ascent(0.f), descent(0.f), down(0.f), spaceWidth(0.f), 
	m_flipped(flip)
{
	glyphs = new Glyph**[PAGES];
	memset(glyphs, 0, PAGES * sizeof(void*));

	const int lineMax = 2048;
	char* line = new char[lineMax];

    std::ifstream reader;
    fontFile->read(reader); 
	try
	{
        reader.getline(	line, lineMax);// info 
	
		reader.getline(	line, lineMax);
		if(reader.fail())
			throw new GdxRuntimeException("Invalid font file: " + fontFile->getFullPathName());
		
		vector<string> common;
		StringTokenizer::split(line, common);
		if(common.size() < 4) 
			throw new GdxRuntimeException("Invalid font file: " + fontFile->getFullPathName());

		if(!StringUtils::startsWith(common[1], "lineHeight="))
			throw new GdxRuntimeException("Invalid font file: " + fontFile->getFullPathName());
		m_lineHeight = atoi(common[1].substr(11).c_str());
		
		if(!StringUtils::startsWith(common[2], "base="))
			throw new GdxRuntimeException("Invalid font file: " + fontFile->getFullPathName());
		int baseLine = atoi(common[2].substr(5).c_str());

		reader.getline(	line, lineMax);
		if(reader.fail()) 
			throw new GdxRuntimeException("Invalid font file: " + fontFile->getFullPathName());

		vector<string> pageLine;
		StringTokenizer::split(line, pageLine);
		if(!StringUtils::startsWith(pageLine[2], "file=")) 
			throw new GdxRuntimeException("Invalid font file: " + fontFile->getFullPathName());
		
		string imgFilename;
		if(StringUtils::endsWith(pageLine[2], "\""))
		{
			imgFilename = pageLine[2].substr(6, pageLine[2].length() - 1 - 6);
		}
		else
		{
			imgFilename = pageLine[2].substr(5, pageLine[2].length() - 6);
		}

		FileHandle* parent = fontFile->parent();
     FileHandle* child = parent->child(imgFilename.c_str());
     m_imagePath = child->getFullPathName();
     delete child;
     delete parent;
        
        
		descent = 0;

		while(true)
		{
			reader.getline(	line, lineMax);
			if(reader.eof() || reader.fail()) 
				break;
			if(StringUtils::startsWith(line, "kernings ")) 
				break;
			if(!StringUtils::startsWith(line, "char ")) 
				continue;

			Glyph* glyph = new Glyph();

			StringTokenizer tokens(line, " =");
			tokens.nextToken();
			tokens.nextToken();
			int ch = atoi(tokens.nextToken().c_str());
			if(ch <= CHAR_MAX)
				setGlyph(ch, glyph);
			else
				continue;
			tokens.nextToken();
			glyph->srcX = atoi(tokens.nextToken().c_str());
			tokens.nextToken();
			glyph->srcY = atoi(tokens.nextToken().c_str());
			tokens.nextToken();
			glyph->width = atoi(tokens.nextToken().c_str());
			tokens.nextToken();
			glyph->height = atoi(tokens.nextToken().c_str());
			tokens.nextToken();
			glyph->xoffset = atoi(tokens.nextToken().c_str());
			tokens.nextToken();
			if(flip)
				glyph->yoffset = atoi(tokens.nextToken().c_str());
			else
				glyph->yoffset = -(glyph->height + atoi(tokens.nextToken().c_str()));
			tokens.nextToken();
			glyph->xadvance = atoi(tokens.nextToken().c_str());
			if(glyph->width > 0 && glyph->height > 0) 
				descent = min(baseLine + glyph->yoffset, descent);
		}

		while(true)
		{
        reader.getline(	line, lineMax);
			if(reader.eof() || reader.fail()) 
				break;
            
			if(!StringUtils::startsWith(line, "kerning ")) 
				break;

			StringTokenizer tokens(line, " =");
			tokens.nextToken();
			tokens.nextToken();
			int first = atoi(tokens.nextToken().c_str());
			tokens.nextToken();
			int second = atoi(tokens.nextToken().c_str());
			if(first < 0 || first > CHAR_MAX || second < 0 || second > CHAR_MAX) 
				continue;
			Glyph* glyph = getGlyph((char)first);
			tokens.nextToken();
			int amount = atoi(tokens.nextToken().c_str());
			glyph->setKerning(second, amount);
		}

		Glyph* spaceGlyph = getGlyph(' ');
		if(spaceGlyph == NULL)
		{
			spaceGlyph = new Glyph();
			Glyph* xadvanceGlyph = getGlyph('l');
			if(xadvanceGlyph == NULL) xadvanceGlyph = getFirstGlyph();
			spaceGlyph->xadvance = xadvanceGlyph->xadvance;
			setGlyph(' ', spaceGlyph);
		}
		spaceWidth = spaceGlyph != NULL ? spaceGlyph->xadvance + spaceGlyph->width : 1;

		Glyph* xGlyph = NULL;
		for(int i = 0; i < 13; i++)
		{
			xGlyph = getGlyph(m_xChars[i]);
			if(xGlyph != NULL) 
				break;
		}
		if(xGlyph == NULL) 
			xGlyph = getFirstGlyph();
		xHeight = xGlyph->height;

		Glyph* capGlyph = NULL;
		for(int i = 0; i < 26; i++)
		{
			capGlyph = getGlyph(m_capChars[i]);
			if(capGlyph != NULL) break;
		}
		if(capGlyph == NULL)
		{
			for(int i = 0; i < PAGES; i++)
			{
				Glyph** page = this->glyphs[i];
			
				if(page == NULL) 
					continue;

				for(int j = 0; j < PAGE_SIZE; j++)
				{
					Glyph* glyph = page[j];
					if(glyph == NULL || glyph->height == 0 || glyph->width == 0)
						continue;
					capHeight = max(capHeight, glyph->height);
				}
			}
		}
		else
			capHeight = capGlyph->height;

		ascent = baseLine - capHeight;
		down = -m_lineHeight;
		if(flip)
		{
			ascent = -ascent;
			down = -down;
		}
	}
	catch(GdxRuntimeException& ex)
	{
		delete[] line;

		throw new GdxRuntimeException("Error loading font file: " + fontFile->getFullPathName());
	}
}


void BitmapFont::BitmapFontData::setGlyph(int ch, Glyph* glyph)
{
	Glyph** page = glyphs[ch / PAGE_SIZE];
	if(!page)
	{
		glyphs[ch / PAGE_SIZE] = page = new Glyph*[PAGE_SIZE];
		memset(page, 0, PAGE_SIZE * sizeof(void*));
	}
	page[ch & PAGE_SIZE - 1] = glyph;
}

BitmapFont::Glyph* BitmapFont::BitmapFontData::getFirstGlyph()
{
	for(int i = 0; i < PAGES; i++)
	{
		Glyph** page = this->glyphs[i];
		if(!page) 
			continue;
		for(int j = 0; j < PAGE_SIZE; j++)
		{
			Glyph* glyph = page[j];
			if(glyph == NULL || glyph->height == 0 || glyph->width == 0) 
				continue;
			return glyph;
		}
	}
	throw new GdxRuntimeException("No glyphs found!");
}

BitmapFont::Glyph* BitmapFont::BitmapFontData::getGlyph(char ch)
{
	Glyph** page = glyphs[ch / PAGE_SIZE];
	if(page) 
		return page[ch & PAGE_SIZE - 1];
	return NULL;
}

string& BitmapFont::BitmapFontData::getImagePath()
{
	return m_imagePath;
}
