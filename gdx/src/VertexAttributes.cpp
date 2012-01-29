#include "StdAfx.h"
#include "VertexAttributes.h"


/** Constructor, sets the vertex attributes in a specific order */
VertexAttributes::VertexAttributes(const VertexAttribute* attributes, int attributesLength) 
{
	if (attributesLength < 1) 
		throw new GdxRuntimeException("attributes must be >= 1");
	m_attributesLength = attributesLength;
	m_attributes = new VertexAttribute[attributesLength];

	for (int i = 0; i < attributesLength; i++)
		m_attributes[i] = attributes[i];

	checkValidity();
	m_vertexSize = calculateOffsets();
}

void VertexAttributes::checkValidity () 
{
	bool pos = false;
	bool cols = false;
	bool nors = false;

	for (int i = 0; i < m_attributesLength; i++) 
	{
		VertexAttribute attribute = m_attributes[i];
		if (attribute.usage == Position) 
		{
			if (pos) 
				throw new GdxRuntimeException("two position attributes were specified");
			pos = true;
		}

		if (attribute.usage == Normal) 
		{
			if (nors) 
				throw new GdxRuntimeException("two normal attributes were specified");
		}

		if (attribute.usage == Color || attribute.usage == ColorPacked) 
		{
			if (attribute.numComponents != 4) 
				throw new GdxRuntimeException("color attribute must have 4 components");

			if (cols) 
				throw new GdxRuntimeException("two color attributes were specified");
			cols = true;
		}
	}

	if (pos == false) 
		throw new GdxRuntimeException("no position attribute was specified");
}

int VertexAttributes::calculateOffsets ()
{
	int count = 0;
	for (int i = 0; i < m_attributesLength; i++) 
	{
		VertexAttribute attribute = m_attributes[i];
		attribute.offset = count;
		if (attribute.usage == ColorPacked)
			count += 4;
		else
			count += 4 * attribute.numComponents;
	}

	return count;
}

/** @return the number of attributes */
int VertexAttributes::size()
{
	return m_attributesLength;
}

/** @param index the index
* @return the VertexAttribute at the given index */
const VertexAttribute& VertexAttributes::get (int index) 
{
	return m_attributes[index];
}

int VertexAttributes::vertexSize() const
{
	return m_vertexSize;
}

std::wstring VertexAttributes::toString () 
{
	std::wstringstream ret;
	for (int i = 0; i < m_attributesLength; i++) 
	{
		ret << m_attributes[i].alias;
		ret << L", ";
		ret << m_attributes[i].usage;
		ret << L", ";
		ret << m_attributes[i].numComponents;
		ret << L", ";
		ret << m_attributes[i].offset;
		ret << L"\n";
	}
	return ret.str();
}