#include "stdafx.h"
#include "MipMapGenerator.h"
#include "Gdx.h"

bool MipMapGenerator::m_useHWMipMap = true;

void MipMapGenerator::setUseHardwareMipMap(bool useHWMipMap)
{
	m_useHWMipMap = useHWMipMap;
}

/** Sets the image data of the {@link Texture} based on the {@link Pixmap}. The texture must be bound for this to work. If
* <code>disposePixmap</code> is true, the pixmap will be disposed at the end of the method.
* @param pixmap the Pixmap
* @param disposePixmap whether to dispose the Pixmap after upload */
void MipMapGenerator::generateMipMap(Pixmap* pixmap, int textureWidth, int textureHeight, bool disposePixmap)
{
	if(!m_useHWMipMap)
	{
		generateMipMapCPU(pixmap, textureWidth, textureHeight, disposePixmap);
		return;
	}

	//TODO: need to differenciate between iOS and Android?
	if(Gdx.app->getType() == Application::Android || Gdx.app->getType() == Application::iOS)
	{
		if(Gdx.graphics->isGL20Available())
			generateMipMapGLES20(pixmap, disposePixmap);
		else
			generateMipMapCPU(pixmap, textureWidth, textureHeight, disposePixmap);
	}
	else
	{
		generateMipMapDesktop(pixmap, textureWidth, textureHeight, disposePixmap);
	}
}

void MipMapGenerator::generateMipMapGLES20(Pixmap* pixmap, bool disposePixmap)
{
    glTexImage2D(GL_TEXTURE_2D, 0, pixmap->getGLInternalFormat(), pixmap->getWidth(), pixmap->getHeight(), 0, pixmap->getGLFormat(), pixmap->getGLType(), pixmap->getPixels());
    glGenerateMipmap(GL_TEXTURE_2D);
	if(disposePixmap)
	{
		pixmap->dispose();
		delete pixmap;
		pixmap = NULL;
	}
}

void MipMapGenerator::generateMipMapDesktop(Pixmap* pixmap, int textureWidth, int textureHeight, bool disposePixmap)
{
	if(Gdx.graphics->isGL20Available() && 
		(Gdx.graphics->supportsExtension("GL_ARB_framebuffer_object") || Gdx.graphics->supportsExtension("GL_EXT_framebuffer_object")))
	{
		glTexImage2D(GL_TEXTURE_2D, 0, pixmap->getGLInternalFormat(), pixmap->getWidth(), pixmap->getHeight(), 0, pixmap->getGLFormat(), pixmap->getGLType(), pixmap->getPixels());
		glGenerateMipmap(GL_TEXTURE_2D);

		if(disposePixmap)
	{
		pixmap->dispose();
		delete pixmap;
		pixmap = NULL;
	}
	}
	else if(Gdx.graphics->supportsExtension("GL_SGIS_generate_mipmap"))
	{
		if((Gdx.getGlVersion() != GL_VERSION_20) && textureWidth != textureHeight)
			throw GdxRuntimeException("texture width and height must be square when using mipmapping in OpenGL ES 1.x");
		glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_HINT, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, pixmap->getGLInternalFormat(), pixmap->getWidth(), pixmap->getHeight(), 0, pixmap->getGLFormat(), pixmap->getGLType(), pixmap->getPixels());

		if(disposePixmap)
        {
            pixmap->dispose();
            delete pixmap;
            pixmap = NULL;
        }
	}
	else
	{
		generateMipMapCPU(pixmap, textureWidth, textureHeight, disposePixmap);
	}
}


//TODO: Pixmap is always disposed???
void MipMapGenerator::generateMipMapCPU(Pixmap* pixmap, int textureWidth, int textureHeight, bool disposePixmap)
{
	glTexImage2D(GL_TEXTURE_2D, 0, pixmap->getGLInternalFormat(), pixmap->getWidth(), pixmap->getHeight(), 0,
                 pixmap->getGLFormat(), pixmap->getGLType(), pixmap->getPixels());
	if((Gdx.getGlVersion() != GL_VERSION_20) && textureWidth != textureHeight)
		throw GdxRuntimeException("texture width and height must be square when using mipmapping.");

	int width = pixmap->getWidth() / 2;
	int height = pixmap->getHeight() / 2;
	int level = 1;
	Pixmap::Blending blending = Pixmap::getBlending();
	Pixmap::setBlending(Pixmap::None);
	while(width > 0 && height > 0)
	{
		Pixmap* tmp = new Pixmap(width, height, pixmap->getFormat());
		tmp->drawPixmap(pixmap, 0, 0, pixmap->getWidth(), pixmap->getHeight(), 0, 0, width, height);
		if(level > 1 || disposePixmap)
		{
			pixmap->dispose();
			delete pixmap;
		}
		
		pixmap = tmp;

		glTexImage2D(GL_TEXTURE_2D, level, pixmap->getGLInternalFormat(), pixmap->getWidth(), pixmap->getHeight(), 0, pixmap->getGLFormat(), pixmap->getGLType(), pixmap->getPixels());

		width = pixmap->getWidth() / 2;
		height = pixmap->getHeight() / 2;
		level++;
	}
	Pixmap::setBlending(blending);
	
	pixmap->dispose();
	delete pixmap;
}

