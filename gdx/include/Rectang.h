/*******************************************************************************
 * Copyright 2011 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the
 * License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS"
 * BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 ******************************************************************************/

#pragma once
#include "GdxDefines.h"

/** Encapsulates a 2D rectangle defined by it's bottom corner point and its extends in x (width) and y (height)*/
class GdxDllImportExport Rectang
{
public:
	float x, y;
	float width, height;

	/** Constructs a new rectangle with all values set to zero */
	Rectang();

	/** Constructs a new rectangle with the given corner point in the bottom left and dimensions.
	 * @param x The corner point x-coordinate
	 * @param y The corner point y-coordinate
	 * @param width The width
	 * @param height The height */
	Rectang(float x, float y, float width, float height);

	/** Constructs a rectangle based on the given rectangle
	 * @param rect The rectangle */
	Rectang(const Rectang& rect);

	/** @return the x-coordinate of the bottom left corner */
	float getX ();

	/** Sets the x-coordinate of the bottom left corner
	 * @param x The x-coordinate */
	void setX (float x);

	/** @return the y-coordinate of the bottom left corner */
	float getY ();

	/** Sets the y-coordinate of the bottom left corner
	 * @param y The y-coordinate */
	void setY (float y);

	/** @return the width */
	float getWidth ();

	/** Sets the width of this rectangle
	 * @param width The width */
	void setWidth (float width);

	/** @return the height */
	float getHeight ();

	/** Sets the height of this rectangle
	 * @param height The height */
	void setHeight (float height);

	/** @param rectangle the other {@link Rectang}.
	 * @return whether the other rectangle is contained in this rectangle. */
	bool contains(const Rectang& rectangle);

	/** @param rectangle the other {@link Rectang}
	 * @return whether this rectangle overlaps the other rectangle. */
	bool overlaps(const Rectang& rectangle);

	void set(float x, float y, float width, float height);

	/** @param x point x coordinate
	 * @param y point y coordinate
	 * @return whether the point is contained in the rectangle */
	bool contains (float x, float y);

	/** Sets the values of the given rectangle to this rectangle.
	 * @param rect the other rectangle */
	void set(const Rectang& rect);

	/** Merges this rectangle with the other rectangle.
	 * @param rect the other rectangle */
	void merge(const Rectang& rect);

	std::string toString ();
};
