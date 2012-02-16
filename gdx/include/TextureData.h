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

/** Used by a {@link Texture} to load the pixel data. A TextureData can either return a {@link Pixmap} or upload the pixel data
 * itself. It signals it's type via {@link #getType()} to the Texture that's using it. The Texture will then either invoke
 * {@link #consumePixmap()} or {@link #consumeCompressedData()}. These are the first methods to be called by Texture. After that
 * the Texture will invoke the other methods to find out about the size of the image data, the format, whether mipmaps should be
 * generated and whether the TextureData is able to manage the pixel data if the OpenGL ES context is lost.</p>
 *
 * In case the TextureData implementation has the type {@link TextureDataType#Compressed}, the implementation has to generate the
 * mipmaps itself if necessary. See {@link MipMapGenerator}.</p>
 *
 * Before a call to either {@link #consumePixmap()} or {@link #consumeCompressedData()}, Texture will bind the OpenGL ES
 * texture.</p>
 *
 * Look at {@link FileTextureData} and {@link ETC1TextureData} for example implementations of this interface.
 */
class TextureData
{
	/** The type of this {@link TextureData} */
public:
	virtual ~TextureData() {};
	enum TextureDataType 
	{
	    PixmapTexture, CompressedTexture
	};

	/** @return the {@link TextureDataType} */
	virtual TextureDataType getType() = 0;

	/** @return whether the TextureData is prepared or not. */
	virtual bool isPrepared() = 0;

	/** Prepares the TextureData for a call to {@link #consumePixmap()} or {@link #consumeCompressedData()}. This method can be
	 * called from a non OpenGL thread and should thus not interact with OpenGL. */
	virtual void prepare() = 0;

	/** Returns the {@link Pixmap} for upload by Texture. A call to {@link #prepare()} must preceed a call to this method. Any
	 * internal datastructures created in {@link #prepare()} should be disposed of here.
	 *
	 * @return the pixmap. */
	virtual Pixmap* consumePixmap() = 0;

	/** @return whether the caller of {@link #consumePixmap()} should dispose the Pixmap returned by {@link #consumePixmap()} */
	virtual bool disposePixmap() = 0;

	/** Uploads the pixel data to the OpenGL ES texture. The caller must bind an OpenGL ES texture. A call to {@link #prepare()}
	 * must preceed a call to this method. Any internal datastructures created in {@link #prepare()}. */
	virtual void consumeCompressedData() = 0;

	/** @return the width of the pixel data */
	virtual int getWidth() = 0;

	/** @return the height of the pixel data */
	virtual int getHeight() = 0;

	/** @return the {@link Format} of the pixel data */
	virtual Pixmap::Format getFormat() = 0;

	/** @return whether to generate mipmaps or not. */
	virtual bool useMipMaps() = 0;

	/** @return whether this implementation can cope with a EGL context loss. */
	virtual bool isManaged() = 0;
};
