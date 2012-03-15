#include "stdAfx.h"
#include "WoglFileHandleStream.h"

WoglFileHandleStream::WoglFileHandleStream( std::string strFileName, FileAccess nFileAccess, StreamType nStreamType)
: FileHandleStream( strFileName, nFileAccess, nStreamType)
{
  m_pFile = NULL;
  open();
}
WoglFileHandleStream::~WoglFileHandleStream()
{
  close();
}

void WoglFileHandleStream::open()
{
  if( NULL != m_pFile)
  {
    close();
  }

  if( Write == fileAccess())
  {
    if( Binary == streamType())
    {
      m_pFile = fopen( fileName().c_str(), "w+b");
    }
    else
    {
      m_pFile = fopen( fileName().c_str(), "w+t");
    }
  }
  else 
  {
    if( Binary == streamType())
    {
      m_pFile = fopen( fileName().c_str(), "r+b");
    }
    else
    {
      m_pFile = fopen( fileName().c_str(), "r+t");
      _setmode( _fileno( m_pFile), _O_TEXT);
    }
  }
  
}

void WoglFileHandleStream::close()
{
  if( NULL != m_pFile)
  {
    fclose( m_pFile);
    m_pFile = NULL;
  }
}


int WoglFileHandleStream::size()
{
  return _filelength( _fileno( m_pFile));
}

int WoglFileHandleStream::readBytes( unsigned char* pWhere, int nLen)
{
  return fread( ( void*) pWhere, sizeof( char), nLen, m_pFile);
}

char* WoglFileHandleStream::readLine( char* pWhere, int nLen)
{
  return fgets( pWhere, nLen, m_pFile);
}


int WoglFileHandleStream::writeBytes( unsigned char* pFrom, int nLen)
{
  return fwrite( ( void*) pFrom, sizeof( char), nLen, m_pFile);
}

int WoglFileHandleStream::skip( int nCount)
{
	return fseek( m_pFile, nCount, SEEK_CUR);
}