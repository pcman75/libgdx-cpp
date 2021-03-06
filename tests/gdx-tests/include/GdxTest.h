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
#include "ApplicationListener.h"

#define GDX_DEFINE_CREATOR(className) static GdxTest* createInstance() \
	{ \
		return new className(); \
	}

class GdxTest :
	public ApplicationListener
{
public:

	virtual bool needsGL20()
	{
		return false;
	}

	virtual void create ()
	{
	}

	virtual void resume ()
	{
	}

	virtual void render ()
	{
	}

	virtual void resize (int width, int height)
	{
	}

	virtual void pause ()
	{
	}

	virtual void dispose ()
	{
	}
};
