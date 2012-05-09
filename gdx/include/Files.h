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

/** Provides standard access to the filesystem, classpath, Android SD card, and Android assets directory.*/
class Files
{
public:
	Files();
	virtual ~Files();

	/** Returns a handle representing a file or directory.
	* @param type Determines how the path is resolved.
	* @throws GdxRuntimeException if the type is classpath or internal and the file does not exist.
	* @see FileType */
	virtual FileHandle getFileHandle (const std::string& path, FileType type) const = 0;

	/** Convenience method that returns a {@link FileType#Internal} file handle. */
	virtual FileHandle internalHandle (const std::string& path) const = 0;

	/** Convenience method that returns a {@link FileType#External} file handle. */
	virtual FileHandle externalHandle (const std::string& path) const = 0;

	/** Convenience method that returns a {@link FileType#Absolute} file handle. */
	virtual FileHandle absoluteHandle (const std::string& path) const = 0;

	/** Returns the external storage path directory. This is the SD card on Android and the home directory of the current user on
	* the desktop. */
	virtual void getExternalStoragePath(std::string& str) const = 0;

	/** Returns true if the external storage is ready for file IO. Eg, on Android, the SD card is not available when mounted for use
	* with a PC. */
	virtual bool isExternalStorageAvailable() const = 0;

	virtual bool      isDirectory( const std::string& path) const = 0;
	virtual void      list( const std::string& path, std::vector< FileHandle>& handles) const = 0;
	virtual void      mkdir( const std::string& path) const = 0;

	virtual bool recursiveDeleteDirectory(const std::string& path) const = 0;
	virtual bool copyFile(const char* source, const char* dest) const = 0;
    
    virtual std::string getTempFileName() = 0;
};
