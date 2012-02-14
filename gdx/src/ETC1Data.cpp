#include "stdafx.h"
#include "ETC1Data.h"
#include "ETC1.h"

//TODO: need compressedData length? Take over the pointer or copy the data???
ETC1Data::ETC1Data(int width, int height, unsigned char* compressedData, int compressedDataSize, int dataOffset)
	:width(width), height(height), compressedData(compressedData), dataOffset(dataOffset)
{
}

ETC1Data::ETC1Data()
	:width(0), height(0), compressedData(NULL), compressedDataSize(0), dataOffset(0)
{
}

//void ETC1Data::createFrom(int width, int height, unsigned char* compressedData, int compressedDataSize, int dataOffset)
//{
//	this->width = width;
//	this->height = height;
//	this->compressedData = compressedData;
//	this->compressedDataSize = compressedDataSize;
//	this->dataOffset = dataOffset;
//}

ETC1Data::ETC1Data(const FileHandle& pkmFile)
{
	/*TODO: use zlib???
	byte[] buffer = new byte[1024 * 10];
	DataInputStream in = null;
	try
	{
	in = new DataInputStream(new BufferedInputStream(new GZIPInputStream(pkmFile.read())));
	int fileSize = in.readInt();
	compressedData = BufferUtils.newDisposableByteBuffer(fileSize);
	int readBytes = 0;
	while((readBytes = in.read(buffer)) != -1)
	{
	compressedData.put(buffer, 0, readBytes);
	}
	compressedData.position(0);
	compressedData.limit(compressedData.capacity());
	}
	catch(Exception e)
	{
	throw new GdxRuntimeException("Couldn't load pkm file '" + pkmFile + "'", e);
	}
	finally
	{
	if(in != null) try {
	in.close();
	}
	catch(Exception e)
	{
	}
	}

	width = getWidthPKM(compressedData, 0);
	height = getHeightPKM(compressedData, 0);
	dataOffset = PKM_HEADER_SIZE;
	compressedData.position(dataOffset);
	*/
}

/** @return whether this ETC1Data has a PKM header */
bool ETC1Data::hasPKMHeader() const
{
	return dataOffset == 16;
}

/** Writes the ETC1Data with a PKM header to the given file.
* @param file the file. */
void ETC1Data::write(const FileHandle& file)
{
	/*TODO: use zlib
	DataOutputStream write = null;
	byte[] buffer = new byte[10 * 1024];
	int writtenBytes = 0;
	compressedData.position(0);
	compressedData.limit(compressedData.capacity());
	try
	{
	write = new DataOutputStream(new GZIPOutputStream(file.write(false)));
	write.writeInt(compressedData.capacity());
	while(writtenBytes != compressedData.capacity())
	{
	int bytesToWrite = Math.min(compressedData.remaining(), buffer.length);
	compressedData.get(buffer, 0, bytesToWrite);
	write.write(buffer, 0, bytesToWrite);
	writtenBytes += bytesToWrite;
	}
	}
	catch(Exception e)
	{
	throw new GdxRuntimeException("Couldn't write PKM file to '" + file + "'", e);
	}
	finally
	{
	if(write != null) try {
	write.close();
	}
	catch(Exception e)
	{
	}
	}
	compressedData.position(dataOffset);
	compressedData.limit(compressedData.capacity());
	*/
}

/** Releases the native resources of the ETC1Data instance. */
void ETC1Data::dispose()
{
	//BufferUtils.freeMemory(compressedData);
}

std::string ETC1Data::toString()
{
	std::stringstream ret;
	if(hasPKMHeader())
	{
		ret << (ETC1::isValidPKM(compressedData, 0) ? "valid" : "invalid") << " pkm [" + ETC1::getWidthPKM(compressedData, 0)
			<< "x" << ETC1::getHeightPKM(compressedData, 0) + "], compressed: "
			<< (compressedDataSize - ETC1::PKM_HEADER_SIZE);
	}
	else
	{
		ret << "raw [" << width << "x" << height << "], compressed: " << (compressedDataSize - ETC1::PKM_HEADER_SIZE);
	}
	return ret.str();
}

