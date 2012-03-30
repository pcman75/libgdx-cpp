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
#include "Mesh.h"
#include "Texture.h"

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
	int m_numBuffers;

	Texture* m_lastTexture;
	float m_invTexWidth;
	float m_invTexHeight;

	int m_idx;
	int m_currBufferIdx;
	float* m_vertices;
	int m_verticesSize;

	Matrix4 m_transformMatrix;
	Matrix4 m_projectionMatrix;
	Matrix4 m_combinedMatrix;

	bool m_drawing;

	bool m_blendingDisabled;
	int m_blendSrcFunc;
	int m_blendDstFunc;

	ShaderProgram* m_shader;
	bool m_shaderProvided;
	ShaderProgram* m_customShader;

	float m_color;
	Color m_tempColor;

private:
	void setup();
	void init(int size);
	void init(int size, ShaderProgram* defaultShader);
	void init(int size, int buffers);
	void init(int size, int buffers, ShaderProgram* defaultShader);

public:
	virtual ~SpriteBatch();

	/** Constructs a new SpriteBatch. Sets the projection matrix to an orthographic projection with y-axis point upwards, x-axis
	 * point to the right and the origin being in the bottom left corner of the screen. The projection will be pixel perfect with
	 * respect to the screen resolution. */
	SpriteBatch();

	/** Constructs a SpriteBatch with the specified size and (if GL2) the default shader. See
	 * {@link #SpriteBatch(int, ShaderProgram)}. */
	SpriteBatch(int size);

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
	SpriteBatch(int size, ShaderProgram* defaultShader);

	/** Constructs a SpriteBatch with the specified size and number of buffers and (if GL2) the default shader. See
	 * {@link #SpriteBatch(int, int, ShaderProgram)}. */
	SpriteBatch(int size, int buffers);

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
	SpriteBatch(int size, int buffers, ShaderProgram* defaultShader);

	/** Returns a new instance of the default shader used by SpriteBatch for GL2 when no shader is specified. 
	caller must delete it*/
	static ShaderProgram* createDefaultShader();

	/** Sets up the SpriteBatch for drawing. This will disable depth buffer writting. It enables blending and texturing. If you have
	 * more texture units enabled than the first one you have to disable them before calling this. Uses a screen coordinate system
	 * by default where everything is given in pixels. You can specify your own projection and modelview matrices via
	 * {@link #setProjectionMatrix(Matrix4)} and {@link #setTransformMatrix(Matrix4)}. */
	void begin();

	/** Finishes off rendering. Enables depth writes, disables blending and texturing. Must always be called after a call to
	 * {@link #begin()} */
	void end();

	/** Sets the color used to tint images when they are added to the SpriteBatch. Default is {@link Color#WHITE}. */
	void setColor(const Color& tint);

	/** @see #setColor(Color) */
	void setColor(float r, float g, float b, float a);

	/** @see #setColor(Color)
	 * @see Color#toFloatBits() */
	void setColor(float color);

	/** @return the rendering color of this SpriteBatch. Manipulating the returned instance has no effect. */
	Color& getColor();

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
	void draw(Texture* texture, float x, float y, float originX, float originY, float width, float height, float scaleX,
	                 float scaleY, float rotation, int srcX, int srcY, int srcWidth, int srcHeight, bool flipX, bool flipY);

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
	void draw(Texture* texture, float x, float y, float width, float height, int srcX, int srcY, int srcWidth,
	                 int srcHeight, bool flipX, bool flipY);

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
	void draw(Texture* texture, float x, float y, int srcX, int srcY, int srcWidth, int srcHeight);

	/** Draws a rectangle with the bottom left corner at x,y having the given width and height in pixels. The portion of the
	 * {@link Texture} given by u, v and u2, v2 are used. These coordinates and sizes are given in texture size percentage. The
	 * rectangle will have the given tint {@link Color}.
	 *
	 * @param texture the Texture
	 * @param x the x-coordinate in screen space
	 * @param y the y-coordinate in screen space
	 * @param width the width in pixels
	 * @param height the height in pixels */
	void draw(Texture* texture, float x, float y, float width, float height, float u, float v, float u2, float v2);

	/** Draws a rectangle with the bottom left corner at x,y having the width and height of the texture.
	 * @param texture the Texture
	 * @param x the x-coordinate in screen space
	 * @param y the y-coordinate in screen space */
	void draw(Texture* texture, float x, float y);

	/** Draws a rectangle with the bottom left corner at x,y and stretching the region to cover the given width and height. */
	void draw(Texture* texture, float x, float y, float width, float height);

	/** Draws a rectangle using the given m_vertices. There must be 4 m_vertices, each made up of 5 elements in this order: x, y, color,
	 * u, v. */
	void draw(Texture* texture, float* spriteVertices, int offset, int length);

	/** Draws a rectangle with the bottom left corner at x,y having the width and height of the region. */
	void draw(TextureRegion* region, float x, float y);

	/** Draws a rectangle with the bottom left corner at x,y and stretching the region to cover the given width and height. */
	void draw(TextureRegion* region, float x, float y, float width, float height);

	/** Draws a rectangle with the bottom left corner at x,y and stretching the region to cover the given width and height. The
	 * rectangle is offset by originX, originY relative to the origin. Scale specifies the scaling factor by which the rectangle
	 * should be scaled around originX, originY. Rotation specifies the angle of counter clockwise rotation of the rectangle around
	 * originX, originY. */
	void draw(TextureRegion* region, float x, float y, float originX, float originY, float width, float height,
	                 float scaleX, float scaleY, float rotation);

	/** Draws a rectangle with the bottom left corner at x,y and stretching the region to cover the given width and height. The
	 * rectangle is offset by originX, originY relative to the origin. Scale specifies the scaling factor by which the rectangle
	 * should be scaled around originX, originY. Rotation specifies the angle of counter clockwise rotation of the rectangle around
	 * originX, originY. */
	void draw(TextureRegion* region, float x, float y, float originX, float originY, float width, float height,
	                 float scaleX, float scaleY, float rotation, bool clockwise);

	/** Causes any pending sprites to be rendered, without ending the SpriteBatch. */
	void flush();

	void renderMesh();

	/** Disables blending for drawing sprites. Does not disable blending for text rendering */
	void disableBlending();

	/** Enables blending for sprites */
	void enableBlending();

	/** Sets the blending function to be used when rendering sprites.
	 *
	 * @param srcFunc the source function, e.g. GL_SRC_ALPHA
	 * @param dstFunc the destination function, e.g. GL_ONE_MINUS_SRC_ALPHA */
	void setBlendFunction(int srcFunc, int dstFunc);

	/** Disposes all resources associated with this SpriteBatch */
	void dispose();

	/** Returns the current projection matrix. Changing this will result in undefined behaviour.
	 *
	 * @return the currently set projection matrix */
	Matrix4& getProjectionMatrix();

	/** Returns the current transform matrix. Changing this will result in undefined behaviour.
	 *
	 * @return the currently set transform matrix */
	Matrix4& getTransformMatrix();

	/** Sets the projection matrix to be used by this SpriteBatch. If this is called inside a {@link #begin()}/{@link #end()} block.
	 * the current batch is flushed to the gpu.
	 *
	 * @param projection the projection matrix */
	void setProjectionMatrix(const Matrix4& projection);

	/** Sets the transform matrix to be used by this SpriteBatch. If this is called inside a {@link #begin()}/{@link #end()} block.
	 * the current batch is flushed to the gpu.
	 *
	 * @param transform the transform matrix */
	void setTransformMatrix(const Matrix4& transform);
private:
	void setupMatrices();
public:
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
	void setShader(ShaderProgram* shader);

	/** @return whether blending for sprites is enabled */
	bool isBlendingEnabled();

public:
	static int X1;
	static int Y1;
	static int C1;
	static int U1;
	static int V1;
	static int X2;
	static int Y2;
	static int C2;
	static int U2;
	static int V2;
	static int X3;
	static int Y3;
	static int C3;
	static int U3;
	static int V3;
	static int X4;
	static int Y4;
	static int C4;
	static int U4;
	static int V4;
};
