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

#include "DynamicGameObject.h"

class Platform :
	public DynamicGameObject 
{
public:
	static const float PLATFORM_WIDTH;
	static const float PLATFORM_HEIGHT;
	static const int PLATFORM_TYPE_STATIC;
	static const int PLATFORM_TYPE_MOVING;
	static const int PLATFORM_STATE_NORMAL;
	static const int PLATFORM_STATE_PULVERIZING;
	static const float PLATFORM_PULVERIZE_TIME;
	static const float PLATFORM_VELOCITY;

	int type;
	int state;
	float stateTime;

	Platform (int type, float x, float y);
	void update (float deltaTime);
	void pulverize ();
};
