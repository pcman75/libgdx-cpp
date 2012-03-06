#include "stdafx.h"
#include "Settings.h"

bool Settings::soundEnabled = true;
const int Settings::highscores[] = {100, 80, 50, 30, 10};
const char* Settings::file = ".superjumper";

void Settings::load()
{
	/*TODO:
	BufferedReader in = null;
	try
	{
		in = new BufferedReader(new InputStreamReader(Gdx.files->external(file).read()));
		soundEnabled = Boolean.parseBoolean(in.readLine());
		for(int i = 0; i < 5; i++)
		{
			highscores[i] = Integer.parseInt(in.readLine());
		}
	}
	catch(Throwable e)
	{
		// :( It's ok we have defaults
	} finally
	{
		try {
			if(in != null) in.close();
		}
		catch(IOException e)
		{
		}
	}
	*/
}

void Settings::save()
{
/*TODO:
	BufferedWriter out = null;
	try
	{
		out = new BufferedWriter(new OutputStreamWriter(Gdx.files.external(file).write(false)));
		out.write(Boolean.toString(soundEnabled));
		for(int i = 0; i < 5; i++)
		{
			out.write(Integer.toString(highscores[i]));
		}

	}
	catch(Throwable e)
	{
	} finally
	{
		try {
			if(out != null) out.close();
		}
		catch(IOException e)
		{
		}
	}
	*/
}

void Settings::addScore(int score)
{
	/*
	for(int i = 0; i < 5; i++)
	{
		if(highscores[i] < score)
		{
			for(int j = 4; j > i; j--)
				highscores[j] = highscores[j - 1];
			highscores[i] = score;
			break;
		}
	}
	*/
}

