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
#include "Application.h"

/** Interface for a game screen, e.g. main menu, game loop, game over screen and so on.*/
class Screen
{
public:
	virtual ~Screen() {}

	/** Called when the screen should update itself, e.g. continue a simulation etc.
	 *
	 * @param app the Application */
	virtual void update (Application* app) = 0;

	/** Called when a screen should render itself
	 * @param app */
	virtual void render(Application* app) = 0;

	/** Called by GdxInvaders to check whether the screen is done.
	 *
	 * @return true when the screen is done, false otherwise */
	virtual bool isDone() = 0;

	/** Cleans up all resources of the screen, e.g. meshes, textures etc. */
	virtual void dispose() = 0;
};
