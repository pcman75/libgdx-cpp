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
#include "Screen.h"
#include "OrthographicCamera.h"
#include "SpriteBatch.h"
#include "Rectang.h"
#include "Vector3.h"


class HighscoresScreen :
	public Screen 
{
	OrthographicCamera guiCam;
	SpriteBatch* batcher;
	Rectang backBounds;
	Vector3 touchPoint;
	std::string highScores[5];
	float xOffset;

public:
	HighscoresScreen(Game* game);
	~HighscoresScreen();
	void update(float deltaTime);
	void present (float deltaTime);
	void resume ();
	void pause ();
	void dispose ();
};
