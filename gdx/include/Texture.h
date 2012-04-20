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

#include <list>
#include <map>
#include "Application.h"
#include "FileHandle.h"
#include "TextureData.h"
#include "Pixmap.h"
#include "Gdx.h"
#include "ETC1TextureData.h"
#include "FileTextureData.h"
#include "PixmapTextureData.h"
#include "MathUtils.h"


/** <p>
 * A Texture wraps a standard OpenGL ES texture.
 * </p>
 *
 * <p>
 * A Texture can be managed. If the OpenGL context is lost all managed textures get invalidated. This happens when a user switches
 * to another application or receives an incoming call. Managed textures get reloaded automatically.
 * </p>
 *
 * <p>
 * A Texture has to be bound via the {@link Texture#bind()} method in order for it to be applied to geometry. The texture will be
 * bound to the currently active texture unit specified via {@link GLCommon#glActiveTexture(int)}.
 * </p>
 *
 * <p>
 * You can draw {@link Pixmap}s to a texture at any time. The changes will be automatically uploaded to texture memory. This is of
 * course not extremely fast so use it with care. It also only works with unmanaged textures.
 * </p>
 *
 * <p>
 * A Texture must be disposed when it is no longer used
 * </p>
 */
class Texture
{
public:
	class TextureFilter
	{
	public:
	    static const TextureFilter Nearest;
		static const TextureFilter Linear;
		static const TextureFilter MipMap;
		static const TextureFilter MipMapNearestNearest;
		static const TextureFilter MipMapLinearNearest;
		static const TextureFilter MipMapNearestLinear;
		static const TextureFilter MipMapLinearLinear;

		TextureFilter();
	private:
	    int m_glEnum;
	    TextureFilter(int glEnum);
	public:
		bool isMipMap();
		int getGLEnum();
	};
	class TextureWrap
	{
	public:
		static const TextureWrap ClampToEdge;
		static const TextureWrap Repeat;

		TextureWrap();
	private:
	    int m_glEnum;
	    TextureWrap(int glEnum);

	public:
		int getGLEnum();
	};

private:
	static bool m_enforcePotImages;

	//TODO: unused???
	static bool m_useHWMipMap;

	//TODO:
	//static AssetManager assetManager;
	typedef std::list<Texture*> TextureList;
	typedef TextureList::iterator TextureListIterator;
	typedef std::map<Application*, TextureList> TextureMap;
	typedef TextureMap::iterator TextureMapIterator;
	static TextureMap m_managedTextures;

	static unsigned int m_buffer;

	TextureFilter m_minFilter;
	TextureFilter m_magFilter;
	TextureWrap m_uWrap;
	TextureWrap m_vWrap;
	unsigned int m_glHandle;
	TextureData* m_data;

private:
	void init();
	void init(const FileHandle& file, Pixmap::Format format, bool useMipMaps);
	void init(TextureData* data);
	void create(TextureData* data);

public:
	Texture();
	Texture(const std::string& internalPath);
	Texture(const FileHandle& file);
	Texture(const FileHandle& file, bool useMipMaps);
	Texture(const FileHandle& file, Pixmap::Format format, bool useMipMaps);
	Texture(Pixmap* pixmap);
	Texture(Pixmap* pixmap, bool useMipMaps);
	Texture(Pixmap* pixmap, Pixmap::Format format, bool useMipMaps);
	Texture(int width, int height, Pixmap::Format format);
	Texture(TextureData* data);
	virtual ~Texture();

private:
	static int createGLHandle();
	void load(TextureData* data);
	void uploadImageData(Pixmap* pixmap);
	/** Used internally to reload after context loss. Creates a new GL handle then calls {@link #load(TextureData)}. */
	void reload();

public:
	/** Binds this texture. The texture will be bound to the currently active texture unit specified via
	 * {@link GLCommon#glActiveTexture(int)}. */
	void bind();

	/** Binds the texture to the given texture unit. Sets the currently active texture unit via
	 * {@link GLCommon#glActiveTexture(int)}.
	 * @param unit the unit (0 to MAX_TEXTURE_UNITS). */
	void bind(int unit);

	/** Draws the given {@link Pixmap} to the texture at position x, y. No clipping is performed so you have to make sure that you
	 * draw only inside the texture region. Note that this will only draw to mipmap level 0!
	 *
	 * @param pixmap The Pixmap
	 * @param x The x coordinate in pixels
	 * @param y The y coordinate in pixels */
	void draw(Pixmap* pixmap, int x, int y);

	/** @return the width of the texture in pixels */
	int getWidth();

	/** @return the height of the texture in pixels */
	int getHeight();

	TextureFilter getMinFilter();

	TextureFilter getMagFilter();

	TextureWrap getUWrap();

	TextureWrap getVWrap();

	TextureData* getTextureData();

	/** @return whether this texture is managed or not. */
	bool isManaged();

	int getTextureObjectHandle();

	/** Sets the {@link TextureWrap} for this texture on the u and v axis. This will bind this texture!
	 *
	 * @param u the u wrap
	 * @param v the v wrap */
	void setWrap(TextureWrap u, TextureWrap v);

	void setFilter(TextureFilter minFilter, TextureFilter magFilter);

	/** Disposes all resources associated with the texture */
	void dispose();

	/** @param m_enforcePotImages whether to enforce power of two images in OpenGL ES 1.0 or not. */
	static void setEnforcePotImages(bool enforcePotImages);

	static void addManagedTexture(Application* app, Texture* texture);

	/** Clears all managed textures. This is an internal method. Do not use it! */
	static void clearAllTextures(Application* app);

	/** Invalidate all managed textures. This is an internal method. Do not use it! */
	static void invalidateAllTextures(Application* app);

	/** Sets the {@link AssetManager}. When the context is lost, textures managed by the asset manager are reloaded by the manager
	 * on a separate thread (provided that a suitable {@link AssetLoader} is registered with the manager). Textures not managed by
	 * the AssetManager are reloaded via the usual means on the rendering thread.
	 * @param manager the asset manager. */
	/*TODO after implementing Assets
	static void setAssetManager(AssetManager manager)
	{
		Texture.assetManager = manager;
	}
	*/

	static std::string getManagedStatus();
};
