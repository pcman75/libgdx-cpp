#include "stdafx.h"
#include "PixmapIO.h"

#include "lodepng.h"

void PixmapIO::writePNG(const FileHandle& file, Pixmap* pixmap)
{
	int fileNameLength = file.name().length();
	char* buf = new char[fileNameLength+1];
	strcpy( buf, file.name().c_str());

	//TODO: 
	//Probably need to let the FileHandle write it

	Pixmap::Format format(pixmap->getFormat());
	if( format == Pixmap::Format::RGBA8888)
		LodePNG_encode32_file(buf, pixmap->getPixels(),  pixmap->getWidth(), pixmap->getHeight()); 
	else if(format == Pixmap::Format::RGB888)
		LodePNG_encode24_file(buf, pixmap->getPixels(),  pixmap->getWidth(), pixmap->getHeight());
	//TODO:
	//Why 4444 is not working???
	//else if(format == Pixmap::Format::RGBA4444)
	//	LodePNG_encode_file(buf, pixmap->getPixels(),  pixmap->getWidth(), pixmap->getHeight(), 6, 4);
	else
		throw GdxRuntimeException("Unknown pixmap format");
	delete[] buf;

	//file.writeBytes(PNG.write(pixmap), false);
}