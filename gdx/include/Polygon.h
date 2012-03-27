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


#include "Rectang.h"

class Polygon 
{
public:
	Polygon();
	Polygon( const std::vector<float>& vertices);

	std::vector<float> getVertices();

	void setOrigin( float originX, float originY);

	void setPosition( float x, float y);

	void translate( float x, float y);

	void setRotation( float degrees);

	void rotate( float degrees);

	void setScale( float scaleX, float scaleY);

	void scale( float amount);

	float area();

	Rectang getBoundingRectangle();

	bool contains( float x, float y);

	float getX();

	float getY();

	float getOriginX();

	float getOriginY();

	float getRotation();

	float getScaleX();

	float getScaleY();

private:
  std::vector<float> m_vertices;
	float m_x, m_y;
	float m_originX, m_originY;
	float m_rotation;
	float m_scaleX, m_scaleY;
	bool  m_dirty;
	Rectang m_bounds;
};
