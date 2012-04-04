#include "stdAfx.h"
#include "WoglFileHandleStream.h"


WoglFileHandleStream::WoglFileHandleStream( const std::string& strFileName, FileAccess nFileAccess, StreamType nStreamType)
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
      
//TODO:
#ifdef WIN32
        _setmode( fileno( m_pFile), _O_TEXT);
#endif
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
//TODO:    
#ifdef WIN32
  return _filelength( fileno( m_pFile));
#else
    return 0;
#endif
}

int WoglFileHandleStream::readBytes( unsigned char* pWhere, int nLen)
{
  return fread( ( void*) pWhere, sizeof( char), nLen, m_pFile);
}

char* WoglFileHandleStream::readLine( char* pWhere, int nLen)
{
  	char* ret = fgets( pWhere, nLen, m_pFile);
	
	if(ret)
	{
		//remove the new line character
		int len = strlen(ret);
		ret[len-1] = 0;
	}

	return ret;
}


int WoglFileHandleStream::writeBytes( unsigned char* pFrom, int nLen)
{
  return fwrite( ( void*) pFrom, sizeof( char), nLen, m_pFile);
}

int WoglFileHandleStream::skip( int nCount)
{
	return fseek( m_pFile, nCount, SEEK_CUR);
}