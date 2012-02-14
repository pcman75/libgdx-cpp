#include "StdAfx.h"
#include "WoglFiles.h"
#include "WoglFileHandleStream.h"


WoglFiles::WoglFiles(void)
{
}

WoglFiles::~WoglFiles(void)
{
}

FileHandle WoglFiles::getFileHandle( std::string path, FileType type) const
{
  return FileHandle( path);
}

FileHandle WoglFiles::classpathHandle( std::string path) const
{
  return FileHandle();
}

FileHandle WoglFiles::internalHandle( std::string path) const
{
  return FileHandle( path);
}

FileHandle WoglFiles::externalHandle( std::string path) const
{
  return FileHandle( path);
}

FileHandle WoglFiles::absoluteHandle( std::string path) const
{
  return FileHandle( path);
}

std::string WoglFiles::getExternalStoragePath() const
{
  return std::string();
}

bool WoglFiles::isExternalStorageAvailable() const
{
  return false;
}

FileType WoglFiles::getFileType( std::string path) const
{
  if( isDirectory( path))
    return Internal;
  
  // ??
  //
  return Absolute;
}

bool WoglFiles::isDirectory( std::string path) const
{
  DWORD dwFileType = GetFileAttributesA( path.c_str());
  if( FILE_ATTRIBUTE_DIRECTORY & dwFileType)
  {
    return true;
  }

  return false;
}

void WoglFiles::list( std::string path, std::vector< FileHandle>& handles) const
{
  if( isDirectory( path))
  {
    WIN32_FIND_DATAA FileData; 
    HANDLE hSearch; 

    std::string strSearchText = path;
    if( '\\' != strSearchText[ strSearchText.length() - 1])
    {
      strSearchText +=  "\\";
    }
    strSearchText +=  "*.*";

    hSearch = FindFirstFileA( strSearchText.c_str(), &FileData); 
    
    do 
    {
      handles.push_back( FileHandle( path + FileData.cFileName));
    } while ( FindNextFileA( hSearch, &FileData));

    FindClose( hSearch);
  }
}

FileHandleStream* WoglFiles::getStream( std::string path, FileAccess nFileAccess, StreamType nStreamType) const
{
  FileHandleStream* pRet = new WoglFileHandleStream( path, nFileAccess, nStreamType);
  return pRet;
}