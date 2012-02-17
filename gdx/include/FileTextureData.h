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

#include "TextureData.h"
#include "Pixmap.h"
#include "GdxDefines.h"

class GdxDllImportExport FileTextureData :
	public TextureData
{
public:
	static bool copyToPOT;

private:
	FileHandle m_file;
	int m_width;
	int m_height;
	Pixmap::Format m_format;
	Pixmap* m_pixmap;
	bool m_useMipMaps;
	bool m_isPrepared;

public:
	//preloaded Pixmap can be NULL
	//TODO: implement Pixmap::Empty
	FileTextureData(const FileHandle& file, Pixmap* preloadedPixmap, Pixmap::Format format, bool useMipMaps);
	bool isPrepared();
	void prepare();

	//TODO:
	//Return a Pixmap not a pointer. In order not to copy big data while transfering objects
	//implement a handOver mechanism for Pixmaps and other classes. pixmap.handOver(other) should take (not copy)
	//the ownership of "other" pointer to the data and "Empty" the pixmap.
	//implemetn also clone() mechanism and make protected copy constructor and assignement operators 
	Pixmap* consumePixmap();
	bool disposePixmap();
	int getWidth();
	int getHeight();
	Pixmap::Format getFormat();
	bool useMipMaps();
	bool isManaged();
	FileHandle getFileHandle();
	TextureDataType getType();
	void consumeCompressedData();

private:
	Pixmap* ensurePot(Pixmap* pixmap);

};
