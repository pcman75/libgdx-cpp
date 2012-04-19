#include "StdAfx.h"
#include "WindowsFiles.h"
#include "WoglFileHandleStream.h"
#include "GdxRuntimeException.h"

WindowsFiles::WindowsFiles(void)
{
}

WindowsFiles::~WindowsFiles(void)
{
}

FileHandle* WindowsFiles::getFileHandle(const std::string& path, FileType type) const
{
	return new FileHandle(path, type);
}

FileHandle* WindowsFiles::internalHandle(const std::string& path) const
{
	char modulePath[MAX_PATH] = {0};
	char drive[_MAX_DRIVE] = {0};
	char dir[_MAX_DIR] = {0};

	::GetModuleFileName(NULL, modulePath, MAX_PATH);
	_splitpath(modulePath, drive, dir, NULL, NULL);
	std::string fullPath = std::string(drive) + dir + path;
	return new FileHandle(fullPath, Internal);
}

FileHandle* WindowsFiles::externalHandle(const std::string& path) const
{
	std::string externalStoragePath;
	getExternalStoragePath(externalStoragePath);
	return new FileHandle(externalStoragePath + "/" + path, External);
}

FileHandle* WindowsFiles::absoluteHandle(const std::string& path) const
{
	return new FileHandle(path, Absolute);
}

void WindowsFiles::getExternalStoragePath(std::string& externalPath) const
{
	char path[MAX_PATH] = "";
	HRESULT hr = ::SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, SHGFP_TYPE_CURRENT, path);
	externalPath = path;
}

bool WindowsFiles::isExternalStorageAvailable() const
{
	return true;
}

FileType WindowsFiles::getFileType(const std::string& path) const
{
	if( isDirectory( path))
		return Internal;

	// ??
	//
	return Absolute;
}

bool WindowsFiles::isDirectory(const std::string& path) const
{
	DWORD dwFileType = GetFileAttributesA( path.c_str());
	return (dwFileType != INVALID_FILE_ATTRIBUTES &&
            (dwFileType & FILE_ATTRIBUTE_DIRECTORY));
}

void WindowsFiles::list(const std::string& path, std::vector< FileHandle>& handles) const
{
	if( isDirectory( path))
	{
		WIN32_FIND_DATA FileData; 
		HANDLE hSearch; 

		std::string strSearchText = path;
		strSearchText +=  "\\*";
		

		hSearch = FindFirstFile( strSearchText.c_str(), &FileData); 

		do 
		{
			if(!isDots(FileData.cFileName))
				handles.push_back( FileHandle( path + "/" + FileData.cFileName));
		} 
		while (FindNextFile(hSearch, &FileData));
		FindClose( hSearch);
	}
}


void  WindowsFiles::mkdir( const std::string& path) const
{
	_mkdir(path.c_str());
}

bool WindowsFiles::isDots(const TCHAR* str) const
{
   if(strcmp(str,".") && strcmp(str,"..")) 
	   return false;
   return true;
}

bool WindowsFiles::recursiveDeleteDirectory(const std::string& path) const
{
   HANDLE hFind;
   WIN32_FIND_DATA FindFileData;
 
   TCHAR dirPath[MAX_PATH];
   TCHAR fileName[MAX_PATH];
 
   strcpy(dirPath,path.c_str());
   strcat(dirPath, "\\*");
   strcpy(fileName, path.c_str());
   strcat(fileName,"\\");
 
   // find the first file
   hFind = FindFirstFile(dirPath, &FindFileData);
   if(hFind == INVALID_HANDLE_VALUE) 
	   return false;
   
   strcpy(dirPath, fileName);
 
   bool bSearch = true;
   while(bSearch) 
   {    
	   // until we find an entry
      if(FindNextFile(hFind,&FindFileData)) 
	  {
         if(isDots(FindFileData.cFileName)) 
			 continue;
         strcat(fileName,FindFileData.cFileName);
         if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
		 {
             // we have found a directory, recurse
            if(!recursiveDeleteDirectory(fileName)) 
			{
                FindClose(hFind);
                return false;    // directory couldn't be deleted
            }
            // remove the empty directory
            RemoveDirectory(fileName);
             strcpy(fileName, dirPath);
         }
      }
      else 
	  {
         // no more files there
         if(GetLastError() == ERROR_NO_MORE_FILES)
         bSearch = false;
         else 
		 {
            // some error occurred; close the handle and return FALSE
               FindClose(hFind);
               return false;
         }
       }
    }
   FindClose(hFind);                  // close the file handle
   return RemoveDirectory(path.c_str()) == TRUE;     // remove the empty directory
}

FileHandleStream* WindowsFiles::getStream(const std::string& path, FileAccess nFileAccess, StreamType nStreamType) const
{
	FileHandleStream* pRet = new WoglFileHandleStream( path, nFileAccess, nStreamType);
	return pRet;
}

bool WindowsFiles::copyFile(const char* source, const char* dest) const
{
	return ::CopyFileA(source, dest, TRUE) == TRUE;
}

bool WindowsFiles::moveFile(const char* source, const char* dest) const
{
	struct stat filestatus;
	if(!stat( dest, &filestatus))
	{
		//destination exists so I delete it before trying to move over it
		::DeleteFileA(dest);
	}

	return ::MoveFileA(source, dest) == TRUE;
}