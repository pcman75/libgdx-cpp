#include "stdafx.h"
#include "SoundController.h"
#include "Assets.h"

void SoundController::jump()
{
	Assets::playSound(Assets::jumpSound);
}


void SoundController::highJump()
{
	Assets::playSound(Assets::highJumpSound);
}


void SoundController::hit()
{
	Assets::playSound(Assets::hitSound);
}


void SoundController::coin()
{
	Assets::playSound(Assets::coinSound);
}
