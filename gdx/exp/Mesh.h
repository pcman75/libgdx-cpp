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

#include "VertexData.h"
#include "VertexAttribute.h"
#include "VertexAttributes.h"

#include "IndexData.h"
#include "Gdx.h"

/** <p>
 * A Mesh holds vertices composed of attributes specified by a {@link VertexAttributes} instance. The vertices are held either in
 * VRAM in form of vertex buffer objects or in RAM in form of vertex arrays. The former variant is more performant and is prefered
 * over vertex arrays if hardware supports it.
 * </p>
 * 
 * <p>
 * Meshes are automatically managed. If the OpenGL context is lost all vertex buffer objects get invalidated and must be reloaded
 * when the context is recreated. This only happens on Android when a user switches to another application or receives an incoming
 * call. A managed Mesh will be reloaded automagically so you don't have to do this manually.
 * </p>
 * 
 * <p>
 * A Mesh consists of vertices and optionally indices which specify which vertices define a triangle. Each vertex is composed of
 * attributes such as position, normal, color or texture coordinate. Note that not all of this attributes must be given, except
 * for position which is non-optional. Each attribute has an alias which is used when rendering a Mesh in OpenGL ES 2.0. The alias
 * is used to bind a specific vertex attribute to a shader attribute. The shader source and the alias of the attribute must match
 * exactly for this to work. For OpenGL ES 1.x rendering this aliases are irrelevant.
 * </p>
 * 
 * <p>
 * Meshes can be used with either OpenGL ES 1.x or OpenGL ES 2.0.
 * </p>
 */
class GdxDllImportExport Mesh
{
public:
	//TODO: changed the enums, otherwise they clash with classes name
	enum VertexDataType 
	{
		VertexArrayType, 
		VertexBufferObjectType, 
		VertexBufferObjectSubDataType
	};
	/** used for benchmarking **/
	static bool forceVBO;

private:
	/** list of all meshes **/
	//TODO: single application is not enough???
	//static final Map<Application, List<Mesh>> meshes = new HashMap<Application, List<Mesh>>();
	static std::list<Mesh*> m_meshes;
	VertexData* m_vertices;
	IndexData* m_indices;
	bool m_autoBind;
	bool m_isVertexArray;
	int m_refCount;

private:
	void init();

	

public:

	/** Creates a new Mesh with the given attributes.
	 * 
	 * @param isStatic whether this mesh is static or not. Allows for internal optimizations.
	 * @param maxVertices the maximum number of vertices this mesh can hold
	 * @param maxIndices the maximum number of indices this mesh can hold
	 * @param attributes the {@link VertexAttribute}s. Each vertex attribute defines one property of a vertex such as position,
	 *           normal or texture coordinate */
	Mesh(bool isStatic, const VertexAttribute& attribute);

	/** Creates a new Mesh with the given attributes.
	 * 
	 * @param isStatic whether this mesh is static or not. Allows for internal optimizations.
	 * @param maxVertices the maximum number of vertices this mesh can hold
	 * @param maxIndices the maximum number of indices this mesh can hold
	 * @param attributes the {@link VertexAttributes}. Each vertex attribute defines one property of a vertex such as position,
	 *           normal or texture coordinate */
	Mesh (bool isStatic, const VertexAttributes& attributes);

	/** Creates a new Mesh with the given attributes. This is an expert method with no error checking. Use at your own risk.
	 * 
	 * @param type the {@link VertexDataType} to be used, VBO or VA.
	 * @param isStatic whether this mesh is static or not. Allows for internal optimizations.
	 * @param maxVertices the maximum number of vertices this mesh can hold
	 * @param maxIndices the maximum number of indices this mesh can hold
	 * @param attributes the {@link VertexAttribute}s. Each vertex attribute defines one property of a vertex such as position,
	 *           normal or texture coordinate */
	/*
	Mesh (VertexDataType type, bool isStatic, int maxVertices, int maxIndices, VertexAttribute... attributes) {
		if (type == VertexDataType.VertexArray && Gdx.graphics.isGL20Available()) type = VertexDataType.VertexBufferObject;

		if (type == VertexDataType.VertexBufferObject) {
			vertices = new VertexBufferObject(isStatic, maxVertices, attributes);
			indices = new IndexBufferObject(isStatic, maxIndices);
			isVertexArray = false;
		} else if (type == VertexDataType.VertexBufferObjectSubData) {
			vertices = new VertexBufferObjectSubData(isStatic, maxVertices, attributes);
			indices = new IndexBufferObjectSubData(isStatic, maxIndices);
			isVertexArray = false;
		} else {
			vertices = new VertexArray(maxVertices, attributes);
			indices = new IndexBufferObject(maxIndices);
			isVertexArray = true;
		}
		addManagedMesh(Gdx.app, this);
	}
	*/

	~Mesh();

	/** Sets the vertices of this Mesh. The attributes are assumed to be given in float format. If this mesh is configured to use
	 * fixed point an IllegalArgumentException will be thrown.
	 * 
	 * @param vertices the vertices. */
	void setVertices(const float* vertices, int verticesLength);

	/** Sets the indices of this Mesh.
	 * 
	 * @param indices the indices
	 * @param offset the offset into the indices array
	 * @param count the number of indices to copy */
	void setIndices (const short* indices, int count);

	/** Copies the indices from the Mesh to the short array. The short array must be large enough to hold all the Mesh's indices.
	 * @param indices the array to copy the indices to */
	void getIndices(short* indices, int indicesLength);

	/** @return the number of defined indices */
	int getNumIndices ();

	/** @return the number of defined vertices */
	int getNumVertices ();

	//int getMaxVertices(); 

	/** @return the maximum number of indices this mesh can hold */
	int getMaxIndices ();

	/** @return the size of a single vertex in bytes */
	int getVertexSize ();

	/** Sets whether to bind the underlying {@link VertexArray} or {@link VertexBufferObject} automatically on a call to one of the
	 * {@link #render(int)} methods or not. Usually you want to use autobind. Manual binding is an expert functionality. There is a
	 * driver bug on the MSM720xa chips that will fuck up memory if you manipulate the vertices and indices of a Mesh multiple
	 * times while it is bound. Keep this in mind.
	 * 
	 * @param autoBind whether to autobind meshes. */
	void setAutoBind (bool autoBind);

	/** Binds the underlying {@link VertexArray}/{@link VertexBufferObject} and {@link IndexBufferObject} if indices were given. Use
	 * this with OpenGL ES 1.x and when auto-bind is disabled. */
	void bind ();

	/** Unbinds the underlying {@link VertexArray}/{@link VertexBufferObject} and {@link IndexBufferObject} is indices were given.
	 * Use this with OpenGL ES 1.x and when auto-bind is disabled. */
	void unbind ();

	/** Binds the underlying {@link VertexBufferObject} and {@link IndexBufferObject} if indices where given. Use this with OpenGL
	 * ES 2.0 and when auto-bind is disabled.
	 * 
	 * @param shader the shader (does not bind the shader) */
	/*
	void bind (ShaderProgram shader);

	/** Unbinds the underlying {@link VertexBufferObject} and {@link IndexBufferObject} is indices were given. Use this with OpenGL
	 * ES 1.x and when auto-bind is disabled.
	 * 
	 * @param shader the shader (does not unbind the shader) */
	/*
	void unbind (ShaderProgram shader);

	/** <p>
	 * Renders the mesh using the given primitive type. If indices are set for this mesh then getNumIndices() / #vertices per
	 * primitive primitives are rendered. If no indices are set then getNumVertices() / #vertices per primitive are rendered.
	 * </p>
	 * 
	 * <p>
	 * This method is intended for use with OpenGL ES 1.x and will throw an IllegalStateException when OpenGL ES 2.0 is used.
	 * </p>
	 * 
	 * @param primitiveType the primitive type */
	void render (int primitiveType);

	/** <p>
	 * Renders the mesh using the given primitive type. offset specifies the offset into vertex buffer and is ignored for the index
	 * buffer. Count specifies the number of vertices or indices to use thus count / #vertices per primitive primitives are
	 * rendered.
	 * </p>
	 * 
	 * <p>
	 * This method is intended for use with OpenGL ES 1.x and will throw an IllegalStateException when OpenGL ES 2.0 is used.
	 * </p>
	 * 
	 * @param primitiveType the primitive type
	 * @param offset the offset into the vertex buffer, ignored for indexed rendering
	 * @param count number of vertices or indices to use */
	void render (int primitiveType, int offset, int count);

	/** <p>
	 * Renders the mesh using the given primitive type. If indices are set for this mesh then getNumIndices() / #vertices per
	 * primitive primitives are rendered. If no indices are set then getNumVertices() / #vertices per primitive are rendered.
	 * </p>
	 * 
	 * <p>
	 * This method will automatically bind each vertex attribute as specified at construction time via {@link VertexAttributes} to
	 * the respective shader attributes. The binding is based on the alias defined for each VertexAttribute.
	 * </p>
	 * 
	 * <p>
	 * This method must only be called after the {@link ShaderProgram#begin()} method has been called!
	 * </p>
	 * 
	 * <p>
	 * This method is intended for use with OpenGL ES 2.0 and will throw an IllegalStateException when OpenGL ES 1.x is used.
	 * </p>
	 * 
	 * @param primitiveType the primitive type */
	/*
	void render (ShaderProgram shader, int primitiveType);
	*/

	/** <p>
	 * Renders the mesh using the given primitive type. offset specifies the offset into either the vertex buffer or the index
	 * buffer depending on whether indices are defined. count specifies the number of vertices or indices to use thus count /
	 * #vertices per primitive primitives are rendered.
	 * </p>
	 * 
	 * <p>
	 * This method will automatically bind each vertex attribute as specified at construction time via {@link VertexAttributes} to
	 * the respective shader attributes. The binding is based on the alias defined for each VertexAttribute.
	 * </p>
	 * 
	 * <p>
	 * This method must only be called after the {@link ShaderProgram#begin()} method has been called!
	 * </p>
	 * 
	 * <p>
	 * This method is intended for use with OpenGL ES 2.0 and will throw an IllegalStateException when OpenGL ES 1.x is used.
	 * </p>
	 * 
	 * @param shader the shader to be used
	 * @param primitiveType the primitive type
	 * @param offset the offset into the vertex or index buffer
	 * @param count number of vertices or indices to use */
	/*
	void render (ShaderProgram shader, int primitiveType, int offset, int count);
	*/

	/** Frees all resources associated with this Mesh */
	void dispose ();

	/** get the first {@link VertexAttribute} having the given {@link Usage}.
	 * 
	 * @param usage the Usage.
	 * @return false if no attribute with that usage was found. */
	bool getVertexAttribute (int usage, VertexAttribute& attribute);

	/** @return the vertex attributes of this Mesh */
	const VertexAttributes& getVertexAttributes ();

	/** @return the backing FloatBuffer holding the vertices. Does not have to be a direct buffer on Android! */
	float* getVerticesBuffer ();

	/** Calculates the {@link BoundingBox} of the vertices contained in this mesh. In case no vertices are defined yet a
	 * {@link GdxRuntimeException} is thrown. This method creates a new BoundingBox instance.
	 * 
	 * @return the bounding box. */
	/*
	BoundingBox calculateBoundingBox ();

	/** Calculates the {@link BoundingBox} of the vertices contained in this mesh. In case no vertices are defined yet a
	 * {@link GdxRuntimeException} is thrown.
	 * 
	 * @param bbox the bounding box to store the result in. */
	/*
	void calculateBoundingBox (BoundingBox bbox);
	*/
	/** @return the backing shortbuffer holding the indices. Does not have to be a direct buffer on Android! */
	short* getIndicesBuffer ();

		/** Method to scale the positions in the mesh. Normals will be kept as is. This is a potentially slow operation, use with care.
	 * It will also create a temporary float[] which will be garbage collected.
	 * 
	 * @param scaleX scale on x
	 * @param scaleY scale on y
	 * @param scaleZ scale on z */
	void scale (float scaleX, float scaleY, float scaleZ);

private:
	static void addManagedMesh(Mesh* mesh);

	/** Invalidates all meshes so the next time they are rendered new VBO handles are generated.
	 * @param app */
	static void invalidateAllMeshes();

	/** Will clear the managed mesh cache. I wouldn't use this if i was you :) */
	static void clearAllMeshes();

	/*
	static String getManagedStatus ();
	*/
};
