#include "stdafx.h"
#include "BitmapFont.h"
#include "StringTokenizer.h"

using namespace std;

void split(const char* line, vector<string>& tokens)
{
	istringstream iss(line);
    copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter<vector<string>>(tokens));
}

bool startsWith(const string& str, const char* with)
{
	return str.compare(0, strlen(with), with) == 0;
}

bool endsWith(const string& str, const char* with)
{
	int lenWidth = strlen(with);
	int lenStr = str.size();
	return str.compare(lenStr - lenWidth, strlen(with), with) == 0;
}

void makeSamePathAs(const char* sibling, const char* filename, string& result)
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath(sibling, drive, dir, fname, ext);

	char resbuf[MAX_PATH];
	_makepath(resbuf, drive, dir, filename, NULL);
	result = resbuf;
}

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

BitmapFont::BitmapFontData::BitmapFontData(const FileHandle& fontFile, bool flip)
	:capHeight(1), scaleX(1), scaleY(1),
	m_lineHeight(0.f), ascent(0.f), descent(0.f), down(0.f), spaceWidth(0.f), 
	m_fontFile(fontFile), m_flipped(flip)
{
	glyphs = new Glyph**[PAGES];
	memset(glyphs, NULL, PAGES * sizeof(void*));

	int maxBuf = 1024;
	char* line = new char[maxBuf];

	FileHandleStream* reader =  m_fontFile.getStream(Read, String);
	try
	{
		line = reader->readLine(line, maxBuf); // info
	
		line = reader->readLine(line, maxBuf);
		if(!line)
			throw new GdxRuntimeException("Invalid font file: " + m_fontFile.getFullPathName());
		
		vector<string> common;
		split(line, common);
		if(common.size() < 4) 
			throw new GdxRuntimeException("Invalid font file: " + m_fontFile.getFullPathName());

		if(!startsWith(common[1], "lineHeight="))
			throw new GdxRuntimeException("Invalid font file: " + m_fontFile.getFullPathName());
		m_lineHeight = atoi(common[1].substr(11).c_str());
		
		if(!startsWith(common[2], "base="))
			throw new GdxRuntimeException("Invalid font file: " + m_fontFile.getFullPathName());
		int baseLine = atoi(common[2].substr(5).c_str());

		line = reader->readLine(line, maxBuf);
		if(!line) 
			throw new GdxRuntimeException("Invalid font file: " + m_fontFile.getFullPathName());

		vector<string> pageLine;
		split(line, pageLine);
		if(!startsWith(pageLine[2], "file=")) 
			throw new GdxRuntimeException("Invalid font file: " + m_fontFile.getFullPathName());
		
		string imgFilename;
		if(endsWith(pageLine[2], "\""))
		{
			imgFilename = pageLine[2].substr(6, pageLine[2].length() - 1 - 6);
		}
		else
		{
			imgFilename = pageLine[2].substr(5, pageLine[2].length() - 6);
		}

		//TODO:
		//imagePath = m_fontFile.parent().child(imgFilename).path().replaceAll("\\\\", "/");
		//I don't think this works on something else except Windows but right now 
		//FileHandle parent and child are not implemented
		makeSamePathAs(m_fontFile.getFullPathName().c_str(), imgFilename.c_str(), m_imagePath);
		descent = 0;

		while(true)
		{
			line = reader->readLine(line, maxBuf);
			if(line == NULL) 
				break;
			if(startsWith(line, "kernings ")) 
				break;
			if(!startsWith(line, "char ")) 
				continue;

			Glyph* glyph = new Glyph();

			StringTokenizer tokens(line, " =");
			tokens.nextToken();
			tokens.nextToken();
			int ch = atoi(tokens.nextToken().c_str());
			if(ch <= MAXCHAR)
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
			line = reader->readLine(line, maxBuf);
			if(line == NULL) 
				break;
			if(!startsWith(line, "kerning ")) 
				break;

			StringTokenizer tokens(line, " =");
			tokens.nextToken();
			tokens.nextToken();
			int first = atoi(tokens.nextToken().c_str());
			tokens.nextToken();
			int second = atoi(tokens.nextToken().c_str());
			if(first < 0 || first > MAXCHAR || second < 0 || second > MAXCHAR) 
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
			xGlyph = getGlyph(xChars[i]);
			if(xGlyph != NULL) 
				break;
		}
		if(xGlyph == NULL) 
			xGlyph = getFirstGlyph();
		xHeight = xGlyph->height;

		Glyph* capGlyph = NULL;
		for(int i = 0; i < 26; i++)
		{
			capGlyph = getGlyph(capChars[i]);
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
		delete reader;
		delete[] line;

		throw new GdxRuntimeException("Error loading font file: " + m_fontFile.getFullPathName());
	}
}


void BitmapFont::BitmapFontData::setGlyph(int ch, Glyph* glyph)
{
	Glyph** page = glyphs[ch / PAGE_SIZE];
	if(!page)
	{
		glyphs[ch / PAGE_SIZE] = page = new Glyph*[PAGE_SIZE];
		memset(page, NULL, PAGE_SIZE * sizeof(void*));
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

FileHandle& BitmapFont::BitmapFontData::getFontFile()
{
	return m_fontFile;
}
