#include "stdafx.h"
#include "ETC1.h"
#include "ETC1Data.h"
#include "Pixmap.h"
#include "etc1_utils.h"


/** The PKM header size in bytes **/
int ETC1::PKM_HEADER_SIZE = 16;
//int ETC1::ETC1_RGB8_OES = 0x00008d64;

int ETC1::getPixelSize(Pixmap::Format format)
{
	if(format == Pixmap::Format::RGB565) 
		return 2;
	if(format == Pixmap::Format::RGB888) 
		return 3;
	throw new GdxRuntimeException("Can only handle RGB565 or RGB888 images");
}

/** Encodes the image via the ETC1 compression scheme. Only {@link Format#RGB565} and {@link Format#RGB888} are supported.
* @param pixmap the {@link Pixmap}
* @return the {@link ETC1Data} */

void ETC1::encodeImage(Pixmap& pixmap, ETC1Data& etc1Data)
{
	int pixelSize = getPixelSize(pixmap.getFormat());
	encodeImage(pixmap.getPixels(), 0, &etc1Data.compressedData, &etc1Data.compressedDataSize, pixmap.getWidth(), pixmap.getHeight(), pixelSize);
	//etc1Data.createFrom(pixmap.getWidth(), pixmap.getHeight(), compressedData, 0); 
}

/** Encodes the image via the ETC1 compression scheme. Only {@link Format#RGB565} and {@link Format#RGB888} are supported. Adds
* a PKM header in front of the compressed image data.
* @param pixmap the {@link Pixmap}
* @return the {@link ETC1Data} */
void ETC1::encodeImagePKM(Pixmap& pixmap, ETC1Data& etc1Data)
{
	int pixelSize = getPixelSize(pixmap.getFormat());
	//unsigned char* compressedData = NULL;
	//int compressedDataSize = 0;
	encodeImagePKM(pixmap.getPixels(), 0, &etc1Data.compressedData, &etc1Data.compressedDataSize, pixmap.getWidth(), pixmap.getHeight(), pixelSize);
	//etc1Data.createFrom(pixmap.getWidth(), pixmap.getHeight(), compressedData, compressedDataSize, 0); 
}

/** Takes ETC1 compressed image data and converts it to a {@link Format#RGB565} or {@link Format#RGB888} {@link Pixmap}. Does
* not modify the ByteBuffer's position or limit.
* @param etc1Data the {@link ETC1Data} instance
* @param format either {@link Format#RGB565} or {@link Format#RGB888}
* @return the Pixmap */
void ETC1::decodeImage(ETC1Data& etc1Data, Pixmap::Format format, Pixmap& pixmap)
{
	int dataOffset = 0;
	int width = 0;
	int height = 0;

	if(etc1Data.hasPKMHeader())
	{
		dataOffset = 16;
		width = ETC1::getWidthPKM(etc1Data.compressedData, 0);
		height = ETC1::getHeightPKM(etc1Data.compressedData, 0);
	}
	else
	{
		dataOffset = 0;
		width = etc1Data.width;
		height = etc1Data.height;
	}

	int pixelSize = getPixelSize(format);
	pixmap.createFrom(width, height, format);
	decodeImage(etc1Data.compressedData, dataOffset, pixmap.getPixels(), 0, width, height, pixelSize);
}

/** @param width the width in pixels
* @param height the height in pixels
* @return the number of bytes needed to store the compressed data */
int ETC1::getCompressedDataSize(int width, int height)
{
	return etc1_get_encoded_data_size(width, height);
}


/** Writes a PKM header to the {@link ByteBuffer}. Does not modify the position or limit of the ByteBuffer.
* @param header the direct order {@link ByteBuffer}
* @param offset the offset to the header in bytes
* @param width the width in pixels
* @param height the height in pixels */
void ETC1::formatHeader(unsigned char* header, int offset, int width, int height)
{
	etc1_pkm_format_header(header + offset, width, height);
}

/** @param header direct order {@link ByteBuffer} holding the PKM header
* @param offset the offset in bytes to the PKM header from the ByteBuffer's start
* @return the width stored in the PKM header */
int ETC1::getWidthPKM(unsigned char* header, int offset)
{
	return etc1_pkm_get_width(header + offset);
}

/** @param header direct order {@link ByteBuffer} holding the PKM header
* @param offset the offset in bytes to the PKM header from the ByteBuffer's start
* @return the height stored in the PKM header */
int ETC1::getHeightPKM(unsigned char* header, int offset)
{
	return etc1_pkm_get_height((etc1_byte*)header + offset);
}

/** @param header direct order {@link ByteBuffer} holding the PKM header
* @param offset the offset in bytes to the PKM header from the ByteBuffer's start
* @return the width stored in the PKM header */
bool ETC1::isValidPKM(unsigned char* header, int offset)
{
	return etc1_pkm_is_valid((etc1_byte*)header + offset) != 0?true:false;
}

/** Decodes the compressed image data to RGB565 or RGB888 pixel data. Does not modify the position or limit of the
* {@link ByteBuffer} instances.
* @param compressedData the compressed image data in a direct order {@link ByteBuffer}
* @param offset the offset in bytes to the image data from the start of the buffer
* @param decodedData the decoded data in a direct order ByteBuffer, must hold width * height * pixelSize bytes.
* @param offsetDec the offset in bytes to the decoded image data.
* @param width the width in pixels
* @param height the height in pixels
* @param pixelSize the pixel size, either 2 (RBG565) or 3 (RGB888) */
void ETC1::decodeImage(unsigned char* compressedData, int offset, unsigned char* decodedData, int offsetDec,
	int width, int height, int pixelSize)
{
	etc1_decode_image(compressedData + offset, decodedData + offsetDec, width, height, pixelSize, width * pixelSize);
}

/** Encodes the image data given as RGB565 or RGB888. Does not modify the position or limit of the {@link ByteBuffer}.
* @param imageData the image data in a direct order {@link ByteBuffer}
* @param offset the offset in bytes to the image data from the start of the buffer
* @param width the width in pixels
* @param height the height in pixels
* @param pixelSize the pixel size, either 2 (RGB565) or 3 (RGB888)
* @return a new direct order ByteBuffer containing the compressed image data */
void ETC1::encodeImage(unsigned char* imageData, int offset, unsigned char** compressedData, int* compressedDataSize, int width, int height, int pixelSize)
{
	*compressedDataSize = etc1_get_encoded_data_size(width, height);
	*compressedData = new unsigned char[*compressedDataSize];
	etc1_encode_image(imageData + offset, width, height, pixelSize, width * pixelSize, *compressedData);
}

/** Encodes the image data given as RGB565 or RGB888. Does not modify the position or limit of the {@link ByteBuffer}.
* @param imageData the image data in a direct order {@link ByteBuffer}
* @param offset the offset in bytes to the image data from the start of the buffer
* @param width the width in pixels
* @param height the height in pixels
* @param pixelSize the pixel size, either 2 (RGB565) or 3 (RGB888)
* @return a new direct order ByteBuffer containing the compressed image data */
void ETC1::encodeImagePKM(unsigned char* imageData, int offset, unsigned char** compressedData, int* compressedDataSize, int width, int height, int pixelSize)
{
	*compressedDataSize = etc1_get_encoded_data_size(width, height);
	*compressedData = new unsigned char[*compressedDataSize + ETC_PKM_HEADER_SIZE];
	etc1_pkm_format_header(*compressedData, width, height);
	etc1_encode_image(imageData + offset, width, height, pixelSize, width * pixelSize, *compressedData + ETC_PKM_HEADER_SIZE);
}

