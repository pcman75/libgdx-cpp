#include "StdAfx.h"
#include "VertexBufferObject.h"
#include "GL11.h"
#include "GL20.h"
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
	m_usage = isStatic ? GL11::GDX_GL_STATIC_DRAW : GL11::GDX_GL_DYNAMIC_DRAW;
}

void VertexBufferObject::createBufferObject()
{
	if(Gdx.gl20 != NULL)
		Gdx.gl20->glGenBuffers(1, &m_bufferHandle);
	else
		Gdx.gl11->glGenBuffers(1, &m_bufferHandle);
}

VertexBufferObject::~VertexBufferObject()
{
	//TODO: call dispose???
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
		if(Gdx.gl20 != NULL)
		{
			GL20* gl = Gdx.gl20;
			gl->glBufferData(GL20::GDX_GL_ARRAY_BUFFER, bufferSizeInBytes, m_buffer, m_usage);
		}
		else
		{
			GL11* gl = Gdx.gl11;
			gl->glBufferData(GL11::GDX_GL_ARRAY_BUFFER, bufferSizeInBytes, m_buffer, m_usage);
		}
		m_isDirty = false;
	}
}



void VertexBufferObject::bind()
{
	GL11* gl = Gdx.gl11;
	int bufferSizeInBytes = m_attributes.vertexSize() * m_numVertices;

	gl->glBindBuffer(GL11::GDX_GL_ARRAY_BUFFER, m_bufferHandle);
	if(m_isDirty)
	{
		gl->glBufferData(GL11::GDX_GL_ARRAY_BUFFER, bufferSizeInBytes, m_buffer, m_usage);
		m_isDirty = false;
	}

	int textureUnit = 0;
	int numAttributes = m_attributes.size();
	int colorType = GL10::GDX_GL_FLOAT;

	for(int i = 0; i < numAttributes; i++)
	{
		const VertexAttribute& attribute = m_attributes.get(i);

		switch(attribute.usage)
		{
		case VertexAttributes::Position:
			gl->glEnableClientState(GL11::GDX_GL_VERTEX_ARRAY);
			gl->glVertexPointer(attribute.numComponents, GL10::GDX_GL_FLOAT, m_attributes.vertexSize(), (void*)attribute.offset);
			break;

		case VertexAttributes::ColorPacked:
			colorType = GL11::GDX_GL_UNSIGNED_BYTE;
			//don't break leave it to go trough, only color type is different
		case VertexAttributes::Color:
			gl->glEnableClientState(GL10::GDX_GL_COLOR_ARRAY);
			gl->glColorPointer(attribute.numComponents, colorType, m_attributes.vertexSize(), (void*)attribute.offset);
			break;

		case VertexAttributes::Normal:
			gl->glEnableClientState(GL10::GDX_GL_NORMAL_ARRAY);
			gl->glNormalPointer(GL10::GDX_GL_FLOAT, m_attributes.vertexSize(), (void*)attribute.offset);
			break;

		case VertexAttributes::TextureCoordinates:
			gl->glClientActiveTexture(GL10::GDX_GL_TEXTURE0 + textureUnit);
			gl->glEnableClientState(GL10::GDX_GL_TEXTURE_COORD_ARRAY);
			gl->glTexCoordPointer(attribute.numComponents, GL10::GDX_GL_FLOAT, m_attributes.vertexSize(), (void*)attribute.offset);
			textureUnit++;
			break;

		default:
			throw new GdxRuntimeException("unkown vertex attribute type");
		}
	}

	m_isBound = true;
}

/** Binds this VertexBufferObject for rendering via glDrawArrays or glDrawElements
*
* @param shader the shader */
void VertexBufferObject::bind(ShaderProgram& shader)
{
	GL20* gl = Gdx.gl20;
	int bufferSizeInBytes = m_attributes.vertexSize() * m_numVertices;

	gl->glBindBuffer(GL20::GDX_GL_ARRAY_BUFFER, m_bufferHandle);
	if(m_isDirty)
	{
		gl->glBufferData(GL20::GDX_GL_ARRAY_BUFFER, bufferSizeInBytes, m_buffer, m_usage);
		m_isDirty = false;
	}

	int numAttributes = m_attributes.size();
	for(int i = 0; i < numAttributes; i++)
	{
		VertexAttribute attribute = m_attributes.get(i);
		shader.enableVertexAttribute(attribute.alias);
		int colorType = GL20::GDX_GL_FLOAT;
		bool normalize = false;
		if(attribute.usage == VertexAttributes::ColorPacked)
		{
			colorType = GL20::GDX_GL_UNSIGNED_BYTE;
			normalize = true;
		}
		shader.setVertexAttribute(attribute.alias, attribute.numComponents, colorType, normalize, m_attributes.vertexSize(),
			attribute.offset);
	}
	m_isBound = true;
}


void VertexBufferObject::unbind()
{
	GL11* gl = Gdx.gl11;
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
			gl->glDisableClientState(GL11::GDX_GL_COLOR_ARRAY);
			break;
		case VertexAttributes::Normal:
			gl->glDisableClientState(GL11::GDX_GL_NORMAL_ARRAY);
			break;
		case VertexAttributes::TextureCoordinates:
			gl->glClientActiveTexture(GL11::GDX_GL_TEXTURE0 + textureUnit);
			gl->glDisableClientState(GL11::GDX_GL_TEXTURE_COORD_ARRAY);
			textureUnit++;
			break;
		default:
			throw new GdxRuntimeException("unkown vertex attribute type");
		}
	}
	gl->glBindBuffer(GL11::GDX_GL_ARRAY_BUFFER, 0);
	m_isBound = false;
}

/** Unbinds this VertexBufferObject.
*
* @param shader the shader */

void VertexBufferObject::unbind(ShaderProgram& shader)
{
	GL20* gl = Gdx.gl20;
	int numAttributes = m_attributes.size();
	for(int i = 0; i < numAttributes; i++)
	{
		const VertexAttribute& attribute = m_attributes.get(i);
		shader.disableVertexAttribute(attribute.alias);
	}
	gl->glBindBuffer(GL20::GDX_GL_ARRAY_BUFFER, 0);
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
	if(Gdx.gl20)
	{
		GL20* gl = Gdx.gl20;
		gl->glBindBuffer(GL20::GDX_GL_ARRAY_BUFFER, 0);
		gl->glDeleteBuffers(1, &m_bufferHandle);
		m_bufferHandle = 0;
	}
	else if(Gdx.gl11)
	{
		GL11* gl = Gdx.gl11;
		gl->glBindBuffer(GL11::GDX_GL_ARRAY_BUFFER, 0);
		gl->glDeleteBuffers(1, &m_bufferHandle);
		m_bufferHandle = 0;
	}
};
