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
	/*
	FileHandle handle = Gdx.files->internalHandle("data/badlogic.jpg");
	if(!handle.exists()) 
		fail();
	if(handle.isDirectory()) 
		fail();

	try 
	{
		handle.delete();
		fail();
	}
	catch(Exception expected)
	{
	}

	if(handle.list().length != 0) fail();
	if(!handle.parent().exists()) fail();
	try {
		handle.read().close();
		fail();
	}
	catch(Exception ignored)
	{
	}
	FileHandle dir;
	if(Gdx.app.getType() == ApplicationType.Android)
		dir = Gdx.files.internal("data");
	else
		dir = Gdx.files.internal("../gdx-tests-android/assets/data");
	if(!dir.exists()) fail();
	if(!dir.isDirectory()) fail();
	if(dir.list().length == 0) fail();
	FileHandle child = dir.child("badlogic.jpg");
	if(!child.name().equals("badlogic.jpg")) fail();
	if(!child.nameWithoutExtension().equals("badlogic")) fail();
	if(!child.extension().equals("jpg")) fail();
	if(!child.parent().exists()) fail();
	FileHandle copy = Gdx.files.external("badlogic.jpg-copy");
	copy.delete();
	if(copy.exists()) fail();
	handle.copyTo(copy);
	if(!copy.exists()) fail();
	if(copy.length() != 68465) fail();
	copy.delete();
	if(copy.exists()) fail();
	handle.read().close();
	if(handle.readBytes().length != handle.length()) fail();
	*/
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

	/*
	std::ifstream input;
	handle->read(input);

	if(input.read(bytes) != 3) 
		fail();
	input.close();
	*/

	/*
	InputStream input = handle.read();
	byte[] bytes = new byte[6];
	if(input.read(bytes) != 3) fail();
	input.close();
	if(!new String(bytes, 0, 3).equals("moo")) fail();
	output = handle.write(true);
	output.write("cow".getBytes());
	output.close();
	if(handle.length() != 6) fail();
	input = handle.read();
	if(input.read(bytes) != 6) fail();
	input.close();
	if(!new String(bytes, 0, 6).equals("moocow")) fail();
	if(handle.isDirectory()) fail();
	if(handle.list().length != 0) fail();
	if(!handle.name().equals("meow")) fail();
	if(!handle.nameWithoutExtension().equals("meow")) fail();
	if(!handle.extension().equals("")) fail();
	handle.deleteDirectory();
	if(handle.exists()) fail();
	if(handle.isDirectory()) fail();
	handle.delete();
	handle.deleteDirectory();
	*/
}
void FilesTest::testAbsolute()
{
	/*
	String path = new File(Gdx.files.getExternalStoragePath(), "meow").getAbsolutePath();
	FileHandle handle = Gdx.files.absolute(path);
	handle.delete();
	if(handle.exists()) fail();
	if(handle.isDirectory()) fail();
	if(handle.delete()) fail();
	if(handle.list().length != 0) fail();
	if(handle.child("meow").exists()) fail();
	if(!handle.parent().exists()) fail();
	try {
		handle.read().close();
		fail();
	}
	catch(Exception ignored)
	{
	}
	handle.mkdirs();
	if(!handle.exists()) fail();
	if(!handle.isDirectory()) fail();
	if(handle.list().length != 0) fail();
	handle.child("meow").mkdirs();
	if(handle.list().length != 1) fail();
	FileHandle child = handle.list()[0];
	if(!child.name().equals("meow")) fail();
	if(!child.parent().exists()) fail();
	if(!handle.deleteDirectory()) fail();
	if(handle.exists()) fail();
	OutputStream output = handle.write(false);
	output.write("moo".getBytes());
	output.close();
	if(!handle.exists()) fail();
	if(handle.length() != 3) fail();
	FileHandle copy = Gdx.files.absolute(path + "-copy");
	copy.delete();
	if(copy.exists()) fail();
	handle.copyTo(copy);
	if(!copy.exists()) fail();
	if(copy.length() != 3) fail();
	FileHandle move = Gdx.files.absolute(path + "-move");
	move.delete();
	if(move.exists()) fail();
	copy.moveTo(move);
	if(!move.exists()) fail();
	if(move.length() != 3) fail();
	move.deleteDirectory();
	if(move.exists()) fail();
	InputStream input = handle.read();
	byte[] bytes = new byte[6];
	if(input.read(bytes) != 3) fail();
	input.close();
	if(!new String(bytes, 0, 3).equals("moo")) fail();
	output = handle.write(true);
	output.write("cow".getBytes());
	output.close();
	if(handle.length() != 6) fail();
	input = handle.read();
	if(input.read(bytes) != 6) fail();
	input.close();
	if(!new String(bytes, 0, 6).equals("moocow")) fail();
	if(handle.isDirectory()) fail();
	if(handle.list().length != 0) fail();
	if(!handle.name().equals("meow")) fail();
	if(!handle.nameWithoutExtension().equals("meow")) fail();
	if(!handle.extension().equals("")) fail();
	handle.deleteDirectory();
	if(handle.exists()) fail();
	if(handle.isDirectory()) fail();
	handle.delete();
	handle.deleteDirectory();
	*/
}
void FilesTest::fail()
{
	throw GdxRuntimeException("FilesTest failed");
}

