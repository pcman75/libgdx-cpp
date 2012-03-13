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

#include "Vector3.h"

class Invader
{
public:
	static const float INVADER_RADIUS;
	static const float INVADER_VELOCITY;
	static const int INVADER_POINTS;
	static const int STATE_MOVE_LEFT;
	static const int STATE_MOVE_DOWN;
	static const int STATE_MOVE_RIGHT;

	Vector3 position;
	int state;
	bool wasLastStateLeft;
	float movedDistance;

public:
	Invader(const Vector3& position);
	void update(float delta, float speedMultiplier);
};
