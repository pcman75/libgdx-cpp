#include "stdafx.h"
#include "BitmapFont.h"
#include "NumberUtils.h"

///////////////////////////////////////////////////////////////
//BitmapFont
const int BitmapFont::LOG2_FONT_PAGE_SIZE = 9;
const int BitmapFont::FONT_PAGE_SIZE = 1 << LOG2_FONT_PAGE_SIZE;
const int BitmapFont::PAGES = 0x10000 / FONT_PAGE_SIZE;

const char BitmapFont::m_xChars[] = {'x', 'e', 'a', 'o', 'n', 's', 'r', 'c', 'u', 'm', 'v', 'w', 'z'};
const char BitmapFont::m_capChars[] = {'M', 'N', 'B', 'D', 'C', 'E', 'F', 'K', 'A', 'G', 'H', 'I', 'J', 'L', 'O', 'P', 'Q', 'R', 'S',
	'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};


void BitmapFont::init()
{
	m_color = Color::WHITE.toFloatBits();
	m_tempColor = Color(1, 1, 1, 1);
	m_integer = true;
	m_ownsBitmapFontData = false;
	m_region = NULL;
}

BitmapFont::~BitmapFont()
{
	if(m_ownsTexture)
	{
		Texture* texture = m_region->getTexture();
		texture->dispose();
		delete texture;
		texture = NULL;

		delete m_region;
		m_region = NULL;
	}
	if(m_ownsBitmapFontData)
	{
		delete m_data;
		m_data = NULL;
	}
}

/** Creates a BitmapFont using the default 15pt Arial font included in the libgdx JAR file. This is convenient to easily display
* text without bothering with generating a bitmap font. */
BitmapFont::BitmapFont()
{
	init();

	//TODO:
	//init(Gdx.files->classpathHandle("com/badlogic/gdx/utils/arial-15.fnt"),
	//	Gdx.files->classpathHandle("com/badlogic/gdx/utils/arial-15.png"), false, true);
	init(Gdx.files->internalHandle("data/arial-15.fnt"),
		Gdx.files->internalHandle("data/arial-15.png"), false, true);
}

/** Creates a BitmapFont using the default 15pt Arial font included in the libgdx JAR file. This is convenient to easily display
* text without bothering with generating a bitmap font.
* @param flip If true, the glyphs will be flipped for use with a perspective where 0,0 is the upper left corner. */
BitmapFont::BitmapFont(bool flip)
{
	init();
	//TODO:
	//init(Gdx.files->classpathHandle("com/badlogic/gdx/utils/arial-15.fnt"),
	//	Gdx.files->classpathHandle("com/badlogic/gdx/utils/arial-15.png"), flip, true);
	init(Gdx.files->internalHandle("data/arial-15.fnt"),
		Gdx.files->internalHandle("data/arial-15.png"), flip, true);
}

/** Creates a BitmapFont with the glyphs relative to the specified region. If the region is NULL, the glyph textures are loaded
* from the image file given in the font file. The {@link #dispose()} method will not dispose the region's texture in this
* case!
* @param region The texture region containing the glyphs. The glyphs must be relative to the lower left corner (ie, the region
*           should not be flipped). If the region is NULL the glyph images are loaded from the image path in the font file.
* @param flip If true, the glyphs will be flipped for use with a perspective where 0,0 is the upper left corner. */
BitmapFont::BitmapFont(const FileHandle& fontFile, TextureRegion* region, bool flip)
{
	init();
	init(new BitmapFontData(fontFile, flip), region, true);
	m_ownsBitmapFontData = true;
}

/** Creates a BitmapFont from a BMFont file. The image file name is read from the BMFont file and the image is loaded from the
* same directory.
* @param flip If true, the glyphs will be flipped for use with a perspective where 0,0 is the upper left corner. */
BitmapFont::BitmapFont(const FileHandle& fontFile, bool flip)
{
	init();
	init(new BitmapFontData(fontFile, flip), NULL, true);
	m_ownsBitmapFontData = true;
}

/** Creates a BitmapFont from a BMFont file, using the specified image for glyphs. Any image specified in the BMFont file is
* ignored.
* @param flip If true, the glyphs will be flipped for use with a perspective where 0,0 is the upper left corner. */
BitmapFont::BitmapFont(const FileHandle& fontFile, const FileHandle& imageFile, bool flip)
{
	init();
	init(fontFile, imageFile, flip, true);
}

/** Creates a BitmapFont from a BMFont file, using the specified image for glyphs. Any image specified in the BMFont file is
* ignored.
* @param flip If true, the glyphs will be flipped for use with a perspective where 0,0 is the upper left corner.
* @param integer If true, rendering positions will be at integer values to avoid filtering artifacts.s */
BitmapFont::BitmapFont(const FileHandle& fontFile, const FileHandle& imageFile, bool flip, bool integer)
{
	init();
	init(fontFile, imageFile, flip, integer);
}

/** Constructs a new BitmapFont from the given {@link BitmapFontData} and {@link TextureRegion}. If the TextureRegion is NULL,
* the image path is read from the BitmapFontData. The dispose() method will not dispose the texture of the region if the
* region is != NULL.
* @param data
* @param region
* @param integer */
BitmapFont::BitmapFont(BitmapFontData* data, TextureRegion* region, bool integer)
{
	init();
	init(data, region, integer);
}


void BitmapFont::init(const FileHandle& fontFile, const FileHandle& imageFile, bool flip, bool integer)
{
	init(new BitmapFontData(fontFile, flip), new TextureRegion(new Texture(imageFile, false)), integer);
	m_ownsTexture = true;
	m_ownsBitmapFontData = true;
}

void BitmapFont::init(BitmapFontData* data, TextureRegion* region, bool integer)
{
	//TODO:
	//this->region = region == NULL ? new TextureRegion(new Texture(Gdx.files->internalHandle(data->m_imagePath), false)) : region;
	m_region = region == NULL ? new TextureRegion(new Texture(Gdx.files->absoluteHandle(data->m_imagePath), false)) : region;

	m_flipped = data->m_flipped;
	m_integer = integer;
	m_data = data;
	load(data);
	m_ownsTexture = region == NULL;
}

void BitmapFont::load(BitmapFontData* data)
{
	float invTexWidth = 1.0f / m_region->getTexture()->getWidth();
	float invTexHeight = 1.0f / m_region->getTexture()->getHeight();
	float u = m_region->getU();
	float v = m_region->getV();

	for(int i = 0; i < PAGES; i++)
	{
		Glyph** page = data->glyphs[i];
		
		if(page == NULL) 
			continue;
		
		for(int j = 0; j < FONT_PAGE_SIZE; j++)
		{
			Glyph* glyph = page[j];
		
			if(glyph == NULL) 
				continue;
			glyph->u = u + glyph->srcX * invTexWidth;
			glyph->u2 = u + (glyph->srcX + glyph->width) * invTexWidth;
			if(data->m_flipped)
			{
				glyph->v = v + glyph->srcY * invTexHeight;
				glyph->v2 = v + (glyph->srcY + glyph->height) * invTexHeight;
			}
			else
			{
				glyph->v2 = v + glyph->srcY * invTexHeight;
				glyph->v = v + (glyph->srcY + glyph->height) * invTexHeight;
			}
		}
	}
}

/** Draws a string at the specified position.
* @param x The x position for the left most character.
* @param y The y position for the top of most capital letters in the font (the {@link #getCapHeight() cap height}).
* @return The bounds of the rendered string (the height is the distance from y to the baseline). Note the same TextBounds
*         instance is used for all methods that return TextBounds. */
BitmapFont::TextBounds& BitmapFont::draw(SpriteBatch* spriteBatch, const std::string& str, float x, float y)
{
	return draw(spriteBatch, str, x, y, 0, (int)str.length());
}

/** Draws a substring at the specified position.
* @param x The x position for the left most character.
* @param y The y position for the top of most capital letters in the font (the {@link #getCapHeight() cap height}).
* @param start The first character of the string to draw.
* @param end The last character of the string to draw (exclusive).
* @return The bounds of the rendered string (the height is the distance from y to the baseline). Note the same TextBounds
*         instance is used for all methods that return TextBounds. */
BitmapFont::TextBounds& BitmapFont::draw(SpriteBatch* spriteBatch, const std::string& str, float x, float y, int start, int end)
{
	float batchColor = spriteBatch->getColor().toFloatBits();
	spriteBatch->setColor(m_color);

	Texture* texture = m_region->getTexture();
	y += m_data->ascent;
	float startX = x;
	Glyph* lastGlyph = NULL;
	if(m_data->scaleX == 1 && m_data->scaleY == 1)
	{
		if(m_integer)
		{
			y = ( float) (int)y;
			x = ( float) (int)x;
		}
		while(start < end)
		{
			lastGlyph = m_data->getGlyph(str.at(start++));
			if(lastGlyph != NULL)
			{
				spriteBatch->draw(texture, //
					x + lastGlyph->xoffset, y + lastGlyph->yoffset, //
					( float) lastGlyph->width, ( float) lastGlyph->height, //
					lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2);
				x += lastGlyph->xadvance;
				break;
			}
		}
		while(start < end)
		{
			char ch = str.at(start++);
			Glyph* g = m_data->getGlyph(ch);
			if(!g) 
				continue;
			x += lastGlyph->getKerning(ch);
			if(m_integer) 
				x = ( float) ( (int)x);
			lastGlyph = g;
			spriteBatch->draw(texture, //
				x + lastGlyph->xoffset, y + lastGlyph->yoffset, //
				( float) lastGlyph->width, ( float) lastGlyph->height, //
				lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2);
			x += g->xadvance;
		}
	}
	else
	{
		float scaleX = m_data->scaleX, scaleY = m_data->scaleY;
		while(start < end)
		{
			lastGlyph = m_data->getGlyph(str.at(start++));
			if(lastGlyph != NULL)
			{
				if(!m_integer)
				{
					spriteBatch->draw(texture, //
						x + lastGlyph->xoffset * scaleX, //
						y + lastGlyph->yoffset * scaleY, //
						lastGlyph->width * scaleX, //
						lastGlyph->height * scaleY, //
						lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2);
				}
				else
				{
					spriteBatch->draw(texture, //
						(float)(int)(x + lastGlyph->xoffset * scaleX), //
						(float)(int)(y + lastGlyph->yoffset * scaleY), //
						(float)(int)(lastGlyph->width * scaleX), //
						(float)(int)(lastGlyph->height * scaleY), //
						lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2);
				}
				x += lastGlyph->xadvance * scaleX;
				break;
			}
		}
		while(start < end)
		{
			char ch = str.at(start++);
			Glyph* g = m_data->getGlyph(ch);
			if(g == NULL) continue;
			x += lastGlyph->getKerning(ch) * scaleX;
			lastGlyph = g;
			if(!m_integer)
			{
				spriteBatch->draw(texture, //
					x + lastGlyph->xoffset * scaleX, //
					y + lastGlyph->yoffset * scaleY, //
					lastGlyph->width * scaleX, //
					lastGlyph->height * scaleY, //
					lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2);
			}
			else
			{
				spriteBatch->draw(texture, //
					(float)(int)(x + lastGlyph->xoffset * scaleX), //
					(float)(int)(y + lastGlyph->yoffset * scaleY), //
					(float)(int)(lastGlyph->width * scaleX), //
					(float)(int)(lastGlyph->height * scaleY), //
					lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2);
			}
			x += g->xadvance * scaleX;
		}
	}
	spriteBatch->setColor(batchColor);
	m_textBounds.width = x - startX;
	m_textBounds.height = m_data->capHeight;
	return m_textBounds;
}

/** Draws a string, which may contain newlines (\n), at the specified position.
* @param x The x position for the left most character.
* @param y The y position for the top of most capital letters in the font (the {@link #getCapHeight() cap height}).
* @return The bounds of the rendered string (the height is the distance from y to the baseline of the last line). Note the
*         same TextBounds instance is used for all methods that return TextBounds. */
BitmapFont::TextBounds& BitmapFont::drawMultiLine(SpriteBatch* spriteBatch, const std::string& str, float x, float y)
{
	return drawMultiLine(spriteBatch, str, x, y, 0, LEFT);
}

/** Draws a string, which may contain newlines (\n), at the specified position and alignment. Each line is aligned horizontally
* within a rectangle of the specified width.
* @param x The x position for the left most character.
* @param y The y position for the top of most capital letters in the font (the {@link #getCapHeight() cap height}).
* @return The bounds of the rendered string (the height is the distance from y to the baseline of the last line). Note the
*         same TextBounds instance is used for all methods that return TextBounds. */
BitmapFont::TextBounds& BitmapFont::drawMultiLine(SpriteBatch* spriteBatch, const std::string& str, float x, float y, float alignmentWidth,
	HAlignment alignment)
{
	float batchColor = spriteBatch->getColor().toFloatBits();
	float down = m_data->down;
	int start = 0;
	int numLines = 0;
	int length = ( int) str.length();
	float maxWidth = 0;
	while(start < length)
	{
		int lineEnd = indexOf(str, '\n', start);
		float xOffset = 0;
		if(alignment != LEFT)
		{
			float lineWidth = getBounds(str, start, lineEnd).width;
			xOffset = alignmentWidth - lineWidth;
			if(alignment == CENTER) xOffset = xOffset / 2;
		}
		float lineWidth = draw(spriteBatch, str, x + xOffset, y, start, lineEnd).width;
		maxWidth = max(maxWidth, lineWidth);
		start = lineEnd + 1;
		y += down;
		numLines++;
	}
	spriteBatch->setColor(batchColor);

	m_textBounds.width = maxWidth;
	m_textBounds.height = m_data->capHeight + (numLines - 1) * m_data->m_lineHeight;
	return m_textBounds;
}

/** Draws a string, which may contain newlines (\n), with the specified position. Each line is automatically wrapped to keep it
* within a rectangle of the specified width.
* @param x The x position for the left most character.
* @param y The y position for the top of most capital letters in the font (the {@link #getCapHeight() cap height}).
* @return The bounds of the rendered string (the height is the distance from y to the baseline of the last line). Note the
*         same TextBounds instance is used for all methods that return TextBounds. */
BitmapFont::TextBounds& BitmapFont::drawWrapped(SpriteBatch* spriteBatch, const std::string& str, float x, float y, float wrapWidth)
{
	return drawWrapped(spriteBatch, str, x, y, wrapWidth, LEFT);
}

/** Draws a string, which may contain newlines (\n), with the specified position. Each line is automatically wrapped to keep it
* within a rectangle of the specified width, and aligned horizontally within that rectangle.
* @param x The x position for the left most character.
* @param y The y position for the top of most capital letters in the font (the {@link #getCapHeight() cap height}).
* @return The bounds of the rendered string (the height is the distance from y to the baseline of the last line). Note the
*         same TextBounds instance is used for all methods that return TextBounds. */
BitmapFont::TextBounds& BitmapFont::drawWrapped(SpriteBatch* spriteBatch, const std::string& str, float x, float y, float wrapWidth,
	HAlignment alignment)
{
	if(wrapWidth <= 0) 
		wrapWidth = ( float) INT_MAX;
	float batchColor = spriteBatch->getColor().toFloatBits();
	float down = m_data->down;
	int start = 0;
	int numLines = 0;
	int length = ( int) str.length();
	float maxWidth = 0;
	while(start < length)
	{
		int newLine = indexOf(str, '\n', start);
		// Eat whitespace at start of line.
		while(start < newLine)
		{
			if(!isWhitespace(str.at(start))) 
				break;
			start++;
		}
		int lineEnd = start + computeVisibleGlyphs(str, start, newLine, wrapWidth);
		int nextStart = lineEnd + 1;
		if(lineEnd < newLine)
		{
			// Find char to break on.
			while(lineEnd > start)
			{
				if(isWhitespace(str.at(lineEnd))) 
					break;
				lineEnd--;
			}
			if(lineEnd == start)
				lineEnd = nextStart; // If no characters to break, show all.
			else
			{
				nextStart = lineEnd;
				// Eat whitespace at end of line.
				while(lineEnd > start)
				{
					if(!isWhitespace(str.at(lineEnd - 1))) 
						break;
					lineEnd--;
				}
			}
		}
		else
			nextStart = lineEnd + 1;
		if(lineEnd > start)
		{
			float xOffset = 0;
			if(alignment != LEFT)
			{
				float lineWidth = getBounds(str, start, lineEnd).width;
				xOffset = wrapWidth - lineWidth;
				if(alignment == CENTER) xOffset /= 2;
			}
			float lineWidth = draw(spriteBatch, str, x + xOffset, y, start, lineEnd).width;
			maxWidth = max(maxWidth, lineWidth);
		}
		start = nextStart;
		y += down;
		numLines++;
	}
	spriteBatch->setColor(batchColor);
	m_textBounds.width = maxWidth;
	m_textBounds.height = m_data->capHeight + (numLines - 1) * m_data->m_lineHeight;
	return m_textBounds;
}

/** Returns the size of the specified string. The height is the distance from the top of most capital letters in the font (the
* {@link #getCapHeight() cap height}) to the baseline. Note the same TextBounds instance is used for all methods that return
* TextBounds. */
BitmapFont::TextBounds& BitmapFont::getBounds(const std::string& str)
{
	return getBounds(str, 0, (int)str.length());
}

/** Returns the size of the specified substring. The height is the distance from the top of most capital letters in the font
* (the {@link #getCapHeight() cap height}) to the baseline. Note the same TextBounds instance is used for all methods that
* return TextBounds.
* @param start The first character of the string.
* @param end The last character of the string (exclusive). */
BitmapFont::TextBounds& BitmapFont::getBounds(const std::string& str, int start, int end)
{
	int width = 0;
	Glyph* lastGlyph = NULL;
	while(start < end)
	{
		lastGlyph = m_data->getGlyph(str.at(start++));
		if(lastGlyph != NULL)
		{
			width = lastGlyph->xadvance;
			break;
		}
	}
	while(start < end)
	{
		char ch = str.at(start++);
		Glyph* g = m_data->getGlyph(ch);
		if(g != NULL)
		{
			width += lastGlyph->getKerning(ch);
			lastGlyph = g;
			width += g->xadvance;
		}
	}
	m_textBounds.width = width * m_data->scaleX;
	m_textBounds.height = m_data->capHeight;
	return m_textBounds;
}

/** Returns the size of the specified string, which may contain newlines. The height is the distance from the top of most
* capital letters in the font (the {@link #getCapHeight() cap height}) to the baseline of the last line of text. Note the same
* TextBounds instance is used for all methods that return TextBounds. */
BitmapFont::TextBounds& BitmapFont::getMultiLineBounds(const std::string& str)
{
	int start = 0;
	float maxWidth = 0;
	int numLines = 0;
	int length = ( int) str.length();
	while(start < length)
	{
		int lineEnd = indexOf(str, '\n', start);
		float lineWidth = getBounds(str, start, lineEnd).width;
		maxWidth = max(maxWidth, lineWidth);
		start = lineEnd + 1;
		numLines++;
	}
	m_textBounds.width = maxWidth;
	m_textBounds.height = m_data->capHeight + (numLines - 1) * m_data->m_lineHeight;
	return m_textBounds;
}

/** Returns the size of the specified string, which may contain newlines and is wrapped to keep it within a rectangle of the
* specified width. The height is the distance from the top of most capital letters in the font (the {@link #getCapHeight() cap
* height}) to the baseline of the last line of text. Note the same TextBounds instance is used for all methods that return
* TextBounds. */
BitmapFont::TextBounds& BitmapFont::getWrappedBounds(const std::string& str, float wrapWidth)
{
	if(wrapWidth <= 0) wrapWidth = ( float) INT_MAX;
	float down = m_data->down;
	int start = 0;
	int numLines = 0;
	int length = ( int) str.length();
	float maxWidth = 0;
	while(start < length)
	{
		int newLine = indexOf(str, '\n', start);
		// Eat whitespace at start of line.
		while(start < newLine)
		{
			if(!isWhitespace(str.at(start))) break;
			start++;
		}
		int lineEnd = start + computeVisibleGlyphs(str, start, newLine, wrapWidth);
		int nextStart = lineEnd + 1;
		if(lineEnd < newLine)
		{
			// Find char to break on.
			while(lineEnd > start)
			{
				if(isWhitespace(str.at(lineEnd))) break;
				lineEnd--;
			}
			if(lineEnd == start)
				lineEnd = nextStart; // If no characters to break, show all.
			else
			{
				nextStart = lineEnd;
				// Eat whitespace at end of line.
				while(lineEnd > start)
				{
					if(!isWhitespace(str.at(lineEnd - 1))) break;
					lineEnd--;
				}
			}
		}
		if(lineEnd > start)
		{
			float lineWidth = getBounds(str, start, lineEnd).width;
			maxWidth = max(maxWidth, lineWidth);
		}
		start = nextStart;
		numLines++;
	}
	m_textBounds.width = maxWidth;
	m_textBounds.height = m_data->capHeight + (numLines - 1) * m_data->m_lineHeight;
	return m_textBounds;
}

/** Computes the glyph advances for the given character sequence and stores them in the provided {@link FloatArray}. The
* FloatArray is cleared. This will add an additional element at the end.
* @param str the character sequence
* @param glyphAdvances the glyph advances output array.
* @param glyphPositions the glyph positions output array. */
void BitmapFont::computeGlyphAdvancesAndPositions(const std::string& str, std::vector<float>& glyphAdvances, std::vector<float>& glyphPositions)
{
	glyphAdvances.clear();
	glyphPositions.clear();
	int index = 0;
	int end = (int)str.length();
	int width = 0;
	Glyph* lastGlyph = NULL;
	if(m_data->scaleX == 1)
	{
		for(; index < end; index++)
		{
			char ch = str.at(index);
			Glyph* g = m_data->getGlyph(ch);
			if(g != NULL)
			{
				if(lastGlyph != NULL) width += lastGlyph->getKerning(ch);
				lastGlyph = g;
				glyphAdvances.push_back( ( float) g->xadvance);
				glyphPositions.push_back( ( float) width);
				width += g->xadvance;
			}
		}
		glyphAdvances.push_back(0.f);
		glyphPositions.push_back( ( float) width);
	}
	else
	{
		float scaleX = m_data->scaleX;
		for(; index < end; index++)
		{
			char ch = str.at(index);
			Glyph* g = m_data->getGlyph(ch);
			if(g != NULL)
			{
				if(lastGlyph != NULL) width += ( int) ( lastGlyph->getKerning(ch) * scaleX);
				lastGlyph = g;
				glyphAdvances.push_back( ( float) ( g->xadvance * scaleX));
				glyphPositions.push_back( ( float) width);
				width += g->xadvance;
			}
		}
		glyphAdvances.push_back(0.f);
		glyphPositions.push_back( ( float) width);
	}
}

/** Returns the number of glyphs from the substring that can be rendered in the specified width.
* @param start The first character of the string.
* @param end The last character of the string (exclusive). */
int BitmapFont::computeVisibleGlyphs(const std::string& str, int start, int end, float availableWidth)
{
	int index = start;
	int width = 0;
	Glyph* lastGlyph = NULL;
	if(m_data->scaleX == 1)
	{
		for(; index < end; index++)
		{
			char ch = str.at(index);
			Glyph* g = m_data->getGlyph(ch);
			if(g != NULL)
			{
				if(lastGlyph != NULL) width += lastGlyph->getKerning(ch);
				if(width + g->xadvance > availableWidth) break;
				width += g->xadvance;
				lastGlyph = g;
			}
		}
	}
	else
	{
		float scaleX = m_data->scaleX;
		for(; index < end; index++)
		{
			char ch = str.at(index);
			Glyph* g = m_data->getGlyph(ch);
			if(g != NULL)
			{
				if(lastGlyph != NULL) width += ( int) ( lastGlyph->getKerning(ch) * scaleX);
				if(width + g->xadvance * scaleX > availableWidth) break;
				width += ( int) ( g->xadvance * scaleX);
				lastGlyph = g;
			}
		}
	}
	return index - start;
}

void BitmapFont::setColor(float color)
{
	m_color = color;
}

void BitmapFont::setColor(const Color& tint)
{
	m_color = tint.toFloatBits();
}

void BitmapFont::setColor(float r, float g, float b, float a)
{
	int intBits = (int)(255 * a) << 24 | (int)(255 * b) << 16 | (int)(255 * g) << 8 | (int)(255 * r);
	m_color = NumberUtils::intToFloatColor(intBits);
}

/** Returns the color of this font. Changing the returned color will have no affect, {@link #setColor(Color)} or
* {@link #setColor(float, float, float, float)} must be used. */
Color& BitmapFont::getColor()
{
	int intBits = NumberUtils::floatToIntColor(m_color);
	Color& color = m_tempColor;
	color.r = (intBits & 0xff) / 255.f;
	color.g = ((intBits >> 8) & 0xff) / 255.f;
	color.b = ((intBits >> 16) & 0xff) / 255.f;
	color.a = ((intBits >> 24) & 0xff) / 255.f;
	return color;
}

void BitmapFont::setScale(float scaleX, float scaleY)
{
	m_data->spaceWidth = m_data->spaceWidth / m_data->scaleX * scaleX;
	m_data->xHeight = m_data->xHeight / m_data->scaleY * scaleY;
	m_data->capHeight = m_data->capHeight / m_data->scaleY * scaleY;
	m_data->ascent = m_data->ascent / m_data->scaleY * scaleY;
	m_data->descent = m_data->descent / m_data->scaleY * scaleY;
	m_data->down = m_data->down / m_data->scaleY * scaleY;
	m_data->scaleX = scaleX;
	m_data->scaleY = scaleY;
}

/** Scales the font by the specified amount in both directions.<br>
* <br>
* Note that smoother scaling can be achieved if the texture backing the BitmapFont is using {@link TextureFilter#Linear}. The
* default is Nearest, so use a BitmapFont constructor that takes a {@link TextureRegion}. */
void BitmapFont::setScale(float scaleXY)
{
	setScale(scaleXY, scaleXY);
}

/** Sets the font's scale relative to the current scale. */
void BitmapFont::scale(float amount)
{
	setScale(m_data->scaleX + amount, m_data->scaleY + amount);
}

float BitmapFont::getScaleX()
{
	return m_data->scaleX;
}

float BitmapFont::getScaleY()
{
	return m_data->scaleY;
}

TextureRegion* BitmapFont::getRegion()
{
	return m_region;
}

/** Returns the line height, which is the distance from one line of text to the next. */
float BitmapFont::getLineHeight()
{
	return m_data->m_lineHeight;
}

/** Returns the width of the space character. */
float BitmapFont::getSpaceWidth()
{
	return m_data->spaceWidth;
}

/** Returns the x-height, which is the distance from the top of most lowercase characters to the baseline. */
float BitmapFont::getXHeight()
{
	return m_data->xHeight;
}

/** Returns the cap height, which is the distance from the top of most uppercase characters to the baseline. Since the drawing
* position is the cap height of the first line, the cap height can be used to get the location of the baseline. */
float BitmapFont::getCapHeight()
{
	return m_data->capHeight;
}

/** Returns the ascent, which is the distance from the cap height to the top of the tallest glyph-> */
float BitmapFont::getAscent()
{
	return m_data->ascent;
}

/** Returns the descent, which is the distance from the bottom of the glyph that extends the lowest to the baseline. This number
* is negative. */
float BitmapFont::getDescent()
{
	return m_data->descent;
}

/** Returns true if this BitmapFont has been flipped for use with a y-down coordinate system. */
bool BitmapFont::isFlipped()
{
	return m_flipped;
}

/** Disposes the texture used by this BitmapFont's region IF this BitmapFont created the texture. */
void BitmapFont::dispose()
{
}

/** Makes the specified glyphs fixed width. This can be useful to make the numbers in a font fixed width. Eg, when horizontally
* centering a score or loading percentage text, it will not jump around as different numbers are shown. */
void BitmapFont::setFixedWidthGlyphs(const std::string& glyphs)
{
	int maxAdvance = 0;
	for(int index = 0, end = (int)glyphs.length(); index < end; index++)
	{
		Glyph* g = m_data->getGlyph(glyphs.at(index));
		if(g != NULL && g->xadvance > maxAdvance) 
			maxAdvance = g->xadvance;
	}
	for(int index = 0, end = (int)glyphs.length(); index < end; index++)
	{
		Glyph* g = m_data->getGlyph(glyphs.at(index));
		if(g == NULL) 
			continue;
		g->xoffset += (maxAdvance - g->xadvance) / 2;
		g->xadvance = maxAdvance;
		g->kerning = NULL;
	}
}

/** @param character
* @return whether the given character is contained in this font. */
bool BitmapFont::containsCharacter(char character)
{
	return m_data->getGlyph(character) != NULL;
}

/** Specifies whether to use integer positions or not. Default is to use them so filtering doesn't kick in as badly.
* @param use */
void BitmapFont::setUseIntegerPositions(bool use)
{
	m_integer = use;
}

/** @return whether this font uses integer positions for drawing. */
bool BitmapFont::usesIntegerPositions()
{
	return m_integer;
}

BitmapFont::BitmapFontData* BitmapFont::getData()
{
	return m_data;
}

int BitmapFont::indexOf(const std::string& text, char ch, int start)
{
	const int n = (int)text.length();
	for(; start < n; start++)
		if(text.at(start) == ch) return start;
	return n;
}

bool BitmapFont::isWhitespace(char c)
{
	switch(c)
	{
	case '\n':
	case '\r':
	case '\t':
	case ' ':
		return true;
	default:
		return false;
	}
}

