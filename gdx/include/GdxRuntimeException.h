#pragma once
#include "GdxDefines.h"

class GdxRuntimeException : public std::exception
{
public:
	GdxDllImportExport GdxRuntimeException(const std::string& message);
	GdxDllImportExport virtual ~GdxRuntimeException(void) throw();

	GdxDllImportExport virtual const char* what() const throw();
private:
	std::string m_message;
};
