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

/** A color class, holding the r, g, b and alpha component as floats in the range [0,1]. All methods perform clamping on the
 * internal values after execution.
 */
class Color
{
public:
	static const Color CLEAR;
	static const Color WHITE;
	static const Color BLACK;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color LIGHT_GRAY;
	static const Color GRAY;
	static const Color DARK_GRAY;
	static const Color PINK;
	static const Color ORANGE;
	static const Color YELLOW;
	static const Color MAGENTA;
	static const Color CYAN;

	/** the red, green, blue and alpha components **/
	float r, g, b, a;

	/** Constructs a new Color with all components set to 0. */
	Color ();

	/** Constructor, sets the components of the color
	 *
	 * @param r the red component
	 * @param g the green component
	 * @param b the blue component
	 * @param a the alpha component */
	Color (float r, float g, float b, float a);

	/** Constructs a new color using the given color
	 *
	 * @param color the color */
	Color(const Color& color);

	/** Sets this color to the given color.
	 *
	 * @param color the Color */
	Color& set (const Color& color);

	/** Multiplies the this color and the given color
	 *
	 * @param color the color
	 * @return this color. */
	Color& mul(const Color& color);

	/** Multiplies all components of this Color with the given value.
	 *
	 * @param value the value
	 * @return this color */
	Color& mul(float value);

	/** Adds the given color to this color.
	 *
	 * @param color the color
	 * @return this color */
	Color& add (const Color& color);

	/** Subtracts the given color from this color
	 *
	 * @param color the color
	 * @return this color */
	Color& sub (const Color& color);

	void clamp ();

	void set (float r, float g, float b, float a);

	std::wstring toString ();

	/** Packs the four color components which should be in the range 0-255 into a 32-bit integer and then converts it to a float.
	 * Note that no range checking is performed for higher performance.
	 *
	 * @param r the red component, 0 - 255
	 * @param g the green component, 0 - 255
	 * @param b the blue component, 0 - 255
	 * @param a the alpha component, 0 - 255
	 * @return the packed color as a float */
	static float toFloatBits (int r, int g, int b, int a);

	/** Packs the four color components which should be in the range 0-255 into a 32-bit. Note that no range checking is performed
	 * for higher performance.
	 *
	 * @param r the red component, 0 - 255
	 * @param g the green component, 0 - 255
	 * @param b the blue component, 0 - 255
	 * @param a the alpha component, 0 - 255
	 * @return the packed color as a 32-bit int */
	static int toIntBits (int r, int g, int b, int a);

	/** Packs the 4 components of this color into a 32-bit int and returns it as a float.
	 *
	 * @return the packed color as a 32-bit float */
	float toFloatBits ();

	/** Packs the 4 components of this color into a 32-bit int.
	 *
	 * @return the packed color as a 32-bit int. */
	int toIntBits ();

	/** Packs the 4 components of this color into a 32-bit int and returns it as a float.
	 *
	 * @return the packed color as a 32-bit float */
	static float toFloatBits (float r, float g, float b, float a);

	static int alpha (float alpha);

	static int luminanceAlpha (float luminance, float alpha);

	static int rgb565 (float r, float g, float b);

	static int rgba4444 (float r, float g, float b, float a);

	static int rgb888 (float r, float g, float b);

	static int rgba8888 (float r, float g, float b, float a);

	static int rgb565 (const Color& color);

	static int rgba4444 (const Color& color);

	static int rgb888 (const Color& color);

	static int rgba8888 (const Color& color);

	/** Sets the Color components using the specified integer value in the format RGB565. This is inverse to the rgb565(r, g, b)
	 * method.
	 *
	 * @param color The Color to be modified.
	 * @param value An integer color value in RGB565 format. */
	static void rgb565ToColor (Color& color, int value);

	/** Sets the Color components using the specified integer value in the format RGBA4444. This is inverse to the rgba4444(r, g, b,
	 * a) method.
	 *
	 * @param color The Color to be modified.
	 * @param value An integer color value in RGBA4444 format. */
	static void rgba4444ToColor (Color& color, int value);

	/** Sets the Color components using the specified integer value in the format RGB888. This is inverse to the rgb888(r, g, b)
	 * method.
	 *
	 * @param color The Color to be modified.
	 * @param value An integer color value in RGB888 format. */
	static void rgb888ToColor (Color& color, int value);

	/** Sets the Color components using the specified integer value in the format RGBA8888. This is inverse to the rgb8888(r, g, b,
	 * a) method.
	 *
	 * @param color The Color to be modified.
	 * @param value An integer color value in RGBA8888 format. */
	static void rgba8888ToColor (Color& color, int value);
};
