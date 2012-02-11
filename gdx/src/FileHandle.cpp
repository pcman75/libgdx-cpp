#include "stdafx.h"
#include "FileHandle.h"

void FileHandle::writeBytes(const char* bytes, int bufferLength) const
{
	std::ofstream file(m_name, std::ios::out | std::ios::binary);
	file.write(bytes, bufferLength);
	file.close();
}

int FileHandle::readBytes(std::vector<unsigned char>& buffer) const 
{
	std::ifstream file(m_name, std::ios::in | std::ios::binary);
	// get length of file:
	file.seekg (0, std::ios::end);
	int length = file.tellg();
	file.seekg(0, std::ios::beg);

	// allocate memory:
	buffer.resize(length, 0);

	// read data as a block:
	file.read((char*)buffer.data(), length);
	file.close();
	return length;
}