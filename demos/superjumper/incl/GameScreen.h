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
#include "Screen.h"
#include "OrthographicCamera.h"
#include "Vector3.h"
#include "SpriteBatch.h"
#include "World.h"
#include "WorldListener.h"
#include "WorldRenderer.h"
#include "Rectang.h"
#include "Game.h"

class GameScreen :
	public Screen
{
private:
	static const int GAME_READY;
	static const int GAME_RUNNING;
	static const int GAME_PAUSED;
	static const int GAME_LEVEL_END;
	static const int GAME_OVER;

	int m_state;
	OrthographicCamera m_guiCam;
	Vector3 m_touchPoint;
	SpriteBatch* m_batcher;
	World* m_world;
	WorldListener* m_worldListener;
	WorldRenderer* m_renderer;
	Rectang m_pauseBounds;
	Rectang m_resumeBounds;
	Rectang m_quitBounds;
	int m_lastScore;
	std::string m_scoreString;

public:
	GameScreen(Game* game);
	~GameScreen();

	void pause();
	void resume();

private:
	void update(float deltaTime);
	void updateReady();

	void updateRunning(float deltaTime);
	void updatePaused();
	void updateLevelEnd();
	void updateGameOver();

	void present(float deltaTime);
	void presentReady();
	void presentRunning();
	void presentPaused();
	void presentLevelEnd();
	void presentGameOver();

public:
};
