#include "stdafx.h"
#include "GdxRuntimeException.h"

GdxRuntimeException::GdxRuntimeException(const std::string& message)
{
	m_message = message;
}

const char* GdxRuntimeException::what() const throw()
{
	return m_message.c_str();
}

GdxRuntimeException::~GdxRuntimeException(void) throw()
{
}
