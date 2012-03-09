#pragma once
#include "WorldListener.h"

class SoundController :
	public WorldListener
{
public:
	void jump();
	void highJump();
	void hit();
	void coin();
};