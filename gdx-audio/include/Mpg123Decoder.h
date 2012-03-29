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

/** A {@link Decoder} implementation that decodes MP3 files via libmpg123 natively.*/

class Mpg123Decoder :
	public Decoder
{

public:
	void* handle;

	/** Opens the given file for mp3 decoding. Throws an GdxRuntimeException in case the file could not be opened.
	 *
	 * @param filename the filename */
	Mpg123Decoder(const FileHandle* file);
	int readSamples(short samples[], int numSamples);
	int skipSamples(int numSamples);
	int getChannels();
	int getRate();
	float getLength();
	void dispose();
};
