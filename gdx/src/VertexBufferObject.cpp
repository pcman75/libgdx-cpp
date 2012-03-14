#include "StdAfx.h"
#include "VertexBufferObject.h"
#include "Gdx.h"

/** Constructs a new interleaved VertexBufferObject.
*
* @param isStatic whether the vertex data is static.
* @param numVertices the maximum number of vertices
* @param attributes the {@link VertexAttributes}. */
VertexBufferObject::VertexBufferObject(bool isStatic, const VertexAttributes& attributes)
	:m_attributes(attributes), m_isBound(false), m_numVertices(0), m_isStatic(isStatic), m_buffer(NULL), m_isDirty(false)
{
	createBufferObject();
	m_usage = isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
}

VertexBufferObject::VertexBufferObject(bool isStatic, const VertexAttribute attributes[], int attributesLength)
	:m_attributes(attributes, attributesLength), m_isBound(false), m_numVertices(0), m_isStatic(isStatic), m_buffer(NULL), m_isDirty(false)
{
	createBufferObject();
	m_usage = isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
}

void VertexBufferObject::createBufferObject()
{
	if(Gdx.getGLVersion() == GL_VERSION_20)
		glGenBuffers(1, &m_bufferHandle);
	else
        throw new GdxRuntimeException("OpenGL 1.x not yet supported");
}

VertexBufferObject::~VertexBufferObject()
{
    dispose();
	if(m_buffer)
	{
		delete[] m_buffer;
		m_buffer = NULL;
	}
}

const VertexAttributes& VertexBufferObject::getAttributes()
{
	return m_attributes;
}

int VertexBufferObject::getNumVertices () 
{
	return m_numVertices;
}


float* VertexBufferObject::getBuffer()
{
	m_isDirty = true;
	return m_buffer;
}

void VertexBufferObject::setVertices(const float* vertices, int count)
{
	int bufferSizeInBytes = sizeof(float) * count;
	m_numVertices = bufferSizeInBytes / m_attributes.vertexSize();
	m_buffer = new float[bufferSizeInBytes];
	memcpy(m_buffer, vertices, bufferSizeInBytes);
	m_isDirty = true;
	
	if(m_isBound)
	{
		if(Gdx.getGLVersion() == GL_VERSION_20)
		{
			glBufferData(GL_ARRAY_BUFFER, bufferSizeInBytes, m_buffer, m_usage);
		}
		else
		{
            throw new GdxRuntimeException("OpenGL 1.x not yet supported");
		}
		m_isDirty = false;
	}
}



void VertexBufferObject::bind()
{
    throw new GdxRuntimeException("OpenGL 1.x not yet supported");
/*
	int bufferSizeInBytes = m_attributes.vertexSize() * m_numVertices;

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferHandle);
	if(m_isDirty)
	{
		glBufferData(GL_ARRAY_BUFFER, bufferSizeInBytes, m_buffer, m_usage);
		m_isDirty = false;
	}

	int textureUnit = 0;
	int numAttributes = m_attributes.size();
	int colorType = GL_FLOAT;

	for(int i = 0; i < numAttributes; i++)
	{
		const VertexAttribute& attribute = m_attributes.get(i);

		switch(attribute.usage)
		{
		case VertexAttributes::Position:
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(attribute.numComponents, GL_FLOAT, m_attributes.vertexSize(), (void*)attribute.offset);
			break;

		case VertexAttributes::ColorPacked:
			colorType = GL_UNSIGNED_BYTE;
			//don't break leave it to go trough, only color type is different
		case VertexAttributes::Color:
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(attribute.numComponents, colorType, m_attributes.vertexSize(), (void*)attribute.offset);
			break;

		case VertexAttributes::Normal:
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, m_attributes.vertexSize(), (void*)attribute.offset);
			break;

		case VertexAttributes::TextureCoordinates:
			glClientActiveTexture(GL_TEXTURE0 + textureUnit);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(attribute.numComponents, GL_FLOAT, m_attributes.vertexSize(), (void*)attribute.offset);
			textureUnit++;
			break;

		default:
			throw new GdxRuntimeException("unkown vertex attribute type");
		}
	}

	m_isBound = true;
 */
}

/** Binds this VertexBufferObject for rendering via glDrawArrays or glDrawElements
*
* @param shader the shader */
void VertexBufferObject::bind(ShaderProgram* shader)
{
	int bufferSizeInBytes = m_attributes.vertexSize() * m_numVertices;

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferHandle);
	if(m_isDirty)
	{
		glBufferData(GL_ARRAY_BUFFER, bufferSizeInBytes, m_buffer, m_usage);
		m_isDirty = false;
	}

	int numAttributes = m_attributes.size();
	for(int i = 0; i < numAttributes; i++)
	{
		VertexAttribute attribute = m_attributes.get(i);
		shader->enableVertexAttribute(attribute.alias);
		int colorType = GL_FLOAT;
		bool normalize = false;
		if(attribute.usage == VertexAttributes::ColorPacked)
		{
			colorType = GL_UNSIGNED_BYTE;
			normalize = true;
		}
		shader->setVertexAttribute(attribute.alias, attribute.numComponents, colorType, normalize, m_attributes.vertexSize(),
			attribute.offset);
	}
	m_isBound = true;
}


void VertexBufferObject::unbind()
{
    throw new GdxRuntimeException("OpenGL 1.x not yet supported");
/*
	int textureUnit = 0;
	int numAttributes = m_attributes.size();

	for(int i = 0; i < numAttributes; i++)
	{
		VertexAttribute attribute = m_attributes.get(i);
		switch(attribute.usage)
		{
		case VertexAttributes::Position:
			break; // no-op, we also need a position bound in gles
		case VertexAttributes::Color:
		case VertexAttributes::ColorPacked:
			glDisableClientState(GL_COLOR_ARRAY);
			break;
		case VertexAttributes::Normal:
			glDisableClientState(GL_NORMAL_ARRAY);
			break;
		case VertexAttributes::TextureCoordinates:
			glClientActiveTexture(GL_TEXTURE0 + textureUnit);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			textureUnit++;
			break;
		default:
			throw new GdxRuntimeException("unkown vertex attribute type");
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_isBound = false;
*/
}

/** Unbinds this VertexBufferObject.
*
* @param shader the shader */

void VertexBufferObject::unbind(ShaderProgram* shader)
{
	int numAttributes = m_attributes.size();
	for(int i = 0; i < numAttributes; i++)
	{
		const VertexAttribute& attribute = m_attributes.get(i);
		shader->disableVertexAttribute(attribute.alias);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_isBound = false;
}

/** Invalidates the VertexBufferObject so a new OpenGL m_buffer handle is created. Use this in case of a context loss. */
void VertexBufferObject::invalidate()
{
	createBufferObject();
	m_isDirty = true;
}

/** Disposes of all resources this VertexBufferObject uses. */

void VertexBufferObject::dispose()
{
	//TODO: check for multiple dispose
	if(Gdx.getGLVersion() == GL_VERSION_20)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &m_bufferHandle);
		m_bufferHandle = 0;
	}
	else if(Gdx.getGLVersion() == GL_VERSION_11)
	{
        throw new GdxRuntimeException("OpenGL 1.x not yet supported");
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &m_bufferHandle);
		m_bufferHandle = 0;
	}
};
