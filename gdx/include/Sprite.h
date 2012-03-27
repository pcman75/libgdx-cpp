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

/** Holds the geometry, color, and texture information for drawing 2D sprites using {@link SpriteBatch}. A Sprite has a position
 * and a size given as width and height. The position is relative to the origin of the coordinate system specified via
 * {@link SpriteBatch#begin()} and the respective matrices. A Sprite is always rectangular and its position (x, y) are located in
 * the bottom left corner of that rectangle. A Sprite also has an origin around which rotations and scaling are performed (that
 * is, the origin is not modified by rotation and scaling). The origin is given relative to the bottom left corner of the Sprite,
 * its position.
 */
#pragma once



#include "TextureRegion.h"
#include "Rectang.h"
class SpriteBatch;

class Sprite: public TextureRegion
{
public:
	static const int VERTEX_SIZE = 2 + 1 + 2;
	static const int SPRITE_SIZE = 4 * VERTEX_SIZE;

	static const int X1;
	static const int Y1;
	static const int C1;
	static const int U1;
	static const int V1;
	static const int X2;
	static const int Y2;
	static const int C2;
	static const int U2;
	static const int V2;
	static const int X3;
	static const int Y3;
	static const int C3;
	static const int U3;
	static const int V3;
	static const int X4;
	static const int Y4;
	static const int C4;
	static const int U4;
	static const int V4;

private:
	float m_vertices[20];
	Color m_color;
	float m_x, m_y;
	float m_width, m_height;
	float m_originX, m_originY;
	float m_rotation;
	float m_scaleX, m_scaleY;
	bool m_dirty;
	Rectang m_bounds;

private:
	void init();

	void init(Texture* texture, int srcX, int srcY, int srcWidth, int srcHeight);

public:
	/** Creates an uninitialized sprite. The sprite will need a texture, texture region, bounds, and color set before it can be
	 * drawn. */
	Sprite();

	/** Creates a sprite with width, height, and texture region equal to the size of the texture. */
	Sprite(Texture* texture);

	/** Creates a sprite with width, height, and texture region equal to the specified size. The texture region's upper left corner
	 * will be 0,0. * @param srcWidth The width of the texture region. May be negative to flip the sprite when drawn.
	 * @param srcHeight The height of the texture region. May be negative to flip the sprite when drawn. */
	Sprite(Texture* texture, int srcWidth, int srcHeight);

	/** Creates a sprite with width, height, and texture region equal to the specified size. * @param srcWidth The width of the
	 * texture region. May be negative to flip the sprite when drawn.
	 * @param srcHeight The height of the texture region. May be negative to flip the sprite when drawn. */
	Sprite(Texture* texture, int srcX, int srcY, int srcWidth, int srcHeight);

	// Note the region is copied.
	Sprite(TextureRegion* region);

	/** Creates a sprite with width, height, and texture region equal to the specified size, relative to specified sprite's texture
	 * region.
	 * @param srcWidth The width of the texture region. May be negative to flip the sprite when drawn.
	 * @param srcHeight The height of the texture region. May be negative to flip the sprite when drawn. */
	Sprite(TextureRegion* region, int srcX, int srcY, int srcWidth, int srcHeight);

	/** Creates a sprite that is a copy in every way of the specified sprite. */
	Sprite(const Sprite& sprite);

	void set(const Sprite& sprite);

	/** Sets the position and size of the sprite when drawn, before scaling and rotation are applied. If origin, rotation, or scale
	 * are changed, it is slightly more efficient to set the bounds after those operations. */
	void setBounds(float x, float y, float width, float height);

	/** Sets the size of the sprite when drawn, before scaling and rotation are applied. If origin, rotation, or scale are changed,
	 * it is slightly more efficient to set the size after those operations. If both position and size are to be changed, it is
	 * better to use {@link #setBounds(float, float, float, float)}. */
	void setSize(float width, float height);

	/** Sets the position where the sprite will be drawn. If origin, rotation, or scale are changed, it is slightly more efficient
	 * to set the position after those operations. If both position and size are to be changed, it is better to use
	 * {@link #setBounds(float, float, float, float)}. */
	void setPosition(float x, float y);

	/** Sets the x position where the sprite will be drawn. If origin, rotation, or scale are changed, it is slightly more efficient
	 * to set the position after those operations. If both position and size are to be changed, it is better to use
	 * {@link #setBounds(float, float, float, float)}. */
	void setX(float x);

	/** Sets the y position where the sprite will be drawn. If origin, rotation, or scale are changed, it is slightly more efficient
	 * to set the position after those operations. If both position and size are to be changed, it is better to use
	 * {@link #setBounds(float, float, float, float)}. */
	void setY(float y);

	/** Sets the x position relative to the current position where the sprite will be drawn. If origin, rotation, or scale are
	 * changed, it is slightly more efficient to translate after those operations. */
	void translateX(float xAmount);

	/** Sets the y position relative to the current position where the sprite will be drawn. If origin, rotation, or scale are
	 * changed, it is slightly more efficient to translate after those operations. */
	void translateY(float yAmount);

	/** Sets the position relative to the current position where the sprite will be drawn. If origin, rotation, or scale are
	 * changed, it is slightly more efficient to translate after those operations. */
	void translate(float xAmount, float yAmount);

	void setColor(Color tint);

	void setColor(float r, float g, float b, float a);

	/** Sets the origin in relation to the sprite's position for scaling and rotation. */
	void setOrigin(float originX, float originY);

	void setRotation(float degrees);

	/** Sets the sprite's rotation relative to the current rotation. */
	void rotate(float degrees);

	/** Rotates this sprite 90 degrees in-place by rotating the texture coordinates. This rotation is unaffected by
	 * {@link #setRotation(float)} and {@link #rotate(float)}. */
	void rotate90(bool clockwise);

	void setScale(float scaleXY);

	void setScale(float scaleX, float scaleY);

	/** Sets the sprite's scale relative to the current scale. */
	void scale(float amount);

	/** Returns the packed vertices, colors, and texture coordinates for this sprite. */
	float* getVertices();

	/** Returns the bounding axis aligned {@link Rectangle} that bounds this sprite. The rectangles x and y coordinates describe its
	 * bottom left corner.
	 *
	 * @return the bounding Rectangle */
	const Rectang& getBoundingRectangle();

	void draw(SpriteBatch* spriteBatch);
	void draw(SpriteBatch* spriteBatch, float alphaModulation);

	float getX();

	float getY();

	float getWidth();

	float getHeight();

	float getOriginX();

	float getOriginY();

	float getRotation();

	float getScaleX();

	float getScaleY();

	/** Returns the color of this sprite. Changing the returned color will have no affect, {@link #setColor(Color)} or
	 * {@link #setColor(float, float, float, float)} must be used. */
	Color& getColor();

	virtual void setRegion(float u, float v, float u2, float v2);
	
	virtual void setU(float u);

	virtual void setV(float v);

	virtual void setU2(float u2);

	virtual void setV2(float v2);

	virtual void flip(bool x, bool y);

	virtual void scroll(float xAmount, float yAmount);
	
};
