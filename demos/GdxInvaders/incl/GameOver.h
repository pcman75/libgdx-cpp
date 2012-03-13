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

#include "Screen.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "BitmapFont.h"
#include "Matrix4.h"


/** The game over screen displays the final score and a game over text and waits for the user to touch the screen in which case it
 * will signal that it is done to the orchestrating GdxInvaders class.
 */
class GameOver :
	public Screen
{
private:
	/** the SpriteBatch used to draw the background, logo and text **/
	SpriteBatch* m_spriteBatch;
	/** the background texture **/
	Texture* m_background;
	/** the logo texture **/
	Texture* m_logo;
	/** the font **/
	BitmapFont* m_font;
	/** is done flag **/
	bool m_isDone;
	/** view & transform matrix **/
	Matrix4 m_viewMatrix;
	Matrix4 m_transformMatrix;

public:
	GameOver(Application* app);
	void dispose ();
	bool isDone();
	void render(Application* app);
	void update(Application* app);
};
