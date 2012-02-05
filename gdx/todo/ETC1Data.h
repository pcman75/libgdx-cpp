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

#pragma once

#include "FileHandle.h"

/** Class for storing ETC1 compressed image data*/

class ETC1Data
{
public:
	/** the width in pixels **/
	int width;
	/** the height in pixels **/
	int height;
	/** the optional PKM header and compressed image data **/
	unsigned char* compressedData;
	
	int compressedDataSize;

	/** the offset in bytes to the actual compressed data. Might be 16 if this contains a PKM header, 0 otherwise **/
	int dataOffset;

	//TODO: need compressedData length? Take over the pointer, must be allocated with new[]???
	ETC1Data(int width, int height, unsigned char* compressedData, int compressedDataSize, int dataOffset);
	//void createFrom(int width, int height, unsigned char* compressedData, int compressedDataSize, int dataOffset);
	ETC1Data();

	ETC1Data(const FileHandle& pkmFile);

	/** @return whether this ETC1Data has a PKM header */
	bool hasPKMHeader() const;

	/** Writes the ETC1Data with a PKM header to the given file.
	 * @param file the file. */
	void write(const FileHandle& file);

	/** TODO: move it on destructor
	Releases the resources of the ETC1Data instance. */
	void dispose();

	std::wstring toString();
};
