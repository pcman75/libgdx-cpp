#include "stdafx.h"
#include "FilesTest.h"
#include "GdxRuntimeException.h"

void FilesTest::create()
{
	font = new BitmapFont();
	batch = new SpriteBatch();

	if(Gdx.files->isExternalStorageAvailable())
	{
		message += "External storage available\n";
		std::string externalStoragePath;
		Gdx.files->getExternalStoragePath(externalStoragePath);
		message += "External storage path: " + externalStoragePath + "\n";
		try
		{
			FileHandle* cube = Gdx.files->internalHandle("data/cube.obj");
			std::ifstream in;
			cube->read(in);
			delete cube;
			try
			{
				in.close();
			}
			catch(std::exception e)
			{
			}
			message += "Open internal success\n";
		}
		catch(std::exception e)
		{
			message += "Couldn't open internal data/cube.obj\n";
			message += e.what();
			message += "\n";
		}

		try
		{
			FileHandle* testFile = Gdx.files->externalHandle("test.txt");
			std::ofstream testStream;
			testFile->write(false, testStream);
			delete testFile;
			testStream << "test";
			testStream.close();
			
			message += "Write external success\n";
		}
		catch(GdxRuntimeException ex)
		{
			message += "Couldn't open externalstorage/test.txt\n";
		}
		catch(std::exception e)
		{
			message += "Couldn't write externalstorage/test.txt\n";
		}
		
		try
		{
			FileHandle* testFile = Gdx.files->externalHandle("test.txt");
			std::ifstream in;
			testFile->read(in);
			in.close();
			delete testFile;
			message += "Open external success\n";
		}
		catch(GdxRuntimeException e)
		{
			message += "Couldn't open internal externalstorage/test.txt\n";
		}

		FileHandle* file = Gdx.files->externalHandle("test.txt");
		if(!file->remove())
		{
			message += "Couldn't delete externalstorage/test.txt";
		}
		delete file;

		file = Gdx.files->externalHandle("this/is/a/test");
		file->mkdirs();
		file->remove();

		//memory leak here
		if(!file->parent()->remove())
			message += "failed to remove this/is/a/ directory";
		//bigger leak here
		if(!file->parent()->parent()->parent()->removeRecursive())
			message += "failed to remove this directory";

		delete file;
		
	}
	else
	{
		message += "External storage not available";
	}

	try
	{
		testInternal();
		testExternal();
		testAbsolute();
	}
	catch(std::exception ex)
	{
		throw GdxRuntimeException(ex.what());
	}
}
void FilesTest::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	batch->begin();
	font->drawMultiLine(batch, message, 20, Gdx.graphics->getHeight() - 20.f);
	batch->end();
}

bool FilesTest::needsGL20()
{
	return false;
}

void FilesTest::testInternal()
{
	FileHandle* handle = Gdx.files->internalHandle("data/badlogic.jpg");
	if(!handle->exists()) 
		fail();
	if(handle->isDirectory()) 
		fail();

	try 
	{
		handle->remove();
		fail();
	}
	catch(GdxRuntimeException expected)
	{
	}

	std::vector<FileHandle> files;
	handle->list(files);
	if(files.size() != 0)
		fail();
	if(!handle->parent()->exists()) 
		fail();
	try 
	{
		std::ifstream input;
		handle->read(input);
		input.close();
		//TODO: why???
		fail();
	}
	catch(GdxRuntimeException ignored)
	{
	}
	handle;

	FileHandle* dir;
	dir = Gdx.files->internalHandle("data");

	if(!dir->exists()) 
		fail();
	if(!dir->isDirectory()) 
		fail();

	dir->list(files);
	if(files.size() == 0)
		fail();
	
	FileHandle* child = dir->child("badlogic.jpg");
	delete dir;

	if(child->name() != "badlogic.jpg")
		fail();

	if(child->nameWithoutExtension() != "badlogic")
		fail();

	if(child->extension() != "jpg") 
		fail();
	
	if(!child->parent()->exists()) 
		fail();
	delete child;

	FileHandle* copy = Gdx.files->externalHandle("badlogic.jpg-copy");
	copy->remove();
	if(copy->exists()) 
		fail();
	handle->copyTo(copy);

	if(!copy->exists()) 
		fail();
	if(copy->length() != 68465) 
		fail();
	copy->remove();
	
	if(copy->exists()) 
		fail();
}

void FilesTest::testExternal()
{
	std::string path = "meow";
	FileHandle* handle = Gdx.files->externalHandle(path);
	handle->remove();
	if(handle->exists()) 
		fail();
	if(handle->isDirectory()) 
		fail();
	if(handle->remove()) 
		fail();

	std::vector<FileHandle> handles;
	handle->list(handles);
	if(handles.size() != 0)
		fail();

	if(handle->child("meow")->exists()) 
		fail();

	if(!handle->parent()->exists()) 
		fail();
	try 
	{
		std::ifstream in;
		handle->read(in);
		in.close();
		fail();
	}
	catch(GdxRuntimeException ignored)
	{
	}
	handle->mkdirs();
	if(!handle->exists()) 
		fail();
	if(!handle->isDirectory()) 
		fail();
	handle->list(handles);
	if(handles.size() != 0)
		fail();

	handle->child("meow")->mkdirs();

	handle->list(handles);
	if(handles.size() != 1) 
		fail();
	
	FileHandle child = handles[0];
	if(child.name() != "meow")
		fail();
	
	if(!child.parent()->exists()) 
		fail();
	
	if(!handle->removeRecursive()) 
		fail();
	
	
	if(handle->exists()) 
		fail();
	
	std::ofstream output;
	handle->write(false, output);
	output << "moo";
	output.close();
	if(!handle->exists()) 
		fail();

	if(handle->length() != 3) 
		fail();
	
	FileHandle* copy = Gdx.files->externalHandle(path + "-copy");
	copy->remove();
	if(copy->exists()) 
		fail();
	
	handle->copyTo(copy);
	if(!copy->exists()) 
		fail();

	if(copy->length() != 3) 
		fail();
	
	FileHandle* move = Gdx.files->externalHandle(path + "-move");
	move->remove();
	if(move->exists()) 
		fail();
	copy->moveTo(move);
	if(!move->exists()) 
		fail();
	if(move->length() != 3) 
		fail();
	move->removeRecursive();
	if(move->exists()) 
		fail();
	delete copy;
	delete move;

	std::ifstream input;
	handle->read(input);

	char bytes[7];
	input.read(bytes, 3);
	bytes[3] = 0;
	if(strcmp("moo", bytes))
		fail();
	input.close();

	handle->write(true, output);
	output << "cow";
	output.close();
	if(handle->length() != 6) 
		fail();

	handle->readBytes((unsigned char*)bytes, 6);
	bytes[6] = 0;
	if(strcmp("moocow", bytes))
		fail();
	if(handle->isDirectory()) fail();
	
	std::vector<FileHandle> files;
	handle->list(files);
	if(files.size() != 0) 
		fail();

	if(handle->name() != "meow")
		fail();
	
	if(handle->nameWithoutExtension() != "meow")
		fail();
	if(handle->extension() != "")
		fail();
	
	handle->remove();

	if(handle->exists()) 
		fail();
	if(handle->isDirectory()) 
		fail();
	
	handle->remove();
	handle->removeRecursive();
}

void FilesTest::testAbsolute()
{
	std::string path; 
	Gdx.files->getExternalStoragePath(path);
	path += "/meow";

	FileHandle* handle = Gdx.files->absoluteHandle(path);
	handle->remove();
	if(handle->exists()) 
		fail();
	if(handle->isDirectory()) 
		fail();
	if(handle->remove()) 
		fail();

	std::vector<FileHandle> handles;
	handle->list(handles);
	if(handles.size() != 0)
		fail();

	if(handle->child("meow")->exists()) 
		fail();

	if(!handle->parent()->exists()) 
		fail();
	try 
	{
		std::ifstream in;
		handle->read(in);
		in.close();
		fail();
	}
	catch(GdxRuntimeException ignored)
	{
	}
	handle->mkdirs();
	if(!handle->exists()) 
		fail();
	if(!handle->isDirectory()) 
		fail();
	handle->list(handles);
	if(handles.size() != 0)
		fail();

	handle->child("meow")->mkdirs();

	handle->list(handles);
	if(handles.size() != 1) 
		fail();
	
	FileHandle child = handles[0];
	if(child.name() != "meow")
		fail();
	
	if(!child.parent()->exists()) 
		fail();
	
	if(!handle->removeRecursive()) 
		fail();
	
	
	if(handle->exists()) 
		fail();
	
	std::ofstream output;
	handle->write(false, output);
	output << "moo";
	output.close();
	if(!handle->exists()) 
		fail();

	if(handle->length() != 3) 
		fail();
	
	FileHandle* copy = Gdx.files->absoluteHandle(path + "-copy");
	copy->remove();
	if(copy->exists()) 
		fail();
	
	handle->copyTo(copy);
	if(!copy->exists()) 
		fail();

	if(copy->length() != 3) 
		fail();
	
	FileHandle* move = Gdx.files->absoluteHandle(path + "-move");
	move->remove();
	if(move->exists()) 
		fail();
	copy->moveTo(move);
	if(!move->exists()) 
		fail();
	if(move->length() != 3) 
		fail();
	move->removeRecursive();
	if(move->exists()) 
		fail();
	delete copy;
	delete move;

	std::ifstream input;
	handle->read(input);

	char bytes[7];
	input.read(bytes, 3);
	bytes[3] = 0;
	if(strcmp("moo", bytes))
		fail();
	input.close();

	handle->write(true, output);
	output << "cow";
	output.close();
	if(handle->length() != 6) 
		fail();

	handle->readBytes((unsigned char*)bytes, 6);
	bytes[6] = 0;
	if(strcmp("moocow", bytes))
		fail();
	if(handle->isDirectory()) fail();
	
	std::vector<FileHandle> files;
	handle->list(files);
	if(files.size() != 0) 
		fail();

	if(handle->name() != "meow")
		fail();
	
	if(handle->nameWithoutExtension() != "meow")
		fail();
	if(handle->extension() != "")
		fail();
	
	handle->remove();

	if(handle->exists()) 
		fail();
	if(handle->isDirectory()) 
		fail();
	
	handle->remove();
	handle->removeRecursive();
}
void FilesTest::fail()
{
	throw GdxRuntimeException("FilesTest failed");
}

