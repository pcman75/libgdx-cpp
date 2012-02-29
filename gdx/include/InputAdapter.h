/*******************************************************************************
 * Copyright 2011 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0(the "License");
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

#include "InputProcessor.h"

/** An adapter class for {@link InputProcessor}. You can derive from this and only override what you are interested in.*/

class InputAdapter : public InputProcessor
{
	virtual bool keyDown(int keycode);
	virtual bool keyUp(int keycode);
	virtual bool keyTyped(char character);
	virtual bool touchDown(int x, int y, int pointer, int button);
	virtual bool touchUp(int x, int y, int pointer, int button);
	virtual bool touchDragged(int x, int y, int pointer);
	virtual bool touchMoved(int x, int y);
	virtual bool scrolled(int amount);
};
