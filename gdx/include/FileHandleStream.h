#pragma once


enum FileAccess
{
  Write,
  Read,
};

enum StreamType
{
  String,
  Binary,
};

// generic interface for FileStream 
//
class FileHandleStream
{
public:
  FileHandleStream( std::string strFileName, FileAccess nFileAccess, StreamType nStreamType);
  virtual ~FileHandleStream();

  const std::string&  fileName() const;
  FileAccess          fileAccess() const;
  StreamType          streamType() const;


  // file size int bytes
  //
  virtual int         size() = 0;

  // read nLen bytes in pWhere ( allocated by the caller)
  //
  virtual int         readBytes( unsigned char* pWhere, int nLen) = 0;
  
  // call fgets
  virtual char*		  readLine( char* pWhere, int nLen) = 0;
  
  // write nLen bytes from pWhere
  //
  virtual int         writeBytes( unsigned char* pFrom, int nLen) = 0;

  // skip nCount bytes
  //
  virtual int         skip( int nCount) = 0;

private:
  std::string m_strFileName;
  FileAccess  m_nFileAccess;
  StreamType  m_nStreamType;
};