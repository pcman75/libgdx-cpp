#include "stdafx.h"
#include "Settings.h"
#include "Gdx.h"

bool Settings::soundEnabled = true;
int Settings::highscores[] = {100, 80, 50, 30, 10};
const char* Settings::file = ".superjumper";

void Settings::load()
{
	std::ifstream in;
	try
	{
		Gdx.files->externalHandle(file).read(in);
		in >> soundEnabled;
		for(int i = 0; i < 5; i++)
		{
			in >> highscores[i];
		}
	}
	catch(std::exception& e)
	{
		// :( It's ok we have defaults
		Gdx.app->log("loading", std::string("error loading high score ") + e.what());
	}

	in.close();
}

void Settings::save()
{
    /*
	std::ofstream out;
	Gdx.files->externalHandle(file).write(false, out);

	try
	{
		out << soundEnabled << "\n";
		for(int i = 0; i < 5; i++)
		{
			out << highscores[i] << "\n";
		}
	}
	catch(std::exception& e)
	{
		Gdx.app->log("save", std::string("error saving high score ") + e.what());
	}
	out.close();*/
}

void Settings::addScore(int score)
{
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
}

