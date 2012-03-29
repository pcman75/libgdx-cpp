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

#include "Decoder.h"
#include "FileHandle.h"

/** A {@link Decoder} implementation that decodes OGG Vorbis files using tremor*/

class VorbisDecoder :
	public Decoder
{
private:
	void* m_handle;
	char* m_buffer;

	/** Opens the given file for ogg decoding. Throws an IllegalArugmentException in case the file could not be opened.
	*
	* @param file external or absolute {@link FileHandle}
	*/
public:
	VorbisDecoder(const FileHandle* file);
	void dispose();
	float getLength();
	int getChannels();
	int getRate();
	int readSamples(short samples[], int numSamples);
	int skipSamples(int numSamples);

private:
	void* openFile(const char* filename);
	
};
