/*******************************************************************************
 * Copyright 2011 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License") = 0;
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

#include "Matrix4.h"

class ImmediateModeRenderer
{
public:
	virtual ~ImmediateModeRenderer() {}

	virtual void begin(const Matrix4& projModelView, int primitiveType) = 0;
	virtual void color(float r, float g, float b, float a) = 0;
	virtual void texCoord(float u, float v) = 0;
	virtual void normal(float x, float y, float z) = 0;
	virtual void vertex(float x, float y, float z) = 0;
	virtual void end() = 0;
	virtual int getNumVertices() = 0;
	virtual int getMaxVertices() = 0;
};
