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
#include "Texture.h"

class HelpScreen :
	public Screen 
{
	OrthographicCamera m_guiCam;
	SpriteBatch* m_batcher;
	Rectang m_nextBounds;
	Vector3 m_touchPoint;
	Texture* m_helpImage;
	TextureRegion* m_helpRegion;
	int m_helpScreenNumber;

public:
	HelpScreen(Game* game, int helpScreenNumber);
	~HelpScreen();
	void resume();
	void pause();
	void update(float deltaTime);
	void present(float deltaTime);

private:
	const char* getPictureName();
};
