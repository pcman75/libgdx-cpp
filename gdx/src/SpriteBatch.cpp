#include "stdafx.h"
#include "SpriteBatch.h"
#include "NumberUtils.h"

int SpriteBatch::X1 = 0;
int SpriteBatch::Y1 = 1;
int SpriteBatch::C1 = 2;
int SpriteBatch::U1 = 3;
int SpriteBatch::V1 = 4;
int SpriteBatch::X2 = 5;
int SpriteBatch::Y2 = 6;
int SpriteBatch::C2 = 7;
int SpriteBatch::U2 = 8;
int SpriteBatch::V2 = 9;
int SpriteBatch::X3 = 10;
int SpriteBatch::Y3 = 11;
int SpriteBatch::C3 = 12;
int SpriteBatch::U3 = 13;
int SpriteBatch::V3 = 14;
int SpriteBatch::X4 = 15;
int SpriteBatch::Y4 = 16;
int SpriteBatch::C4 = 17;
int SpriteBatch::U4 = 18;
int SpriteBatch::V4 = 19;

void SpriteBatch::init()
{
	renderCalls = 0;
	totalRenderCalls = 0;
	maxSpritesInBatch = 0;
	m_mesh = NULL;
	m_buffers = NULL;
	m_numBuffers = 0;
	m_lastTexture = NULL;
	m_invTexWidth = 0;
	m_invTexHeight = 0;
	m_idx = 0;
	m_currBufferIdx = 0;
	m_vertices = NULL;
	m_verticesSize = 0;
	m_drawing = false;
	m_blendingDisabled = false;
	m_blendSrcFunc = GL11::GDX_GL_SRC_ALPHA;
	m_blendDstFunc = GL11::GDX_GL_ONE_MINUS_SRC_ALPHA;
	m_shader = NULL;
	m_shaderProvided = true;
	m_customShader = NULL;
	m_color = Color::WHITE.toFloatBits();
	m_tempColor = Color(1, 1, 1, 1);
}

void SpriteBatch::init(int size)
{
	init(size, (ShaderProgram*)NULL);
}

void SpriteBatch::init(int size, ShaderProgram* defaultShader)
{
	init(size, 1, defaultShader);
}

SpriteBatch::~SpriteBatch()
{
	for(int i = 0; i < m_numBuffers; i++)
	{
		if(m_buffers[i])
		{
			delete m_buffers[i];
			m_buffers[i] = NULL;
		}
	}
	if(m_buffers)
	{
		delete[] m_buffers;
		m_buffers = NULL;
	}
	if(m_vertices)
	{
		delete[] m_vertices;
		m_vertices = NULL;
	}

	if(!m_shaderProvided)
	{
		m_shader->dispose();
		delete m_shader;
		m_shader = NULL;
	}
}

void SpriteBatch::init(int size, int buffers)
{
	init(size, buffers, NULL);
}

void SpriteBatch::init(int size, int buffers, ShaderProgram* defaultShader)
{
	m_numBuffers = buffers;
	m_buffers = new Mesh*[buffers];

	for(int i = 0; i < buffers; i++)
	{
		VertexAttribute attributes[] = {VertexAttribute(VertexAttributes::Position, 2, ShaderProgram::POSITION_ATTRIBUTE), 
			VertexAttribute(VertexAttributes::ColorPacked, 4, ShaderProgram::COLOR_ATTRIBUTE),
			VertexAttribute(VertexAttributes::TextureCoordinates, 2, (std::string(ShaderProgram::TEXCOORD_ATTRIBUTE) + "0").c_str())};
		m_buffers[i] = new Mesh(Mesh::VertexArrayType, false, VertexAttributes(attributes, sizeof(attributes)/sizeof(attributes[0])));
	}

	m_projectionMatrix.setToOrtho2D(0, 0, (float)Gdx.graphics->getWidth(), (float)Gdx.graphics->getHeight());

	m_verticesSize = size * Sprite::SPRITE_SIZE;
	m_vertices = new float[m_verticesSize];

	int len = size * 6;
	short* indices = new short[len];
	short j = 0;
	for(int i = 0; i < len; i += 6, j += 4)
	{
		indices[i + 0] = (short)(j + 0);
		indices[i + 1] = (short)(j + 1);
		indices[i + 2] = (short)(j + 2);
		indices[i + 3] = (short)(j + 2);
		indices[i + 4] = (short)(j + 3);
		indices[i + 5] = (short)(j + 0);
	}
	for(int i = 0; i < buffers; i++)
	{
		m_buffers[i]->setIndices(indices, len);
	}
	m_mesh = m_buffers[0];

	if(Gdx.graphics->isGL20Available() && defaultShader == NULL)
	{
		m_shader = createDefaultShader();
		m_shaderProvided = false;
	}
	else
		m_shader = defaultShader;
}

/** Constructs a new SpriteBatch. Sets the projection matrix to an orthographic projection with y-axis point upwards, x-axis
* point to the right and the origin being in the bottom left corner of the screen. The projection will be pixel perfect with
* respect to the screen resolution. */
SpriteBatch::SpriteBatch()
{
	init();
	init(1000);
}

/** Constructs a SpriteBatch with the specified size and (if GL2) the default shader. See
* {@link #SpriteBatch(int, ShaderProgram)}. */
SpriteBatch::SpriteBatch(int size)
{
	init();
	init(size);
}

/** <p>
* Constructs a new SpriteBatch. Sets the projection matrix to an orthographic projection with y-axis point upwards, x-axis
* point to the right and the origin being in the bottom left corner of the screen. The projection will be pixel perfect with
* respect to the screen resolution.
* </p>
*
* <p>
* The size parameter specifies the maximum size of a single batch in number of sprites
* </p>
*
* @param size the batch size in number of sprites
* @param defaultShader the default shader to use */
SpriteBatch::SpriteBatch(int size, ShaderProgram* defaultShader)
{
	init();
	init(size, defaultShader);
}

/** Constructs a SpriteBatch with the specified size and number of buffers and (if GL2) the default shader. See
* {@link #SpriteBatch(int, int, ShaderProgram)}. */
SpriteBatch::SpriteBatch(int size, int buffers)
{
	init();
	init(size, buffers);
}

/** <p>
* Constructs a new SpriteBatch. Sets the projection matrix to an orthographic projection with y-axis point upwards, x-axis
* point to the right and the origin being in the bottom left corner of the screen. The projection will be pixel perfect with
* respect to the screen resolution.
* </p>
*
* <p>
* The size parameter specifies the maximum size of a single batch in number of sprites
* </p>
*
* @param size the batch size in number of sprites
* @param buffers the number of buffers to use. only makes sense with VBOs. This is an expert function.
* @param defaultShader the default shader to use */
SpriteBatch::SpriteBatch(int size, int buffers, ShaderProgram* defaultShader)
{
	init();
	init(size, buffers, defaultShader);
}

/** Returns a new instance of the default shader used by SpriteBatch for GL2 when no shader is specified. 
caller must delete it*/
ShaderProgram* SpriteBatch::createDefaultShader()
{
	std::string vertexShader = std::string("attribute vec4 ") + ShaderProgram::POSITION_ATTRIBUTE + ";\n"
		+ "attribute vec4 " + ShaderProgram::COLOR_ATTRIBUTE + ";\n"
		+ "attribute vec2 " + ShaderProgram::TEXCOORD_ATTRIBUTE + "0;\n"
		+ "uniform mat4 u_projectionViewMatrix;\n"
		+ "varying vec4 v_color;\n"
		+ "varying vec2 v_texCoords;\n"
		+ "\n"
		+ "void main()\n"
		+ "{\n"
		+ "   v_color = " + ShaderProgram::COLOR_ATTRIBUTE + ";\n"
		+ "   v_texCoords = " + ShaderProgram::TEXCOORD_ATTRIBUTE + "0;\n"
		+ "   gl_Position =  u_projectionViewMatrix * " + ShaderProgram::POSITION_ATTRIBUTE + ";\n"
		+ "}\n";
	std::string fragmentShader = std::string("#ifdef GL_ES\n")
		+ "#define LOWP lowp\n" + "precision mediump float;\n"
		+ "#else\n" + "#define LOWP \n" + "#endif\n"
		+ "varying LOWP vec4 v_color;\n"
		+ "varying vec2 v_texCoords;\n"
		+ "uniform sampler2D u_texture;\n"
		+ "void main()\n"
		+ "{\n"
		+ "  gl_FragColor = v_color * texture2D(u_texture, v_texCoords);\n"
		+ "}";

	ShaderProgram* shader = new ShaderProgram(vertexShader, fragmentShader);
	if(!shader->isCompiled())
		throw new GdxRuntimeException(std::string("couldn't compile shader: ") + shader->getLog());
	return shader;
}

/** Sets up the SpriteBatch for drawing. This will disable depth buffer writting. It enables blending and texturing. If you have
* more texture units enabled than the first one you have to disable them before calling this. Uses a screen coordinate system
* by default where everything is given in pixels. You can specify your own projection and modelview matrices via
* {@link #setProjectionMatrix(Matrix4)} and {@link #setTransformMatrix(Matrix4)}. */
void SpriteBatch::begin()
{
	if(m_drawing) 
		throw new GdxRuntimeException("you have to call SpriteBatch.end() first");
	renderCalls = 0;

	Gdx.gl->glDepthMask(false);
	if(Gdx.graphics->isGL20Available())
	{
		if(m_customShader != NULL)
			m_customShader->begin();
		else
			m_shader->begin();
	}
	else
	{
		Gdx.gl->glEnable(GL10::GDX_GL_TEXTURE_2D);
	}
	setupMatrices();

	m_idx = 0;
	m_lastTexture = NULL;
	m_drawing = true;
}

/** Finishes off rendering. Enables depth writes, disables blending and texturing. Must always be called after a call to
* {@link #begin()} */
void SpriteBatch::end()
{
	if(!m_drawing) 
		throw new GdxRuntimeException("SpriteBatch.begin must be called before end.");
	if(m_idx > 0) 
		renderMesh();
	m_lastTexture = NULL;
	m_idx = 0;
	m_drawing = false;

	GLCommon* gl = Gdx.gl;
	gl->glDepthMask(true);
	if(isBlendingEnabled()) 
		gl->glDisable(GL10::GDX_GL_BLEND);
	
	gl->glDisable(GL10::GDX_GL_TEXTURE_2D);

	if(Gdx.graphics->isGL20Available())
	{
		if(m_customShader != NULL)
			m_customShader->end();
		else
			m_shader->end();
	}
}

/** Sets the color used to tint images when they are added to the SpriteBatch. Default is {@link Color#WHITE}. */
void SpriteBatch::setColor(const Color& tint)
{
	m_color = tint.toFloatBits();
}

/** @see #setColor(Color) */
void SpriteBatch::setColor(float r, float g, float b, float a)
{
	int intBits = (int)(255 * a) << 24 | (int)(255 * b) << 16 | (int)(255 * g) << 8 | (int)(255 * r);
	m_color = NumberUtils::intToFloatColor(intBits);
}

/** @see #setColor(Color)
* @see Color#toFloatBits() */
void SpriteBatch::setColor(float color)
{
	m_color = color;
}

/** @return the rendering color of this SpriteBatch. Manipulating the returned instance has no effect. */
Color& SpriteBatch::getColor()
{
	int intBits = NumberUtils::floatToIntColor(m_color);
	Color& color = m_tempColor;
	color.r = (intBits & 0xff) / 255.f;
	color.g = ((intBits >> 8) & 0xff) / 255.f;
	color.b = ((intBits >> 16) & 0xff) / 255.f;
	color.a = ((intBits >> 24) & 0xff) / 255.f;
	return color;
}

/** Draws a rectangle with the bottom left corner at x,y having the given width and height in pixels. The rectangle is offset by
* originX, originY relative to the origin. Scale specifies the scaling factor by which the rectangle should be scaled around
* originX, originY. Rotation specifies the angle of counter clockwise rotation of the rectangle around originX, originY. The
* portion of the {@link Texture} given by srcX, srcY and srcWidth, srcHeight is used. These coordinates and sizes are given in
* texels. FlipX and flipY specify whether the texture portion should be fliped horizontally or vertically.
*
* @param texture the Texture
* @param x the x-coordinate in screen space
* @param y the y-coordinate in screen space
* @param originX the x-coordinate of the scaling and rotation origin relative to the screen space coordinates
* @param originY the y-coordinate of the scaling and rotation origin relative to the screen space coordinates
* @param width the width in pixels
* @param height the height in pixels
* @param scaleX the scale of the rectangle around originX/originY in x
* @param scaleY the scale of the rectangle around originX/originY in y
* @param rotation the angle of counter clockwise rotation of the rectangle around originX/originY
* @param srcX the x-coordinate in texel space
* @param srcY the y-coordinate in texel space
* @param srcWidth the source with in texels
* @param srcHeight the source height in texels
* @param flipX whether to flip the sprite horizontally
* @param flipY whether to flip the sprite vertically */
void SpriteBatch::draw(Texture* texture, float x, float y, float originX, float originY, float width, float height, float scaleX,
	float scaleY, float rotation, int srcX, int srcY, int srcWidth, int srcHeight, bool flipX, bool flipY)
{
	if(!m_drawing) 
		throw new GdxRuntimeException("SpriteBatch.begin must be called before draw.");

	//TODO: compare pointers??? It's OK?
	if(texture != m_lastTexture)
	{
		renderMesh();
		m_lastTexture = texture;
		m_invTexWidth = 1.0f / texture->getWidth();
		m_invTexHeight = 1.0f / texture->getHeight();
	}
	else if(m_idx == m_verticesSize) 
		renderMesh();

	// bottom left and top right corner points relative to origin
	float worldOriginX = x + originX;
	float worldOriginY = y + originY;
	float fx = -originX;
	float fy = -originY;
	float fx2 = width - originX;
	float fy2 = height - originY;

	// scale
	if(scaleX != 1 || scaleY != 1)
	{
		fx *= scaleX;
		fy *= scaleY;
		fx2 *= scaleX;
		fy2 *= scaleY;
	}

	// construct corner points, start from top left and go counter clockwise
	float p1x = fx;
	float p1y = fy;
	float p2x = fx;
	float p2y = fy2;
	float p3x = fx2;
	float p3y = fy2;
	float p4x = fx2;
	float p4y = fy;

	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float x4;
	float y4;

	// rotate
	if(rotation != 0)
	{
		float cos = MathUtils::cosDeg(rotation);
		float sin = MathUtils::sinDeg(rotation);

		x1 = cos * p1x - sin * p1y;
		y1 = sin * p1x + cos * p1y;

		x2 = cos * p2x - sin * p2y;
		y2 = sin * p2x + cos * p2y;

		x3 = cos * p3x - sin * p3y;
		y3 = sin * p3x + cos * p3y;

		x4 = x1 + (x3 - x2);
		y4 = y3 - (y2 - y1);
	}
	else
	{
		x1 = p1x;
		y1 = p1y;

		x2 = p2x;
		y2 = p2y;

		x3 = p3x;
		y3 = p3y;

		x4 = p4x;
		y4 = p4y;
	}

	x1 += worldOriginX;
	y1 += worldOriginY;
	x2 += worldOriginX;
	y2 += worldOriginY;
	x3 += worldOriginX;
	y3 += worldOriginY;
	x4 += worldOriginX;
	y4 += worldOriginY;

	float u = srcX * m_invTexWidth;
	float v = (srcY + srcHeight) * m_invTexHeight;
	float u2 = (srcX + srcWidth) * m_invTexWidth;
	float v2 = srcY * m_invTexHeight;

	if(flipX)
	{
		float tmp = u;
		u = u2;
		u2 = tmp;
	}

	if(flipY)
	{
		float tmp = v;
		v = v2;
		v2 = tmp;
	}

	m_vertices[m_idx++] = x1;
	m_vertices[m_idx++] = y1;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v;

	m_vertices[m_idx++] = x2;
	m_vertices[m_idx++] = y2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = x3;
	m_vertices[m_idx++] = y3;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = x4;
	m_vertices[m_idx++] = y4;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v;
}

//TODO: refactor draw functions: common code should make a separate function
/** Draws a rectangle with the bottom left corner at x,y having the given width and height in pixels. The portion of the
* {@link Texture} given by srcX, srcY and srcWidth, srcHeight is used. These coordinates and sizes are given in texels. FlipX
* and flipY specify whether the texture portion should be fliped horizontally or vertically.
*
* @param texture the Texture
* @param x the x-coordinate in screen space
* @param y the y-coordinate in screen space
* @param width the width in pixels
* @param height the height in pixels
* @param srcX the x-coordinate in texel space
* @param srcY the y-coordinate in texel space
* @param srcWidth the source with in texels
* @param srcHeight the source height in texels
* @param flipX whether to flip the sprite horizontally
* @param flipY whether to flip the sprite vertically */
void SpriteBatch::draw(Texture* texture, float x, float y, float width, float height, int srcX, int srcY, int srcWidth,
	int srcHeight, bool flipX, bool flipY)
{
	if(!m_drawing) 
		throw new GdxRuntimeException("SpriteBatch.begin must be called before draw.");

	if(texture != m_lastTexture)
	{
		renderMesh();
		m_lastTexture = texture;
		m_invTexWidth = 1.0f / texture->getWidth();
		m_invTexHeight = 1.0f / texture->getHeight();
	}
	else if(m_idx == m_verticesSize)
		renderMesh();

	float u = srcX * m_invTexWidth;
	float v = (srcY + srcHeight) * m_invTexHeight;
	float u2 = (srcX + srcWidth) * m_invTexWidth;
	float v2 = srcY * m_invTexHeight;
	float fx2 = x + width;
	float fy2 = y + height;

	if(flipX)
	{
		float tmp = u;
		u = u2;
		u2 = tmp;
	}

	if(flipY)
	{
		float tmp = v;
		v = v2;
		v2 = tmp;
	}

	m_vertices[m_idx++] = x;
	m_vertices[m_idx++] = y;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v;

	m_vertices[m_idx++] = x;
	m_vertices[m_idx++] = fy2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = fx2;
	m_vertices[m_idx++] = fy2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = fx2;
	m_vertices[m_idx++] = y;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v;
}

/** Draws a rectangle with the bottom left corner at x,y having the given width and height in pixels. The portion of the
* {@link Texture} given by srcX, srcY and srcWidth, srcHeight are used. These coordinates and sizes are given in texels.
*
* @param texture the Texture
* @param x the x-coordinate in screen space
* @param y the y-coordinate in screen space
* @param srcX the x-coordinate in texel space
* @param srcY the y-coordinate in texel space
* @param srcWidth the source with in texels
* @param srcHeight the source height in texels */
void SpriteBatch::draw(Texture* texture, float x, float y, int srcX, int srcY, int srcWidth, int srcHeight)
{
	if(!m_drawing) 
		throw new GdxRuntimeException("SpriteBatch.begin must be called before draw.");

	if(texture != m_lastTexture)
	{
		renderMesh();
		m_lastTexture = texture;
		m_invTexWidth = 1.0f / texture->getWidth();
		m_invTexHeight = 1.0f / texture->getHeight();
	}
	else if(m_idx == m_verticesSize) renderMesh();

	float u = srcX * m_invTexWidth;
	float v = (srcY + srcHeight) * m_invTexHeight;
	float u2 = (srcX + srcWidth) * m_invTexWidth;
	float v2 = srcY * m_invTexHeight;
	float fx2 = x + srcWidth;
	float fy2 = y + srcHeight;

	m_vertices[m_idx++] = x;
	m_vertices[m_idx++] = y;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v;

	m_vertices[m_idx++] = x;
	m_vertices[m_idx++] = fy2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = fx2;
	m_vertices[m_idx++] = fy2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = fx2;
	m_vertices[m_idx++] = y;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v;
}

/** Draws a rectangle with the bottom left corner at x,y having the given width and height in pixels. The portion of the
* {@link Texture} given by u, v and u2, v2 are used. These coordinates and sizes are given in texture size percentage. The
* rectangle will have the given tint {@link Color}.
*
* @param texture the Texture
* @param x the x-coordinate in screen space
* @param y the y-coordinate in screen space
* @param width the width in pixels
* @param height the height in pixels */
void SpriteBatch::draw(Texture* texture, float x, float y, float width, float height, float u, float v, float u2, float v2)
{
	if(!m_drawing)
		throw new GdxRuntimeException("SpriteBatch.begin must be called before draw.");

	if(texture != m_lastTexture)
	{
		renderMesh();
		m_lastTexture = texture;
		m_invTexWidth = 1.0f / texture->getWidth();
		m_invTexHeight = 1.0f / texture->getHeight();
	}
	else if(m_idx == m_verticesSize) 
		renderMesh();

	float fx2 = x + width;
	float fy2 = y + height;

	m_vertices[m_idx++] = x;
	m_vertices[m_idx++] = y;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v;

	m_vertices[m_idx++] = x;
	m_vertices[m_idx++] = fy2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = fx2;
	m_vertices[m_idx++] = fy2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = fx2;
	m_vertices[m_idx++] = y;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v;
}

/** Draws a rectangle with the bottom left corner at x,y having the width and height of the texture.
* @param texture the Texture
* @param x the x-coordinate in screen space
* @param y the y-coordinate in screen space */
void SpriteBatch::draw(Texture* texture, float x, float y)
{
	if(!m_drawing) throw new GdxRuntimeException("SpriteBatch.begin must be called before draw.");

	if(texture != m_lastTexture)
	{
		renderMesh();
		m_lastTexture = texture;
		m_invTexWidth = 1.0f / texture->getWidth();
		m_invTexHeight = 1.0f / texture->getHeight();
	}
	else if(m_idx == m_verticesSize) 
		renderMesh();

	float fx2 = x + texture->getWidth();
	float fy2 = y + texture->getHeight();

	m_vertices[m_idx++] = x;
	m_vertices[m_idx++] = y;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = 0;
	m_vertices[m_idx++] = 1;

	m_vertices[m_idx++] = x;
	m_vertices[m_idx++] = fy2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = 0;
	m_vertices[m_idx++] = 0;

	m_vertices[m_idx++] = fx2;
	m_vertices[m_idx++] = fy2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = 1;
	m_vertices[m_idx++] = 0;

	m_vertices[m_idx++] = fx2;
	m_vertices[m_idx++] = y;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = 1;
	m_vertices[m_idx++] = 1;
}

/** Draws a rectangle with the bottom left corner at x,y and stretching the region to cover the given width and height. */
void SpriteBatch::draw(Texture* texture, float x, float y, float width, float height)
{
	if(!m_drawing) throw new GdxRuntimeException("SpriteBatch.begin must be called before draw.");

	if(texture != m_lastTexture)
	{
		renderMesh();
		m_lastTexture = texture;
		m_invTexWidth = 1.f / texture->getWidth();
		m_invTexHeight = 1.f / texture->getHeight();
	}
	else if(m_idx == m_verticesSize)    //
		renderMesh();

	float fx2 = x + width;
	float fy2 = y + height;
	float u = 0;
	float v = 1;
	float u2 = 1;
	float v2 = 0;

	m_vertices[m_idx++] = x;
	m_vertices[m_idx++] = y;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v;

	m_vertices[m_idx++] = x;
	m_vertices[m_idx++] = fy2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = fx2;
	m_vertices[m_idx++] = fy2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = fx2;
	m_vertices[m_idx++] = y;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v;
}

/** Draws a rectangle using the given m_vertices. There must be 4 m_vertices, each made up of 5 elements in this order: x, y, color,
* u, v. */
void SpriteBatch::draw(Texture* texture, float* spriteVertices, int offset, int length)
{
	if(!m_drawing) 
		throw new GdxRuntimeException("SpriteBatch.begin must be called before draw.");

	if(texture != m_lastTexture)
	{
		renderMesh();
		m_lastTexture = texture;
		m_invTexWidth = 1.0f / texture->getWidth();
		m_invTexHeight = 1.0f / texture->getHeight();
	}

	int remainingVertices = m_verticesSize - m_idx;
	if(remainingVertices == 0)
	{
		renderMesh();
		remainingVertices = m_verticesSize;
	}
	int vertexCount = std::min(remainingVertices, length - offset);
	//System.arraycopy(spriteVertices, offset, m_vertices, m_idx, vertexCount);
	memcpy(m_vertices + m_idx, spriteVertices + offset, vertexCount * sizeof(float));

	offset += vertexCount;
	m_idx += vertexCount;

	while(offset < length)
	{
		renderMesh();
		vertexCount = std::min(m_verticesSize, length - offset);
		//System.arraycopy(spriteVertices, offset, m_vertices, 0, vertexCount);
		memcpy(m_vertices, spriteVertices + offset, vertexCount * sizeof(float));
		offset += vertexCount;
		m_idx += vertexCount;
	}
}

/** Draws a rectangle with the bottom left corner at x,y having the width and height of the region. */
void SpriteBatch::draw(TextureRegion* region, float x, float y)
{
	draw(region, x, y, (float)abs(region->getRegionWidth()), (float)abs(region->getRegionHeight()));
}

/** Draws a rectangle with the bottom left corner at x,y and stretching the region to cover the given width and height. */
void SpriteBatch::draw(TextureRegion* region, float x, float y, float width, float height)
{
	if(!m_drawing) 
		throw new GdxRuntimeException("SpriteBatch.begin must be called before draw.");

	Texture* texture = region->getTexture();
	if(texture != m_lastTexture)
	{
		renderMesh();
		m_lastTexture = texture;
		m_invTexWidth = 1.f / texture->getWidth();
		m_invTexHeight = 1.f / texture->getHeight();
	}
	else if(m_idx == m_verticesSize)    //
		renderMesh();

	float fx2 = x + width;
	float fy2 = y + height;
	float u = region->getU();
	float v = region->getV2();
	float u2 = region->getU2();
	float v2 = region->getV();

	m_vertices[m_idx++] = x;
	m_vertices[m_idx++] = y;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v;

	m_vertices[m_idx++] = x;
	m_vertices[m_idx++] = fy2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = fx2;
	m_vertices[m_idx++] = fy2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = fx2;
	m_vertices[m_idx++] = y;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v;
}

/** Draws a rectangle with the bottom left corner at x,y and stretching the region to cover the given width and height. The
* rectangle is offset by originX, originY relative to the origin. Scale specifies the scaling factor by which the rectangle
* should be scaled around originX, originY. Rotation specifies the angle of counter clockwise rotation of the rectangle around
* originX, originY. */
void SpriteBatch::draw(TextureRegion* region, float x, float y, float originX, float originY, float width, float height,
	float scaleX, float scaleY, float rotation)
{
	if(!m_drawing) 
		throw new GdxRuntimeException("SpriteBatch.begin must be called before draw.");

	Texture* texture = region->getTexture();
	if(texture != m_lastTexture)
	{
		renderMesh();
		m_lastTexture = texture;
		m_invTexWidth = 1.f / texture->getWidth();
		m_invTexHeight = 1.f / texture->getHeight();
	}
	else if(m_idx == m_verticesSize)    //
		renderMesh();

	// bottom left and top right corner points relative to origin
	float worldOriginX = x + originX;
	float worldOriginY = y + originY;
	float fx = -originX;
	float fy = -originY;
	float fx2 = width - originX;
	float fy2 = height - originY;

	// scale
	if(scaleX != 1 || scaleY != 1)
	{
		fx *= scaleX;
		fy *= scaleY;
		fx2 *= scaleX;
		fy2 *= scaleY;
	}

	// construct corner points, start from top left and go counter clockwise
	float p1x = fx;
	float p1y = fy;
	float p2x = fx;
	float p2y = fy2;
	float p3x = fx2;
	float p3y = fy2;
	float p4x = fx2;
	float p4y = fy;

	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float x4;
	float y4;

	// rotate
	if(rotation != 0)
	{
		float cos = MathUtils::cosDeg(rotation);
		float sin = MathUtils::sinDeg(rotation);

		x1 = cos * p1x - sin * p1y;
		y1 = sin * p1x + cos * p1y;

		x2 = cos * p2x - sin * p2y;
		y2 = sin * p2x + cos * p2y;

		x3 = cos * p3x - sin * p3y;
		y3 = sin * p3x + cos * p3y;

		x4 = x1 + (x3 - x2);
		y4 = y3 - (y2 - y1);
	}
	else
	{
		x1 = p1x;
		y1 = p1y;

		x2 = p2x;
		y2 = p2y;

		x3 = p3x;
		y3 = p3y;

		x4 = p4x;
		y4 = p4y;
	}

	x1 += worldOriginX;
	y1 += worldOriginY;
	x2 += worldOriginX;
	y2 += worldOriginY;
	x3 += worldOriginX;
	y3 += worldOriginY;
	x4 += worldOriginX;
	y4 += worldOriginY;

	float u = region->getU();
	float v = region->getV2();
	float u2 = region->getU2();
	float v2 = region->getV();

	m_vertices[m_idx++] = x1;
	m_vertices[m_idx++] = y1;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v;

	m_vertices[m_idx++] = x2;
	m_vertices[m_idx++] = y2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = x3;
	m_vertices[m_idx++] = y3;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = x4;
	m_vertices[m_idx++] = y4;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v;
}

/** Draws a rectangle with the bottom left corner at x,y and stretching the region to cover the given width and height. The
* rectangle is offset by originX, originY relative to the origin. Scale specifies the scaling factor by which the rectangle
* should be scaled around originX, originY. Rotation specifies the angle of counter clockwise rotation of the rectangle around
* originX, originY. */
void SpriteBatch::draw(TextureRegion* region, float x, float y, float originX, float originY, float width, float height,
	float scaleX, float scaleY, float rotation, bool clockwise)
{
	if(!m_drawing) 
		throw new GdxRuntimeException("SpriteBatch.begin must be called before draw.");

	Texture* texture = region->getTexture();
	if(texture != m_lastTexture)
	{
		renderMesh();
		m_lastTexture = texture;
		m_invTexWidth = 1.f / texture->getWidth();
		m_invTexHeight = 1.f / texture->getHeight();
	}
	else if(m_idx == m_verticesSize)    //
		renderMesh();

	// bottom left and top right corner points relative to origin
	float worldOriginX = x + originX;
	float worldOriginY = y + originY;
	float fx = -originX;
	float fy = -originY;
	float fx2 = width - originX;
	float fy2 = height - originY;

	// scale
	if(scaleX != 1 || scaleY != 1)
	{
		fx *= scaleX;
		fy *= scaleY;
		fx2 *= scaleX;
		fy2 *= scaleY;
	}

	// construct corner points, start from top left and go counter clockwise
	float p1x = fx;
	float p1y = fy;
	float p2x = fx;
	float p2y = fy2;
	float p3x = fx2;
	float p3y = fy2;
	float p4x = fx2;
	float p4y = fy;

	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float x4;
	float y4;

	// rotate
	if(rotation != 0)
	{
		float cos = MathUtils::cosDeg(rotation);
		float sin = MathUtils::sinDeg(rotation);

		x1 = cos * p1x - sin * p1y;
		y1 = sin * p1x + cos * p1y;

		x2 = cos * p2x - sin * p2y;
		y2 = sin * p2x + cos * p2y;

		x3 = cos * p3x - sin * p3y;
		y3 = sin * p3x + cos * p3y;

		x4 = x1 + (x3 - x2);
		y4 = y3 - (y2 - y1);
	}
	else
	{
		x1 = p1x;
		y1 = p1y;

		x2 = p2x;
		y2 = p2y;

		x3 = p3x;
		y3 = p3y;

		x4 = p4x;
		y4 = p4y;
	}

	x1 += worldOriginX;
	y1 += worldOriginY;
	x2 += worldOriginX;
	y2 += worldOriginY;
	x3 += worldOriginX;
	y3 += worldOriginY;
	x4 += worldOriginX;
	y4 += worldOriginY;

	float u1, v1, u2, v2, u3, v3, u4, v4;
	if(clockwise)
	{
		u1 = region->getU2();
		v1 = region->getV2();
		u2 = region->getU();
		v2 = region->getV2();
		u3 = region->getU();
		v3 = region->getV();
		u4 = region->getU2();
		v4 = region->getV();
	}
	else
	{
		u1 = region->getU();
		v1 = region->getV();
		u2 = region->getU2();
		v2 = region->getV();
		u3 = region->getU2();
		v3 = region->getV2();
		u4 = region->getU();
		v4 = region->getV2();
	}

	m_vertices[m_idx++] = x1;
	m_vertices[m_idx++] = y1;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u1;
	m_vertices[m_idx++] = v1;

	m_vertices[m_idx++] = x2;
	m_vertices[m_idx++] = y2;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u2;
	m_vertices[m_idx++] = v2;

	m_vertices[m_idx++] = x3;
	m_vertices[m_idx++] = y3;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u3;
	m_vertices[m_idx++] = v3;

	m_vertices[m_idx++] = x4;
	m_vertices[m_idx++] = y4;
	m_vertices[m_idx++] = m_color;
	m_vertices[m_idx++] = u4;
	m_vertices[m_idx++] = v4;
}

/** Causes any pending sprites to be rendered, without ending the SpriteBatch. */
void SpriteBatch::flush()
{
	renderMesh();
}

void SpriteBatch::renderMesh()
{
	if(m_idx == 0) return;

	renderCalls++;
	totalRenderCalls++;
	int spritesInBatch = m_idx / 20;
	if(spritesInBatch > maxSpritesInBatch) maxSpritesInBatch = spritesInBatch;

	m_lastTexture->bind();
	m_mesh->setVertices(m_vertices, m_idx);

  if(m_blendingDisabled)
	{
		Gdx.gl->glDisable(GL20::GDX_GL_BLEND);
	}
	else
	{
		Gdx.gl->glEnable(GL20::GDX_GL_BLEND);
		Gdx.gl->glBlendFunc(m_blendSrcFunc, m_blendDstFunc);
	}
	

	if(Gdx.graphics->isGL20Available())
	{
		if(m_customShader != NULL)
			m_mesh->render(m_customShader, GL10::GDX_GL_TRIANGLES, 0, spritesInBatch * 6);
		else
			m_mesh->render(m_shader, GL10::GDX_GL_TRIANGLES, 0, spritesInBatch * 6);
	}
	else
	{
		m_mesh->render(GL10::GDX_GL_TRIANGLES, 0, spritesInBatch * 6);
	}

	m_idx = 0;
	m_currBufferIdx++;
	if(m_currBufferIdx == m_numBuffers) 
		m_currBufferIdx = 0;
	m_mesh = m_buffers[m_currBufferIdx];
}

/** Disables blending for drawing sprites. Does not disable blending for text rendering */
void SpriteBatch::disableBlending()
{
	renderMesh();
	m_blendingDisabled = true;
}

/** Enables blending for sprites */
void SpriteBatch::enableBlending()
{
	renderMesh();
	m_blendingDisabled = false;
}

/** Sets the blending function to be used when rendering sprites.
*
* @param srcFunc the source function, e.g. GL11::GDX_GL_SRC_ALPHA
* @param dstFunc the destination function, e.g. GL11::GDX_GL_ONE_MINUS_SRC_ALPHA */
void SpriteBatch::setBlendFunction(int srcFunc, int dstFunc)
{
	renderMesh();
	m_blendSrcFunc = srcFunc;
	m_blendDstFunc = dstFunc;
}

/** Disposes all resources associated with this SpriteBatch */
void SpriteBatch::dispose()
{
	for(int i = 0; i < m_numBuffers; i++)
		m_buffers[i]->dispose();
	if(m_shader != NULL) 
		m_shader->dispose();
}

/** Returns the current projection matrix. Changing this will result in undefined behaviour.
*
* @return the currently set projection matrix */
Matrix4& SpriteBatch::getProjectionMatrix()
{
	return m_projectionMatrix;
}

/** Returns the current transform matrix. Changing this will result in undefined behaviour.
*
* @return the currently set transform matrix */
Matrix4& SpriteBatch::getTransformMatrix()
{
	return m_transformMatrix;
}

/** Sets the projection matrix to be used by this SpriteBatch. If this is called inside a {@link #begin()}/{@link #end()} block.
* the current batch is flushed to the gpu.
*
* @param projection the projection matrix */
void SpriteBatch::setProjectionMatrix(const Matrix4& projection)
{
	if(m_drawing) 
		flush();
	m_projectionMatrix.set(projection);
	if(m_drawing) 
		setupMatrices();
}

/** Sets the transform matrix to be used by this SpriteBatch. If this is called inside a {@link #begin()}/{@link #end()} block.
* the current batch is flushed to the gpu.
*
* @param transform the transform matrix */
void SpriteBatch::setTransformMatrix(const Matrix4& transform)
{
	if(m_drawing) 
		flush();
	m_transformMatrix.set(transform);
	if(m_drawing) 
		setupMatrices();
}

void SpriteBatch::setupMatrices()
{
	if(!Gdx.graphics->isGL20Available())
	{
		GL10* gl = Gdx.gl10;
		gl->glMatrixMode(GL10::GDX_GL_PROJECTION);
		gl->glLoadMatrixf(m_projectionMatrix.val, 0);
		gl->glMatrixMode(GL10::GDX_GL_MODELVIEW);
		gl->glLoadMatrixf(m_transformMatrix.val, 0);
	}
	else
	{
		m_combinedMatrix.set(m_projectionMatrix).mul(m_transformMatrix);
		if(m_customShader != NULL)
		{
			m_customShader->setUniformMatrix("u_proj", m_projectionMatrix);
			m_customShader->setUniformMatrix("u_trans", m_transformMatrix);
			m_customShader->setUniformMatrix("u_projTrans", m_combinedMatrix);
			m_customShader->setUniformi("u_texture", 0);
		}
		else
		{
			m_shader->setUniformMatrix("u_projectionViewMatrix", m_combinedMatrix);
			m_shader->setUniformi("u_texture", 0);
		}
	}
}

/** Sets the shader to be used in a GLES 2.0 environment. Vertex position attribute is called "a_position", the texture
* coordinates attribute is called called "a_texCoords0", the color attribute is called "a_color". See
* {@link ShaderProgram#POSITION_ATTRIBUTE}, {@link ShaderProgram#COLOR_ATTRIBUTE} and {@link ShaderProgram#TEXCOORD_ATTRIBUTE}
* which gets "0" appened to indicate the use of the first texture unit. The projection matrix is uploaded via a mat4 uniform
* called "u_proj", the transform matrix is uploaded via a uniform called "u_trans", the combined transform and projection
* matrx is is uploaded via a mat4 uniform called "u_projTrans". The texture sampler is passed via a uniform called
* "u_texture".
*
* Call this method with a NULL argument to use the default shader.
*
* @param shader the {@link ShaderProgram} or NULL to use the default shader. */
void SpriteBatch::setShader(ShaderProgram* shader)
{
	m_customShader = shader;
}

/** @return whether blending for sprites is enabled */
bool SpriteBatch::isBlendingEnabled()
{
	return !m_blendingDisabled;
}


