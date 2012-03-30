#include "StdAfx.h"
#include "FileHandle.h"
#include "Gdx.h"
#include "GdxRuntimeException.h"

using namespace std;

FileHandle::FileHandle()
{
}

FileHandle::FileHandle(const string& strFullPath) 
{
	m_strFullPath = strFullPath;
	replace(m_strFullPath.begin(), m_strFullPath.end(), '\\', '/');
}

string FileHandle::getFullPathName() const
{
	return m_strFullPath;
}

string FileHandle::path() const
{
	int nIndex = m_strFullPath.rfind('/');
	if( string::npos == nIndex) 
		return "";

	return m_strFullPath.substr( 0, nIndex);
}

string FileHandle::name()  const
{
	int nIndex = m_strFullPath.rfind( '/');
	if( string::npos == nIndex) 
		return "";

	return m_strFullPath.substr( nIndex + 1);
}

string FileHandle::extension() const
{
	int dotIndex = m_strFullPath.rfind( '.');
	if( string::npos == dotIndex) return "";

	return m_strFullPath.substr( dotIndex + 1);
}

string FileHandle::nameWithoutExtension()  const
{
	string strName = name();
	int dotIndex = strName.rfind('.');
	if (dotIndex == string::npos) 
		return strName;
	return strName.substr(0, dotIndex);
}

FileType FileHandle::type()  const
{
	FileType nType = Gdx.app->getFiles()->getFileType( m_strFullPath);
	return nType;
}

void FileHandle::list(vector<FileHandle> &handles) const
{
	Gdx.app->getFiles()->list( m_strFullPath, handles);
	/*
	vector< string> relativePaths;
	getFile()->list( relativePaths);
	handles.resize( relativePaths.size());
	for( int nIdx = 0; nIdx < relativePaths.size(); nIdx++) 
	{
	handles[ nIdx] = child( relativePaths[ nIdx]);
	}
	*/
	return;
}

bool FileHandle::isDirectory() const
{
	return Gdx.app->getFiles()->isDirectory( m_strFullPath); 
}

FileHandle* FileHandle::child(const string& name) const
{
	/*
	if( m_pFile->getPath().length() == 0) 
	return FileHandle( File( name), type);
	return FileHandle( File( file, name), type);
	*/
	return new FileHandle();

}

FileHandleStream* FileHandle::getStream( FileAccess nFileAccess, StreamType nStreamType) const
{
	return Gdx.app->getFiles()->getStream( m_strFullPath, nFileAccess, nStreamType);
}


/** open the stream for reading this file as bytes.
* @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
void FileHandle::read(ifstream& stream) const
{
	stream.open(m_strFullPath.c_str());
}

/** open the stream for reading this file as characters.
* @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
void FileHandle::reader(ifstream& stream) const
{
	stream.open(m_strFullPath.c_str(), ios_base::binary);
}

  /** Reads the entire file into the string using the platform's default charset.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  void FileHandle::readstring(string& str) const
  {
	  ifstream stream(m_strFullPath.c_str());
	  stream >> str;
	  stream.close();
  }
  

  /** Reads the entire file into a string using the specified charset.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  void FileHandle::readstring(const string& charset, std::string& str) const
  {
	  throw GdxRuntimeException("not yet implemented");
  	  ifstream stream(m_strFullPath.c_str());
	  stream >> str;
	  stream.close();
  }

  ///** Reads the entire file into a byte array.
  //* read nLen bytes in pWhere ( allocated by the caller)
  //* @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. 
  //*/
  //size_t FileHandle::readBytes(unsigned char* pWhere, size_t size) const
  //{
	 // ifstream stream = reader();
	 // stream.read((char*)pWhere, size);
	 // stream.close();
  //}


  ///** Returns a stream for writing to this file. Parent directories will be created if necessary.
  //* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  //* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  //*        {@link FileType#Internal} file, or if it could not be written. */
  //ofstream write(bool append) const;

  ///** Reads the remaining bytes from the specified stream and writes them to this file. The stream is closed. Parent directories
  //* will be created if necessary.
  //* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  //* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  //*        {@link FileType#Internal} file, or if it could not be written. */
  //void write(ifstream& input, bool append) const;

  ///** Returns a writer for writing to this file using the default charset. Parent directories will be created if necessary.
  //* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  //* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  //*        {@link FileType#Internal} file, or if it could not be written. */
  //ofstream writer(bool append) const;

  ///** Returns a writer for writing to this file. Parent directories will be created if necessary.
  //* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  //* @param charset May be null to use the default charset.
  //* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  //*        {@link FileType#Internal} file, or if it could not be written. */
  //ofstream writer(bool append, const string& charset) const;

  ///** Writes the specified string to the file using the default charset. Parent directories will be created if necessary.
  //* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  //* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  //*        {@link FileType#Internal} file, or if it could not be written. */
  //void writestring(const string& str, bool append) const;

  ///** Writes the specified string to the file as UTF-8. Parent directories will be created if necessary.
  //* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  //* @param charset May be null to use the default charset.
  //* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  //*        {@link FileType#Internal} file, or if it could not be written. */
  //void writestring(const string& str, bool append, const string& charset) const;

  ///** Writes the specified bytes to the file. Parent directories will be created if necessary.
  //* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  //* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  //*        {@link FileType#Internal} file, or if it could not be written. */
  //void writeBytes(const unsigned char*, size_t size, bool append) const;
