#include "stdafx.h"
#include "Texture.h"
#include "GL10.h"

bool Texture::m_enforcePotImages = true;

//TODO: unused???
bool m_useHWMipMap = true;

//TODO:
//AssetManager assetManager;
Texture::TextureMap Texture::m_managedTextures;

const Texture::TextureFilter Texture::TextureFilter::Nearest = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::Linear = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMap = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_LINEAR_MIPMAP_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMapNearestNearest = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_NEAREST_MIPMAP_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::MipMapLinearNearest = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_LINEAR_MIPMAP_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::MipMapNearestLinear = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_NEAREST_MIPMAP_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMapLinearLinear = Texture::TextureFilter::TextureFilter(GL10::GDX_GL_LINEAR_MIPMAP_LINEAR);

unsigned int Texture::m_buffer = -1;

Texture::TextureFilter::TextureFilter()
{
	m_glEnum = GL10::GDX_GL_NEAREST;
}

/*
Texture::TextureFilter::TextureFilter(const TextureFilter& other)
:m_glEnum(other.m_glEnum)
{
}

Texture::TextureFilter& Texture::TextureFilter::operator=(const TextureFilter& other)
{
if (this == &other)
return *this;  

m_glEnum = other.m_glEnum;
return *this;
}


*/

Texture::TextureFilter::TextureFilter(int glEnum)
	:m_glEnum(glEnum)
{
}

bool Texture::TextureFilter::isMipMap()
{
	return m_glEnum != GL10::GDX_GL_NEAREST && m_glEnum != GL10::GDX_GL_LINEAR;
}

int Texture::TextureFilter::getGLEnum()
{
	return m_glEnum;
}

const Texture::TextureWrap Texture::TextureWrap::ClampToEdge = Texture::TextureWrap::TextureWrap(GL10::GDX_GL_CLAMP_TO_EDGE);
const Texture::TextureWrap Texture::TextureWrap::Repeat = Texture::TextureWrap::TextureWrap(GL10::GDX_GL_REPEAT);

Texture::TextureWrap::TextureWrap()
{
	m_glEnum = GL10::GDX_GL_CLAMP_TO_EDGE;
}

Texture::TextureWrap::TextureWrap(int glEnum)
	:m_glEnum(glEnum)
{
}

int Texture::TextureWrap::getGLEnum()
{
	return m_glEnum;
}

Texture::~Texture()
{
}

void Texture::init()
{
	m_data = NULL;
	m_minFilter = TextureFilter::Nearest;
	m_magFilter = TextureFilter::Nearest;
	m_uWrap = TextureWrap::ClampToEdge;
	m_vWrap = TextureWrap::ClampToEdge;
}

void Texture::init(const FileHandle& file, Pixmap::Format format, bool useMipMaps)
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

Texture::Texture()
{
}

Texture::Texture(const std::wstring& internalPath)
{
	//TODO:
	//init(Gdx.files->internalHandle(internalPath), Pixmap::Format::Unknown, false);
}

Texture::Texture(const FileHandle& file)
{
	init(file, Pixmap::Format::Unknown, false);
}

Texture::Texture(const FileHandle& file, bool useMipMaps)
{
	init(file, Pixmap::Format::Unknown, useMipMaps);
}


Texture::Texture(const FileHandle& file, Pixmap::Format format, bool useMipMaps)
{
	init(file, format, useMipMaps);
}

Texture::Texture(Pixmap* pixmap)
{
	init(new PixmapTextureData(pixmap, Pixmap::Format::Unknown, false, false));
}

Texture::Texture(Pixmap* pixmap, bool useMipMaps)
{
	init(new PixmapTextureData(pixmap, Pixmap::Format::Unknown, useMipMaps, false));
}

Texture::Texture(Pixmap* pixmap, Pixmap::Format format, bool useMipMaps)
{
	init(new PixmapTextureData(pixmap, format, useMipMaps, false));
}

Texture::Texture(int width, int height, Pixmap::Format format)
{
	init(new PixmapTextureData(new Pixmap(width, height, format), Pixmap::Format::Unknown, false, true));
}

Texture::Texture(TextureData* data)
{
	create(data);
}

void Texture::init(TextureData* data)
{
	create(data);
}

void Texture::create(TextureData* data)
{
	m_glHandle = createGLHandle();
	load(data);
	if(data->isManaged()) 
		addManagedTexture(Gdx.app, this);
}

int Texture::createGLHandle()
{
	Gdx.gl->glGenTextures(1, &m_buffer);
	return m_buffer;
}

void Texture::load(TextureData* data)
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


void Texture::uploadImageData(Pixmap* pixmap)
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
void Texture::reload()
{
	if(!m_data->isManaged()) throw new GdxRuntimeException("Tried to reload unmanaged Texture");
	m_glHandle = createGLHandle();
	load(m_data);
}

/** Binds this texture. The texture will be bound to the currently active texture unit specified via
* {@link GLCommon#glActiveTexture(int)}. */
void Texture::bind()
{
	Gdx.gl->glBindTexture(GL10::GDX_GL_TEXTURE_2D, m_glHandle);
}

/** Binds the texture to the given texture unit. Sets the currently active texture unit via
* {@link GLCommon#glActiveTexture(int)}.
* @param unit the unit (0 to MAX_TEXTURE_UNITS). */
void Texture::bind(int unit)
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
void Texture::draw(Pixmap* pixmap, int x, int y)
{
	if(m_data->isManaged()) 
		throw new GdxRuntimeException("can't draw to a managed texture");

	Gdx.gl->glBindTexture(GL10::GDX_GL_TEXTURE_2D, m_glHandle);
	Gdx.gl->glTexSubImage2D(GL10::GDX_GL_TEXTURE_2D, 0, x, y, pixmap->getWidth(), pixmap->getHeight(), pixmap->getGLFormat(),
		pixmap->getGLType(), pixmap->getPixels());
}

/** @return the width of the texture in pixels */
int Texture::getWidth()
{
	return m_data->getWidth();
}

/** @return the height of the texture in pixels */
int Texture::getHeight()
{
	return m_data->getHeight();
}

Texture::TextureFilter Texture::getMinFilter()
{
	return m_minFilter;
}

Texture::TextureFilter Texture::getMagFilter()
{
	return m_magFilter;
}

Texture::TextureWrap Texture::getUWrap()
{
	return m_uWrap;
}

Texture::TextureWrap Texture::getVWrap()
{
	return m_vWrap;
}

TextureData* Texture::getTextureData()
{
	return m_data;
}

/** @return whether this texture is managed or not. */
bool Texture::isManaged()
{
	return m_data->isManaged();
}

int Texture::getTextureObjectHandle()
{
	return m_glHandle;
}

/** Sets the {@link TextureWrap} for this texture on the u and v axis. This will bind this texture!
*
* @param u the u wrap
* @param v the v wrap */
void Texture::setWrap(TextureWrap u, TextureWrap v)
{
	m_uWrap = u;
	m_vWrap = v;
	bind();
	Gdx.gl->glTexParameterf(GL10::GDX_GL_TEXTURE_2D, GL10::GDX_GL_TEXTURE_WRAP_S, u.getGLEnum());
	Gdx.gl->glTexParameterf(GL10::GDX_GL_TEXTURE_2D, GL10::GDX_GL_TEXTURE_WRAP_T, v.getGLEnum());
}

void Texture::setFilter(TextureFilter minFilter, TextureFilter magFilter)
{
	m_minFilter = minFilter;
	m_magFilter = magFilter;
	bind();
	Gdx.gl->glTexParameterf(GL10::GDX_GL_TEXTURE_2D, GL10::GDX_GL_TEXTURE_MIN_FILTER, minFilter.getGLEnum());
	Gdx.gl->glTexParameterf(GL10::GDX_GL_TEXTURE_2D, GL10::GDX_GL_TEXTURE_MAG_FILTER, magFilter.getGLEnum());
}

/** Disposes all resources associated with the texture */
void Texture::dispose()
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
void Texture::setEnforcePotImages(bool enforcePotImages)
{
	m_enforcePotImages = enforcePotImages;
}

void Texture::addManagedTexture(Application* app, Texture* texture)
{
	m_managedTextures[app].push_back(texture);
}

/** Clears all managed textures. This is an internal method. Do not use it! */
void Texture::clearAllTextures(Application* app)
{
	m_managedTextures.erase(app);
}

/** Invalidate all managed textures. This is an internal method. Do not use it! */
void Texture::invalidateAllTextures(Application* app)
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
void setAssetManager(AssetManager manager)
{
Texture.assetManager = manager;
}
*/

std::wstring Texture::getManagedStatus()
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