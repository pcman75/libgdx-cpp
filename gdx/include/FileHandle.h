/*******************************************************************************
* Copyright 2011 See AUTHORS file.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*   http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
******************************************************************************/
#pragma once

enum FileType 
{
  /** Path relative to the asset directory on Android and to the application's root directory on the desktop. On the desktop,
  * if the file is not found, then the classpath is checked. This enables files to be found when using JWS or applets.
  * Internal files are always readonly. */
  Internal,

  /** Path relative to the root of the SD card on Android and to the home directory of the current user on the desktop. */
  External,

  /** Path that is a fully qualified, absolute filesystem path. To ensure portability across platforms use absolute files only
  * when absolutely (heh) necessary. */
  Absolute
};


/** Represents a file or directory on the filesystem, classpath, Android SD card, or Android assets directory. FileHandles are
* created via a {@link Files} instance.
*/
class FileHandle 
{
public:
  FileHandle();
  FileHandle(const std::string& fileName);
  FileHandle(const std::string& fileName, FileType type);

  std::string path() const;
  std::string name() const;
  std::string extension() const;
  std::string nameWithoutExtension() const;
  std::string getFullPathName() const;
  FileType type() const;


  /** Returns a std::fstream that represents this file handle. Note the returned file will only be usable for
	 * {@link FileType#Absolute} and {@link FileType#External} file handles. */
  //TODO: why???
  void file(std::fstream& stream) const;

  /** open the stream for reading this file as bytes.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  void read(std::ifstream& stream) const;

  /** open the stream for reading this file as characters.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  void reader(std::ifstream& stream) const;

  /** Reads the entire file into a std::string using the platform's default charset.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  void readString(std::string& str) const;
  

  /** Reads the entire file into a std::string using the specified charset.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  void readstring(const std::string& charset, std::string& str) const;

  /** Reads the entire file into a byte array.
  * read nLen bytes in pWhere ( allocated by the caller)
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. 
  */
  void readBytes(unsigned char* pWhere, size_t size) const;


  /** Returns a stream for writing to this file. Parent directories will be created if necessary.
  * @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  * @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  *        {@link FileType#Internal} file, or if it could not be written. */
  void write(bool append, std::ofstream& stream) const;

  /** Reads the remaining bytes from the specified stream and writes them to this file. The stream is closed. Parent directories
  * will be created if necessary.
  * @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  * @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  *        {@link FileType#Internal} file, or if it could not be written. */
  //void write(std::ifstream& input, bool append) const;

  /** Writes the specified std::string to the file using the default charset. Parent directories will be created if necessary.
  * @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  * @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  *        {@link FileType#Internal} file, or if it could not be written. */
  void writeString(const std::string& str, bool append) const;

  /** Writes the specified bytes to the file. Parent directories will be created if necessary.
  * @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  * @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  *        {@link FileType#Internal} file, or if it could not be written. */
  void writeBytes(const unsigned char*, size_t size, bool append) const;

  /** Returns the paths to the children of this directory. Returns an empty list if this file handle represents a file and not a
  * directory. On the desktop, an {@link FileType#Internal} handle to a directory on the classpath will return a zero length
  * array.
  * @throw GdxRuntimeException if this file is an {@link FileType#Classpath} file. */
  void list(std::vector<FileHandle> &handles) const;
  
  /** Returns the paths to the children of this directory with the specified suffix. Returns an empty list if this file handle
  * represents a file and not a directory. On the desktop, an {@link FileType#Internal} handle to a directory on the classpath
  * will return a zero length array.
  * @throw GdxRuntimeException if this file is an {@link FileType#Classpath} file. */
  //void list( std::string suffix, std::vector< FileHandle> &handles) const;
  
  /** Returns true if this file is a directory. Always returns false for classpath files. On Android, an {@link FileType#Internal}
  * handle to an empty directory will return false. On the desktop, an {@link FileType#Internal} handle to a directory on the
  * classpath will return false. */
  bool isDirectory() const;

  /** Returns a handle to the child with the specified name.
  * @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} and the child
  *        doesn't exist. */
  FileHandle child(const std::string& name) const;

  FileHandle parent() const;

  /** @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file. */
  void mkdirs() const;

  /** Returns true if the file exists. On Android, a {@link FileType#Classpath} or {@link FileType#Internal} handle to a directory
  * will always return false. */
  bool exists() const; 

  /** Deletes this file or empty directory and returns success. Will not delete a directory that has children.
  * @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file. */
  bool remove() const;

  /** Deletes this file or directory and all children, recursively.
  * @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file. */
  bool removeRecursive() const;

  /** Copies this file or directory to the specified file or directory. If this handle is a file, then 1) if the destination is a
  * file, it is overwritten, or 2) if the destination is a directory, this file is copied into it, or 3) if the destination
  * doesn't exist, {@link #mkdirs()} is called on the destination's parent and this file is copied into it with a new name. If
  * this handle is a directory, then 1) if the destination is a file, GdxRuntimeException is thrown, or 2) if the destination is
  * a directory, this directory is copied recursively into it as a subdirectory, overwriting existing files, or 3) if the
  * destination doesn't exist, {@link #mkdirs()} is called on the destination and this directory is copied recursively into it
  * as a subdirectory.
  * @throw GdxRuntimeException if the destination file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file,
  *        or copying failed. */
  void copyTo(const FileHandle& dest) const;

  /** Moves this file to the specified file, overwriting the file if it already exists.
  * @throw GdxRuntimeException if the source or destination file handle is a {@link FileType#Classpath} or
  *        {@link FileType#Internal} file. */
  void moveTo(const FileHandle& dest) const;

  /** Returns the length in bytes of this file, or 0 if this file is a directory, does not exist, or the size cannot otherwise be
  * determined. */
  size_t length() const;

  /** Returns the last modified time in milliseconds for this file. Zero is returned if the file doesn't exist. Zero is returned
  * for {@link FileType#Classpath} files. On Android, zero is returned for {@link FileType#Internal} files. On the desktop, zero
  * is returned for {@link FileType#Internal} files on the classpath. */
  long long lastModified() const;

  std::string toString () const;

  /**Delete the temp file after finish working with it!*/
  static FileHandle tempFile();
  /**Delete the temp directory after finish working with it!*/
  static FileHandle tempDirectory();

private:
	void init(const std::string& strFullPath, FileType type);
    int removeDirectory(const char *path) const;
	static void copyFile(const FileHandle& source, const FileHandle& dest);
	static void copyDirectory(const FileHandle& sourceDir, const FileHandle& destDir);

protected:
  std::string m_strFullPath;
  FileType m_type;

};
