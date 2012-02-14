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

#include "stdafx.h"
#include "Color.h"
#include "NumberUtils.h"

const Color Color::CLEAR = Color(0, 0, 0, 0);
const Color Color::WHITE = Color(1, 1, 1, 1);
const Color Color::BLACK = Color(0, 0, 0, 1);
const Color Color::RED = Color(1, 0, 0, 1);
const Color Color::GREEN = Color(0, 1, 0, 1);
const Color Color::BLUE = Color(0, 0, 1, 1);
const Color Color::LIGHT_GRAY = Color(0.75f, 0.75f, 0.75f, 1);
const Color Color::GRAY = Color(0.5f, 0.5f, 0.5f, 1);
const Color Color::DARK_GRAY = Color(0.25f, 0.25f, 0.25f, 1);
const Color Color::PINK = Color(1, 0.68f, 0.68f, 1);
const Color Color::ORANGE = Color(1, 0.78f, 0, 1);
const Color Color::YELLOW = Color(1, 1, 0, 1);
const Color Color::MAGENTA = Color(1, 0, 1, 1);
const Color Color::CYAN = Color(0, 1, 1, 1);

/** Constructs a new Color with all components set to 0. */
Color::Color ()
{

}

/** Constructor, sets the components of the color
*
* @param r the red component
* @param g the green component
* @param b the blue component
* @param a the alpha component */
Color::Color (float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	clamp();
}

/** Constructs a new color using the given color
*
* @param color the color */
Color::Color(const Color& color)
{
	set(color);
}

/** Sets this color to the given color.
*
* @param color the Color */
Color& Color::set (const Color& color)
{
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->a = color.a;
	clamp();
	return *this;
}

/** Multiplies the this color and the given color
*
* @param color the color
* @return this color. */
Color& Color::mul(const Color& color)
{
	this->r *= color.r;
	this->g *= color.g;
	this->b *= color.b;
	this->a *= color.a;
	clamp();
	return *this;
}

/** Multiplies all components of this Color with the given value.
*
* @param value the value
* @return this color */
Color& Color::mul(float value)
{
	this->r *= value;
	this->g *= value;
	this->b *= value;
	this->a *= value;
	clamp();
	return *this;
}

/** Adds the given color to this color.
*
* @param color the color
* @return this color */
Color& Color::add (const Color& color)
{
	this->r += color.r;
	this->g += color.g;
	this->b += color.b;
	this->a += color.a;
	clamp();
	return *this;
}

/** Subtracts the given color from this color
*
* @param color the color
* @return this color */
Color& Color::sub (const Color& color)
{
	this->r -= color.r;
	this->g -= color.g;
	this->b -= color.b;
	this->a -= color.a;
	clamp();
	return *this;
}

void Color::clamp ()
{
	if (r < 0)
		r = 0;
	else if (r > 1) r = 1;

	if (g < 0)
		g = 0;
	else if (g > 1) g = 1;

	if (b < 0)
		b = 0;
	else if (b > 1) b = 1;

	if (a < 0)
		a = 0;
	else if (a > 1) a = 1;
}

void Color::set (float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

std::string Color::toString ()
{
	std::stringstream ret;
	ret << "0x" << std::hex << toIntBits();
	return ret.str();
}

/** Packs the four color components which should be in the range 0-255 into a 32-bit integer and then converts it to a float.
* Note that no range checking is performed for higher performance.
*
* @param r the red component, 0 - 255
* @param g the green component, 0 - 255
* @param b the blue component, 0 - 255
* @param a the alpha component, 0 - 255
* @return the packed color as a float */
float Color::toFloatBits (int r, int g, int b, int a)
{
	int color = (a << 24) | (b << 16) | (g << 8) | r;
	float floatColor = NumberUtils::intToFloatColor(color);
	return floatColor;
}

/** Packs the four color components which should be in the range 0-255 into a 32-bit. Note that no range checking is performed
* for higher performance.
*
* @param r the red component, 0 - 255
* @param g the green component, 0 - 255
* @param b the blue component, 0 - 255
* @param a the alpha component, 0 - 255
* @return the packed color as a 32-bit int */
int Color::toIntBits (int r, int g, int b, int a)
{
	return (a << 24) | (b << 16) | (g << 8) | r;
}

/** Packs the 4 components of this color into a 32-bit int and returns it as a float.
*
* @return the packed color as a 32-bit float */
float Color::toFloatBits () const
{
	int color = ((int)(255 * a) << 24) | ((int)(255 * b) << 16) | ((int)(255 * g) << 8) | ((int)(255 * r));
	return NumberUtils::intToFloatColor(color);
}

/** Packs the 4 components of this color into a 32-bit int.
*
* @return the packed color as a 32-bit int. */
int Color::toIntBits () const
{
	int color = ((int)(255 * a) << 24) | ((int)(255 * b) << 16) | ((int)(255 * g) << 8) | ((int)(255 * r));
	return color;
}

/** Packs the 4 components of this color into a 32-bit int and returns it as a float.
*
* @return the packed color as a 32-bit float */
float Color::toFloatBits (float r, float g, float b, float a)
{
	int color = ((int)(255 * a) << 24) | ((int)(255 * b) << 16) | ((int)(255 * g) << 8) | ((int)(255 * r));
	return NumberUtils::intToFloatColor(color);
}

int Color::alpha (float alpha)
{
	return (int)(alpha * 255.0f);
}

int Color::luminanceAlpha (float luminance, float alpha)
{
	return ((int)(luminance * 255.0f) << 8) | (int)(alpha * 255);
}

int Color::rgb565 (float r, float g, float b)
{
	return ((int)(r * 31) << 11) | ((int)(g * 63) << 5) | (int)(b * 31);
}

int Color::rgba4444 (float r, float g, float b, float a)
{
	return ((int)(r * 15) << 12) | ((int)(g * 15) << 8) | ((int)(b * 15) << 4) | (int)(a * 15);
}

int Color::rgb888 (float r, float g, float b)
{
	return ((int)(r * 255) << 16) | ((int)(g * 255) << 8) | (int)(b * 255);
}

int Color::rgba8888 (float r, float g, float b, float a)
{
	return ((int)(r * 255) << 24) | ((int)(g * 255) << 16) | ((int)(b * 255) << 8) | (int)(a * 255);
}

int Color::rgb565 (const Color& color)
{
	return ((int)(color.r * 31) << 11) | ((int)(color.g * 63) << 5) | (int)(color.b * 31);
}

int Color::rgba4444 (const Color& color)
{
	return ((int)(color.r * 15) << 12) | ((int)(color.g * 15) << 8) | ((int)(color.b * 15) << 4) | (int)(color.a * 15);
}

int Color::rgb888 (const Color& color)
{
	return ((int)(color.r * 255) << 16) | ((int)(color.g * 255) << 8) | (int)(color.b * 255);
}

int Color::rgba8888 (const Color& color)
{
	return ((int)(color.r * 255) << 24) | ((int)(color.g * 255) << 16) | ((int)(color.b * 255) << 8) | (int)(color.a * 255);
}

/** Sets the Color components using the specified integer value in the format RGB565. This is inverse to the rgb565(r, g, b)
* method.
*
* @param color The Color to be modified.
* @param value An integer color value in RGB565 format. */
void Color::rgb565ToColor (Color& color, int value)
{
	unsigned int uvalue = value;
	color.r = ((uvalue & 0x0000F800) >> 11) / 31.f;
	color.g = ((uvalue & 0x000007E0) >> 5) / 63.f;
	color.b = ((uvalue & 0x0000001F) >> 0) / 31.f;
}

/** Sets the Color components using the specified integer value in the format RGBA4444. This is inverse to the rgba4444(r, g, b,
* a) method.
*
* @param color The Color to be modified.
* @param value An integer color value in RGBA4444 format. */
void Color::rgba4444ToColor (Color& color, int value)
{
	unsigned int uvalue = value;
	color.r = ((uvalue & 0x0000f000) >> 12) / 15.f;
	color.g = ((uvalue & 0x00000f00) >> 8) / 15.f;
	color.b = ((uvalue & 0x000000f0) >> 4) / 15.f;
	color.a = ((uvalue & 0x0000000f)) / 15.f;
}

/** Sets the Color components using the specified integer value in the format RGB888. This is inverse to the rgb888(r, g, b)
* method.
*
* @param color The Color to be modified.
* @param value An integer color value in RGB888 format. */
void Color::rgb888ToColor (Color& color, int value)
{
	unsigned int uvalue = value;
	color.r = ((uvalue & 0x00ff0000) >> 16) / 255.f;
	color.g = ((uvalue & 0x0000ff00) >> 8) / 255.f;
	color.b = ((uvalue & 0x000000ff)) / 255.f;
}

/** Sets the Color components using the specified integer value in the format RGBA8888. This is inverse to the rgb8888(r, g, b,
* a) method.
*
* @param color The Color to be modified.
* @param value An integer color value in RGBA8888 format. */
void Color::rgba8888ToColor (Color& color, int value)
{
	unsigned int uvalue = value;
	color.r = ((uvalue & 0xff000000) >> 24) / 255.f;
	color.g = ((uvalue & 0x00ff0000) >> 16) / 255.f;
	color.b = ((uvalue & 0x0000ff00) >> 8) / 255.f;
	color.a = ((uvalue & 0x000000ff)) / 255.f;
}

