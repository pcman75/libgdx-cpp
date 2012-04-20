#pragma once
#include "files.h"

// Win implementation of Files class
//
class WindowsFiles :	public Files
{
public:
	WindowsFiles(void);
	virtual ~WindowsFiles(void);

  /** Returns a handle representing a file or directory.
  * @param type Determines how the path is resolved.
  * @throws GdxRuntimeException if the type is classpath or internal and the file does not exist.
  * @see FileType */
  virtual FileHandle getFileHandle(const std::string& path, FileType type) const;

  /** Convenience method that returns a {@link FileType#Internal} file handle. */
  virtual FileHandle internalHandle(const std::string& path) const;

  /** Convenience method that returns a {@link FileType#External} file handle. */
  virtual FileHandle externalHandle(const std::string& path) const;

  /** Convenience method that returns a {@link FileType#Absolute} file handle. */
  virtual FileHandle absoluteHandle(const std::string& path) const;

  /** Returns the external storage path directory. This is the SD card on Android and the home directory of the current user on
  * the desktop. */
  virtual void getExternalStoragePath(std::string& path) const;

  /** Returns true if the external storage is ready for file IO. Eg, on Android, the SD card is not available when mounted for use
  * with a PC. */
  virtual bool isExternalStorageAvailable() const;

  virtual FileType  getFileType(const std::string& path) const;
  virtual bool      isDirectory(const std::string& path) const;
  virtual void      list(const std::string& path, std::vector<FileHandle>& handles) const;
  virtual void      mkdir( const std::string& path) const;
  virtual bool recursiveDeleteDirectory(const std::string& path) const;

  virtual FileHandleStream* getStream(const std::string& path, FileAccess nFileAccess, StreamType nStreamType) const;
  bool copyFile(const char* source, const char* dest) const;

private:
	bool isDots(const TCHAR* str) const;
};

