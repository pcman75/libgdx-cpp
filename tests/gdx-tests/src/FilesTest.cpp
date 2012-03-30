#include "stdafx.h"
#include "FilesTest.h"
#include "GdxRuntimeException.h"

void FilesTest::create()
{
	//font = new BitmapFont();
	//batch = new SpriteBatch();

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
			FileHandle* testFile = Gdx.files->externalHandle("GdxTests/test.txt");
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
		
/*
		try
		{
			InputStream in = Gdx.files.external("test.txt").read();
			try
			{
				in.close();
			}
			catch(IOException e)
			{
			}
			message += "Open external success\n";
		}
		catch(Throwable e)
		{
			message += "Couldn't open internal externalstorage/test.txt\n" + e.getMessage() + "\n";
		}

		BufferedReader in = null;
		try
		{
			in = new BufferedReader(new InputStreamReader(Gdx.files.external("test.txt").read()));
			if(!in.readLine().equals("test"))
				message += "Read result wrong\n";
			else
				message += "Read external success\n";
		}
		catch(GdxRuntimeException ex)
		{
			message += "Couldn't open externalstorage/test.txt\n";
		}
		catch(IOException e)
		{
			message += "Couldn't read externalstorage/test.txt\n";
		}
		finally
		{
			if(in != null)
			{
				try
				{
					in.close();
				}
				catch(IOException e)
				{
				}
			}
		}

		if(!Gdx.files.external("test.txt").delete()) message += "Couldn't delete externalstorage/test.txt";
		*/
	}
	else
	{
		message += "External storage not available";
	}

	try
	{
		testClasspath();
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

void FilesTest::testClasspath()
{
	/*
	FileHandle handle = Gdx.files.classpath("com/badlogic/gdx/utils/arial-15.png");
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
	try 
	{
		handle.list();
		fail();
	}
	catch(Exception expected)
	{
	}
	try 
	{
		handle.read().close();
		fail();
	}
	catch(Exception ignored)
	{
	}
	FileHandle dir = Gdx.files.classpath("com/badlogic/gdx/utils");
	if(dir.isDirectory()) fail();
	FileHandle child = dir.child("arial-15.fnt");
	if(!child.name().equals("arial-15.fnt")) fail();
	if(!child.nameWithoutExtension().equals("arial-15")) fail();
	if(!child.extension().equals("fnt")) fail();
	handle.read().close();
	if(handle.readBytes().length != handle.length()) fail();
	*/
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
	/*
	String path = "meow";
	FileHandle handle = Gdx.files.external(path);
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
	FileHandle copy = Gdx.files.external(path + "-copy");
	copy.delete();
	if(copy.exists()) fail();
	handle.copyTo(copy);
	if(!copy.exists()) fail();
	if(copy.length() != 3) fail();
	FileHandle move = Gdx.files.external(path + "-move");
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

