#pragma once
#include "FileHandleStream.h"

class fstream;

class WoglFileHandleStream : public FileHandleStream
{
public:
  WoglFileHandleStream( std::string strFileName, FileAccess nFileAccess, StreamType nStreamType);
  virtual ~WoglFileHandleStream();


  // file size int bytes
  //
  virtual int         size();

  // read nLen bytes in pWhere ( allocated by the caller)
  //
  virtual int         readBytes( unsigned char* pWhere, int nLen);
  
  // write nLen bytes from pWhere
  //
  virtual int         writeBytes( unsigned char* pFrom, int nLen);




protected:
  void open();
  void close();
  void freeBuff();

private:
  FILE* m_pFile;
};

