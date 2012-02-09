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

#include "ETC1Data.h"
#include "Pixmap.h"
//#include "etc1_utils.h"

/** Class for encoding and decoding ETC1 compressed images. Also provides methods to add a PKM header*/

class ETC1
{
public:
	
	/** The PKM header size in bytes **/
	static int PKM_HEADER_SIZE;
	//static int ETC1_RGB8_OES;

private: 
	

private:
	static int getPixelSize(Pixmap::Format format);

	/** Encodes the image via the ETC1 compression scheme. Only {@link Format#RGB565} and {@link Format#RGB888} are supported.
	 * @param pixmap the {@link Pixmap}
	 * @return the {@link ETC1Data} */
public:
	static void encodeImage(Pixmap& pixmap, ETC1Data& etc1Data);

	/** Encodes the image via the ETC1 compression scheme. Only {@link Format#RGB565} and {@link Format#RGB888} are supported. Adds
	 * a PKM header in front of the compressed image data.
	 * @param pixmap the {@link Pixmap}
	 * @return the {@link ETC1Data} */
	static void encodeImagePKM(Pixmap& pixmap, ETC1Data& etc1Data);

	/** Takes ETC1 compressed image data and converts it to a {@link Format#RGB565} or {@link Format#RGB888} {@link Pixmap}. Does
	 * not modify the ByteBuffer's position or limit.
	 * @param etc1Data the {@link ETC1Data} instance
	 * @param format either {@link Format#RGB565} or {@link Format#RGB888}
	 * @return the Pixmap */
	static void decodeImage(ETC1Data& etc1Data, Pixmap::Format format, Pixmap& pixmap);

	/** @param width the width in pixels
	 * @param height the height in pixels
	 * @return the number of bytes needed to store the compressed data */
	static int getCompressedDataSize(int width, int height);


	/** Writes a PKM header to the {@link ByteBuffer}. Does not modify the position or limit of the ByteBuffer.
	 * @param header the direct order {@link ByteBuffer}
	 * @param offset the offset to the header in bytes
	 * @param width the width in pixels
	 * @param height the height in pixels */
	static void formatHeader(unsigned char* header, int offset, int width, int height);

	/** @param header direct order {@link ByteBuffer} holding the PKM header
	 * @param offset the offset in bytes to the PKM header from the ByteBuffer's start
	 * @return the width stored in the PKM header */
	static int getWidthPKM(unsigned char* header, int offset);

	/** @param header direct order {@link ByteBuffer} holding the PKM header
	 * @param offset the offset in bytes to the PKM header from the ByteBuffer's start
	 * @return the height stored in the PKM header */
	static int getHeightPKM(unsigned char* header, int offset);

	/** @param header direct order {@link ByteBuffer} holding the PKM header
	 * @param offset the offset in bytes to the PKM header from the ByteBuffer's start
	 * @return the width stored in the PKM header */
	static bool isValidPKM(unsigned char* header, int offset);

private:
	/** Decodes the compressed image data to RGB565 or RGB888 pixel data. Does not modify the position or limit of the
	 * {@link ByteBuffer} instances.
	 * @param compressedData the compressed image data in a direct order {@link ByteBuffer}
	 * @param offset the offset in bytes to the image data from the start of the buffer
	 * @param decodedData the decoded data in a direct order ByteBuffer, must hold width * height * pixelSize bytes.
	 * @param offsetDec the offset in bytes to the decoded image data.
	 * @param width the width in pixels
	 * @param height the height in pixels
	 * @param pixelSize the pixel size, either 2 (RBG565) or 3 (RGB888) */
	static void decodeImage(unsigned char* compressedData, int offset, unsigned char* decodedData, int offsetDec,
	                                       int width, int height, int pixelSize);

	/** Encodes the image data given as RGB565 or RGB888. Does not modify the position or limit of the {@link ByteBuffer}.
	 * @param imageData the image data in a direct order {@link ByteBuffer}
	 * @param offset the offset in bytes to the image data from the start of the buffer
	 * @param width the width in pixels
	 * @param height the height in pixels
	 * @param pixelSize the pixel size, either 2 (RGB565) or 3 (RGB888)
	 * @return a new direct order ByteBuffer containing the compressed image data */
	static void encodeImage(unsigned char* imageData, int offset, unsigned char** compressedData, int* compressedDataSize, int width, int height, int pixelSize);

	/** Encodes the image data given as RGB565 or RGB888. Does not modify the position or limit of the {@link ByteBuffer}.
	 * @param imageData the image data in a direct order {@link ByteBuffer}
	 * @param offset the offset in bytes to the image data from the start of the buffer
	 * @param width the width in pixels
	 * @param height the height in pixels
	 * @param pixelSize the pixel size, either 2 (RGB565) or 3 (RGB888)
	 * @return a new direct order ByteBuffer containing the compressed image data */
	static void encodeImagePKM(unsigned char* imageData, int offset, unsigned char** compressedData, int* compressedDataSize, int width, int height, int pixelSize);
};
