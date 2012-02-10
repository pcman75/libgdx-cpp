#include "stdafx.h"
#include "FileHandle.h"

void FileHandle::writeBytes(const char* bytes, int bufferLength) const
{
	std::ofstream file(m_name, std::ios::out | std::ios::binary);
	file.write (bytes, bufferLength);
}