#include "stdafx.h"
#include "PixmapIO.h"

#include "lodepng.h"

void PixmapIO::writePNG(const FileHandle& file, Pixmap* pixmap)
{
	try
	{
		int fileNameLength = file.name().length();
		char* buf = new char[fileNameLength+1];
		wcstombs(buf, file.name().c_str(), fileNameLength+1);
		//TODO: 
		//1. Probably need to let the FileHandle write it
		//2. Use the pixmap format and call proper lodePNG function
		LodePNG_encode24_file(buf, pixmap->getPixels(),  pixmap->getWidth(), pixmap->getHeight()); 
		delete[] buf;
		
		//file.writeBytes(PNG.write(pixmap), false);
	}
	catch(std::exception ex)
	{
		throw new GdxRuntimeException("Error writing PNG");
	}
}