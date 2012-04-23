#include "StdAfx.h"
#include "FileHandle.h"
#include "Gdx.h"
#include "GdxRuntimeException.h"

using namespace std;

FileHandle::FileHandle()
{
	init("", Absolute);
}

FileHandle::FileHandle(const string& strFullPath) 
{
	init(strFullPath, Absolute);
}

FileHandle::FileHandle(const string& strFullPath, FileType type) 
{
	init(strFullPath, type);
}

void FileHandle::init(const string& strFullPath, FileType type) 
{
	m_strFullPath = strFullPath;
	m_type = type;
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
	return m_type;
}

void FileHandle::list(vector<FileHandle> &handles) const
{
	Gdx.app->getFiles()->list( m_strFullPath, handles);
	for(vector<FileHandle>::iterator it = handles.begin(); it != handles.end(); it++)
	{
		it->m_type = m_type;
	}
}

bool FileHandle::isDirectory() const
{
	return Gdx.app->getFiles()->isDirectory(m_strFullPath); 
}


/** Returns a handle to the child with the specified name.
* @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} and the child
* doesn't exist. */
FileHandle FileHandle::child(const string& name) const
{
	/*
	public FileHandle child (String name) {
	if (file.getPath().length() == 0) return new FileHandle(new File(name), type);
	return new FileHandle(new File(file, name), type);
	}
	*/
	//TODO: review this
	return FileHandle(m_strFullPath + "/" + name, m_type);
}

/** open the stream for reading this file as bytes.
* @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
void FileHandle::read(ifstream& stream) const
{
	stream.open(m_strFullPath.c_str(), ios_base::binary);
	if(stream.fail())
	{
		throw GdxRuntimeException("Error reading file: " + m_strFullPath);
	}
}

/** open the stream for reading this file as characters.
* @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
void FileHandle::reader(ifstream& stream) const
{
	stream.open(m_strFullPath.c_str());
	if(stream.fail())
	{
		throw GdxRuntimeException("Error reading file: " + m_strFullPath);
	}
}

/** Reads the entire file into the string using the platform's default charset.
* @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
void FileHandle::readString(string& str) const
{
	ifstream stream;
	reader(stream);
	std::istreambuf_iterator<char> eos;
	str.assign(std::istreambuf_iterator<char>(stream), eos);
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
	read(stream);
	stream.read((char*)pWhere, size);

	//try to read one more byte
	//just to check that we read everything
	char dummy = 0;
	stream >> dummy;
	if(!stream.eof())
	{
		stream.close();
		throw GdxRuntimeException("buffer not big enough to read the entire file");
	}
	stream.close();
}


/** Returns a stream for writing to this file. Parent directories will be created if necessary.
* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
*        {@link FileType#Internal} file, or if it could not be written. */
void FileHandle::write(bool append, ofstream& stream) const
{
	FileHandle parentHandle = parent();
	parentHandle.mkdirs();

	std::ios_base::openmode mode;
	mode = append? ios_base::out | ios_base::app: ios_base::out | ios_base::trunc;
	stream.open(m_strFullPath.c_str(), mode);
	if(stream.fail())
	{
		throw GdxRuntimeException("Error writing file: " + m_strFullPath);
	}
}

/** Reads the remaining bytes from the specified stream and writes them to this file. The stream is closed. Parent directories
* will be created if necessary.
* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
*        {@link FileType#Internal} file, or if it could not be written. 
void FileHandle::write(ifstream& input, bool append) const
{
	//TODO: implement this
	throw GdxRuntimeException("not implemented");
}
*/
/** Writes the specified string to the file using the default charset. Parent directories will be created if necessary.
* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
*        {@link FileType#Internal} file, or if it could not be written. */
void FileHandle::writeString(const string& str, bool append) const
{
	std::ofstream output;
	write(append, output);
	output << str;
	output.close();
}

/** Writes the specified bytes to the file. Parent directories will be created if necessary.
* @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
* @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
*        {@link FileType#Internal} file, or if it could not be written. */
void FileHandle::writeBytes(const unsigned char* bytes, size_t size, bool append) const
{
	std::ofstream output;
	write(append, output);
	output.write((const char*)bytes, size);
	output.close();
}


/** Returns the paths to the children of this directory with the specified suffix. Returns an empty list if this file handle
* represents a file and not a directory. On the desktop, an {@link FileType#Internal} handle to a directory on the classpath
* will return a zero length array.
* @throw GdxRuntimeException if this file is an {@link FileType#Classpath} file. */
//void list( std::string suffix, std::vector< FileHandle> &handles) const;


FileHandle FileHandle::parent() const
{
	int nIndex = m_strFullPath.rfind('/');
	if( string::npos == nIndex) 
		return FileHandle(m_strFullPath, m_type);

	return FileHandle(m_strFullPath.substr( 0, nIndex), m_type);
}

//
/** @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file. */
void FileHandle::mkdirs() const
{
	char* path = _strdup(m_strFullPath.c_str());
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
			if(*path && !Gdx.files->isDirectory(path)) 
				Gdx.files->mkdir(path);
			*p = '/';
		}
	}
	if(*path && !Gdx.files->isDirectory(path)) 
		Gdx.files->mkdir(path);

	free(path);
}


/** Returns true if the file exists. On Android, a {@link FileType#Classpath} or {@link FileType#Internal} handle to a directory
* will always return false. */
bool FileHandle::exists() const
{
	return _access(m_strFullPath.c_str(), 0) == 0;
}

//  /** Deletes this file or empty directory and returns success. Will not delete a directory that has children.
//  * @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file. */
bool FileHandle::remove() const
{
	if(m_type == Internal)
		throw GdxRuntimeException("File must not be Internal");

	int result = ::remove(m_strFullPath.c_str());
	if(result)
	{
		//maybe it's a directory
		if(isDirectory())
		{
			result = _rmdir(m_strFullPath.c_str());
		}
	}
	return result == 0;
}

/** Deletes this file or directory and all children, recursively.
* @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file. */
bool FileHandle::removeRecursive() const
{
	bool result = ::remove(m_strFullPath.c_str()) == 0;
	if(!result)
	{
		result = Gdx.files->recursiveDeleteDirectory(m_strFullPath);
	}
	return result;
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
void FileHandle::copyTo(const FileHandle& destination) const
{
	/*
	boolean sourceDir = isDirectory();
	if (!sourceDir) {
	if (dest.isDirectory()) dest = dest.child(name());
	copyFile(this, dest);
	return;
	}
	if (dest.exists()) {
	if (!dest.isDirectory()) throw new GdxRuntimeException("Destination exists but is not a directory: " + dest);
	} else {
	dest.mkdirs();
	if (!dest.isDirectory()) throw new GdxRuntimeException("Destination directory cannot be created: " + dest);
	}
	if (!sourceDir) dest = dest.child(name());
	copyDirectory(this, dest);
	*/
	FileHandle dest = destination;
	bool sourceIsDir = isDirectory();
	if (!sourceIsDir) 
	{
		if (dest.isDirectory()) 
		{
			dest = dest.child(name());
		}
		copyFile(*this, dest);
		return;
	}

	if (dest.exists()) 
	{
		if (!dest.isDirectory()) 
			throw new GdxRuntimeException("Destination exists but is not a directory: " + dest.toString());
	} 
	else 
	{
		dest.mkdirs();
		if (!dest.isDirectory()) 
			throw new GdxRuntimeException("Destination directory cannot be created: " + dest.toString());
	}

	if (!sourceIsDir)
	{
		dest = dest.child(name());
	}
	copyDirectory(*this, dest);
}


/** Moves this file to the specified file, overwriting the file if it already exists.
* @throw GdxRuntimeException if the source or destination file handle is a {@link FileType#Classpath} or
*        {@link FileType#Internal} file. */
void FileHandle::moveTo(const FileHandle& dest) const
{
	if(m_type == Internal)
		throw GdxRuntimeException("File must not be Internal");
	if(std::rename(m_strFullPath.c_str(), dest.m_strFullPath.c_str()))
		throw GdxRuntimeException("Failed to move " + m_strFullPath + " to " + dest.m_strFullPath);
}

/** Returns the length in bytes of this file, or 0 if this file is a directory, does not exist, or the size cannot otherwise be
* determined. */
size_t FileHandle::length() const
{
	struct stat filestatus;
	memset(&filestatus, 0, sizeof(filestatus));
	stat( m_strFullPath.c_str(), &filestatus);
	return filestatus.st_size;
}


/** Returns the last modified time in milliseconds for this file. Zero is returned if the file doesn't exist. Zero is returned
* for {@link FileType#Classpath} files. On Android, zero is returned for {@link FileType#Internal} files. On the desktop, zero
* is returned for {@link FileType#Internal} files on the classpath. */
long long FileHandle::lastModified() const
{
	struct stat filestatus;
	memset(&filestatus, 0, sizeof(filestatus));
	stat(m_strFullPath.c_str(), &filestatus);
	return filestatus.st_mtime;
}


std::string FileHandle::toString() const
{
	return m_strFullPath;
}

FileHandle FileHandle::tempFile()
{
	char* tempFileName = ::tmpnam(NULL);
	FileHandle tempHandle(tempFileName);
	std::ofstream output;
	tempHandle.write(false, output);
	if(output.fail())
	{
		throw GdxRuntimeException("Error creating temp file " + tempHandle.m_strFullPath);
	}
	output.close();
	return tempHandle;
}

FileHandle FileHandle::tempDirectory()
{
	char* tempFileName = ::tmpnam(NULL);
	FileHandle tempHandle(tempFileName);
	Gdx.files->mkdir(tempFileName);
	if(!tempHandle.exists())
	{
		throw GdxRuntimeException("Error creating temp directory " + tempHandle.m_strFullPath);
	}
	
	return tempHandle;
}

void FileHandle::copyFile(const FileHandle& source, const FileHandle& dest) 
{
	dest.parent().mkdirs();
	if(!Gdx.files->copyFile(source.m_strFullPath.c_str(), dest.m_strFullPath.c_str()))
		throw GdxRuntimeException("failed to copy " + source.m_strFullPath + " to " + dest.m_strFullPath);
}

void FileHandle::copyDirectory(const FileHandle& sourceDir, const FileHandle& destDir) 
{
	destDir.mkdirs();
	vector<FileHandle> files;
	sourceDir.list(files);
	for (int i = 0, n = files.size(); i < n; i++) 
	{
		FileHandle srcFile = files[i];
		FileHandle destFile = destDir.child(srcFile.name());
		if (srcFile.isDirectory())
			copyDirectory(srcFile, destFile);
		else
			copyFile(srcFile, destFile);
	}
}