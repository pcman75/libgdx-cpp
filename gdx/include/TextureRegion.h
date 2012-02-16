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
#include "GdxDefines.h"
#include "Texture.h"

/** Defines a rectangular area of a texture. The coordinate system used has its origin in the upper left corner with the x-axis
 * pointing to the right and the y axis pointing downwards.
 */

class GdxDllImportExport TextureRegion
{
protected:
	Texture* m_texture;
	float m_u, m_v;
	float m_u2, m_v2;

public:

	/** Constructs a region with no texture and no coordinates defined. */
	TextureRegion();

	/** Constructs a region the size of the specified texture. */
	TextureRegion(Texture* texture);

	/** @param width The width of the texture region. May be negative to flip the sprite when drawn.
	 * @param height The height of the texture region. May be negative to flip the sprite when drawn. */
	TextureRegion(Texture* texture, int width, int height);

	/** @param width The width of the texture region. May be negative to flip the sprite when drawn.
	 * @param height The height of the texture region. May be negative to flip the sprite when drawn. */
	TextureRegion(Texture* texture, int x, int y, int width, int height);

	TextureRegion(Texture* texture, float u, float v, float u2, float v2);

	/** Constructs a region with the same texture and coordinates of the specified region. */
	TextureRegion(TextureRegion* region);

	/** Constructs a region with the same texture as the specified region and sets the coordinates relative to the specified region.
	 * @param width The width of the texture region. May be negative to flip the sprite when drawn.
	 * @param height The height of the texture region. May be negative to flip the sprite when drawn. */
	TextureRegion(TextureRegion* region, int x, int y, int width, int height);

	/** Sets the texture and sets the coordinates to the size of the specified texture. */
	void setRegion(Texture* texture);

	/** @param width The width of the texture region. May be negative to flip the sprite when drawn.
	 * @param height The height of the texture region. May be negative to flip the sprite when drawn. */
	void setRegion(int x, int y, int width, int height);

	void setRegion(float u, float v, float u2, float v2);

	/** Sets the texture and coordinates to the specified region. */
	void setRegion(TextureRegion* region);

	/** Sets the texture to that of the specified region and sets the coordinates relative to the specified region. */
	void setRegion(TextureRegion* region, int x, int y, int width, int height);

	Texture* getTexture();

	void setTexture(Texture* texture);

	float getU();

	void setU(float u);

	float getV();

	void setV(float v);

	float getU2();

	void setU2(float u2);

	float getV2();

	void setV2(float v2);

	int getRegionX();

	void setRegionX(int x);

	int getRegionY();

	void setRegionY(int y);

	/** Returns the region's width. May be negative if the texture region is flipped horizontally. */
	int getRegionWidth();

	void setRegionWidth(int width);

	/** Returns the region's height. May be negative if the texture region is flipped horizontally. */
	int getRegionHeight();

	void setRegionHeight(int height);

	void flip(bool x, bool y);

	/** Offsets the region relative to the current region. Generally the region's size should be the entire size of the texture in
	 * the direction(s) it is scrolled.
	 * @param xAmount The percentage to offset horizontally.
	 * @param yAmount The percentage to offset vertically. This is done in texture space, so up is negative. */
	void scroll(float xAmount, float yAmount);

	/** Helper function to create tiles out of this TextureRegion starting from the top left corner going to the left and ending at
	 * the bottom right corner. Only complete tiles will be returned so if the region's width or height are not a multiple of the
	 * tile width and height not all of the region will be used.
	 *
	 * @param tileWidth a tile's width in pixels
	 * @param tileHeight a tile's height in pixels
	 * @return a 2D array of TextureRegions indexed by [row][column]. */
	TextureRegion** split(int tileWidth, int tileHeight);

	/** Helper function to create tiles out of the given {@link Texture} starting from the top left corner going to the left and
	 * ending at the bottom right corner. Only complete tiles will be returned so if the texture's width or height are not a
	 * multiple of the tile width and height not all of the texture will be used.
	 *
	 * @param texture the Texture
	 * @param tileWidth a tile's width in pixels
	 * @param tileHeight a tile's height in pixels
	 * @return a 2D array of TextureRegions indexed by [row][column]. */
	static TextureRegion** split(Texture* texture, int tileWidth, int tileHeight);

private:
	inline float round(float value);
};
