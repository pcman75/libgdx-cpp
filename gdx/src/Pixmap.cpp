#include "stdafx.h"
#include "Pixmap.h"

const Pixmap::Format Pixmap::Format::Unknown = Pixmap::Format(Gdx2DPixmap::GDX2D_FORMAT_UNKNOWN);
const Pixmap::Format Pixmap::Format::Alpha = Pixmap::Format(Gdx2DPixmap::GDX2D_FORMAT_ALPHA);
const Pixmap::Format Pixmap::Format::Intensity = Pixmap::Format(Gdx2DPixmap::GDX2D_FORMAT_ALPHA);
const Pixmap::Format Pixmap::Format::LuminanceAlpha = Pixmap::Format(Gdx2DPixmap::GDX2D_FORMAT_LUMINANCE_ALPHA);
const Pixmap::Format Pixmap::Format::RGB565 = Pixmap::Format(Gdx2DPixmap::GDX2D_FORMAT_RGB565);
const Pixmap::Format Pixmap::Format::RGBA4444 = Pixmap::Format(Gdx2DPixmap::GDX2D_FORMAT_RGBA4444);
const Pixmap::Format Pixmap::Format::RGB888 = Pixmap::Format(Gdx2DPixmap::GDX2D_FORMAT_RGB888);
const Pixmap::Format Pixmap::Format::RGBA8888 = Pixmap::Format(Gdx2DPixmap::GDX2D_FORMAT_RGBA8888);

Pixmap::Blending Pixmap::m_blending = None;

int Pixmap::Format::toGdx2DPixmapFormat(Format format)
{
	if (format == Unknown) return Gdx2DPixmap::GDX2D_FORMAT_UNKNOWN;
	if (format == Alpha) return Gdx2DPixmap::GDX2D_FORMAT_ALPHA;
	if (format == Intensity) return Gdx2DPixmap::GDX2D_FORMAT_ALPHA;
	if (format == LuminanceAlpha) return Gdx2DPixmap::GDX2D_FORMAT_LUMINANCE_ALPHA;
	if (format == RGB565) return Gdx2DPixmap::GDX2D_FORMAT_RGB565;
	if (format == RGBA4444) return Gdx2DPixmap::GDX2D_FORMAT_RGBA4444;
	if (format == RGB888) return Gdx2DPixmap::GDX2D_FORMAT_RGB888;
	if (format == RGBA8888) return Gdx2DPixmap::GDX2D_FORMAT_RGBA8888;
	throw new GdxRuntimeException(std::string("Unknown Format"));
}

Pixmap::Format Pixmap::Format::fromGdx2DPixmapFormat (int format)
{
	if (format == Gdx2DPixmap::GDX2D_FORMAT_UNKNOWN) return Unknown;
	if (format == Gdx2DPixmap::GDX2D_FORMAT_ALPHA) return Alpha;
	if (format == Gdx2DPixmap::GDX2D_FORMAT_LUMINANCE_ALPHA) return LuminanceAlpha;
	if (format == Gdx2DPixmap::GDX2D_FORMAT_RGB565) return RGB565;
	if (format == Gdx2DPixmap::GDX2D_FORMAT_RGBA4444) return RGBA4444;
	if (format == Gdx2DPixmap::GDX2D_FORMAT_RGB888) return RGB888;
	if (format == Gdx2DPixmap::GDX2D_FORMAT_RGBA8888) return RGBA8888;
	throw new GdxRuntimeException(std::string("Unknown Gdx2DPixmap Format"));
}
bool Pixmap::Format::operator==(const Format& other)
{
	return m_format == other.m_format;
}

bool Pixmap::Format::operator!=(const Format& other)
{
	return !(*this == other);
}

Pixmap::Format::Format(int format)
	:m_format(format)
{
}

void Pixmap::setBlending (Blending blending)
{
	m_blending = blending;
	Gdx2DPixmap::setBlend(blending == None ? 0 : 1);
}

/*Pixmap::Pixmap()
{
}
*/
/** Sets the type of interpolation {@link Filter} to be used in conjunction with
* {@link Pixmap#drawPixmap(Pixmap, int, int, int, int, int, int, int, int)}.
* @param filter the filter. */
void Pixmap::setFilter (Filter filter)
{
	Gdx2DPixmap::setScale(filter == NearestNeighbour ? Gdx2DPixmap::GDX2D_SCALE_NEAREST : Gdx2DPixmap::GDX2D_SCALE_LINEAR);
}

/** Creates a new Pixmap instance with the given width, height and format.
* @param width the width in pixels
* @param height the height in pixels
* @param format the {@link Format} */
Pixmap::Pixmap (int width, int height, Format format)
	:m_pixmap(width, height, Format::toGdx2DPixmapFormat(format)), m_color(0)
{
	setColor(0, 0, 0, 0);
	fill();
}

/** Creates a new Pixmap instance from the given encoded image data. The image can be encoded as JPEG, PNG or BMP.
* @param encodedData the encoded image data
* @param offset the offset
* @param len the length */
Pixmap::Pixmap(const unsigned char* encodedData, int len)
	:m_pixmap(encodedData, len, 0), m_color(0)
{
}

/** Creates a new Pixmap instance from the given file. The file must be a Png, Jpeg or Bitmap. Paletted formats are not
* supported.
*
* @param file the {@link FileHandle} */
Pixmap::Pixmap (const FileHandle* file)
	: m_color(0)
{   
  size_t nSize = file->length();
  unsigned char* pBuff = new unsigned char [nSize];
    file->readBytes(pBuff, nSize);

	m_pixmap.createFrom( pBuff, nSize, 0);
  delete [] pBuff;
}

/** Constructs a new Pixmap from a {@link Gdx2DPixmap}.
* @param pixmap */
Pixmap::Pixmap (const Gdx2DPixmap& pixmap)
	:m_pixmap(pixmap), m_color(0)
{
}

/** Sets the color for the following drawing operations
* @param color the color, encoded as RGBA8888 */
void Pixmap::setColor (int color)
{
	m_color = color;
}

/** Sets the color for the following drawing operations.
*
* @param r The red component.
* @param g The green component.
* @param b The blue component.
* @param a The alpha component. */
void Pixmap::setColor (float r, float g, float b, float a)
{
	m_color = Color::rgba8888(r, g, b, a);
}

/** Sets the color for the following drawing operations.
* @param color The color. */
void Pixmap::setColor(const Color& color)
{
	m_color = Color::rgba8888(color.r, color.g, color.b, color.a);
}

/** Fills the complete bitmap with the currently set color. */
void Pixmap::fill ()
{
	m_pixmap.clear(m_color);
}

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
void Pixmap::drawLine (int x, int y, int x2, int y2)
{
	m_pixmap.drawLine(x, y, x2, y2, m_color);
}

/** Draws a rectangle outline starting at x, y extending by width to the right and by height downwards (y-axis points downwards)
* using the current color.
*
* @param x The x coordinate
* @param y The y coordinate
* @param width The width in pixels
* @param height The height in pixels */
void Pixmap::drawRectangle (int x, int y, int width, int height)
{
	m_pixmap.drawRect(x, y, width, height, m_color);
}

/** Draws an area form another Pixmap to this Pixmap.
*
* @param pixmap The other Pixmap
* @param x The target x-coordinate (top left corner)
* @param y The target y-coordinate (top left corner)
* @param srcx The source x-coordinate (top left corner)
* @param srcy The source y-coordinate (top left corner);
* @param srcWidth The width of the area form the other Pixmap in pixels
* @param srcHeight The height of the area form the other Pixmap in pixles */
void Pixmap::drawPixmap (Pixmap* pixmap, int x, int y, int srcx, int srcy, int srcWidth, int srcHeight)
{
	m_pixmap.drawPixmap(&pixmap->m_pixmap, srcx, srcy, x, y, srcWidth, srcHeight);
}

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
void Pixmap::drawPixmap (Pixmap* pixmap, int srcx, int srcy, int srcWidth, int srcHeight, int dstx, int dsty, int dstWidth,
	int dstHeight)
{
	m_pixmap.drawPixmap(&pixmap->m_pixmap, srcx, srcy, srcWidth, srcHeight, dstx, dsty, dstWidth, dstHeight);
}

/** Fills a rectangle starting at x, y extending by width to the right and by height downwards (y-axis points downwards) using
* the current color.
*
* @param x The x coordinate
* @param y The y coordinate
* @param width The width in pixels
* @param height The height in pixels */
void Pixmap::fillRectangle (int x, int y, int width, int height)
{
	m_pixmap.fillRect(x, y, width, height, m_color);
}

/** Draws a circle outline with the center at x,y and a radius using the current color and stroke width.
*
* @param x The x-coordinate of the center
* @param y The y-coordinate of the center
* @param radius The radius in pixels */
void Pixmap::drawCircle (int x, int y, int radius)
{
	m_pixmap.drawCircle(x, y, radius, m_color);
}

/** Fills a circle with the center at x,y and a radius using the current color.
*
* @param x The x-coordinate of the center
* @param y The y-coordinate of the center
* @param radius The radius in pixels */
void Pixmap::fillCircle (int x, int y, int radius)
{
	m_pixmap.fillCircle(x, y, radius, m_color);
}

/** Returns the 32-bit RGBA8888 value of the pixel at x, y. For Alpha formats the RGB components will be one.
*
* @param x The x-coordinate
* @param y The y-coordinate
* @return The pixel color in RGBA8888 format. */
int Pixmap::getPixel (int x, int y)
{
	return m_pixmap.getPixel(x, y);
}

/** @return The width of the Pixmap in pixels. */
int Pixmap::getWidth ()
{
	return m_pixmap.getWidth();
}

/** @return The height of the Pixmap in pixels. */
int Pixmap::getHeight ()
{
	return m_pixmap.getHeight();
}

/** Releases all resources associated with this Pixmap. */
void Pixmap::dispose ()
{
	m_pixmap.dispose();
}

/** Draws a pixel at the given location with the current color.
*
* @param x the x-coordinate
* @param y the y-coordinate */
void Pixmap::drawPixel (int x, int y)
{
	m_pixmap.setPixel(x, y, m_color);
}

/** Draws a pixel at the given location with the given color.
*
* @param x the x-coordinate
* @param y the y-coordinate
* @param color the color in RGBA8888 format. */
void Pixmap::drawPixel (int x, int y, int color)
{
	m_pixmap.setPixel(x, y, color);
}

/** Returns the OpenGL ES format of this Pixmap. Used as the seventh parameter to
* {@link GLCommon#glTexImage2D(int, int, int, int, int, int, int, int, java.nio.Buffer)}.
* @return one of GL_ALPHA, GL_RGB, GL_RGBA, GL_LUMINANCE, or GL_LUMINANCE_ALPHA. */
int Pixmap::getGLFormat ()
{
	return m_pixmap.getGLFormat();
}

/** Returns the OpenGL ES format of this Pixmap. Used as the third parameter to
* {@link GLCommon#glTexImage2D(int, int, int, int, int, int, int, int, java.nio.Buffer)}.
* @return one of GL_ALPHA, GL_RGB, GL_RGBA, GL_LUMINANCE, or GL_LUMINANCE_ALPHA. */
int Pixmap::getGLInternalFormat ()
{
	return m_pixmap.getGLInternalFormat();
}

/** Returns the OpenGL ES type of this Pixmap. Used as the eighth parameter to
* {@link GLCommon#glTexImage2D(int, int, int, int, int, int, int, int, java.nio.Buffer)}.
* @return one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4 */
int Pixmap::getGLType ()
{
	return m_pixmap.getGLType();
}

/** Returns the direct ByteBuffer holding the pixel data. For the format Alpha each value is encoded as a byte. For the format
* LuminanceAlpha the luminance is the first byte and the alpha is the second byte of the pixel. For the formats RGB888 and
* RGBA8888 the color components are stored in a single byte each in the order red, green, blue (alpha). For the formats RGB565
* and RGBA4444 the pixel colors are stored in shorts in machine dependent order.
* @return the direct {@link ByteBuffer} holding the pixel data. */
 unsigned char* Pixmap::getPixels ()
{
	return m_pixmap.getPixels();
}

/** @return the {@link Format} of this Pixmap. */
Pixmap::Format Pixmap::getFormat () const
{
	return Format::fromGdx2DPixmapFormat(m_pixmap.getFormat());
}

/** @return the currently set {@link Blending} */
Pixmap::Blending Pixmap::getBlending ()
{
	return m_blending;
}

