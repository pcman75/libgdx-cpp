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
	virtual ~Texture();

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
	
		//TextureFilter(const TextureFilter& other);
		//TextureFilter& operator=(const TextureFilter& other);

		TextureFilter();
	private:
	    int m_glEnum;
	    TextureFilter(int glEnum);
	public:
		bool isMipMap();
		int getGLEnum();
	};

public:
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
	static unsigned int m_buffer;

	TextureFilter m_minFilter;
	TextureFilter m_magFilter;
	TextureWrap m_uWrap;
	TextureWrap m_vWrap;
	unsigned int m_glHandle;
	TextureData* m_data;

private:
	void init()
	{
		m_data = NULL;
		m_minFilter = TextureFilter::Nearest;
		m_magFilter = TextureFilter::Nearest;
		m_uWrap = TextureWrap::ClampToEdge;
		m_vWrap = TextureWrap::ClampToEdge;
	}

	void init(const FileHandle& file, Pixmap::Format format, bool useMipMaps)
	{
		init();
		if(file.name().find(L".etc1") != std::wstring::npos)
		{
			create(new ETC1TextureData(file, useMipMaps));
		}
		else
		{
			//TODO:
			//create(FileTextureData(file, NULL, format, useMipMaps));
		}
	}

public:
	Texture(const std::wstring& internalPath)
	{
		init(Gdx.files->internalHandle(internalPath), Pixmap::Format::Unknown, false);
	}

	Texture(const FileHandle& file)
	{
		init(file, Pixmap::Format::Unknown, false);
	}

	Texture(const FileHandle& file, bool useMipMaps)
	{
		init(file, Pixmap::Format::Unknown, useMipMaps);
	}
	

	Texture(const FileHandle& file, Pixmap::Format format, bool useMipMaps)
	{
		init(file, format, useMipMaps);
	}

	Texture(Pixmap* pixmap)
	{
		init(new PixmapTextureData(pixmap, Pixmap::Format::Unknown, false, false));
	}

	Texture(Pixmap* pixmap, bool useMipMaps)
	{
		init(new PixmapTextureData(pixmap, Pixmap::Format::Unknown, useMipMaps, false));
	}

	Texture(Pixmap* pixmap, Pixmap::Format format, bool useMipMaps)
	{
		init(new PixmapTextureData(pixmap, format, useMipMaps, false));
	}

	Texture(int width, int height, Pixmap::Format format)
	{
		init(new PixmapTextureData(new Pixmap(width, height, format), Pixmap::Format::Unknown, false, true));
	}

	Texture(TextureData* data)
	{
		create(data);
	}

	void init(TextureData* data)
	{
		create(data);
	}

private:
	
	void create(TextureData* data)
	{
		m_glHandle = createGLHandle();
		load(data);
		if(data->isManaged()) 
			addManagedTexture(Gdx.app, this);
	}

	static int createGLHandle()
	{
		Gdx.gl->glGenTextures(1, &m_buffer);
		return m_buffer;
	}

	void load(TextureData* data)
	{
		if( m_data != NULL && data->isManaged() != m_data->isManaged())
			throw new GdxRuntimeException("New data must have the same managed status as the old data");
		
		m_data = data;

		if(!data->isPrepared()) 
			data->prepare();

		if(data->getType() == TextureData::PixmapTexture)
		{
			Pixmap* pixmap = data->consumePixmap();
			uploadImageData(pixmap);
			if(data->disposePixmap()) 
				pixmap->dispose();
			setFilter(m_minFilter, m_magFilter);
			setWrap(m_uWrap, m_vWrap);
		}

		if(data->getType() == TextureData::CompressedTexture)
		{
			Gdx.gl->glBindTexture(GL10::GDX_GL_TEXTURE_2D, m_glHandle);
			data->consumeCompressedData();
			setFilter(m_minFilter, m_magFilter);
			setWrap(m_uWrap, m_vWrap);
		}
		Gdx.gl->glBindTexture(GL10::GDX_GL_TEXTURE_2D, 0);
	}

private:
	void uploadImageData(Pixmap* pixmap)
	{
		if(m_enforcePotImages && Gdx.gl20 == NULL
		        && (!MathUtils::isPowerOfTwo(m_data->getWidth()) || !MathUtils::isPowerOfTwo(m_data->getHeight())))
		{
			throw new GdxRuntimeException("Texture width and height must be powers of two");
		}

		bool disposePixmap = false;
		if(m_data->getFormat() != pixmap->getFormat())
		{
			//TODO: review this!!!!
			Pixmap* tmp = new Pixmap(pixmap->getWidth(), pixmap->getHeight(), m_data->getFormat());
			Pixmap::Blending blend = Pixmap::getBlending();
			Pixmap::setBlending(Pixmap::None);
			tmp->drawPixmap(/*TODO: */*pixmap, 0, 0, 0, 0, pixmap->getWidth(), pixmap->getHeight());
			Pixmap::setBlending(blend);
			pixmap = tmp;
			disposePixmap = true;
		}

		Gdx.gl->glBindTexture(GL10::GDX_GL_TEXTURE_2D, m_glHandle);
		Gdx.gl->glPixelStorei(GL10::GDX_GL_UNPACK_ALIGNMENT, 1);
		if(m_data->useMipMaps())
		{
			//TODO:
			//MipMapGenerator.generateMipMap(pixmap, pixmap->getWidth(), pixmap->getHeight(), disposePixmap);
		}
		else
		{
			Gdx.gl->glTexImage2D(GL10::GDX_GL_TEXTURE_2D, 0, pixmap->getGLInternalFormat(), pixmap->getWidth(), pixmap->getHeight(), 0,
			                    pixmap->getGLFormat(), pixmap->getGLType(), pixmap->getPixels());
			if(disposePixmap)
			{
				pixmap->dispose();
			}
		}
	}

	/** Used internally to reload after context loss. Creates a new GL handle then calls {@link #load(TextureData)}. */
	void reload()
	{
		if(!m_data->isManaged()) throw new GdxRuntimeException("Tried to reload unmanaged Texture");
		m_glHandle = createGLHandle();
		load(m_data);
	}

	/** Binds this texture. The texture will be bound to the currently active texture unit specified via
	 * {@link GLCommon#glActiveTexture(int)}. */
	void bind()
	{
		Gdx.gl->glBindTexture(GL10::GDX_GL_TEXTURE_2D, m_glHandle);
	}

	/** Binds the texture to the given texture unit. Sets the currently active texture unit via
	 * {@link GLCommon#glActiveTexture(int)}.
	 * @param unit the unit (0 to MAX_TEXTURE_UNITS). */
	void bind(int unit)
	{
		Gdx.gl->glActiveTexture(GL10::GDX_GL_TEXTURE0 + unit);
		Gdx.gl->glBindTexture(GL10::GDX_GL_TEXTURE_2D, m_glHandle);
	}

	/** Draws the given {@link Pixmap} to the texture at position x, y. No clipping is performed so you have to make sure that you
	 * draw only inside the texture region. Note that this will only draw to mipmap level 0!
	 *
	 * @param pixmap The Pixmap
	 * @param x The x coordinate in pixels
	 * @param y The y coordinate in pixels */
	void draw(Pixmap* pixmap, int x, int y)
	{
		if(m_data->isManaged()) 
			throw new GdxRuntimeException("can't draw to a managed texture");

		Gdx.gl->glBindTexture(GL10::GDX_GL_TEXTURE_2D, m_glHandle);
		Gdx.gl->glTexSubImage2D(GL10::GDX_GL_TEXTURE_2D, 0, x, y, pixmap->getWidth(), pixmap->getHeight(), pixmap->getGLFormat(),
		                       pixmap->getGLType(), pixmap->getPixels());
	}

	/** @return the width of the texture in pixels */
	int getWidth()
	{
		return m_data->getWidth();
	}

	/** @return the height of the texture in pixels */
	int getHeight()
	{
		return m_data->getHeight();
	}

	TextureFilter getMinFilter()
	{
		return m_minFilter;
	}

	TextureFilter getMagFilter()
	{
		return m_magFilter;
	}

	TextureWrap getUWrap()
	{
		return m_uWrap;
	}

	TextureWrap getVWrap()
	{
		return m_vWrap;
	}

	TextureData* getTextureData()
	{
		return m_data;
	}

	/** @return whether this texture is managed or not. */
	bool isManaged()
	{
		return m_data->isManaged();
	}

	int getTextureObjectHandle()
	{
		return m_glHandle;
	}

	/** Sets the {@link TextureWrap} for this texture on the u and v axis. This will bind this texture!
	 *
	 * @param u the u wrap
	 * @param v the v wrap */
	void setWrap(TextureWrap u, TextureWrap v)
	{
		m_uWrap = u;
		m_vWrap = v;
		bind();
		Gdx.gl->glTexParameterf(GL10::GDX_GL_TEXTURE_2D, GL10::GDX_GL_TEXTURE_WRAP_S, u.getGLEnum());
		Gdx.gl->glTexParameterf(GL10::GDX_GL_TEXTURE_2D, GL10::GDX_GL_TEXTURE_WRAP_T, v.getGLEnum());
	}

	void setFilter(TextureFilter minFilter, TextureFilter magFilter)
	{
		m_minFilter = minFilter;
		m_magFilter = magFilter;
		bind();
		Gdx.gl->glTexParameterf(GL10::GDX_GL_TEXTURE_2D, GL10::GDX_GL_TEXTURE_MIN_FILTER, minFilter.getGLEnum());
		Gdx.gl->glTexParameterf(GL10::GDX_GL_TEXTURE_2D, GL10::GDX_GL_TEXTURE_MAG_FILTER, magFilter.getGLEnum());
	}

	/** Disposes all resources associated with the texture */
	void dispose()
	{
		// this is a hack. reason: we have to set the glHandle to 0 for textures that are
		// reloaded through the asset manager as we first remove (and thus dispose) the texture
		// and then reload it. the glHandle is set to 0 in invalidateAllTextures prior to
		// removal from the asset manager.
		if(m_glHandle == 0) 
			return;
		Gdx.gl->glDeleteTextures(1, &m_glHandle);
		if(m_data->isManaged())
		{
			TextureMapIterator it = m_managedTextures.find(Gdx.app);
			if( it != m_managedTextures.end())
			{
				it->second.remove(this);
			}
		}
		m_glHandle = 0;
	}

	/** @param m_enforcePotImages whether to enforce power of two images in OpenGL ES 1.0 or not. */
	static void setEnforcePotImages(bool enforcePotImages)
	{
		m_enforcePotImages = enforcePotImages;
	}

	static void addManagedTexture(Application* app, Texture* texture)
	{
		m_managedTextures[app].push_back(texture);
	}

	/** Clears all managed textures. This is an internal method. Do not use it! */
	static void clearAllTextures(Application* app)
	{
		m_managedTextures.erase(app);
	}

	/** Invalidate all managed textures. This is an internal method. Do not use it! */
	static void invalidateAllTextures(Application* app)
	{
		/*TODO: implement it after AssetManager implementation
		List<Texture> managedTexureList = m_managedTextures.get(app);
		if(managedTexureList == NULL) return;

		if(assetManager == NULL)
		{
			for(int i = 0; i < managedTexureList.size(); i++)
			{
				Texture texture = managedTexureList.get(i);
				texture.reload();
			}
		}
		else
		{
			// first we have to make sure the AssetManager isn't loading anything anymore,
			// otherwise the ref counting trick below wouldn't work (when a texture is
			// currently on the task stack of the manager.)
			assetManager.finishLoading();

			// next we go through each texture and reload either directly or via the
			// asset manager.
			List<Texture> textures = new ArrayList<Texture>(managedTexureList);
			for(Texture texture : textures)
			{
				String fileName = assetManager.getAssetFileName(texture);
				if(fileName == NULL)
				{
					texture.reload();
				}
				else
				{
					// get the ref count of the texture, then set it to 0 so we
					// can actually remove it from the assetmanager. Also set the
					// handle to zero, otherwise we might accidentially dispose
					// already reloaded textures.
					final int refCount = assetManager.getReferenceCount(fileName);
					assetManager.setReferenceCount(fileName, 0);
					texture.m_glHandle = 0;

					// create the parameters, passing the reference to the texture as
					// well as a callback that sets the ref count.
					TextureParameter params = new TextureParameter();
					params.textureData = texture.getTextureData();
					params.minFilter = texture.getMinFilter();
					params.magFilter = texture.getMagFilter();
					params.wrapU = texture.getUWrap();
					params.wrapV = texture.getVWrap();
					params.genMipMaps = texture.m_data->useMipMaps(); //not sure about this?
					params.texture = texture; // special parameter which will ensure that the references stay the same.
					params.loadedCallback = new LoadedCallback()
					{
						void finishedLoading(AssetManager assetManager, const std::wstring& fileName, Class type)
						{
							assetManager.setReferenceCount(fileName, refCount);
						}
					};

					// unload the texture, create a new gl handle then reload it.
					assetManager.unload(fileName);
					texture.m_glHandle = Texture.createGLHandle();
					assetManager.load(fileName, Texture.class, params);
				}
			}
			managedTexureList.clear();
			managedTexureList.addAll(textures);
			
		}
		*/
	}

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

	static std::wstring getManagedStatus()
	{
		std::wstringstream ret;
		ret << "Managed textures/app: { ";
		for(TextureMapIterator it = m_managedTextures.begin(); it != m_managedTextures.end(); it++)
		{
			ret << it->second.size() << " ";
		}
		ret << "}";
		return ret.str();
	}
};
