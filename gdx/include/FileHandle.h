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

#include "FileHandleStream.h"

enum FileType 
{
  /** Path relative to the root of the classpath. Classpath files are always readonly. Note that classpath files are not
  * compatible with some functionality on Android, such as {@link Audio#newSound(FileHandle)} and
  * {@link Audio#newMusic(FileHandle)}. */
  Classpath,

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
* @author mzechner
* @author Nathan Sweet */
class FileHandle 
{
public:
  FileHandle();
  FileHandle( std::string fileName);


  std::string path() const;
  std::string name() const;
  std::string extension() const;
  std::string nameWithoutExtension() const;
  std::string getFullPathName() const;
  FileType    type() const;


  FileHandleStream* getStream( FileAccess nFileAccess, StreamType nStreamType) const;








  /** Returns a java.io.File that represents this file handle. Note the returned file will only be usable for
  * {@link FileType#Absolute} and {@link FileType#External} file handles. */
  //File* file();

  
  /** Returns a stream for reading this file as bytes.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  /*public InputStream read () {
    if (type == FileType.Classpath || (type == FileType.Internal && !file.exists())) {
      InputStream input = FileHandle.class.getResourceAsStream("/" + file.getPath().replace('\\', '/'));
      if (input == null) throw new GdxRuntimeException("File not found: " + file + " (" + type + ")");
      return input;
    }
    try {
      return new FileInputStream(file());
    } catch (FileNotFoundException ex) {
      if (file().isDirectory())
        throw new GdxRuntimeException("Cannot open a stream to a directory: " + file + " (" + type + ")", ex);
      throw new GdxRuntimeException("Error reading file: " + file + " (" + type + ")", ex);
    }
  }*/

  /** Returns a reader for reading this file as characters.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  /*
  public Reader reader () {
    return new InputStreamReader(read());
  }
  */

  /** Returns a reader for reading this file as characters.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  /*
  public Reader reader (std::string charset) {
    try{return new InputStreamReader(read(), charset);
    } catch (UnsupportedEncodingException ex) {
      throw new GdxRuntimeException("Error reading file: " + this,ex);
    }
  }
  */

  /** Returns a buffered reader for reading this file as characters.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  /*
  public BufferedReader reader (int bufferSize) {
    return new BufferedReader(new InputStreamReader(read()), bufferSize);
  }
  */

  /** Returns a buffered reader for reading this file as characters.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  /*
  public BufferedReader reader (int bufferSize, std::string charset) {
    try {
      return new BufferedReader(new InputStreamReader(read(), charset), bufferSize);
    } catch (UnsupportedEncodingException ex) {
      throw new GdxRuntimeException("Error reading file: " + this,ex);
    }
  }
  */

  /** Reads the entire file into a std::string using the platform's default charset.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  /*
  public std::string readstd::string () {
    return readstd::string(null);
  }
  */

  /** Reads the entire file into a std::string using the specified charset.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  /*
  public std::string readstd::string (std::string charset) {
    std::stringBuilder output = new std::stringBuilder(512);
    InputStreamReader reader = null;
    try {
      if (charset == null)
        reader = new InputStreamReader(read());
      else
        reader = new InputStreamReader(read(), charset);
      char[] buffer = new char[256];
      while (true) {
        int length = reader.read(buffer);
        if (length == -1) break;
        output.append(buffer, 0, length);
      }
    } catch (IOException ex) {
      throw new GdxRuntimeException("Error reading layout file: " + this, ex);
    } finally {
      try {
        if (reader != null) reader.close();
      } catch (IOException ignored) {
      }
    }
    return output.tostd::string();
  }*/

  /** Reads the entire file into a byte array.
  * @throw GdxRuntimeException if the file handle represents a directory, doesn't exist, or could not be read. */
  /*
  public byte[] readBytes () {
    int length = (int)length();
    if (length == 0) length = 512;
    byte[] buffer = new byte[length];
    int position = 0;
    InputStream input = read();
    try {
      while (true) {
        int count = input.read(buffer, position, buffer.length - position);
        if (count == -1) break;
        position += count;
        if (position == buffer.length) {
          // Grow buffer.
          byte[] newBuffer = new byte[buffer.length * 2];
          System.arraycopy(buffer, 0, newBuffer, 0, position);
          buffer = newBuffer;
        }
      }
    } catch (IOException ex) {
      throw new GdxRuntimeException("Error reading file: " + this, ex);
    } finally {
      try {
        if (input != null) input.close();
      } catch (IOException ignored) {
      }
    }
    if (position < buffer.length) {
      // Shrink buffer.
      byte[] newBuffer = new byte[position];
      System.arraycopy(buffer, 0, newBuffer, 0, position);
      buffer = newBuffer;
    }
    return buffer;
  }
  */

  /** Reads the entire file into the byte array. The byte array must be big enough to hold the file's data.
  * @param bytes the array to load the file into
  * @param offset the offset to start writing bytes
  * @param size the number of bytes to read, see {@link #length()}
  * @return the number of read bytes */
  /*
  public int readBytes (byte[] bytes, int offset, int size) {
    InputStream input = read();
    int position = 0;
    try {
      while (true) {
        int count = input.read(bytes, offset + position, size - position);
        if (count <= 0) break;
        position += count;
      }
    } catch (IOException ex) {
      throw new GdxRuntimeException("Error reading file: " + this, ex);
    } finally {
      try {
        if (input != null) input.close();
      } catch (IOException ignored) {
      }
    }
    return position - offset;
  }
  */

  /** Returns a stream for writing to this file. Parent directories will be created if necessary.
  * @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  * @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  *        {@link FileType#Internal} file, or if it could not be written. */
  /*
  public OutputStream write (boolean append) {
    if (type == FileType.Classpath) throw new GdxRuntimeException("Cannot write to a classpath file: " + file);
    if (type == FileType.Internal) throw new GdxRuntimeException("Cannot write to an internal file: " + file);
    parent().mkdirs();
    try {
      return new FileOutputStream(file(), append);
    } catch (FileNotFoundException ex) {
      if (file().isDirectory())
        throw new GdxRuntimeException("Cannot open a stream to a directory: " + file + " (" + type + ")", ex);
      throw new GdxRuntimeException("Error writing file: " + file + " (" + type + ")", ex);
    }
  }
  */

  /** Reads the remaining bytes from the specified stream and writes them to this file. The stream is closed. Parent directories
  * will be created if necessary.
  * @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  * @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  *        {@link FileType#Internal} file, or if it could not be written. */
  /*
  public void write (InputStream input, boolean append) {
    OutputStream output = null;
    try {
      output = write(append);
      byte[] buffer = new byte[4096];
      while (true) {
        int length = input.read(buffer);
        if (length == -1) break;
        output.write(buffer, 0, length);
      }
    } catch (Exception ex) {
      throw new GdxRuntimeException("Error stream writing to file: " + file + " (" + type + ")", ex);
    } finally {
      try {
        if (input != null) input.close();
      } catch (Exception ignored) {
      }
      try {
        if (output != null) output.close();
      } catch (Exception ignored) {
      }
    }
  }
  */

  /** Returns a writer for writing to this file using the default charset. Parent directories will be created if necessary.
  * @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  * @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  *        {@link FileType#Internal} file, or if it could not be written. */
  /*
  public Writer writer (boolean append) {
    return writer(append, null);
  }
  */

  /** Returns a writer for writing to this file. Parent directories will be created if necessary.
  * @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  * @param charset May be null to use the default charset.
  * @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  *        {@link FileType#Internal} file, or if it could not be written. */
  /*
  public Writer writer (boolean append, std::string charset) {
    if (type == FileType.Classpath) throw new GdxRuntimeException("Cannot write to a classpath file: " + file);
    if (type == FileType.Internal) throw new GdxRuntimeException("Cannot write to an internal file: " + file);
    parent().mkdirs();
    try {
      FileOutputStream output = new FileOutputStream(file(), append);
      if (charset == null)
        return new OutputStreamWriter(output);
      else
        return new OutputStreamWriter(output, charset);
    } catch (IOException ex) {
      if (file().isDirectory())
        throw new GdxRuntimeException("Cannot open a stream to a directory: " + file + " (" + type + ")", ex);
      throw new GdxRuntimeException("Error writing file: " + file + " (" + type + ")", ex);
    }
  }
  */

  /** Writes the specified std::string to the file using the default charset. Parent directories will be created if necessary.
  * @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  * @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  *        {@link FileType#Internal} file, or if it could not be written. */
  /*
  public void writestd::string (std::string std::string, boolean append) {
    writestd::string(std::string, append, null);
  }
  */

  /** Writes the specified std::string to the file as UTF-8. Parent directories will be created if necessary.
  * @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  * @param charset May be null to use the default charset.
  * @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  *        {@link FileType#Internal} file, or if it could not be written. */
  /*public void writestd::string (std::string std::string, boolean append, std::string charset) {
    Writer writer = null;
    try {
      writer = writer(append, charset);
      writer.write(std::string);
    } catch (Exception ex) {
      throw new GdxRuntimeException("Error writing file: " + file + " (" + type + ")", ex);
    } finally {
      try {
        if (writer != null) writer.close();
      } catch (Exception ignored) {
      }
    }
  }
  */

  /** Writes the specified bytes to the file. Parent directories will be created if necessary.
  * @param append If false, this file will be overwritten if it exists, otherwise it will be appended.
  * @throw GdxRuntimeException if this file handle represents a directory, if it is a {@link FileType#Classpath} or
  *        {@link FileType#Internal} file, or if it could not be written. */
  /*public void writeBytes (byte[] bytes, boolean append) {
    OutputStream output = write(append);
    try {
      output.write(bytes);
    } catch (IOException ex) {
      throw new GdxRuntimeException("Error writing file: " + file + " (" + type + ")", ex);
    } finally {
      try {
        output.close();
      } catch (IOException ignored) {
      }
    }
  }*/

  /** Returns the paths to the children of this directory. Returns an empty list if this file handle represents a file and not a
  * directory. On the desktop, an {@link FileType#Internal} handle to a directory on the classpath will return a zero length
  * array.
  * @throw GdxRuntimeException if this file is an {@link FileType#Classpath} file. */
  void list( std::vector< FileHandle> &handles);
  
  /** Returns the paths to the children of this directory with the specified suffix. Returns an empty list if this file handle
  * represents a file and not a directory. On the desktop, an {@link FileType#Internal} handle to a directory on the classpath
  * will return a zero length array.
  * @throw GdxRuntimeException if this file is an {@link FileType#Classpath} file. */
  //void list( std::string suffix, std::vector< FileHandle> &handles);
  
  /** Returns true if this file is a directory. Always returns false for classpath files. On Android, an {@link FileType#Internal}
  * handle to an empty directory will return false. On the desktop, an {@link FileType#Internal} handle to a directory on the
  * classpath will return false. */
  bool isDirectory();

  /** Returns a handle to the child with the specified name.
  * @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} and the child
  *        doesn't exist. */
  FileHandle child( std::string name);

  /*
  public FileHandle parent () {
    File parent = file.getParentFile();
    if (parent == null) {
      if (type == FileType.Absolute)
        parent = new File("/");
      else
        parent = new File("");
    }
    return new FileHandle(parent, type);
  }
  */

  /** @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file. */
  /*
  public void mkdirs () {
    if (type == FileType.Classpath) throw new GdxRuntimeException("Cannot mkdirs with a classpath file: " + file);
    if (type == FileType.Internal) throw new GdxRuntimeException("Cannot mkdirs with an internal file: " + file);
    file().mkdirs();
  }
  */

  /** Returns true if the file exists. On Android, a {@link FileType#Classpath} or {@link FileType#Internal} handle to a directory
  * will always return false. */
  /*
  public boolean exists () {
    switch (type) {
    case Internal:
      if (file.exists()) return true;
      // Fall through.
    case Classpath:
      return FileHandle.class.getResource("/" + file.getPath().replace('\\', '/')) != null;
    }
    return file().exists();
  }
  */

  /** Deletes this file or empty directory and returns success. Will not delete a directory that has children.
  * @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file. */
  /*
  public boolean delete () {
    if (type == FileType.Classpath) throw new GdxRuntimeException("Cannot delete a classpath file: " + file);
    if (type == FileType.Internal) throw new GdxRuntimeException("Cannot delete an internal file: " + file);
    return file().delete();
  }
  */

  /** Deletes this file or directory and all children, recursively.
  * @throw GdxRuntimeException if this file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file. */
  /*
  public boolean deleteDirectory () {
    if (type == FileType.Classpath) throw new GdxRuntimeException("Cannot delete a classpath file: " + file);
    if (type == FileType.Internal) throw new GdxRuntimeException("Cannot delete an internal file: " + file);
    return deleteDirectory(file());
  }
  */

  /** Copies this file or directory to the specified file or directory. If this handle is a file, then 1) if the destination is a
  * file, it is overwritten, or 2) if the destination is a directory, this file is copied into it, or 3) if the destination
  * doesn't exist, {@link #mkdirs()} is called on the destination's parent and this file is copied into it with a new name. If
  * this handle is a directory, then 1) if the destination is a file, GdxRuntimeException is thrown, or 2) if the destination is
  * a directory, this directory is copied recursively into it as a subdirectory, overwriting existing files, or 3) if the
  * destination doesn't exist, {@link #mkdirs()} is called on the destination and this directory is copied recursively into it
  * as a subdirectory.
  * @throw GdxRuntimeException if the destination file handle is a {@link FileType#Classpath} or {@link FileType#Internal} file,
  *        or copying failed. */
  /*
  public void copyTo (FileHandle dest) {
    if (!isDirectory()) {
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
    dest = dest.child(name());
    copyDirectory(this, dest);
  }
  */

  /** Moves this file to the specified file, overwriting the file if it already exists.
  * @throw GdxRuntimeException if the source or destination file handle is a {@link FileType#Classpath} or
  *        {@link FileType#Internal} file. */
  /*
  public void moveTo (FileHandle dest) {
    if (type == FileType.Classpath) throw new GdxRuntimeException("Cannot move a classpath file: " + file);
    if (type == FileType.Internal) throw new GdxRuntimeException("Cannot move an internal file: " + file);
    copyTo(dest);
    delete();
  }
  */

  /** Returns the length in bytes of this file, or 0 if this file is a directory, does not exist, or the size cannot otherwise be
  * determined. */
  /*
  public long length () {
    if (type == FileType.Classpath || (type == FileType.Internal && !file.exists())) {
      InputStream input = read();
      try {
        return input.available();
      } catch (Exception ignored) {
      } finally {
        try {
          input.close();
        } catch (IOException ignored) {
        }
      }
      return 0;
    }
    return file().length();
  }
  */

  /** Returns the last modified time in milliseconds for this file. Zero is returned if the file doesn't exist. Zero is returned
  * for {@link FileType#Classpath} files. On Android, zero is returned for {@link FileType#Internal} files. On the desktop, zero
  * is returned for {@link FileType#Internal} files on the classpath. */
  /*
  public long lastModified () {
    return file().lastModified();
  }

  public std::string tostd::string () {
    return file.getPath();
  }

  static public FileHandle tempFile (std::string prefix) {
    try {
      return new FileHandle(File.createTempFile(prefix, null));
    } catch (IOException ex) {
      throw new GdxRuntimeException("Unable to create temp file.", ex);
    }
  }

  static public FileHandle tempDirectory (std::string prefix) {
    try {
      File file = File.createTempFile(prefix, null);
      if (!file.delete()) throw new IOException("Unable to delete temp file: " + file);
      if (!file.mkdir()) throw new IOException("Unable to create temp directory: " + file);
      return new FileHandle(file);
    } catch (IOException ex) {
      throw new GdxRuntimeException("Unable to create temp file.", ex);
    }
  }

  static private boolean deleteDirectory (File file) {
    if (file.exists()) {
      File[] files = file.listFiles();
      if (files != null) {
        for (int i = 0, n = files.length; i < n; i++) {
          if (files[i].isDirectory())
            deleteDirectory(files[i]);
          else
            files[i].delete();
        }
      }
    }
    return file.delete();
  }

  static private void copyFile (FileHandle source, FileHandle dest) {
    try {
      dest.write(source.read(), false);
    } catch (Exception ex) {
      throw new GdxRuntimeException("Error copying source file: " + source.file + " (" + source.type + ")\n" //
        + "To destination: " + dest.file + " (" + dest.type + ")", ex);
    }
  }

  static private void copyDirectory (FileHandle sourceDir, FileHandle destDir) {
    destDir.mkdirs();
    FileHandle[] files = sourceDir.list();
    for (int i = 0, n = files.length; i < n; i++) {
      FileHandle srcFile = files[i];
      FileHandle destFile = destDir.child(srcFile.name());
      if (srcFile.isDirectory())
        copyDirectory(srcFile, destFile);
      else
        copyFile(srcFile, destFile);
    }
  }
  */

protected:
  //File* m_pFile;
  //FileType m_nType;
  std::string m_strFullPath;
};
