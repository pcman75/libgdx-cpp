#include "StdAfx.h"
#include "WoglFiles.h"
#include "WoglFileHandleStream.h"


WoglFiles::WoglFiles(void)
{
}

WoglFiles::~WoglFiles(void)
{
}

FileHandle WoglFiles::getFileHandle(const std::string& path, FileType type) const
{
	return FileHandle( path);
}

FileHandle WoglFiles::internalHandle(const std::string& path) const
{
	char modulePath[MAX_PATH] = {0};
	char drive[_MAX_DRIVE] = {0};
	char dir[_MAX_DIR] = {0};

	::GetModuleFileName(NULL, modulePath, MAX_PATH);
	_splitpath(modulePath, drive, dir, NULL, NULL);
	std::string fullPath = std::string(drive) + dir + path;
	return FileHandle(fullPath);
}

FileHandle WoglFiles::externalHandle(const std::string& path) const
{
	return FileHandle( path);
}

FileHandle WoglFiles::absoluteHandle(const std::string& path) const
{
	return FileHandle( path);
}

std::string WoglFiles::getExternalStoragePath() const
{
	std::string externalPath;

#ifdef WIN32
	char path[MAX_PATH] = "";
	HRESULT hr = ::SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, SHGFP_TYPE_CURRENT, path);
	externalPath = path;
#else
	throw GdxRuntimeException("method not implemented");
	/*
	#include <unistd.h>
	#include <sys/types.h>
	#include <pwd.h>

	struct passwd *pw = getpwuid(getuid());

	const char *homedir = pw->pw_dir;
	externalPath = homedir;
	*/
#endif
	return externalPath;
}

bool WoglFiles::isExternalStorageAvailable() const
{
	return true;
}

FileType WoglFiles::getFileType(const std::string& path) const
{
	if( isDirectory( path))
		return Internal;

	// ??
	//
	return Absolute;
}

bool WoglFiles::isDirectory(const std::string& path) const
{
	DWORD dwFileType = GetFileAttributesA( path.c_str());
	if( FILE_ATTRIBUTE_DIRECTORY & dwFileType)
	{
		return true;
	}

	return false;
}

void WoglFiles::list(const std::string& path, std::vector< FileHandle>& handles) const
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

FileHandleStream* WoglFiles::getStream(const std::string& path, FileAccess nFileAccess, StreamType nStreamType) const
{
	FileHandleStream* pRet = new WoglFileHandleStream( path, nFileAccess, nStreamType);
	return pRet;
}