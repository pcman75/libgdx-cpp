#include "StdAfx.h"
#include "GdxRuntimeException.h"

GdxRuntimeException::GdxRuntimeException(const std::string& message)
{
	m_message = message;
}

GdxRuntimeException::GdxRuntimeException(const std::wstring& message)
{
	size_t messageLen = message.length();
	char* buf = new char[messageLen];
	wcstombs(buf, message.c_str(), messageLen);
	m_message = buf;
	delete[] buf;
}

const char* GdxRuntimeException::what() const throw()
{
	return m_message.c_str();
}

GdxRuntimeException::~GdxRuntimeException(void)
{
}
