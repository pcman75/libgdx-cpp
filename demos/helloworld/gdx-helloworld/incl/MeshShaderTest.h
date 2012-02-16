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
#include "SpriteBatch.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture.h"
#include "Matrix4.h"

class MeshShaderTest  :
	public ApplicationListener
{
private:
	SpriteBatch* m_spriteBatch;
	ShaderProgram* m_shader;
	Mesh* m_mesh;
	Texture* m_texture;
	Matrix4 m_matrix;

	Vector3 m_axis;
	float m_angle;
public:
	MeshShaderTest();
	virtual ~MeshShaderTest();

	virtual void create ();
	virtual void render ();

	//TODO: note necessary. remove them after implementing Test base class
	virtual void resize (int width, int height) {}
	virtual void pause () {}
	virtual void resume () {}
	virtual void dispose () {}

};