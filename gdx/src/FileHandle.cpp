#include "StdAfx.h"
#include "FileHandle.h"
#include "Gdx.h"


FileHandle::FileHandle()
{
}

FileHandle::FileHandle( std::string strFullPath) 
{
  m_strFullPath = strFullPath;
}

std::string FileHandle::getFullPathName() const
{
	return m_strFullPath;
}

std::string FileHandle::path() const
{
  int nIndex = m_strFullPath.rfind( '\\');
  if( std::string::npos == nIndex) return "";

  return m_strFullPath.substr( 0, nIndex);
}

std::string FileHandle::name()  const
{
  int nIndex = m_strFullPath.rfind( '\\');
  if( std::string::npos == nIndex) return "";

  return m_strFullPath.substr( nIndex + 1);
}

std::string FileHandle::extension() const
{
  int dotIndex = m_strFullPath.rfind( '.');
  if( std::string::npos == dotIndex) return "";

  return m_strFullPath.substr( dotIndex + 1);
}

std::string FileHandle::nameWithoutExtension()  const
{
  std::string strName = name();
  int dotIndex = strName.rfind('.');
  if (dotIndex == std::string::npos) return strName;
  return strName.substr(0, dotIndex);
}

FileType FileHandle::type()  const
{
  FileType nType = Gdx.app->getFiles()->getFileType( m_strFullPath);
  return nType;
}

void FileHandle::list( std::vector< FileHandle> &handles)
{
  Gdx.app->getFiles()->list( m_strFullPath, handles);
  /*
  std::vector< std::string> relativePaths;
  getFile()->list( relativePaths);
  handles.resize( relativePaths.size());
  for( int nIdx = 0; nIdx < relativePaths.size(); nIdx++) 
  {
    handles[ nIdx] = child( relativePaths[ nIdx]);
  }
  */
  return;
}

bool FileHandle::isDirectory () 
{
  return Gdx.app->getFiles()->isDirectory( m_strFullPath); 
}

FileHandle FileHandle::child( std::string name) 
{
  /*
  if( m_pFile->getPath().length() == 0) 
    return FileHandle( File( name), type);
  return FileHandle( File( file, name), type);
  */
  return FileHandle();

}

FileHandleStream* FileHandle::getStream( FileAccess nFileAccess, StreamType nStreamType) const
{
  return Gdx.app->getFiles()->getStream( m_strFullPath, nFileAccess, nStreamType);
}