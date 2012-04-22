//
//  IOSFiles.cpp
//  backend-glfw
//
//  Created by Cosmin Manoliu on 4/1/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include "IOSFiles.h"

IOSFiles::IOSFiles()
{

}

/** Returns a handle representing a file or directory.
 * @param type Determines how the path is resolved.
 * @throws GdxRuntimeException if the type is classpath or internal and the file does not exist.
 * @see FileType */
FileHandle IOSFiles::getFileHandle (const std::string& path, FileType type) const
{
    return FileHandle(path, type);
}

/** Convenience method that returns a {@link FileType#Internal} file handle. */
FileHandle IOSFiles::internalHandle (const std::string& path) const
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
    return FileHandle(fullPath, Internal); 
}

/** Convenience method that returns a {@link FileType#External} file handle. */
FileHandle IOSFiles::externalHandle (const std::string& path) const
{
    std::string externalStoragePath;
	getExternalStoragePath(externalStoragePath);
	return FileHandle(externalStoragePath + "/" + path, External);
}

/** Convenience method that returns a {@link FileType#Absolute} file handle. */
FileHandle IOSFiles::absoluteHandle (const std::string& path) const
{
    return FileHandle(path, Absolute); 
}

/** Returns the external storage path directory. This is the SD card on Android and the home directory of the current user on
 * the desktop. */
void IOSFiles::getExternalStoragePath(std::string& str) const
{
    struct passwd *pw = getpwuid(getuid());
    
	const char *homedir = pw->pw_dir;
	str = homedir; 
}

/** Returns true if the external storage is ready for file IO. Eg, on Android, the SD card is not available when mounted for use
 * with a PC. */
bool IOSFiles::isExternalStorageAvailable() const
{
    return true;
}

bool IOSFiles::isDirectory( const std::string& path) const
{
    bool isDir = false;
    struct stat filestatus;
    if(!stat(path.c_str(), &filestatus))
       isDir = S_ISDIR(filestatus.st_mode);
    return isDir;
}

void IOSFiles::list( const std::string& path, std::vector< FileHandle>& handles) const
{
	handles.clear();
    DIR *dir = opendir(path.c_str());
    if (dir)
    {
        struct dirent* item;        
        while((item = readdir(dir)))
        {
            // Skip the names "." and ".."
            if (!strcmp(item->d_name, ".") || !strcmp(item->d_name, ".."))
            {
                continue;
            }
            handles.push_back( FileHandle( path + "/" + item->d_name));
        }
        closedir(dir);
    }
    
}

void IOSFiles::mkdir( const std::string& path) const
{
    int test = ::mkdir(path.c_str(), 0777);  
    if(test)
    {
        std::string err = "cannot create directory " + path;
        ::perror(err.c_str());
    }
}

bool IOSFiles::recursiveDeleteDirectory(const std::string& path) const
{
    return removeDirectory(path.c_str()) == 0; 
}


int IOSFiles::removeDirectory(const char *path) const
{
    DIR *d = opendir(path);
    size_t path_len = strlen(path);
    int r = -1;
    
    if (d)
    {
        struct dirent *p;        
        r = 0;
        while (!r && (p=readdir(d)))
        {
            int r2 = -1;
            char *buf;
            size_t len;
            
            /* Skip the names "." and ".." as we don't want to recurse on them. */
            if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
            {
                continue;
            }
            
            len = path_len + strlen(p->d_name) + 2; 
            buf = new char[len];
            
            if (buf)
            {
                struct stat statbuf;
                snprintf(buf, len, "%s/%s", path, p->d_name);
                if (!stat(buf, &statbuf))
                {
                    if (S_ISDIR(statbuf.st_mode))
                    {
                        r2 = removeDirectory(buf);
                    }
                    else
                    {
                        r2 = unlink(buf);
                    }
                }
                delete[] buf;
            }
            
            r = r2;
        }
        closedir(d);
    }
    if (!r)
    {
        r = rmdir(path);
    }
    
    return r;
}

bool IOSFiles::copyFile(const char* source, const char* dest) const
{
    
    int ok = ::copyfile(source, dest, NULL, COPYFILE_ALL);
    return ok == 0;
}


