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
//#include "gdx2d.h"

class GdxDllImportExport Gdx2DPixmap
{
public:
	enum GDX2D_FORMAT
	{
		GDX2D_FORMAT_UNKNOWN = 0,
		GDX2D_FORMAT_ALPHA = 1,
		GDX2D_FORMAT_LUMINANCE_ALPHA = 2,
		GDX2D_FORMAT_RGB888 = 3,
		GDX2D_FORMAT_RGBA8888 = 4,
		GDX2D_FORMAT_RGB565 = 5,
		GDX2D_FORMAT_RGBA4444 = 6
	};

	enum GDX2D_SCALE
	{
		GDX2D_SCALE_NEAREST = 0,
		GDX2D_SCALE_LINEAR = 1
	};

	enum GDX2D_BLEND
	{
		GDX2D_BLEND_NONE = 0,
		GDX2D_BLEND_SRC_OVER = 1
	};

private:
	struct tag_gdx2d_pixmap* m_pixmap;


public:
	Gdx2DPixmap(const unsigned char* encodedData, int len, int requestedFormat);
	Gdx2DPixmap();
	void createFrom(const unsigned char* encodedData, int len, int requestedFormat);
	/*
	Gdx2DPixmap (InputStream in, int requestedFormat)
	{
		ByteArrayOutputStream bytes = new ByteArrayOutputStream(1024);
		byte[] buffer = new byte[1024];
		int readBytes = 0;

		while ((readBytes = in.read(buffer)) != -1)
		{
			bytes.write(buffer, 0, readBytes);
		}

		buffer = bytes.toByteArray();
		pixelPtr = load(nativeData, buffer, 0, buffer.length, requestedFormat);
		if (pixelPtr == null) throw new IOException("couldn't load pixmap");

		basePtr = nativeData[0];
		width = (int)nativeData[1];
		height = (int)nativeData[2];
		format = (int)nativeData[3];
	}
	*/
	Gdx2DPixmap(int width, int height, int format);


	void dispose ();
	void clear (int color);

	void setPixel (int x, int y, int color);
	int getPixel (int x, int y);
	void drawLine (int x, int y, int x2, int y2, int color);
	void drawRect (int x, int y, int width, int height, int color);
	void drawCircle (int x, int y, int radius, int color);
	void fillRect (int x, int y, int width, int height, int color);
	void fillCircle (int x, int y, int radius, int color);
	void drawPixmap (Gdx2DPixmap* src, int srcX, int srcY, int dstX, int dstY, int width, int height);
	void drawPixmap (Gdx2DPixmap* src, int srcX, int srcY, int srcWidth, int srcHeight, int dstX, int dstY, int dstWidth, int dstHeight);
	/*
	static Gdx2DPixmap newPixmap (InputStream in, int requestedFormat)
	{
		try
		{
			return new Gdx2DPixmap(in, requestedFormat);
		}
		catch (IOException e)
		{
			return null;
		}
	}
	*/

	/*caller must delete it*/
	static Gdx2DPixmap* newPixmap(int width, int height, int format);
	unsigned char* getPixels ();
	int getHeight();
	int getWidth();
	int getFormat() const;
	int getGLInternalFormat ();
	int getGLFormat();
	int getGLType();
	std::string getFormatString();
	
	static void setBlend (int blend);
	static void setScale (int scale);

private:
	void init();
};
