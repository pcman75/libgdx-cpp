/*******************************************************************************
 * Copyright 2011 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the
 * License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS"
 * BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 ******************************************************************************/
#pragma once

#include "GdxTest.h"
#include "BitmapFont.h"
#include "SpriteBatch.h"

class FilesTest :
	public GdxTest
{
	std::string message;
	bool success;
	BitmapFont* font;
	SpriteBatch* batch;

public:
	void create();
	void render();
	bool needsGL20();
	GDX_DEFINE_CREATOR(FilesTest);

private:
	void testClasspath();
	void testInternal();
	void testExternal();
	void testAbsolute();
	void fail();
};
