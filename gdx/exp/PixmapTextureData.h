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

class PixmapTextureData : public TextureData
{
	Pixmap* m_pixmap;
	Pixmap::Format m_format;
	bool m_useMipMaps;
	bool m_disposePixmap;

public:
	PixmapTextureData(Pixmap* pixmap, Pixmap::Format format, bool useMipMaps, bool disposePixmap);
	bool disposePixmap();
	Pixmap* consumePixmap();
	int getWidth();
	int getHeight();
	Pixmap::Format getFormat();
	bool useMipMaps();
	bool isManaged();
	TextureDataType getType();
	void consumeCompressedData();
	bool isPrepared();
	void prepare();
};
