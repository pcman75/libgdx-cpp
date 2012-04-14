#include "StdAfx.h"
#include "VertexAttribute.h"


VertexAttribute::VertexAttribute(int usage, int numComponents, const std::string& alias)
	:usage(usage), numComponents(numComponents), alias(alias), offset(0)
{
}

VertexAttribute::VertexAttribute()
	:usage(-1), numComponents(-1)
{
}

VertexAttribute::~VertexAttribute(void)
{
}
