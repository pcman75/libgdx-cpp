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
#include "ETC1.h"

class ETC1TextureData : public TextureData
{
private:
	FileHandle m_file;
	ETC1Data m_data;
	bool m_useMipMaps;
	int m_width;
	int m_height;
	bool m_isPrepared;

private:
	void init();

public:
	ETC1TextureData(const FileHandle& file);
	ETC1TextureData(const FileHandle& file, bool useMipMaps);
	ETC1TextureData(const ETC1Data& encodedImage, bool useMipMaps);
	
	TextureDataType getType();
	bool isPrepared();
	void prepare();
	void consumeCompressedData();
	Pixmap consumePixmap();
	bool disposePixmap();
	int getWidth();
	int getHeight();
	Pixmap::Format getFormat();
	bool useMipMaps();
	bool isManaged();
};
