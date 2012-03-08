/*
 * Copyright (c) 2008-2010, Matthias Mann
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
 * conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the distribution. * Neither the name of Matthias Mann nor
 * the names of its contributors may be used to endorse or promote products derived from this software without specific prior
 * written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once

#include "TextureRegion.h"
#include "SpriteBatch.h"
#include "GdxDefines.h"

/** Renders bitmap fonts. The font consists of 2 files: an image file or {@link TextureRegion} containing the glyphs and a file in
 * the AngleCode BMFont text format that describes where each glyph is on the image. Currently only a single image of glyphs is
 * supported.<br>
 * <br>
 * Text is drawn using a {@link SpriteBatch}. Text can be cached in a {@link BitmapFontCache} for faster rendering of static text,
 * which saves needing to compute the location of each glyph each frame.<br>
 * <br>
 * * The texture for a BitmapFont loaded from a file is managed. {@link #dispose()} must be called to free the texture when no
 * longer needed. A BitmapFont loaded using a {@link TextureRegion} is managed if the region's texture is managed. Disposing the
 * BitmapFont disposes the region's texture, which may not be desirable if the texture is still being used elsewhere.<br>
 */


class GdxDllImportExport BitmapFont
{
public:
	enum HAlignment
	{
		LEFT, CENTER, RIGHT
	};

	class Glyph
	{
	public:
		int srcX;
		int srcY;
		int width, height;
		float u, v, u2, v2;
		int xoffset, yoffset;
		int xadvance;
		char** kerning;

		Glyph();
		~Glyph();
		int getKerning(char ch);
		void setKerning(int ch, int value);
	};

	class TextBounds
	{
	public:
		float width;
		float height;

	public:
		TextBounds();

		TextBounds(const TextBounds& bounds);

		void set(const TextBounds& bounds);
	};
	class BitmapFontData
	{
	public:
		std::string m_imagePath;
		FileHandle m_fontFile;
		const bool m_flipped;
		float m_lineHeight;
		float capHeight;
		float ascent;
		float descent;
		float down;
		float scaleX, scaleY;

		Glyph*** glyphs;
		float spaceWidth;
		float xHeight;

	public:
		BitmapFontData(const FileHandle& fontFile, bool flip);
		~BitmapFontData();

	private:
		void setGlyph(int ch, Glyph* glyph);

		Glyph* getFirstGlyph();

	public:
		Glyph* getGlyph(char ch);

		std::string& getImagePath();

		FileHandle& getFontFile();
	};
private:
	static const int LOG2_PAGE_SIZE;
	static const int PAGE_SIZE;
	static const int PAGES;

	static const char xChars[];
	static const char capChars[];

	TextureRegion* region;
	TextBounds m_textBounds;
	float color;
	Color tempColor;
	bool flipped;
	bool integer;
	BitmapFontData* data;
	bool ownsTexture;
	bool ownsBitmapFontData;

	
public:

	~BitmapFont();

	/** Creates a BitmapFont using the default 15pt Arial font included in the libgdx JAR file. This is convenient to easily display
	 * text without bothering with generating a bitmap font. */
	BitmapFont();

	/** Creates a BitmapFont using the default 15pt Arial font included in the libgdx JAR file. This is convenient to easily display
	 * text without bothering with generating a bitmap font.
	 * @param flip If true, the glyphs will be flipped for use with a perspective where 0,0 is the upper left corner. */
	BitmapFont(bool flip);

	/** Creates a BitmapFont with the glyphs relative to the specified region. If the region is NULL, the glyph textures are loaded
	 * from the image file given in the font file. The {@link #dispose()} method will not dispose the region's texture in this
	 * case!
	 * @param region The texture region containing the glyphs. The glyphs must be relative to the lower left corner (ie, the region
	 *           should not be flipped). If the region is NULL the glyph images are loaded from the image path in the font file.
	 * @param flip If true, the glyphs will be flipped for use with a perspective where 0,0 is the upper left corner. */
	BitmapFont(const FileHandle& fontFile, TextureRegion* region, bool flip);

	/** Creates a BitmapFont from a BMFont file. The image file name is read from the BMFont file and the image is loaded from the
	 * same directory.
	 * @param flip If true, the glyphs will be flipped for use with a perspective where 0,0 is the upper left corner. */
	BitmapFont(const FileHandle& fontFile, bool flip);

	/** Creates a BitmapFont from a BMFont file, using the specified image for glyphs. Any image specified in the BMFont file is
	 * ignored.
	 * @param flip If true, the glyphs will be flipped for use with a perspective where 0,0 is the upper left corner. */
	BitmapFont(const FileHandle& fontFile, const FileHandle& imageFile, bool flip);

	/** Creates a BitmapFont from a BMFont file, using the specified image for glyphs. Any image specified in the BMFont file is
	 * ignored.
	 * @param flip If true, the glyphs will be flipped for use with a perspective where 0,0 is the upper left corner.
	 * @param integer If true, rendering positions will be at integer values to avoid filtering artifacts.s */
	BitmapFont(const FileHandle& fontFile, const FileHandle& imageFile, bool flip, bool integer);

	/** Constructs a new BitmapFont from the given {@link BitmapFontData} and {@link TextureRegion}. If the TextureRegion is NULL,
	 * the image path is read from the BitmapFontData. The dispose() method will not dispose the texture of the region if the
	 * region is != NULL.
	 * @param data
	 * @param region
	 * @param integer */
	BitmapFont(BitmapFontData* data, TextureRegion* region, bool integer);

private:
	void init();

	void init(const FileHandle& fontFile, const FileHandle& imageFile, bool flip, bool integer);

	void init(BitmapFontData* data, TextureRegion* region, bool integer);

	void load(BitmapFontData* data);

public:
	/** Draws a string at the specified position.
	 * @param x The x position for the left most character.
	 * @param y The y position for the top of most capital letters in the font (the {@link #getCapHeight() cap height}).
	 * @return The bounds of the rendered string (the height is the distance from y to the baseline). Note the same TextBounds
	 *         instance is used for all methods that return TextBounds. */
	TextBounds& draw(SpriteBatch* spriteBatch, const std::string& str, float x, float y);

	/** Draws a substring at the specified position.
	 * @param x The x position for the left most character.
	 * @param y The y position for the top of most capital letters in the font (the {@link #getCapHeight() cap height}).
	 * @param start The first character of the string to draw.
	 * @param end The last character of the string to draw (exclusive).
	 * @return The bounds of the rendered string (the height is the distance from y to the baseline). Note the same TextBounds
	 *         instance is used for all methods that return TextBounds. */
	TextBounds& draw(SpriteBatch* spriteBatch, const std::string& str, float x, float y, int start, int end);

	/** Draws a string, which may contain newlines (\n), at the specified position.
	 * @param x The x position for the left most character.
	 * @param y The y position for the top of most capital letters in the font (the {@link #getCapHeight() cap height}).
	 * @return The bounds of the rendered string (the height is the distance from y to the baseline of the last line). Note the
	 *         same TextBounds instance is used for all methods that return TextBounds. */
	TextBounds& drawMultiLine(SpriteBatch* spriteBatch, const std::string& str, float x, float y);

	/** Draws a string, which may contain newlines (\n), at the specified position and alignment. Each line is aligned horizontally
	 * within a rectangle of the specified width.
	 * @param x The x position for the left most character.
	 * @param y The y position for the top of most capital letters in the font (the {@link #getCapHeight() cap height}).
	 * @return The bounds of the rendered string (the height is the distance from y to the baseline of the last line). Note the
	 *         same TextBounds instance is used for all methods that return TextBounds. */
	TextBounds& drawMultiLine(SpriteBatch* spriteBatch, const std::string& str, float x, float y, float alignmentWidth,
	                                HAlignment alignment);

	/** Draws a string, which may contain newlines (\n), with the specified position. Each line is automatically wrapped to keep it
	 * within a rectangle of the specified width.
	 * @param x The x position for the left most character.
	 * @param y The y position for the top of most capital letters in the font (the {@link #getCapHeight() cap height}).
	 * @return The bounds of the rendered string (the height is the distance from y to the baseline of the last line). Note the
	 *         same TextBounds instance is used for all methods that return TextBounds. */
	TextBounds& drawWrapped(SpriteBatch* spriteBatch, const std::string& str, float x, float y, float wrapWidth);

	/** Draws a string, which may contain newlines (\n), with the specified position. Each line is automatically wrapped to keep it
	 * within a rectangle of the specified width, and aligned horizontally within that rectangle.
	 * @param x The x position for the left most character.
	 * @param y The y position for the top of most capital letters in the font (the {@link #getCapHeight() cap height}).
	 * @return The bounds of the rendered string (the height is the distance from y to the baseline of the last line). Note the
	 *         same TextBounds instance is used for all methods that return TextBounds. */
	TextBounds& drawWrapped(SpriteBatch* spriteBatch, const std::string& str, float x, float y, float wrapWidth,
	                              HAlignment alignment);

	/** Returns the size of the specified string. The height is the distance from the top of most capital letters in the font (the
	 * {@link #getCapHeight() cap height}) to the baseline. Note the same TextBounds instance is used for all methods that return
	 * TextBounds. */
	TextBounds& getBounds(const std::string& str);

	/** Returns the size of the specified substring. The height is the distance from the top of most capital letters in the font
	 * (the {@link #getCapHeight() cap height}) to the baseline. Note the same TextBounds instance is used for all methods that
	 * return TextBounds.
	 * @param start The first character of the string.
	 * @param end The last character of the string (exclusive). */
	TextBounds& getBounds(const std::string& str, int start, int end);

	/** Returns the size of the specified string, which may contain newlines. The height is the distance from the top of most
	 * capital letters in the font (the {@link #getCapHeight() cap height}) to the baseline of the last line of text. Note the same
	 * TextBounds instance is used for all methods that return TextBounds. */
	TextBounds& getMultiLineBounds(const std::string& str);

	/** Returns the size of the specified string, which may contain newlines and is wrapped to keep it within a rectangle of the
	 * specified width. The height is the distance from the top of most capital letters in the font (the {@link #getCapHeight() cap
	 * height}) to the baseline of the last line of text. Note the same TextBounds instance is used for all methods that return
	 * TextBounds. */
	TextBounds& getWrappedBounds(const std::string& str, float wrapWidth);

	/** Computes the glyph advances for the given character sequence and stores them in the provided {@link FloatArray}. The
	 * FloatArray is cleared. This will add an additional element at the end.
	 * @param str the character sequence
	 * @param glyphAdvances the glyph advances output array.
	 * @param glyphPositions the glyph positions output array. */
	void computeGlyphAdvancesAndPositions(const std::string& str, std::vector<float>& glyphAdvances, std::vector<float>& glyphPositions);

	/** Returns the number of glyphs from the substring that can be rendered in the specified width.
	 * @param start The first character of the string.
	 * @param end The last character of the string (exclusive). */
	int computeVisibleGlyphs(const std::string& str, int start, int end, float availableWidth);

	void setColor(float color);

	void setColor(const Color& tint);

	void setColor(float r, float g, float b, float a);

	/** Returns the color of this font. Changing the returned color will have no affect, {@link #setColor(Color)} or
	 * {@link #setColor(float, float, float, float)} must be used. */
	Color& getColor();

	void setScale(float scaleX, float scaleY);

	/** Scales the font by the specified amount in both directions.<br>
	 * <br>
	 * Note that smoother scaling can be achieved if the texture backing the BitmapFont is using {@link TextureFilter#Linear}. The
	 * default is Nearest, so use a BitmapFont constructor that takes a {@link TextureRegion}. */
	void setScale(float scaleXY);

	/** Sets the font's scale relative to the current scale. */
	void scale(float amount);

	float getScaleX();

	float getScaleY();

	TextureRegion* getRegion();

	/** Returns the line height, which is the distance from one line of text to the next. */
	float getLineHeight();

	/** Returns the width of the space character. */
	float getSpaceWidth();

	/** Returns the x-height, which is the distance from the top of most lowercase characters to the baseline. */
	float getXHeight();

	/** Returns the cap height, which is the distance from the top of most uppercase characters to the baseline. Since the drawing
	 * position is the cap height of the first line, the cap height can be used to get the location of the baseline. */
	float getCapHeight();

	/** Returns the ascent, which is the distance from the cap height to the top of the tallest glyph. */
	float getAscent();

	/** Returns the descent, which is the distance from the bottom of the glyph that extends the lowest to the baseline. This number
	 * is negative. */
	float getDescent();

	/** Returns true if this BitmapFont has been flipped for use with a y-down coordinate system. */
	bool isFlipped();

	/** Disposes the texture used by this BitmapFont's region IF this BitmapFont created the texture. */
	void dispose();

	/** Makes the specified glyphs fixed width. This can be useful to make the numbers in a font fixed width. Eg, when horizontally
	 * centering a score or loading percentage text, it will not jump around as different numbers are shown. */
	void setFixedWidthGlyphs(const std::string& glyphs);

	/** @param character
	 * @return whether the given character is contained in this font. */
	bool containsCharacter(char character);

	/** Specifies whether to use integer positions or not. Default is to use them so filtering doesn't kick in as badly.
	 * @param use */
	void setUseIntegerPositions(bool use);

	/** @return whether this font uses integer positions for drawing. */
	bool usesIntegerPositions();

	BitmapFontData* getData();

	static int indexOf(const std::string& text, char ch, int start);

	static bool isWhitespace(char c);
};
