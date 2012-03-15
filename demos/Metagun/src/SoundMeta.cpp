#include "stdafx.h"
#include "SoundMeta.h"

/*
Sound* SoundMeta::boom = NULL;
Sound* SoundMeta::hit = NULL;
Sound* SoundMeta::splat = NULL;
Sound* SoundMeta::launch = NULL;
Sound* SoundMeta::pew = NULL;
Sound* SoundMeta::oof = NULL;
Sound* SoundMeta::gethat = NULL;
Sound* SoundMeta::death = NULL;
Sound* SoundMeta::startgame = NULL;
Sound* SoundMeta::jump = NULL;
*/


void SoundMeta::load () 
{
  /*
	boom = load("res/boom.wav");
	hit = load("res/hit.wav");
	splat = load("res/splat.wav");
	launch = load("res/launch.wav");
	pew = load("res/pew.wav");
	oof = load("res/oof.wav");
	gethat = load("res/gethat.wav");
	death = load("res/death.wav");
	startgame = load("res/startgame.wav");
	jump = load("res/jump.wav");
  */
}

Sound* SoundMeta::load( std::string name) 
{
  return Gdx.audio->newSound(Gdx.files->internalHandle(name));
}