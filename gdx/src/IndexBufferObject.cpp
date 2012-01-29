#include "StdAfx.h"
#include "IndexBufferObject.h"

IndexBufferObject::IndexBufferObject(bool isStatic, int numIndices) 
{
	init(numIndices);
	m_usage = isStatic ? GL11::GDX_GL_STATIC_DRAW : GL11::GDX_GL_DYNAMIC_DRAW;
}

IndexBufferObject::IndexBufferObject (int numIndices) 
{
	init(numIndices);
}

void IndexBufferObject::init(int numIndices)
{
	m_isDirty = true;
	m_isBound = false;
	m_buffer = new short[numIndices];
	m_numIndices = numIndices;
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
	if (Gdx.isGL20Available()) 
	{
		Gdx.gl20->glGenBuffers(1, &m_bufferHandle);
	} 
	else if (Gdx.isGL11Available()) 
	{
		Gdx.gl11->glGenBuffers(1, &m_bufferHandle);
	}
	else
		m_bufferHandle = 0;

	return m_bufferHandle;
}

int IndexBufferObject::getNumIndices ()
{
	return m_numIndices;
}

void IndexBufferObject::setIndices (const short* indices, int offset, int count) 
{
	m_isDirty = true;
	if(offset + count > m_numIndices)
		throw new GdxRuntimeException("Indices buffer overrun. Check offset and count");

	memcpy(m_buffer, indices + offset, count);

	if(m_isBound)
	{
		if (Gdx.isGL11Available()) 
		{
			GL11& gl = *Gdx.gl11;
			gl.glBufferData(GL11::GDX_GL_ELEMENT_ARRAY_BUFFER, m_numIndices, m_buffer, m_usage);
		} 
		else if (Gdx.isGL20Available())
		{
			GL20& gl = *Gdx.gl20;
			gl.glBufferData(GL20::GDX_GL_ELEMENT_ARRAY_BUFFER, m_numIndices, m_buffer, m_usage);
		}
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

	//TODO: Why I don't call always GL11::glBindBuffer?
	//maybe in Java it matters but here I don't think so.
	//I only have same pure C calls underneath in both classes
	if (Gdx.isGL11Available()) 
	{
		GL11& gl = *Gdx.gl11;
		gl.glBindBuffer(GL11::GDX_GL_ELEMENT_ARRAY_BUFFER, m_bufferHandle);
		if (m_isDirty) 
		{
			gl.glBufferData(GL11::GDX_GL_ELEMENT_ARRAY_BUFFER, m_numIndices, m_buffer, m_usage);
			m_isDirty = false;
		}
	} 
	else 
	{
		GL20& gl = *Gdx.gl20;
		gl.glBindBuffer(GL20::GDX_GL_ELEMENT_ARRAY_BUFFER, m_bufferHandle);
		if (m_isDirty) 
		{
			gl.glBufferData(GL20::GDX_GL_ELEMENT_ARRAY_BUFFER, m_numIndices, m_buffer, m_usage);
			m_isDirty = false;
		}
	}
	m_isBound = true;
}

void IndexBufferObject::unbind () 
{
	if (Gdx.isGL11Available()) 
	{
		Gdx.gl11->glBindBuffer(GL11::GDX_GL_ELEMENT_ARRAY_BUFFER, 0);
	} 
	else if (Gdx.isGL20Available()) 
	{
		Gdx.gl20->glBindBuffer(GL20::GDX_GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	m_isBound = false;
}

void IndexBufferObject::invalidate () 
{
	m_bufferHandle = createBufferObject();
	m_isDirty = true;
}

void IndexBufferObject::dispose () 
{
	if (Gdx.isGL20Available()) 
	{
		GL20& gl = *Gdx.gl20;
		gl.glBindBuffer(GL20::GDX_GL_ELEMENT_ARRAY_BUFFER, 0);
		gl.glDeleteBuffers(1, &m_bufferHandle);
		m_bufferHandle = 0;
	} 
	else if (Gdx.isGL11Available()) 
	{
		GL11& gl = *Gdx.gl11;
		gl.glBindBuffer(GL11::GDX_GL_ELEMENT_ARRAY_BUFFER, 0);
		gl.glDeleteBuffers(1, &m_bufferHandle);
		m_bufferHandle = 0;
	}
}