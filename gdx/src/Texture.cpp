	#include "stdafx.h"
#include "Texture.h"
#include "MipMapGenerator.h"

bool Texture::m_enforcePotImages = true;

//TODO: unused???
bool m_useHWMipMap = true;

//TODO:
//AssetManager assetManager;
Texture::TextureMap Texture::m_managedTextures;

const Texture::TextureFilter Texture::TextureFilter::Nearest(GL_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::Linear(GL_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMap(GL_LINEAR_MIPMAP_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMapNearestNearest(GL_NEAREST_MIPMAP_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::MipMapLinearNearest(GL_LINEAR_MIPMAP_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::MipMapNearestLinear(GL_NEAREST_MIPMAP_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMapLinearLinear(GL_LINEAR_MIPMAP_LINEAR);

unsigned int Texture::m_buffer = -1;

Texture::TextureFilter::TextureFilter()
{
	m_glEnum = GL_NEAREST;
}

Texture::TextureFilter::TextureFilter(int glEnum)
	:m_glEnum(glEnum)
{
}

bool Texture::TextureFilter::isMipMap()
{
	return m_glEnum != GL_NEAREST && m_glEnum != GL_LINEAR;
}

int Texture::TextureFilter::getGLEnum()
{
	return m_glEnum;
}

const Texture::TextureWrap Texture::TextureWrap::ClampToEdge(GL_CLAMP_TO_EDGE);
const Texture::TextureWrap Texture::TextureWrap::Repeat(GL_REPEAT);

Texture::TextureWrap::TextureWrap()
{
	m_glEnum = GL_CLAMP_TO_EDGE;
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
	if(m_data)
	{
		delete m_data;
		m_data = NULL;
	}
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
	if(file.name().find( ".etc1") != std::string::npos)
	{
		create(new ETC1TextureData(file, useMipMaps));
	}
	else
	{
		create(new FileTextureData(file, NULL, format, useMipMaps));
	}
}

Texture::Texture()
{
	init();
}

Texture::Texture(const std::string& internalPath)
{
	init();
	FileHandle hFile = Gdx.files->internalHandle(internalPath);
	init( hFile, Pixmap::Format::Unknown, false);
}

Texture::Texture(const FileHandle& file)
{
	init();
	init(file, Pixmap::Format::Unknown, false);
}

Texture::Texture(const FileHandle& file, bool useMipMaps)
{
	init();
	init(file, Pixmap::Format::Unknown, useMipMaps);
}


Texture::Texture(const FileHandle& file, Pixmap::Format format, bool useMipMaps)
{
	init();
	init(file, format, useMipMaps);
}

Texture::Texture(Pixmap* pixmap)
{
	init();
	init(new PixmapTextureData(pixmap, Pixmap::Format::Unknown, false, false));
}

Texture::Texture(Pixmap* pixmap, bool useMipMaps)
{
	init();
	init(new PixmapTextureData(pixmap, Pixmap::Format::Unknown, useMipMaps, false));
}

Texture::Texture(Pixmap* pixmap, Pixmap::Format format, bool useMipMaps)
{
	init();
	init(new PixmapTextureData(pixmap, format, useMipMaps, false));
}

Texture::Texture(int width, int height, Pixmap::Format format)
{
	init();
	init(new PixmapTextureData(new Pixmap(width, height, format), Pixmap::Format::Unknown, false, true));
}

Texture::Texture(TextureData* data)
{
	init();
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
	glGenTextures(1, &m_buffer);
	return m_buffer;
}

void Texture::load(TextureData* data)
{
	if( m_data != NULL && data->isManaged() != m_data->isManaged())
		throw GdxRuntimeException("New data must have the same managed status as the old data");

	m_data = data;

	if(!data->isPrepared()) 
		data->prepare();

	if(data->getType() == TextureData::PixmapTexture)
	{
		Pixmap* pixmap = data->consumePixmap();
		uploadImageData(pixmap);
		if(data->disposePixmap()) 
		{
			//pixmap->dispose();

			//TODO: review this! cannot delete now the pixmap. 
			//if I do it getWidth and Height will not work
			//delete pixmap;
		}
		setFilter(m_minFilter, m_magFilter);
		setWrap(m_uWrap, m_vWrap);
	}

	if(data->getType() == TextureData::CompressedTexture)
	{
		glBindTexture(GL_TEXTURE_2D, m_glHandle);
		data->consumeCompressedData();
		setFilter(m_minFilter, m_magFilter);
		setWrap(m_uWrap, m_vWrap);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::uploadImageData(Pixmap* pixmap)
{
	if(m_enforcePotImages && Gdx.getGlVersion() != GL_VERSION_20
		&& (!MathUtils::isPowerOfTwo(m_data->getWidth()) || !MathUtils::isPowerOfTwo(m_data->getHeight())))
	{
		throw GdxRuntimeException("Texture width and height must be powers of two");
	}

	bool disposePixmap = false;
	if(m_data->getFormat() != pixmap->getFormat())
	{
		Pixmap* tmp = new Pixmap(pixmap->getWidth(), pixmap->getHeight(), m_data->getFormat());
		Pixmap::Blending blend = Pixmap::getBlending();
		Pixmap::setBlending(Pixmap::None);
		tmp->drawPixmap(pixmap, 0, 0, 0, 0, pixmap->getWidth(), pixmap->getHeight());
		Pixmap::setBlending(blend);
		pixmap = tmp;
		disposePixmap = true;
	}

	glBindTexture(GL_TEXTURE_2D, m_glHandle);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if(m_data->useMipMaps())
	{
		MipMapGenerator::generateMipMap(pixmap, pixmap->getWidth(), pixmap->getHeight(), disposePixmap);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, pixmap->getGLInternalFormat(), pixmap->getWidth(), pixmap->getHeight(), 0, pixmap->getGLFormat(), pixmap->getGLType(), pixmap->getPixels());
		if(disposePixmap)
		{
			pixmap->dispose();
			delete pixmap;
		}
	}
}

/** Used internally to reload after context loss. Creates a new GL handle then calls {@link #load(TextureData)}. */
void Texture::reload()
{
	if(!m_data->isManaged()) throw GdxRuntimeException("Tried to reload unmanaged Texture");
	m_glHandle = createGLHandle();
	load(m_data);
}

/** Binds this texture. The texture will be bound to the currently active texture unit specified via
* {@link GLCommon#glActiveTexture(int)}. */
void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_glHandle);
}

/** Binds the texture to the given texture unit. Sets the currently active texture unit via
* {@link GLCommon#glActiveTexture(int)}.
* @param unit the unit (0 to MAX_TEXTURE_UNITS). */
void Texture::bind(int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_glHandle);
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
		throw GdxRuntimeException("can't draw to a managed texture");

	glBindTexture(GL_TEXTURE_2D, m_glHandle);
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, pixmap->getWidth(), pixmap->getHeight(), pixmap->getGLFormat(),
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
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLfloat)u.getGLEnum());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLfloat)v.getGLEnum());
}

void Texture::setFilter(TextureFilter minFilter, TextureFilter magFilter)
{
	m_minFilter = minFilter;
	m_magFilter = magFilter;
	bind();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)minFilter.getGLEnum());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)magFilter.getGLEnum());
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
	if(Gdx.isGLInitialised())
	{
		glDeleteTextures(1, &m_glHandle);
		GLenum test = glGetError();
		if(test != GL_NO_ERROR)
			throw GdxRuntimeException("cannot delete texture");
	}
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
	void finishedLoading(AssetManager assetManager, const std::string& fileName, Class type)
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

std::string Texture::getManagedStatus()
{
	std::stringstream ret;
	ret << "Managed textures/app: { ";
	for(TextureMapIterator it = m_managedTextures.begin(); it != m_managedTextures.end(); it++)
	{
		ret << it->second.size() << " ";
	}
	ret << "}";
	return ret.str();
}