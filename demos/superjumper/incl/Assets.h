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
#include "Texture.h"
#include "TextureRegion.h"
#include "Animation.h"
#include "BitmapFont.h"

class Assets
{
public:
	static Texture background;
	static TextureRegion backgroundRegion;

	static Texture* items;
	static TextureRegion* mainMenu;
	static TextureRegion* pauseMenu;
	static TextureRegion* ready;
	static TextureRegion* gameOver;
	static TextureRegion* highScoresRegion;
	static TextureRegion* logo;
	static TextureRegion* soundOn;
	static TextureRegion* soundOff;
	static TextureRegion* arrow;
	static TextureRegion* pause;
	static TextureRegion* spring;
	static TextureRegion* castle;
	static Animation* coinAnim;
	static Animation* bobJump;
	static Animation* bobFall;
	static TextureRegion* bobHit;
	static Animation* squirrelFly;
	static TextureRegion* platform;
	static Animation* brakingPlatform;
	static BitmapFont* font;

	static Music* music;
	static Sound* jumpSound;
	static Sound* highJumpSound;
	static Sound* hitSound;
	static Sound* coinSound;
	static Sound* clickSound;

	static Texture* loadTexture(const char* file);
	static void load();
	static void playSound(Sound* sound);
};
