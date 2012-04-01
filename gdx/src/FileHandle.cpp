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
	FileType nType = Gdx.app->getFiles()->getFileType(m_strFullPath);
	return nType;
}

void FileHandle::list(vector<FileHandle> &handles) const
{
	Gdx.app->getFiles()->list( m_strFullPath, handles);
}

bool FileHandle::isDirectory() const
{
	return Gdx.app->getFiles()->isDirectory(m_strFullPath); 
}

FileHandle* FileHandle::child(const string& name) const
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
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
	if(stream.fail())
	{
		throw GdxRuntimeException("Error reading file: " + m_strFullPath);
	}
}

/** open the stream for reading this file as characters.
* @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
void FileHandle::reader(ifstream& stream) const
{
	stream.open(m_strFullPath.c_str(), ios_base::binary);
	if(stream.fail())
	{
		throw GdxRuntimeException("Error reading file: " + m_strFullPath);
	}
}

/** Reads the entire file into the string using the platform's default charset.
* @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
void FileHandle::readstring(string& str) const
{
	ifstream stream;
	read(stream);
	stream >> str;
	stream.close();
	if(stream.fail())
	{
		throw GdxRuntimeException("Error reading file: " + m_strFullPath);
	}
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

/** Reads the entire file into a byte array.
* read nLen bytes in pWhere ( allocated by the caller)
* @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. 
*/
void FileHandle::readBytes(unsigned char* pWhere, size_t size) const
{
	ifstream stream;
	reader(stream);
	stream.read((char*)pWhere, size);
	stream.close();
	if(!stream.eof())
	{
		throw GdxRuntimeException("buffer not big enough to read the entire file");
	}
	if(stream.fail())
	{
		throw GdxRuntimeException("Error reading file: " + m_strFullPath);
	}
}


/** Returns a stream for writing to this file. Parent directories will be created if necessary.
* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
*        {@link FileType#Internal} file, or if it could not be written. */
void FileHandle::write(bool append, ofstream& stream) const
{
	FileHandle* parentHandle = parent();
	parentHandle->mkdirs();
	delete parentHandle;

	stream.open(m_strFullPath.c_str());
	if(stream.fail())
	{
		throw GdxRuntimeException("Error writing file: " + m_strFullPath);
	}
}

/** Reads the remaining bytes from the specified stream and writes them to this file. The stream is closed. Parent directories
* will be created if necessary.
* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
*        {@link FileType#Internal} file, or if it could not be written. */
void FileHandle::write(ifstream& input, bool append) const
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}


/** Returns a writer for writing to this file using the default charset. Parent directories will be created if necessary.
* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
*        {@link FileType#Internal} file, or if it could not be written. */
void FileHandle::writer(bool append, ofstream& stream) const
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}

/** Returns a writer for writing to this file. Parent directories will be created if necessary.
* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
* @param charset May be null to use the default charset.
* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
*        {@link FileType#Internal} file, or if it could not be written. */
void FileHandle::writer(bool append, const string& charset, ofstream& stream) const
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}


/** Writes the specified string to the file using the default charset. Parent directories will be created if necessary.
* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
*        {@link FileType#Internal} file, or if it could not be written. */
void FileHandle::writestring(const string& str, bool append) const
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}


/** Writes the specified string to the file as UTF-8. Parent directories will be created if necessary.
* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
* @param charset May be null to use the default charset.
* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
*        {@link FileType#Internal} file, or if it could not be written. */
void FileHandle::writestring(const string& str, bool append, const string& charset) const
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}


/** Writes the specified bytes to the file. Parent directories will be created if necessary.
* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
*        {@link FileType#Internal} file, or if it could not be written. */
void FileHandle::writeBytes(const unsigned char*, size_t size, bool append) const
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}


/** Returns the paths to the children of this directory with the specified suffix. Returns an empty list if this file handle
* represents a file and not a directory. On the desktop, an {@link FileType#Internal} handle to a directory on the classpath
* will return a zero length array.
* @throw GdxRuntimeException if this file is an {@link FileType#Classpath} file. */
//void list( std::string suffix, std::vector< FileHandle> &handles) const;


FileHandle* FileHandle::parent() const
{
	int nIndex = m_strFullPath.rfind('/');
	if( string::npos == nIndex) 
		return new FileHandle(m_strFullPath);

	return new FileHandle(m_strFullPath.substr( 0, nIndex));
}

//
/** @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file. */
void FileHandle::mkdirs() const
{
	char* path = strdup(m_strFullPath.c_str());
	char *p; 
	size_t len; 
	len = strlen(path); 
	if(path[len - 1] == '/') 
		path[len - 1] = 0; 

	for(p = path; *p; p++) 
	{
		if(*p == '/') 
		{ 
			*p = 0; 
			if(!Gdx.files->isDirectory(path)) 
				Gdx.files->mkdir(path);
			*p = '/';
		}
	}
	if(!Gdx.files->isDirectory(path)) 
		Gdx.files->mkdir(path);

	free(path);
}


/** Returns true if the file exists. On Android, a {@link FileType#Classpath} or {@link FileType#Internal} handle to a directory
* will always return false. */
bool FileHandle::exists() const
{
	return access(m_strFullPath.c_str(), 0) == 0;
}

//  /** Deletes this file or empty directory and returns success. Will not delete a directory that has children.
//  * @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file. */
bool FileHandle::remove() const
{
	int result = ::remove(m_strFullPath.c_str());
	if(result)
	{
		//maybe it's a directory
		if(isDirectory())
		{
			result = rmdir(m_strFullPath.c_str());
		}
	}
	return result == 0;
}


/** Deletes this file or directory and all children, recursively.
* @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file. */
bool FileHandle::removeRecursive() const
{
	int result = ::remove(m_strFullPath.c_str());
	if(result)
	{
		Gdx.files->recursiveDeleteDirectory(m_strFullPath.c_str());
	}
	return result == 0;
}


/** Copies this file or directory to the specified file or directory. If this handle is a file, then 1) if the destination is a
* file, it is overwritten, or 2) if the destination is a directory, this file is copied into it, or 3) if the destination
* doesn't exist, {@link #mkdirs()} is called on the destination's parent and this file is copied into it with a new name. If
* this handle is a directory, then 1) if the destination is a file, GdxRuntimeException is thrown, or 2) if the destination is
* a directory, this directory is copied recursively into it as a subdirectory, overwriting existing files, or 3) if the
* destination doesn't exist, {@link #mkdirs()} is called on the destination and this directory is copied recursively into it
* as a subdirectory.
* @throw GdxRuntimeException if the destination file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file,
*        or copying failed. */
void FileHandle::copyTo(const FileHandle* dest) const
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}


/** Moves this file to the specified file, overwriting the file if it already exists.
* @throw GdxRuntimeException if the source or destination file handle is a {@link FileType#Classpath} or
*        {@link FileType#Internal} file. */
void FileHandle::moveTo(const FileHandle* dest) const
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}


/** Returns the length in bytes of this file, or 0 if this file is a directory, does not exist, or the size cannot otherwise be
* determined. */
long long FileHandle::length() const
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}


/** Returns the last modified time in milliseconds for this file. Zero is returned if the file doesn't exist. Zero is returned
* for {@link FileType#Classpath} files. On Android, zero is returned for {@link FileType#Internal} files. On the desktop, zero
* is returned for {@link FileType#Internal} files on the classpath. */
//TODO: long it's enough?
long long FileHandle::lastModified() const
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}


std::string FileHandle::toString() const
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}


FileHandle* FileHandle::tempFile(const std::string prefix)
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}


FileHandle* FileHandle::tempDirectory(std::string prefix)
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}
