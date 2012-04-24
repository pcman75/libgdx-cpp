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
#include "StdAfx.h"
#include "VertexArray.h"
#include "VertexAttributes.h"
#include "Gdx.h"

/** Constructs a new interleaved VertexArray
* 
* @param numVertices the number of vertices
* @param attributes the {@link VertexAttributes} */
VertexArray::VertexArray(const VertexAttributes& attributes)
	:m_attributes(attributes), m_isBound(false), m_numVertices(0), m_buffer(NULL)
{
}

VertexArray::VertexArray(const VertexAttribute attributes[], int attributesLength)
	:m_attributes(attributes, attributesLength), m_isBound(false), m_numVertices(0), m_buffer(NULL)
{
}



void VertexArray::dispose() 
{
}

float* VertexArray::getBuffer() 
{
	return m_buffer;
}

int VertexArray::getNumVertices () 
{
	return m_numVertices;
}


void VertexArray::setVertices(const float* vertices, int count) 
{
	m_numVertices = count;
  if( NULL != m_buffer)
  {
    delete [] m_buffer;
    m_buffer = NULL;
  }
	m_buffer = new float[sizeof(float) * count];
	memcpy(m_buffer, vertices, count * sizeof(float));
}


void VertexArray::bind () 
{
	int textureUnit = 0;
	char* byteBuffer = (char*)m_buffer;
	int colorType = GL_FLOAT;

	for (int i = 0; i < m_attributes.size(); i++) 
	{
		VertexAttribute attribute = m_attributes.get(i);
		byteBuffer = (char*)m_buffer + attribute.offset;

		switch (attribute.usage) 
		{
		case VertexAttributes::Position:
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(attribute.numComponents, GL_FLOAT, m_attributes.vertexSize(), byteBuffer);
			break;

		case VertexAttributes::ColorPacked:
		case VertexAttributes::Color:
			if (attribute.usage == VertexAttributes::ColorPacked) 
				colorType = GL_UNSIGNED_BYTE;
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(attribute.numComponents, colorType, m_attributes.vertexSize(), byteBuffer);
			break;

		case VertexAttributes::Normal:
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, m_attributes.size(), byteBuffer);
			break;

		case VertexAttributes::TextureCoordinates:
			glClientActiveTexture(GL_TEXTURE0 + textureUnit);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(attribute.numComponents, GL_FLOAT, m_attributes.vertexSize(), byteBuffer);
			textureUnit++;
			break;

		default:
			throw GdxRuntimeException("unkown vertex attribute type");
		}
	}

	m_isBound = true;
}


void VertexArray::unbind () 
{
	int textureUnit = 0;
	int numAttributes = m_attributes.size();

	for (int i = 0; i < numAttributes; i++) 
	{
		VertexAttribute attribute = m_attributes.get(i);
		switch (attribute.usage) {
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
			throw GdxRuntimeException("unkown vertex attribute type");
		}
	}
	m_isBound = false;
}

const VertexAttributes& VertexArray::getAttributes() 
{
	return m_attributes;
}

VertexArray::~VertexArray(void)
{
	if(m_buffer)
	{
		delete[] m_buffer;
		m_buffer = NULL;
	}
}

