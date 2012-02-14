#include "stdAfx.h"
#include "FileHandleStream.h"

FileHandleStream::FileHandleStream( std::string strFileName, FileAccess nFileAccess, StreamType nStreamType)
{
  m_strFileName = strFileName;
  m_nFileAccess = nFileAccess;
  m_nStreamType = nStreamType;
}

FileHandleStream::~FileHandleStream()
{
}

const std::string& FileHandleStream::fileName() const
{
  return m_strFileName;
}

FileAccess FileHandleStream::fileAccess() const
{
  return m_nFileAccess;
}

StreamType FileHandleStream::streamType() const
{
  return m_nStreamType;
}
