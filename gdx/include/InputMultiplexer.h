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

#include "InputProcessor.h"

/** An {@link InputProcessor} that delegates to an ordered list of other InputProcessors. Delegation for an event stops if a
 * processor returns true, which indicates that the event was handled.*/

class InputMultiplexer :
	public InputProcessor
{
private:
	typedef std::list<InputProcessor*> InputProcessorsList;
	typedef InputProcessorsList::iterator InputProcessorsListIterator;
	InputProcessorsList m_processors;

public:
	InputMultiplexer();

	InputMultiplexer(InputProcessor* processors[], int numProcessors);

	void addProcessor(int index, InputProcessor* processor);

	void removeProcessor(int index);

	void addProcessor(InputProcessor* processor);

	void removeProcessor(InputProcessor* processor);

	/**
	 * @return the number of processors in this multiplexer
	 */
	int size();

	void clear();

	void setProcessors(InputProcessorsList processors);

	InputProcessorsList getProcessors();

	bool keyDown(int keycode);

	bool keyUp(int keycode);

	bool keyTyped(char character);

	bool touchDown(int x, int y, int pointer, int button);

	bool touchUp (int x, int y, int pointer, int button);

	bool touchDragged (int x, int y, int pointer);

	bool touchMoved (int x, int y);

	bool scrolled (int amount);
};
