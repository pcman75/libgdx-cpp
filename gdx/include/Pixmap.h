/*******************************************************************************
* Copyright 2011 See AUTHORS file.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
******************************************************************************/

#pragma once 
#include "GdxRuntimeException.h"
#include "Gdx2DPixmap.h"
#include "Color.h"
#include "FileHandle.h"


/** <p>
* A Pixmap represents an image in memory. It has a width and height expressed in pixels as well as a {@link Format} specifying
* the number and order of color components per pixel. Coordinates of pixels are specified with respect to the top left corner of
* the image, with the x-axis pointing to the right and the y-axis pointing downwards.
* </p>
*
* <p>
* By default all methods use blending. You can disable blending with {@link Pixmap#setBlending(Blending)}. The
* {@link Pixmap#drawPixmap(Pixmap, int, int, int, int, int, int, int, int)} method will scale and stretch the source image to a
* target image. There either nearest neighbour or bilinear filtering can be used.
* </p>
*
* <p>
* A Pixmap stores its data in native heap memory. It is mandatory to call {@link Pixmap#dispose()} when the pixmap is no longer
* needed, otherwise memory leaks will result
* </p>
*/

class Pixmap
{
public:
	/** Different pixel formats*/
	class Format
	{
	public:
		static const Format Unknown;
		static const Format Alpha;
		static const Format Intensity;
		static const Format LuminanceAlpha;
		static const Format RGB565;
		static const Format RGBA4444;
		static const Format RGB888;
		static const Format RGBA8888;

		static int toGdx2DPixmapFormat(Format format);

		static Format fromGdx2DPixmapFormat (int format);
		bool operator==(const Format& other);
		bool operator!=(const Format& other);
	private:
		Format(int format);
		int m_format;
	};

	/** Blending functions to be set with {@link Pixmap#setBlending}*/
	enum Blending
	{
		None, SourceOver
	};

	/** Filters to be used with {@link Pixmap#drawPixmap(Pixmap, int, int, int, int, int, int, int, int)}*/
	enum Filter
	{
		NearestNeighbour, BiLinear
	};

	/** global blending state **/
private:
	static Blending m_blending;

	Gdx2DPixmap m_pixmap;
	int m_color;

	/** Sets the type of {@link Blending} to be used for all operations. Default is {@link Blending#SourceOver}.
	* @param blending the blending type */
public:
	
	static void setBlending (Blending blending);

	/** Sets the type of interpolation {@link Filter} to be used in conjunction with
	* {@link Pixmap#drawPixmap(Pixmap, int, int, int, int, int, int, int, int)}.
	* @param filter the filter. */
	static void setFilter (Filter filter);

	/** Creates a new Pixmap instance with the given width, height and format.
	* @param width the width in pixels
	* @param height the height in pixels
	* @param format the {@link Format} */
	Pixmap (int width, int height, Format format);

	/*Empty Pixmap. Call afterwards one of the Create methods*/
	//Pixmap();

	//TODO: delete this or implement it
	void createFrom(int width, int height, Format format) {};

	/** Creates a new Pixmap instance from the given encoded image data. The image can be encoded as JPEG, PNG or BMP.
	* @param encodedData the encoded image data
	* @param offset the offset
	* @param len the length */
	Pixmap(const unsigned char* encodedData, int len);

	/** Creates a new Pixmap instance from the given file. The file must be a Png, Jpeg or Bitmap. Paletted formats are not
	* supported.
	*
	* @param file the {@link FileHandle} */
	Pixmap(const FileHandle& file);

	/** Constructs a new Pixmap from a {@link Gdx2DPixmap}.
	* @param pixmap */
	Pixmap(const Gdx2DPixmap& pixmap);

	/*Construct an empty Pixmap*/
	//Pixmap();

	/** Sets the color for the following drawing operations
	* @param color the color, encoded as RGBA8888 */
	void setColor (int color);

	/** Sets the color for the following drawing operations.
	*
	* @param r The red component.
	* @param g The green component.
	* @param b The blue component.
	* @param a The alpha component. */
	void setColor(float r, float g, float b, float a);

	/** Sets the color for the following drawing operations.
	* @param color The color. */
	void setColor(const Color& color);

	/** Fills the complete bitmap with the currently set color. */
	void fill();

	// /**
	// * Sets the width in pixels of strokes.
	// *
	// * @param width The stroke width in pixels.
	// */
	// public void setStrokeWidth (int width);

	/** Draws a line between the given coordinates using the currently set color.
	*
	* @param x The x-coodinate of the first point
	* @param y The y-coordinate of the first point
	* @param x2 The x-coordinate of the first point
	* @param y2 The y-coordinate of the first point */
	void drawLine(int x, int y, int x2, int y2);

	/** Draws a rectangle outline starting at x, y extending by width to the right and by height downwards (y-axis points downwards)
	* using the current color.
	*
	* @param x The x coordinate
	* @param y The y coordinate
	* @param width The width in pixels
	* @param height The height in pixels */
	void drawRectangle(int x, int y, int width, int height);

	/** Draws an area form another Pixmap to this Pixmap.
	*
	* @param pixmap The other Pixmap
	* @param x The target x-coordinate (top left corner)
	* @param y The target y-coordinate (top left corner)
	* @param srcx The source x-coordinate (top left corner)
	* @param srcy The source y-coordinate (top left corner);
	* @param srcWidth The width of the area form the other Pixmap in pixels
	* @param srcHeight The height of the area form the other Pixmap in pixles */
	void drawPixmap(Pixmap* pixmap, int x, int y, int srcx, int srcy, int srcWidth, int srcHeight);

	/** Draws an area form another Pixmap to this Pixmap. This will automatically scale and stretch the source image to the
	* specified target rectangle. Use {@link Pixmap#setFilter(Filter)} to specify the type of filtering to be used (nearest
	* neighbour or bilinear).
	*
	* @param pixmap The other Pixmap
	* @param srcx The source x-coordinate (top left corner)
	* @param srcy The source y-coordinate (top left corner);
	* @param srcWidth The width of the area form the other Pixmap in pixels
	* @param srcHeight The height of the area form the other Pixmap in pixles
	* @param dstx The target x-coordinate (top left corner)
	* @param dsty The target y-coordinate (top left corner)
	* @param dstWidth The target width
	* @param dstHeight the target height */
	void drawPixmap(Pixmap* pixmap, int srcx, int srcy, int srcWidth, int srcHeight, int dstx, int dsty, int dstWidth,
		int dstHeight);

	/** Fills a rectangle starting at x, y extending by width to the right and by height downwards (y-axis points downwards) using
	* the current color.
	*
	* @param x The x coordinate
	* @param y The y coordinate
	* @param width The width in pixels
	* @param height The height in pixels */
	void fillRectangle(int x, int y, int width, int height);

	/** Draws a circle outline with the center at x,y and a radius using the current color and stroke width.
	*
	* @param x The x-coordinate of the center
	* @param y The y-coordinate of the center
	* @param radius The radius in pixels */
	void drawCircle(int x, int y, int radius);

	/** Fills a circle with the center at x,y and a radius using the current color.
	*
	* @param x The x-coordinate of the center
	* @param y The y-coordinate of the center
	* @param radius The radius in pixels */
	void fillCircle(int x, int y, int radius);

	/** Returns the 32-bit RGBA8888 value of the pixel at x, y. For Alpha formats the RGB components will be one.
	*
	* @param x The x-coordinate
	* @param y The y-coordinate
	* @return The pixel color in RGBA8888 format. */
	int getPixel(int x, int y);

	/** @return The width of the Pixmap in pixels. */
	int getWidth();

	/** @return The height of the Pixmap in pixels. */
	int getHeight();

	/** Releases all resources associated with this Pixmap. */
	void dispose();

	/** Draws a pixel at the given location with the current color.
	*
	* @param x the x-coordinate
	* @param y the y-coordinate */
	void drawPixel(int x, int y);

	/** Draws a pixel at the given location with the given color.
	*
	* @param x the x-coordinate
	* @param y the y-coordinate
	* @param color the color in RGBA8888 format. */
	void drawPixel(int x, int y, int color);

	/** Returns the OpenGL ES format of this Pixmap. Used as the seventh parameter to
	* {@link GLCommon#glTexImage2D(int, int, int, int, int, int, int, int, java.nio.Buffer)}.
	* @return one of GL_ALPHA, GL_RGB, GL_RGBA, GL_LUMINANCE, or GL_LUMINANCE_ALPHA. */
	int getGLFormat();

	/** Returns the OpenGL ES format of this Pixmap. Used as the third parameter to
	* {@link GLCommon#glTexImage2D(int, int, int, int, int, int, int, int, java.nio.Buffer)}.
	* @return one of GL_ALPHA, GL_RGB, GL_RGBA, GL_LUMINANCE, or GL_LUMINANCE_ALPHA. */
	int getGLInternalFormat();

	/** Returns the OpenGL ES type of this Pixmap. Used as the eighth parameter to
	* {@link GLCommon#glTexImage2D(int, int, int, int, int, int, int, int, java.nio.Buffer)}.
	* @return one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4 */
	int getGLType();

	/** Returns the direct ByteBuffer holding the pixel data. For the format Alpha each value is encoded as a byte. For the format
	* LuminanceAlpha the luminance is the first byte and the alpha is the second byte of the pixel. For the formats RGB888 and
	* RGBA8888 the color components are stored in a single byte each in the order red, green, blue (alpha). For the formats RGB565
	* and RGBA4444 the pixel colors are stored in shorts in machine dependent order.
	* @return the direct {@link ByteBuffer} holding the pixel data. */
	unsigned char* getPixels ();
	
	/** @return the {@link Format} of this Pixmap. */
	Format getFormat() const;

	/** @return the currently set {@link Blending} */
	static Blending getBlending ();
};
