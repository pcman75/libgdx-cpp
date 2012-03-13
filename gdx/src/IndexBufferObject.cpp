#include "StdAfx.h"
#include "IndexBufferObject.h"

IndexBufferObject::IndexBufferObject(bool isStatic) 
{
	init();
	m_usage = isStatic ? GL11::GDX_GL_STATIC_DRAW : GL11::GDX_GL_DYNAMIC_DRAW;
}

void IndexBufferObject::init()
{
	m_isDirty = true;
	m_isBound = false;
	m_buffer = NULL;
	m_numIndices = 0;
	m_isDirect = true;

	m_bufferHandle = createBufferObject();
	m_usage = GL11::GDX_GL_STATIC_DRAW;
}

IndexBufferObject::~IndexBufferObject(void)
{
	if(m_buffer)
	{
		delete[] m_buffer;
		m_buffer = NULL;
	}
}

int IndexBufferObject::createBufferObject () 
{
    glGenBuffers(1, &m_bufferHandle);

	return m_bufferHandle;
}

int IndexBufferObject::getNumIndices ()
{
	return m_numIndices;
}

void IndexBufferObject::setIndices (const short* indices, int count) 
{
	m_numIndices = count;
	m_buffer = new short[m_numIndices];
	m_isDirty = true;

	memcpy(m_buffer, indices, count * sizeof(indices[0]));

	if(m_isBound)
	{
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices, m_buffer, m_usage);
		m_isDirty = false;
	}
}

short* IndexBufferObject::getBuffer () {
	m_isDirty = true;
	return m_buffer;
}

void IndexBufferObject::bind () 
{
	if (m_bufferHandle == 0) throw new GdxRuntimeException("buuh");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferHandle);
    if (m_isDirty) 
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(GLshort), m_buffer, m_usage);
        m_isDirty = false;
    }
	m_isBound = true;
}

void IndexBufferObject::unbind () 
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	m_isBound = false;
}

void IndexBufferObject::invalidate () 
{
	m_bufferHandle = createBufferObject();
	m_isDirty = true;
}

void IndexBufferObject::dispose () 
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_bufferHandle);
    m_bufferHandle = 0;
}