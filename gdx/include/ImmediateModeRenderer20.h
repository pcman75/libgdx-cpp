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

#include "ImmediateModeRenderer.h"
#include "Mesh.h"

/** Immediate mode rendering class for GLES 2.0. The renderer will allow you to specify vertices on the fly and provides a default
 * shader for (unlit) rendering.</p> *
 */
class ImmediateModeRenderer20 :
	public ImmediateModeRenderer
{
private:
	int m_primitiveType;
	int m_vertexIdx;
	int m_numSetTexCoords;
	int m_maxVertices;
	int m_numVertices;

	Mesh* m_mesh;
	int m_numTexCoords;
	int m_vertexSize;
	int m_normalOffset;
	int m_colorOffset;
	int m_texCoordOffset;
	Matrix4 m_projModelView;
	float* m_vertices;
	ShaderProgram* m_customShader;
	ShaderProgram* m_defaultShader;

public:
	ImmediateModeRenderer20(bool hasNormals, bool hasColors, int numTexCoords);
	ImmediateModeRenderer20(int maxVertices, bool hasNormals, bool hasColors, int numTexCoords);
	virtual ~ImmediateModeRenderer20();

	void begin(const Matrix4& projModelView, int primitiveType);
	void begin(ShaderProgram* shader, int primitiveType);
	void color(float r, float g, float b, float a);
	void texCoord(float u, float v);
	void normal(float x, float y, float z);
	void vertex(float x, float y, float z);
	void end();

	int getNumVertices();
	int getMaxVertices();

private:
	void init(int maxVertices, bool hasNormals, bool hasColors, int numTexCoords);
	void buildVertexAttributes(bool hasNormals, bool hasColor, int numTexCoords, std::vector<VertexAttribute>& attribs);
	void createVertexShader(bool hasNormals, bool hasColors, int numTexCoords, std::string& shader);
	void createFragmentShader(bool hasNormals, bool hasColors, int numTexCoords, std::string& shader);
};
