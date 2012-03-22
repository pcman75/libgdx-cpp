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
#include "GdxRuntimeException.h"
#include "GdxDefines.h"

/** An ImmediateModeRenderer allows you to perform immediate mode rendering as you were accustomed to in your desktop OpenGL
 * environment. In order to draw something you first have to call {@link ImmediateModeRenderer10#begin(int)} with the primitive
 * type you want to render. Next you specify as many vertices as you want by first defining the vertex color, normal and texture
 * coordinates followed by the vertex position which finalizes the definition of a single vertex. When you are done specifying the
 * geometry you have to call {@link ImmediateModeRenderer10#end()} to make the renderer render the geometry. Internally the
 * renderer uses vertex arrays to render the provided geometry. This is not the best performing way to do this so use this class
 * only for non performance critical low vertex count geometries while debugging.
 *
 * Note that this class of course only works with OpenGL ES 1.x.
 */
class GdxDllImportExport ImmediateModeRenderer10 :
	public ImmediateModeRenderer
{
private:
	/** the primitive type **/
	int m_primitiveType;

	/** the vertex position array and buffer **/
	float* m_positions;

	/** the vertex color array and buffer **/
	float* m_colors;

	/** the vertex normal array and buffer **/
	float* m_normals;

	/** the texture coordinate array and buffer **/
	float* m_texCoords;

	/** the current vertex attribute indices **/
	int m_idxPos;
	int m_idxCols;
	int m_idxNors;
	int m_idxTexCoords;

	bool m_hasCols;
	bool m_hasNors;
	bool m_hasTexCoords;

	int m_maxVertices;
	int m_numVertices;

public:
	ImmediateModeRenderer10();
	ImmediateModeRenderer10(int maxVertices);

	~ImmediateModeRenderer10();

	void begin(const Matrix4& projModelView, int primitiveType);

	/** Starts a new list of primitives. The primitiveType specifies which primitives to draw. Can be any of GL10.GL_TRIANGLES,
	 * GL10.GL_LINES and so on. A maximum of 6000 vertices can be drawn at once.
	 *
	 * @param primitiveType the primitive type. */
	void begin(int primitiveType);

	/** Specifies the color of the current vertex
	 * @param r the red component
	 * @param g the green component
	 * @param b the blue component
	 * @param a the alpha component */
	void color(float r, float g, float b, float a);

	/** Specifies the normal of the current vertex
	 * @param x the x component
	 * @param y the y component
	 * @param z the z component */
	void normal(float x, float y, float z);

	/** Specifies the texture coordinates of the current vertex
	 * @param u the u coordinate
	 * @param v the v coordinate */
	void texCoord(float u, float v);

	/** Specifies the position of the current vertex and finalizes it. After a call to this method you will effectively define a new
	 * vertex afterwards.
	 *
	 * @param x the x component
	 * @param y the y component
	 * @param z the z component */
	void vertex(float x, float y, float z);

	int getNumVertices();
	int getMaxVertices();

	/** Renders the primitives just defined. */
	void end();
	void vertex(const Vector3& point);

private:
	void init(int maxVertices);
};
