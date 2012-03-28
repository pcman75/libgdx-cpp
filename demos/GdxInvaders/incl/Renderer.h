/*
 * Copyright 2010 Mario Zechner (contact@badlogicgames.com), Nathan Sweet (admin@esotericsoftware.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the
 * License. You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS"
 * BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 */

#pragma once

#include "SpriteBatch.h"
#include "Mesh.h"
#include "Texture.h"
#include "BitmapFont.h"
#include "Matrix4.h"
#include "PerspectiveCamera.h"
#include "Simulation.h"
#include "Ship.h"


/** The renderer receives a simulation and renders it.*/
class Renderer 
{
private:
	/** sprite batch to draw text **/
	SpriteBatch* m_spriteBatch;
	/** the ship mesh **/
	Mesh* m_shipMesh;
	/** the ship texture **/
	Texture* m_shipTexture;
	/** the invader mesh **/
	Mesh* m_invaderMesh;
	/** the invader texture **/
	Texture* m_invaderTexture;
	/** the block mesh **/
	Mesh* m_blockMesh;
	/** the shot mesh **/
	Mesh* m_shotMesh;
	/** the background texture **/
	Texture* m_backgroundTexture;
	/** the explosion mesh **/
	Mesh* m_explosionMesh;
	/** the explosion texture **/
	Texture* m_explosionTexture;
	/** the font **/
	BitmapFont* m_font;
	/** the rotation angle of all invaders around y **/
	float m_invaderAngle;
	/** status string **/
	std::string m_status;
	/** keeping track of the last score so we don't constantly construct a new string **/
	int m_lastScore;
	int m_lastLives;
	int m_lastWave;

	/** view and transform matrix for text rendering **/
	Matrix4 m_viewMatrix;
	Matrix4 m_transformMatrix;

	/** perspective camera **/
	PerspectiveCamera* m_camera;

public:
	Renderer(Application* app);

	void render(Application* app, Simulation* simulation);
	void renderBackground();
	void setProjectionAndCamera(Graphics* graphics, const Ship& ship, Application* app);
	void setLighting ();
	void renderShip(const Ship& ship, Application* app);
	void renderInvaders(const Simulation::Invaders& invaders);
	void renderBlocks(const Simulation::Blocks& blocks);
	void renderShots(const Simulation::Shots& shots);
	void renderShot(const Shot& shot);
	void renderExplosions(const Simulation::Explosions& explosions);
	void dispose();
};
