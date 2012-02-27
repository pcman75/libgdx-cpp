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

#include "GdxTest.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Shapes.h"

class SimpleVertexShader :
	public GdxTest
{
	ShaderProgram* shader;
	Mesh* mesh;
	Matrix4 projection;
	Matrix4 view;
	Matrix4 model;
	Matrix4 combined;
	Vector3 axis;// = new Vector3(1, 0, 1).nor();
	float angle;// = 45;

public:
	
	SimpleVertexShader()
	{
		axis = Vector3(1, 0, 1).nor();
		angle = 45.f;
	}

	bool needsGL20 ()
	{
		return true;
	}


	void create ()
	{
		std::string vertexShader = std::string("uniform mat4 u_mvpMatrix;                   \n") + "attribute vec4 a_position;                  \n"
		                      + "void main()                                 \n" + "{                                           \n"
		                      + "   gl_Position = u_mvpMatrix * a_position;  \n" + "}                            \n";
		std::string fragmentShader = std::string("#ifdef GL_ES\n") + "precision mediump float;\n" + "#endif\n"
		                        + "void main()                                  \n" + "{                                            \n"
		                        + "  gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n" + "}";

		shader = new ShaderProgram(vertexShader.c_str(), fragmentShader.c_str());
		mesh = Shapes::genCube();

		VertexAttribute attrib(-1, -1, "");;
		mesh->getVertexAttribute(VertexAttributes::Position, attrib);
		attrib.alias = "a_position";
	}

	void render ()
	{
		angle += Gdx.graphics->getDeltaTime() * 40.0f;
		float aspect = Gdx.graphics->getWidth() / (float)Gdx.graphics->getHeight();
		projection.setToProjection(1.0f, 20.0f, 60.0f, aspect);
		view.idt().trn(0, 0, -2.0f);
		model.setToRotation(axis, angle);
		combined.set(projection).mul(view).mul(model);

		Gdx.gl20->glViewport(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
		Gdx.gl20->glClear(GL20::GDX_GL_COLOR_BUFFER_BIT);
		shader->begin();
		shader->setUniformMatrix("u_mvpMatrix", combined);
		mesh->render(shader, GL20::GDX_GL_TRIANGLES);
		shader->end();

		//Gdx.app->log("angle", "" + angle);
	}

	GDX_DEFINE_CREATOR(SimpleVertexShader);
};
