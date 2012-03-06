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

#include "OrthographicCamera.h"
#include "SpriteBatch.h"
#include "Rectang.h"
#include "Vector3.h"

class MainMenuScreen :
	public Screen
{
	OrthographicCamera* m_guiCam;
	SpriteBatch* m_batcher;
	Rectang m_soundBounds;
	Rectang m_playBounds;
	Rectang m_highscoresBounds;
	Rectang m_helpBounds;
	Vector3 m_touchPoint;

public:
	MainMenuScreen(Game* game);
	~MainMenuScreen();

	void update(float deltaTime);
	void present(float deltaTime);
	void pause();
	void resume();
	void dispose();
};
