//
//  OSXFiles.cpp
//  backend-glfw
//
//  Created by Cosmin Manoliu on 4/1/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "stdafx.h"
#include "OSXFiles.h"
#include "WoglFileHandleStream.h"

OSXFiles::OSXFiles()
{

}

/** Returns a handle representing a file or directory.
 * @param type Determines how the path is resolved.
 * @throws GdxRuntimeException if the type is classpath or internal and the file does not exist.
 * @see FileType */
FileHandle* OSXFiles::getFileHandle (const std::string& path, FileType type) const
{
    return NULL; 
}

/** Convenience method that returns a {@link FileType#Internal} file handle. */
FileHandle* OSXFiles::internalHandle (const std::string& path) const
{
    unsigned char pathBuf[PATH_MAX];
    CFBundleRef mainBundle;
    
    // Get the main bundle for the app
    mainBundle = CFBundleGetMainBundle();
    CFURLRef url = CFBundleCopyResourcesDirectoryURL(mainBundle);
    CFURLGetFileSystemRepresentation(url, true, pathBuf, PATH_MAX);
         
    std::string fullPath((char*)pathBuf);
    fullPath += "/";
    fullPath += path;
    return new FileHandle(fullPath, Internal); 
}

/** Convenience method that returns a {@link FileType#External} file handle. */
FileHandle* OSXFiles::externalHandle (const std::string& path) const
{
    std::string externalStoragePath;
	getExternalStoragePath(externalStoragePath);
	return new FileHandle(externalStoragePath + "/" + path, External);
}

/** Convenience method that returns a {@link FileType#Absolute} file handle. */
FileHandle* OSXFiles::absoluteHandle (const std::string& path) const
{
    return new FileHandle(path, Absolute); 
}

/** Returns the external storage path directory. This is the SD card on Android and the home directory of the current user on
 * the desktop. */
void OSXFiles::getExternalStoragePath(std::string& str) const
{
    struct passwd *pw = getpwuid(getuid());
    
	const char *homedir = pw->pw_dir;
	str = homedir; 
}

/** Returns true if the external storage is ready for file IO. Eg, on Android, the SD card is not available when mounted for use
 * with a PC. */
bool OSXFiles::isExternalStorageAvailable() const
{
    return true;
}

bool OSXFiles::isDirectory( const std::string& path) const
{
    struct stat filestatus;
	stat( path.c_str(), &filestatus);
    bool isDir = S_ISDIR(filestatus.st_mode);
    return isDir;
}

void OSXFiles::list( const std::string& path, std::vector< FileHandle>& handles) const
{
    
}

void OSXFiles::mkdir( const std::string& path) const
{
    int test = ::mkdir(path.c_str(), 0777);  
    if(test)
    {
        std::string err = "cannot create directory " + path;
        ::perror(err.c_str());
    }
}

bool OSXFiles::recursiveDeleteDirectory(const std::string& path) const
{
    return false; 
}


FileHandleStream* OSXFiles::getStream( const std::string& path, FileAccess nFileAccess, StreamType nStreamType) const
{
    FileHandleStream* pRet = new WoglFileHandleStream(path, nFileAccess, nStreamType);
	return pRet;
}