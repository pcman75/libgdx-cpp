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

#include "Pixmap.h"

class MipMapGenerator
{
private:
	static bool m_useHWMipMap;

public:
	static void setUseHardwareMipMap(bool useHWMipMap);

	/** Sets the image data of the {@link Texture} based on the {@link Pixmap}. The texture must be bound for this to work. If
	 * <code>disposePixmap</code> is true, the pixmap will be disposed at the end of the method.
	 * @param pixmap the Pixmap
	 * @param disposePixmap whether to dispose the Pixmap after upload */
	static void generateMipMap(Pixmap* pixmap, int textureWidth, int textureHeight, bool disposePixmap);

private:
	static void generateMipMapGLES20(Pixmap* pixmap, bool disposePixmap);

	static void generateMipMapDesktop(Pixmap* pixmap, int textureWidth, int textureHeight, bool disposePixmap);

	static void generateMipMapCPU(Pixmap* pixmap, int textureWidth, int textureHeight, bool disposePixmap);
};
