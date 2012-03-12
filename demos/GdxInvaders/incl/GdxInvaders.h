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

#include "ApplicationListener.h"
#include "Screen.h"

class GdxInvaders :
	public ApplicationListener 
{
private:
	/** flag indicating whether we were initialized already **/
	bool m_isInitialized;

	/** the current screen **/
	Screen* screen;

	
public:
	GdxInvaders();

	virtual void dispose ();
	virtual void render ();
	virtual void resize (int width, int height);
	virtual void create ();
	virtual void pause ();
	virtual void resume ();
};
