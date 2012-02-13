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

#include "Sprite.h"

/** <p>
 * A SpriteBatch is used to draw 2D rectangles that reference a texture (region). The class will batch the drawing commands and
 * optimize them for processing by the GPU.
 * </p>
 *
 * <p>
 * To draw something with a SpriteBatch one has to first call the {@link SpriteBatch#begin()} method which will setup appropriate
 * render states. When you are done with drawing you have to call {@link SpriteBatch#end()} which will actually draw the things
 * you specified.
 * </p>
 *
 * <p>
 * All drawing commands of the SpriteBatch operate in screen coordinates. The screen coordinate system has an x-axis pointing to
 * the right, an y-axis pointing upwards and the origin is in the lower left corner of the screen. You can also provide your own
 * transformation and projection matrices if you so wish.
 * </p>
 *
 * <p>
 * A SpriteBatch is managed. In case the OpenGL context is lost all OpenGL resources a SpriteBatch uses internally get
 * invalidated. A context is lost when a user switches to another application or receives an incoming call on Android. A
 * SpriteBatch will be automatically reloaded after the OpenGL context is restored.
 * </p>
 *
 * <p>
 * A SpriteBatch is a pretty heavy object so you should only ever have one in your program.
 * </p>
 *
 * <p>
 * A SpriteBatch works with OpenGL ES 1.x and 2.0. In the case of a 2.0 context it will use its own custom shader to draw all
 * provided sprites. You can set your own custom shader via {@link #setShader(ShaderProgram)}.
 * </p>
 *
 * <p>
 * A SpriteBatch has to be disposed if it is no longer used.
 * </p>
 */

#include "Mesh.h"
#include "Texture.h"

class SpriteBatch
{
public:
	/** number of render calls **/
	int renderCalls;

	/** number of rendering calls in total, will not be reset, unless it's done manually **/
	int totalRenderCalls;

	/** the maximum number of sprites rendered in one batch so far **/
	int maxSpritesInBatch;

private:
	Mesh* m_mesh;
	Mesh** m_buffers;

	Texture* m_lastTexture;
	float m_invTexWidth;
	float m_invTexHeight;

	int m_idx;
	int m_currBufferIdx;
	float* m_vertices;

	Matrix4 m_transformMatrix;
	Matrix4 m_projectionMatrix;
	Matrix4 m_combinedMatrix;

	bool m_drawing;

	bool m_blendingDisabled;
	int m_blendSrcFunc;
	int m_blendDstFunc;

	ShaderProgram* m_shader;
	ShaderProgram* m_customShader;

	float m_color;
	Color m_tempColor;

private:
	void init()
	{
		renderCalls = 0;
		totalRenderCalls = 0;
		maxSpritesInBatch = 0;
		m_mesh = NULL;
		m_buffers = NULL;
		m_lastTexture = NULL;
		m_invTexWidth = 0;
		m_invTexHeight = 0;
		m_idx = 0;
		m_currBufferIdx = 0;
		m_vertices = NULL;
		m_drawing = false;
		m_blendingDisabled = false;
		m_blendSrcFunc = GL11::GDX_GL_SRC_ALPHA;
		m_blendDstFunc = GL11::GDX_GL_ONE_MINUS_SRC_ALPHA;
		ShaderProgram* m_shader = NULL;
		ShaderProgram* m_customShader = NULL;
		m_color = Color::WHITE.toFloatBits();
		m_tempColor = Color(1, 1, 1, 1);
	}

	void init(int size)
	{
		init();
		init(size, NULL);
	}
	
	void init(int size, ShaderProgram* defaultShader)
	{
		init();
		m_buffers = new Mesh*[1];
		VertexAttribute attributes[] = {VertexAttribute(VertexAttributes::Position, 2, ShaderProgram.POSITION_ATTRIBUTE), 
			VertexAttribute(VertexAttributes::ColorPacked, 4, ShaderProgram::COLOR_ATTRIBUTE),
			VertexAttribute(VertexAttributes::TextureCoordinates, 2, (std::wstring(ShaderProgram::TEXCOORD_ATTRIBUTE) + L"0").c_str())};

		m_buffers[0] = new Mesh(Mesh::VertexArrayType, false, VertexAttributes(attributes, sizeof(attributes)/sizeof(attributes[0])));

		m_projectionMatrix.setToOrtho2D(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());

		m_vertices = new float[size * Sprite::SPRITE_SIZE];

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
		m_buffers[0]->setIndices(indices, len);
		m_mesh = m_buffers[0];

		if(Gdx.graphics->isGL20Available() && defaultShader == NULL)
			m_shader = createDefaultShader();
		else
			m_shader = defaultShader;
	}

	virtual ~SpriteBatch()
	{
		short* indices = m_mesh->getIndicesBuffer();
		if(indices)
		{
			delete[] indices;
		}
		if(m_buffers)
		{
			delete[] m_buffers;
			m_buffers = NULL;
		}
		if(m_mesh)
		{
			delete[] m_mesh;
			m_mesh = NULL;
		}
		if(m_vertices)
		{
			delete[] m_vertices;
			m_vertices = NULL;
		}
	}

	void init(int size, int buffers)
	{
		init();
		init(size, buffers, NULL);
	}

	void init(int size, int buffers, ShaderProgram* defaultShader)
	{
		init();
		m_buffers = new Mesh*[buffers];

		for(int i = 0; i < buffers; i++)
		{
			m_buffers[i] = new Mesh(false, size * 4, size * 6, new VertexAttribute(Usage.Position, 2,
			                           ShaderProgram.POSITION_ATTRIBUTE), new VertexAttribute(Usage.ColorPacked, 4, ShaderProgram.COLOR_ATTRIBUTE),
			                           new VertexAttribute(Usage.TextureCoordinates, 2, ShaderProgram.TEXCOORD_ATTRIBUTE + "0"));
		}

		m_projectionMatrix.setToOrtho2D(0, 0, Gdx.graphics.getWidth(), Gdx.graphics.getHeight());

		m_vertices = new float[size * Sprite.SPRITE_SIZE];

		int len = size * 6;
		short[] indices = new short[len];
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
			m_buffers[i].setIndices(indices);
		}
		m_mesh = m_buffers[0];

		if(Gdx.graphics.isGL20Available() && defaultShader == null)
			m_shader = createDefaultShader();
		else
			m_shader = defaultShader;
	}

public:
	/** Constructs a new SpriteBatch. Sets the projection matrix to an orthographic projection with y-axis point upwards, x-axis
	 * point to the right and the origin being in the bottom left corner of the screen. The projection will be pixel perfect with
	 * respect to the screen resolution. */
	SpriteBatch()
	{
		init(1000);
	}

	/** Constructs a SpriteBatch with the specified size and (if GL2) the default shader. See
	 * {@link #SpriteBatch(int, ShaderProgram)}. */
	SpriteBatch(int size)
	{
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
	SpriteBatch(int size, ShaderProgram* defaultShader)
	{
		init(size, defaultShader);
	}

	/** Constructs a SpriteBatch with the specified size and number of buffers and (if GL2) the default shader. See
	 * {@link #SpriteBatch(int, int, ShaderProgram)}. */
	SpriteBatch(int size, int buffers)
	{
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
	SpriteBatch(int size, int buffers, ShaderProgram* defaultShader)
	{
		init(size, buffers, defaultShader);
	}

	/** Returns a new instance of the default shader used by SpriteBatch for GL2 when no shader is specified. */
	static ShaderProgram* createDefaultShader()
	{
		String vertexShader = "attribute vec4 " + ShaderProgram.POSITION_ATTRIBUTE + ";\n" //
		                      + "attribute vec4 " + ShaderProgram.COLOR_ATTRIBUTE + ";\n" //
		                      + "attribute vec2 " + ShaderProgram.TEXCOORD_ATTRIBUTE + "0;\n" //
		                      + "uniform mat4 u_projectionViewMatrix;\n" //
		                      + "varying vec4 v_color;\n" //
		                      + "varying vec2 v_texCoords;\n" //
		                      + "\n" //
		                      + "void main()\n" //
		                      + "{\n" //
		                      + "   v_color = " + ShaderProgram.COLOR_ATTRIBUTE + ";\n" //
		                      + "   v_texCoords = " + ShaderProgram.TEXCOORD_ATTRIBUTE + "0;\n" //
		                      + "   gl_Position =  u_projectionViewMatrix * " + ShaderProgram.POSITION_ATTRIBUTE + ";\n" //
		                      + "}\n";
		String fragmentShader = "#ifdef GL_ES\n" //
		                        + "#define LOWP lowp\n" + "precision mediump float;\n" //
		                        + "#else\n" + "#define LOWP \n" + "#endif\n" //
		                        + "varying LOWP vec4 v_color;\n" //
		                        + "varying vec2 v_texCoords;\n" //
		                        + "uniform sampler2D u_texture;\n" //
		                        + "void main()\n"//
		                        + "{\n" //
		                        + "  gl_FragColor = v_color * texture2D(u_texture, v_texCoords);\n" //
		                        + "}";

		ShaderProgram shader = new ShaderProgram(vertexShader, fragmentShader);
		if(shader.isCompiled() == false) throw new IllegalArgumentException("couldn't compile shader: " + shader.getLog());
		return shader;
	}

	/** Sets up the SpriteBatch for drawing. This will disable depth buffer writting. It enables blending and texturing. If you have
	 * more texture units enabled than the first one you have to disable them before calling this. Uses a screen coordinate system
	 * by default where everything is given in pixels. You can specify your own projection and modelview matrices via
	 * {@link #setProjectionMatrix(Matrix4)} and {@link #setTransformMatrix(Matrix4)}. */
	public void begin()
	{
		if(m_drawing) throw new IllegalStateException("you have to call SpriteBatch.end() first");
		renderCalls = 0;

		Gdx.gl.glDepthMask(false);
		if(Gdx.graphics.isGL20Available())
		{
			if(m_customShader != null)
				m_customShader.begin();
			else
				m_shader.begin();
		}
		else
		{
			Gdx.gl.glEnable(GL10.GL_TEXTURE_2D);
		}
		setupMatrices();

		m_idx = 0;
		m_lastTexture = null;
		m_drawing = true;
	}

	/** Finishes off rendering. Enables depth writes, disables blending and texturing. Must always be called after a call to
	 * {@link #begin()} */
	public void end()
	{
		if(!m_drawing) throw new IllegalStateException("SpriteBatch.begin must be called before end.");
		if(m_idx > 0) renderMesh();
		m_lastTexture = null;
		m_idx = 0;
		m_drawing = false;

		GLCommon gl = Gdx.gl;
		gl.glDepthMask(true);
		if(isBlendingEnabled()) gl.glDisable(GL10.GL_BLEND);

		if(Gdx.graphics.isGL20Available())
		{
			if(m_customShader != null)
				m_customShader.end();
			else
				m_shader.end();
		}
		else
		{
			gl.glDisable(GL10.GL_TEXTURE_2D);
		}
	}

	/** Sets the color used to tint images when they are added to the SpriteBatch. Default is {@link Color#WHITE}. */
	public void setColor(Color tint)
	{
		m_color = tint.toFloatBits();
	}

	/** @see #setColor(Color) */
	public void setColor(float r, float g, float b, float a)
	{
		int intBits = (int)(255 * a) << 24 | (int)(255 * b) << 16 | (int)(255 * g) << 8 | (int)(255 * r);
		m_color = NumberUtils.intToFloatColor(intBits);
	}

	/** @see #setColor(Color)
	 * @see Color#toFloatBits() */
	public void setColor(float color)
	{
		m_color = color;
	}

	/** @return the rendering color of this SpriteBatch. Manipulating the returned instance has no effect. */
	public Color& getColor()
	{
		int intBits = NumberUtils.floatToIntColor(m_color);
		Color& color = m_tempColor;
		color.r = (intBits & 0xff) / 255f;
		color.g = ((intBits >>> 8) & 0xff) / 255f;
		color.b = ((intBits >>> 16) & 0xff) / 255f;
		color.a = ((intBits >>> 24) & 0xff) / 255f;
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
	public void draw(Texture texture, float x, float y, float originX, float originY, float width, float height, float scaleX,
	                 float scaleY, float rotation, int srcX, int srcY, int srcWidth, int srcHeight, bool flipX, bool flipY)
	{
		if(!m_drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

		if(texture != m_lastTexture)
		{
			renderMesh();
			m_lastTexture = texture;
			m_invTexWidth = 1.0f / texture.getWidth();
			m_invTexHeight = 1.0f / texture.getHeight();
		}
		else if(m_idx == m_vertices.length) renderMesh();

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
			float cos = MathUtils.cosDeg(rotation);
			float sin = MathUtils.sinDeg(rotation);

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
	public void draw(Texture texture, float x, float y, float width, float height, int srcX, int srcY, int srcWidth,
	                 int srcHeight, bool flipX, bool flipY)
	{
		if(!m_drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

		if(texture != m_lastTexture)
		{
			renderMesh();
			m_lastTexture = texture;
			m_invTexWidth = 1.0f / texture.getWidth();
			m_invTexHeight = 1.0f / texture.getHeight();
		}
		else if(m_idx == m_vertices.length) renderMesh();

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
	public void draw(Texture texture, float x, float y, int srcX, int srcY, int srcWidth, int srcHeight)
	{
		if(!m_drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

		if(texture != m_lastTexture)
		{
			renderMesh();
			m_lastTexture = texture;
			m_invTexWidth = 1.0f / texture.getWidth();
			m_invTexHeight = 1.0f / texture.getHeight();
		}
		else if(m_idx == m_vertices.length) renderMesh();

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
	public void draw(Texture texture, float x, float y, float width, float height, float u, float v, float u2, float v2)
	{
		if(!m_drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

		if(texture != m_lastTexture)
		{
			renderMesh();
			m_lastTexture = texture;
			m_invTexWidth = 1.0f / texture.getWidth();
			m_invTexHeight = 1.0f / texture.getHeight();
		}
		else if(m_idx == m_vertices.length) renderMesh();

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
	public void draw(Texture texture, float x, float y)
	{
		if(!m_drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

		if(texture != m_lastTexture)
		{
			renderMesh();
			m_lastTexture = texture;
			m_invTexWidth = 1.0f / texture.getWidth();
			m_invTexHeight = 1.0f / texture.getHeight();
		}
		else if(m_idx == m_vertices.length) renderMesh();

		float fx2 = x + texture.getWidth();
		float fy2 = y + texture.getHeight();

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
	public void draw(Texture texture, float x, float y, float width, float height)
	{
		if(!m_drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

		if(texture != m_lastTexture)
		{
			renderMesh();
			m_lastTexture = texture;
			m_invTexWidth = 1f / texture.getWidth();
			m_invTexHeight = 1f / texture.getHeight();
		}
		else if(m_idx == m_vertices.length)    //
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
	public void draw(Texture texture, float[] spriteVertices, int offset, int length)
	{
		if(!m_drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

		if(texture != m_lastTexture)
		{
			renderMesh();
			m_lastTexture = texture;
			m_invTexWidth = 1.0f / texture.getWidth();
			m_invTexHeight = 1.0f / texture.getHeight();
		}

		int remainingVertices = m_vertices.length - m_idx;
		if(remainingVertices == 0)
		{
			renderMesh();
			remainingVertices = m_vertices.length;
		}
		int vertexCount = Math.min(remainingVertices, length - offset);
		System.arraycopy(spriteVertices, offset, m_vertices, m_idx, vertexCount);
		offset += vertexCount;
		m_idx += vertexCount;

		while(offset < length)
		{
			renderMesh();
			vertexCount = Math.min(m_vertices.length, length - offset);
			System.arraycopy(spriteVertices, offset, m_vertices, 0, vertexCount);
			offset += vertexCount;
			m_idx += vertexCount;
		}
	}

	/** Draws a rectangle with the bottom left corner at x,y having the width and height of the region. */
	public void draw(TextureRegion region, float x, float y)
	{
		draw(region, x, y, Math.abs(region.getRegionWidth()), Math.abs(region.getRegionHeight()));
	}

	/** Draws a rectangle with the bottom left corner at x,y and stretching the region to cover the given width and height. */
	public void draw(TextureRegion region, float x, float y, float width, float height)
	{
		if(!m_drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

		Texture texture = region.texture;
		if(texture != m_lastTexture)
		{
			renderMesh();
			m_lastTexture = texture;
			m_invTexWidth = 1f / texture.getWidth();
			m_invTexHeight = 1f / texture.getHeight();
		}
		else if(m_idx == m_vertices.length)    //
			renderMesh();

		float fx2 = x + width;
		float fy2 = y + height;
		float u = region.u;
		float v = region.v2;
		float u2 = region.u2;
		float v2 = region.v;

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
	public void draw(TextureRegion region, float x, float y, float originX, float originY, float width, float height,
	                 float scaleX, float scaleY, float rotation)
	{
		if(!m_drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

		Texture texture = region.texture;
		if(texture != m_lastTexture)
		{
			renderMesh();
			m_lastTexture = texture;
			m_invTexWidth = 1f / texture.getWidth();
			m_invTexHeight = 1f / texture.getHeight();
		}
		else if(m_idx == m_vertices.length)    //
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
			float cos = MathUtils.cosDeg(rotation);
			float sin = MathUtils.sinDeg(rotation);

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

		float u = region.u;
		float v = region.v2;
		float u2 = region.u2;
		float v2 = region.v;

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
	public void draw(TextureRegion region, float x, float y, float originX, float originY, float width, float height,
	                 float scaleX, float scaleY, float rotation, bool clockwise)
	{
		if(!m_drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

		Texture texture = region.texture;
		if(texture != m_lastTexture)
		{
			renderMesh();
			m_lastTexture = texture;
			m_invTexWidth = 1f / texture.getWidth();
			m_invTexHeight = 1f / texture.getHeight();
		}
		else if(m_idx == m_vertices.length)    //
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
			float cos = MathUtils.cosDeg(rotation);
			float sin = MathUtils.sinDeg(rotation);

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
			u1 = region.u2;
			v1 = region.v2;
			u2 = region.u;
			v2 = region.v2;
			u3 = region.u;
			v3 = region.v;
			u4 = region.u2;
			v4 = region.v;
		}
		else
		{
			u1 = region.u;
			v1 = region.v;
			u2 = region.u2;
			v2 = region.v;
			u3 = region.u2;
			v3 = region.v2;
			u4 = region.u;
			v4 = region.v2;
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
	public void flush()
	{
		renderMesh();
	}

	private void renderMesh()
	{
		if(m_idx == 0) return;

		renderCalls++;
		totalRenderCalls++;
		int spritesInBatch = m_idx / 20;
		if(spritesInBatch > maxSpritesInBatch) maxSpritesInBatch = spritesInBatch;

		m_lastTexture.bind();
		m_mesh.setVertices(m_vertices, 0, m_idx);

		if(m_blendingDisabled)
		{
			Gdx.gl.glDisable(GL20.GL_BLEND);
		}
		else
		{
			Gdx.gl.glEnable(GL20.GL_BLEND);
			Gdx.gl.glBlendFunc(m_blendSrcFunc, m_blendDstFunc);
		}

		if(Gdx.graphics.isGL20Available())
		{
			if(m_customShader != null)
				m_mesh.render(m_customShader, GL10.GL_TRIANGLES, 0, spritesInBatch * 6);
			else
				m_mesh.render(m_shader, GL10.GL_TRIANGLES, 0, spritesInBatch * 6);
		}
		else
		{
			m_mesh.render(GL10.GL_TRIANGLES, 0, spritesInBatch * 6);
		}

		m_idx = 0;
		m_currBufferIdx++;
		if(m_currBufferIdx == buffers.length) m_currBufferIdx = 0;
		m_mesh = buffers[m_currBufferIdx];
	}

	/** Disables blending for drawing sprites. Does not disable blending for text rendering */
	public void disableBlending()
	{
		renderMesh();
		m_blendingDisabled = true;
	}

	/** Enables blending for sprites */
	public void enableBlending()
	{
		renderMesh();
		m_blendingDisabled = false;
	}

	/** Sets the blending function to be used when rendering sprites.
	 *
	 * @param srcFunc the source function, e.g. GL11::GDX_GL_SRC_ALPHA
	 * @param dstFunc the destination function, e.g. GL11::GDX_GL_ONE_MINUS_SRC_ALPHA */
	public void setBlendFunction(int srcFunc, int dstFunc)
	{
		renderMesh();
		m_blendSrcFunc = srcFunc;
		m_blendDstFunc = dstFunc;
	}

	/** Disposes all resources associated with this SpriteBatch */
	public void dispose()
	{
		for(int i = 0; i < buffers.length; i++)
			buffers[i].dispose();
		if(m_shader != null) m_shader.dispose();
	}

	/** Returns the current projection matrix. Changing this will result in undefined behaviour.
	 *
	 * @return the currently set projection matrix */
	public Matrix4 getProjectionMatrix()
	{
		return m_projectionMatrix;
	}

	/** Returns the current transform matrix. Changing this will result in undefined behaviour.
	 *
	 * @return the currently set transform matrix */
	public Matrix4 getTransformMatrix()
	{
		return m_transformMatrix;
	}

	/** Sets the projection matrix to be used by this SpriteBatch. If this is called inside a {@link #begin()}/{@link #end()} block.
	 * the current batch is flushed to the gpu.
	 *
	 * @param projection the projection matrix */
	public void setProjectionMatrix(Matrix4 projection)
	{
		if(m_drawing) flush();
		m_projectionMatrix.set(projection);
		if(m_drawing) setupMatrices();
	}

	/** Sets the transform matrix to be used by this SpriteBatch. If this is called inside a {@link #begin()}/{@link #end()} block.
	 * the current batch is flushed to the gpu.
	 *
	 * @param transform the transform matrix */
	public void setTransformMatrix(Matrix4 transform)
	{
		if(m_drawing) flush();
		m_transformMatrix.set(transform);
		if(m_drawing) setupMatrices();
	}

	private void setupMatrices()
	{
		if(!Gdx.graphics.isGL20Available())
		{
			GL10 gl = Gdx.gl10;
			gl.glMatrixMode(GL10.GL_PROJECTION);
			gl.glLoadMatrixf(m_projectionMatrix.val, 0);
			gl.glMatrixMode(GL10.GL_MODELVIEW);
			gl.glLoadMatrixf(m_transformMatrix.val, 0);
		}
		else
		{
			m_combinedMatrix.set(m_projectionMatrix).mul(m_transformMatrix);
			if(m_customShader != null)
			{
				m_customShader.setUniformMatrix("u_proj", m_projectionMatrix);
				m_customShader.setUniformMatrix("u_trans", m_transformMatrix);
				m_customShader.setUniformMatrix("u_projTrans", m_combinedMatrix);
				m_customShader.setUniformi("u_texture", 0);
			}
			else
			{
				m_shader.setUniformMatrix("u_projectionViewMatrix", m_combinedMatrix);
				m_shader.setUniformi("u_texture", 0);
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
	 * Call this method with a null argument to use the default shader.
	 *
	 * @param shader the {@link ShaderProgram} or null to use the default shader. */
	public void setShader(ShaderProgram shader)
	{
		m_customShader = shader;
	}

	/** @return whether blending for sprites is enabled */
	public bool isBlendingEnabled()
	{
		return !m_blendingDisabled;
	}

	static public int X1 = 0;
	static public int Y1 = 1;
	static public int C1 = 2;
	static public int U1 = 3;
	static public int V1 = 4;
	static public int X2 = 5;
	static public int Y2 = 6;
	static public int C2 = 7;
	static public int U2 = 8;
	static public int V2 = 9;
	static public int X3 = 10;
	static public int Y3 = 11;
	static public int C3 = 12;
	static public int U3 = 13;
	static public int V3 = 14;
	static public int X4 = 15;
	static public int Y4 = 16;
	static public int C4 = 17;
	static public int U4 = 18;
	static public int V4 = 19;
}
