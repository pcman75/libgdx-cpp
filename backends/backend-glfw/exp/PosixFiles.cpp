//
//  PosixFile.cpp
//  backend-glfw
//
//  Created by Cosmin Manoliu on 4/1/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <stdafx.h>
#include "PosixFiles.h"

PosixFiles::PosixFiles()
{

}

/** Returns a handle representing a file or directory.
 * @param type Determines how the path is resolved.
 * @throws GdxRuntimeException if the type is classpath or internal and the file does not exist.
 * @see FileType */
FileHandle* PosixFiles::getFileHandle (const std::string& path, FileType type) const
{
    return NULL; 
}

/** Convenience method that returns a {@link FileType#Internal} file handle. */
FileHandle* PosixFiles::internalHandle (const std::string& path) const
{
    return NULL; 
}

/** Convenience method that returns a {@link FileType#External} file handle. */
FileHandle* PosixFiles::externalHandle (const std::string& path) const
{
    return NULL; 
}


/** Convenience method that returns a {@link FileType#Absolute} file handle. */
FileHandle* PosixFiles::absoluteHandle (const std::string& path) const
{
    return NULL; 
}

/** Returns the external storage path directory. This is the SD card on Android and the home directory of the current user on
 * the desktop. */
void PosixFiles::getExternalStoragePath(std::string& str) const
{
   
}

/** Returns true if the external storage is ready for file IO. Eg, on Android, the SD card is not available when mounted for use
 * with a PC. */
bool PosixFiles::isExternalStorageAvailable() const
{
    return true;
}

bool PosixFiles::isDirectory( const std::string& path) const
{
    return false;
}

void PosixFiles::list( const std::string& path, std::vector< FileHandle>& handles) const
{
    
}

void PosixFiles::mkdir( const std::string& path) const
{
    
}

bool PosixFiles::recursiveDeleteDirectory(const std::string& path) const
{
    return false; 
}


FileHandleStream* PosixFiles::getStream( const std::string& path, FileAccess nFileAccess, StreamType nStreamType) const
{
    return NULL;
}
