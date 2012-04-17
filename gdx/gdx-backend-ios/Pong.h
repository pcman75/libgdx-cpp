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

#include "GdxTest.h"
#include "OrthographicCamera.h"
#include "Mesh.h"
#include "SpriteBatch.h"
#include "Vector2.h"

/** A simple Pong remake showing how easy it is to quickly prototype a game with libgdx.*/
class Pong :
	public GdxTest
{
private:
	/** the camera **/
	OrthographicCamera* camera;
	/** the MeshRenderer for the paddles **/
	Mesh* paddleMesh;
	/** the MeshRenderer for the ball **/
	Mesh* ballMesh;
	
	/** the Font **/
	// private Font font;
	/** sprite batch **/
	SpriteBatch* spriteBatch;

	/** the position of the two paddles **/
	Vector2 leftPaddle;
	Vector2 rightPaddle;
	/** the scores of the left and right paddle **/
	int leftScore;
	int rightScore;
	/** the left paddle speed multiplicator, used so that the ai is not perfect **/
	float leftPaddleMulti;

	/** some constants **/
	static const int BALL_SPEED = 100;
	/** the position of the ball **/
	Vector2 ball;
	/** the ball direction **/
	Vector2 ballDirection;
	/** the current ball speed **/
	int ballSpeed;

	/** score string **/
	std::string score;

public:
	Pong();

	/** Here we setup all the resources. A MeshRenderer for the paddles which we use for both, a MeshRenderer for the ball and a
	 * Text for rendering the score. */
	void create();

	/** This method sets up all the graphics related stuff like the Meshes, the camera and the Font */
	void setupGraphics();

	/** This sets up the game data like the initial paddle positions and the ball position and direction. */
	void setupGame();

	void render();

	GDX_DEFINE_CREATOR(Pong);

private:
	/** Updates the game state, moves the ball, checks for collisions or whether the ball has left the playfield. */
	void updateGame();
};
