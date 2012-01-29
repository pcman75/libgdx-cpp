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
#include "Gdx.h"
#include "Graphics.h"
#include "GdxRuntimeException.h"

#include "Matrix4.h"

/** <p>
 * A shader program encapsulates a vertex and fragment shader pair linked to form a shader program useable with OpenGL ES 2.0.
 * </p>
 *
 * <p>
 * After construction a ShaderProgram can be used to draw {@link Mesh}. To make the GPU use a specific ShaderProgram the programs
 * {@link ShaderProgram#begin()} method must be used which effectively binds the program.
 * </p>
 *
 * <p>
 * When a ShaderProgram is bound one can set uniforms, vertex attributes and attributes as needed via the respective methods.
 * </p>
 *
 * <p>
 * A ShaderProgram can be unbound with a call to {@link ShaderProgram#end()}
 * </p>
 *
 * <p>
 * A ShaderProgram must be disposed via a call to {@link ShaderProgram#dispose()} when it is no longer needed
 * </p>
 *
 * <p>
 * ShaderPrograms are managed. In case the OpenGL context is lost all shaders get invalidated and have to be reloaded. This
 * happens on Android when a user switches to another application or receives an incoming call. Managed ShaderPrograms are
 * automatically reloaded when the OpenGL context is recreated so you don't have to do this manually.
 * </p>
 *
 * @author mzechner */
class ShaderProgram
{
public:
	/** default name for position attributes **/
	static const char* POSITION_ATTRIBUTE;
	/** default name for normal attribtues **/
	static const char* NORMAL_ATTRIBUTE;
	/** default name for color attributes **/
	static const char* COLOR_ATTRIBUTE;
	/** default name for texcoords attributes, append texture unit number **/
	static const char* TEXCOORD_ATTRIBUTE;
	/** default name for tangent attribute **/
	static const char* TANGENT_ATTRIBUTE;
	/** default name for binormal attribute **/
	static const char* BINORMAL_ATTRIBUTE;

	/** flag indicating whether attributes & uniforms must be present at all times **/
	static bool pedantic;

private:
	/** the list of currently available shaders **/
	//const static ObjectMap<Application, List<ShaderProgram>> shaders = new ObjectMap<Application, List<ShaderProgram>>();
	static std::list<ShaderProgram> m_shaders;

	/** the log **/
	std::wstring m_log;

	/** whether this program compiled succesfully **/
	bool m_isCompiled;

	typedef std::map<std::wstring, int> ObjectIntMap;
	typedef std::map<std::wstring, int>::iterator ObjectIntMapIterator;

	/** uniform lookup **/
	ObjectIntMap m_uniforms;

	/** uniform types **/
	ObjectIntMap m_uniformTypes;

	/** uniform names **/
	std::vector<std::wstring> m_uniformNames;

	/** attribute lookup **/
	ObjectIntMap m_attributes;

	/** attribute types **/
	ObjectIntMap m_attributeTypes;

	/** attribute names **/
	std::vector<std::wstring> m_attributeNames;

	/** program handle **/
	int m_program;

	/** vertex shader handle **/
	int m_vertexShaderHandle;

	/** fragment shader handle **/
	int m_fragmentShaderHandle;

	/** matrix float buffer **/
	//float m_matrix[16];

	/** vertex shader source **/
	std::wstring m_vertexShaderSource;

	/** fragment shader source **/
	std::wstring m_fragmentShaderSource;

	/** whether this shader was invalidated **/
	bool m_invalidated;

	/** direct buffer for passing float and int uniform arrays **/
	//ByteBuffer buffer = null;
	//FloatBuffer floatBuffer = null;
	//IntBuffer intBuffer = null;

	/** reference count **/
	//int refCount = 0;

	/** Construcs a new JOglShaderProgram and immediatly compiles it.
	 *
	 * @param vertexShader the vertex shader
	 * @param fragmentShader the fragment shader */

	ShaderProgram (const std::wstring& vertexShader, const std::wstring& fragmentShader);

	/** Loads and compiles the shaders, creates a new program and links the shaders.
	 *
	 * @param vertexShader
	 * @param fragmentShader */
private:
	void compileShaders (const std::wstring& vertexShader, const std::wstring& fragmentShader);

	int loadShader (int type, const std::wstring& source);

	int linkProgram ();

	//const static IntBuffer intbuf = BufferUtils.newIntBuffer(1);

	/** @return the log info for the shader compilation and program linking stage. The shader needs to be bound for this method to
	 *         have an effect. */
	std::wstring getLog ();

	/** @return whether this ShaderProgram compiled successfully. */
	bool isCompiled ();

	int fetchAttributeLocation (const std::wstring& name);

	int fetchUniformLocation (const std::wstring& name);

	/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the name of the uniform
	 * @param value the value */
	void setUniformi (const std::wstring& name, int value);

	/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the name of the uniform
	 * @param value1 the first value
	 * @param value2 the second value */
	void setUniformi (const std::wstring& name, int value1, int value2);

	/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the name of the uniform
	 * @param value1 the first value
	 * @param value2 the second value
	 * @param value3 the third value */
	void setUniformi (const std::wstring& name, int value1, int value2, int value3);

	/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the name of the uniform
	 * @param value1 the first value
	 * @param value2 the second value
	 * @param value3 the third value
	 * @param value4 the fourth value */
	void setUniformi (const std::wstring& name, int value1, int value2, int value3, int value4);

	/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the name of the uniform
	 * @param value the value */
	void setUniformf (const std::wstring& name, float value);

	/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the name of the uniform
	 * @param value1 the first value
	 * @param value2 the second value */
	void setUniformf (const std::wstring& name, float value1, float value2);

	/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the name of the uniform
	 * @param value1 the first value
	 * @param value2 the second value
	 * @param value3 the third value */
	void setUniformf (const std::wstring& name, float value1, float value2, float value3);

	/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the name of the uniform
	 * @param value1 the first value
	 * @param value2 the second value
	 * @param value3 the third value
	 * @param value4 the fourth value */
	void setUniformf (const std::wstring& name, float value1, float value2, float value3, float value4);

	void setUniform1fv (const std::wstring& name, const float* values, int offset, int length);

	void setUniform2fv (const std::wstring& name, const float* values, int offset, int length);

	void setUniform3fv (const std::wstring& name, const float* values, int offset, int length);

	void setUniform4fv (const std::wstring& name, const float* values, int offset, int length);

	/** Sets the uniform matrix with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the name of the uniform
	 * @param matrix the matrix */
	void setUniformMatrix (const std::wstring& name, const Matrix4& matrix);

	/** Sets the uniform matrix with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the name of the uniform
	 * @param matrix the matrix
	 * @param transpose whether the matrix shouls be transposed */
	void setUniformMatrix (const std::wstring& name, const Matrix4& matrix, bool transpose);

	/** Sets the uniform matrix with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the name of the uniform
	 * @param matrix the matrix */
	void setUniformMatrix (const std::wstring& name, const Matrix3& matrix);

	/** Sets the uniform matrix with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the name of the uniform
	 * @param matrix the matrix
	 * @param transpose whether the uniform matrix should be transposed */
	void setUniformMatrix (const std::wstring& name, const Matrix3& matrix, bool transpose);

	/** Sets the vertex attribute with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the attribute name
	 * @param size the number of components, must be >= 1 and <= 4
	 * @param type the type, must be one of GL20::GDX_GL_BYTE, GL20::GDX_GL_UNSIGNED_BYTE, GL20::GDX_GL_SHORT,
	 *           GL20::GDX_GL_UNSIGNED_SHORT,GL20::GDX_GL_FIXED, or GL20::GDX_GL_FLOAT. GL_FIXED will not work on the desktop
	 * @param normalize whether fixed point data should be normalized. Will not work on the desktop
	 * @param stride the stride in bytes between successive attributes
	 * @param buffer the buffer containing the vertex attributes. */
	void setVertexAttribute (const std::wstring& name, int size, int type, bool normalize, int stride, const float* buffer);

	/** Sets the vertex attribute with the given name. Throws an IllegalArgumentException in case it is not called in between a
	 * {@link #begin()}/{@link #end()} block.
	 *
	 * @param name the attribute name
	 * @param size the number of components, must be >= 1 and <= 4
	 * @param type the type, must be one of GL20::GDX_GL_BYTE, GL20::GDX_GL_UNSIGNED_BYTE, GL20::GDX_GL_SHORT,
	 *           GL20::GDX_GL_UNSIGNED_SHORT,GL20::GDX_GL_FIXED, or GL20::GDX_GL_FLOAT. GL_FIXED will not work on the desktop
	 * @param normalize whether fixed point data should be normalized. Will not work on the desktop
	 * @param stride the stride in bytes between successive attributes
	 * @param offset byte offset into the vertex buffer object bound to GL20::GDX_GL_ARRAY_BUFFER. */
	void setVertexAttribute (const std::wstring& name, int size, int type, bool normalize, int stride, int offset);

	/** Makes OpenGL ES 2.0 use this vertex and fragment shader pair. When you are done with this shader you have to call
	 * {@link ShaderProgram#end()}. */
	void begin ();

	/** Disables this shader. Must be called when one is done with the shader. Don't mix it with dispose, that will release the
	 * shader resources. */
	void end ();

	/** Disposes all resources associated with this shader. Must be called when the shader is no longer used. */
	void dispose ();

	/** Disables the vertex attribute with the given name
	 *
	 * @param name the vertex attribute name */
	void disableVertexAttribute (const std::wstring& name);

	/** Enables the vertex attribute with the given name
	 *
	 * @param name the vertex attribute name */
	void enableVertexAttribute (const std::wstring& name);

private:
	void checkManaged ();

public:
	void addManagedShader(const ShaderProgram& shaderProgram);

	/** Invalidates all shaders so the next time they are used new handles are generated
	 * @param app */
	static void invalidateAllShaderPrograms();

	static void clearAllShaderPrograms();

	/*
	static String getManagedStatus ()
	{
		StringBuilder builder = new StringBuilder();
		int i = 0;
		builder.append("Managed shaders/app: { ");
for (Application app : m_shaders.keys())
		{
			builder.append(m_shaders.get(app).size());
			builder.append(" ");
		}
		builder.append("}");
		return builder.toString();
	}
	*/

	/** Sets the given attribute
	 *
	 * @param name the name of the attribute
	 * @param value1 the first value
	 * @param value2 the second value
	 * @param value3 the third value
	 * @param value4 the fourth value */
	void setAttributef (const std::wstring& name, float value1, float value2, float value3, float value4);

private:

	void fetchUniforms ();

	void fetchAttributes ();

	/** @param name the name of the attribute
	 * @return whether the attribute is available in the shader */
	bool hasAttribute (const std::wstring& name);

	/** @param name the name of the attribute
	 * @return the type of the attribute, one of {@link GL20#GL_FLOAT}, {@link GL20#GL_FLOAT_VEC2} etc. */
	int getAttributeType (const std::wstring& name);

	/** @param name the name of the attribute
	 * @return the location of the attribute or -1. */
	int getAttributeLocation (const std::wstring& name);

	/** @param name the name of the uniform
	 * @return whether the uniform is available in the shader */
	bool hasUniform (const std::wstring& name);

	/** @param name the name of the uniform
	 * @return the type of the uniform, one of {@link GL20#GL_FLOAT}, {@link GL20#GL_FLOAT_VEC2} etc. */
	int getUniformType (const std::wstring& name);

	/** @param name the name of the uniform
	 * @return the location of the uniform or -1. */
	int getUniformLocation (const std::wstring& name);

	/** @return the attributes */
	const std::vector<std::wstring>& getAttributes();

	/** @return the uniforms */
	const std::vector<std::wstring>&  getUniforms();
};
