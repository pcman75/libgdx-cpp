#include "StdAfx.h"
#include "ShaderProgram.h"

std::list<ShaderProgram> ShaderProgram::m_shaders;
/** default name for position attributes **/
const wchar_t* ShaderProgram::POSITION_ATTRIBUTE = L"a_position";
/** default name for normal attribtues **/
const wchar_t* ShaderProgram::NORMAL_ATTRIBUTE = L"a_normal";
/** default name for color attributes **/
const wchar_t* ShaderProgram::COLOR_ATTRIBUTE = L"a_color";
/** default name for texcoords attributes, append texture unit number **/
const wchar_t* ShaderProgram::TEXCOORD_ATTRIBUTE = L"a_texCoord";
/** default name for tangent attribute **/
const wchar_t* ShaderProgram::TANGENT_ATTRIBUTE = L"a_tangent";
/** default name for binormal attribute **/
const wchar_t* ShaderProgram::BINORMAL_ATTRIBUTE = L"a_binormal";

/** flag indicating whether attributes & uniforms must be present at all times **/
bool ShaderProgram::pedantic = true;


ShaderProgram::ShaderProgram (const std::string& vertexShader, const std::string& fragmentShader)
{
	m_invalidated = false;
	m_vertexShaderSource = vertexShader;
	m_fragmentShaderSource = fragmentShader;

	compileShaders(vertexShader, fragmentShader);
	if (isCompiled())
	{
		fetchAttributes();
		fetchUniforms();
		addManagedShader(*this);
	}
}

/** Loads and compiles the shaders, creates a new program and links the shaders.
*
* @param vertexShader
* @param fragmentShader */

void ShaderProgram::compileShaders (const std::string& vertexShader, const std::string& fragmentShader)
{
	m_vertexShaderHandle = loadShader(GL20::GDX_GL_VERTEX_SHADER, vertexShader);
	m_fragmentShaderHandle = loadShader(GL20::GDX_GL_FRAGMENT_SHADER, fragmentShader);

	if (m_vertexShaderHandle == -1 || m_fragmentShaderHandle == -1)
	{
		m_isCompiled = false;
		return;
	}

	m_program = linkProgram();
	if (m_program == -1)
	{
		m_isCompiled = false;
		return;
	}

	m_isCompiled = true;
}

int ShaderProgram::loadShader (int type, const std::string& source)
{
	GL20* gl = Gdx.gl20;
	int params = -1;

	int shader = gl->glCreateShader(type);
	if (shader == 0) 
		return -1;

	gl->glShaderSource(shader, source);
	gl->glCompileShader(shader);
	gl->glGetShaderiv(shader, GL20::GDX_GL_COMPILE_STATUS, &params);

	if (params == 0)
	{
		gl->glGetShaderiv(shader, GL20::GDX_GL_INFO_LOG_LENGTH, &params);
		if (params > 1)
		{
			std::string infoLog = gl->glGetShaderInfoLog(shader);
			m_log += infoLog;
		}
		return -1;
	}

	return shader;
}

int ShaderProgram::linkProgram ()
{
	GL20* gl = Gdx.gl20;
	int m_program = gl->glCreateProgram();
	if (m_program == 0) 
		return -1;

	gl->glAttachShader(m_program, m_vertexShaderHandle);
	gl->glAttachShader(m_program, m_fragmentShaderHandle);
	gl->glLinkProgram(m_program);

	int params = -1;

	gl->glGetProgramiv(m_program, GL20::GDX_GL_LINK_STATUS, &params);
	if (params == 0)
	{
		return -1;
	}

	return m_program;
}

//const IntBuffer intbuf = BufferUtils.newIntBuffer(1);

/** @return the log info for the shader compilation and program linking stage. The shader needs to be bound for this method to
*         have an effect. */
std::string ShaderProgram::getLog ()
{
	if (isCompiled())
	{
		int params = -1;
		Gdx.gl20->glGetProgramiv(m_program, GL20::GDX_GL_INFO_LOG_LENGTH, &params);
		if (params > 1) 
			m_log = Gdx.gl20->glGetProgramInfoLog(m_program);
		return m_log;
	}
	else
	{
		return m_log;
	}
}

/** @return whether this ShaderProgram compiled successfully. */
bool ShaderProgram::isCompiled ()
{
	return m_isCompiled;
}

int ShaderProgram::fetchAttributeLocation (const std::string& name)
{
	GL20* gl = Gdx.gl20;

	int location = -1;
	ObjectIntMapIterator it = m_attributes.find(name);
	if(it == m_attributes.end())
	{
		location = gl->glGetAttribLocation(m_program, name);
		if (location != -1) 
			m_attributes[name] = location;
	}
	else
		location = it->second;
	return location;
}

int ShaderProgram::fetchUniformLocation (const std::string& name)
{
	GL20* gl = Gdx.gl20;
	int location = 0;
	ObjectIntMapIterator it = m_uniforms.find(name);
	if(it == m_uniforms.end())
	{
		location = gl->glGetUniformLocation(m_program, name);
		if (location == -1 && pedantic) 
			throw new GdxRuntimeException(std::string( "no uniform with name '") + name + "' in shader");
		m_attributes[name] = location;
	}
	else
		location = it->second;
	return location;
}

/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
* {@link #begin()}/{@link #end()} block.
*
* @param name the name of the uniform
* @param value the value */
void ShaderProgram::setUniformi (const std::string& name, int value)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	gl->glUniform1i(location, value);
}

/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
* {@link #begin()}/{@link #end()} block.
*
* @param name the name of the uniform
* @param value1 the first value
* @param value2 the second value */
void ShaderProgram::setUniformi (const std::string& name, int value1, int value2)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	gl->glUniform2i(location, value1, value2);
}

/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
* {@link #begin()}/{@link #end()} block.
*
* @param name the name of the uniform
* @param value1 the first value
* @param value2 the second value
* @param value3 the third value */
void ShaderProgram::setUniformi (const std::string& name, int value1, int value2, int value3)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	gl->glUniform3i(location, value1, value2, value3);
}

/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
* {@link #begin()}/{@link #end()} block.
*
* @param name the name of the uniform
* @param value1 the first value
* @param value2 the second value
* @param value3 the third value
* @param value4 the fourth value */
void ShaderProgram::setUniformi (const std::string& name, int value1, int value2, int value3, int value4)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	gl->glUniform4i(location, value1, value2, value3, value4);
}

/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
* {@link #begin()}/{@link #end()} block.
*
* @param name the name of the uniform
* @param value the value */
void ShaderProgram::setUniformf (const std::string& name, float value)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	gl->glUniform1f(location, value);
}

/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
* {@link #begin()}/{@link #end()} block.
*
* @param name the name of the uniform
* @param value1 the first value
* @param value2 the second value */
void ShaderProgram::setUniformf (const std::string& name, float value1, float value2)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	gl->glUniform2f(location, value1, value2);
}

/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
* {@link #begin()}/{@link #end()} block.
*
* @param name the name of the uniform
* @param value1 the first value
* @param value2 the second value
* @param value3 the third value */
void ShaderProgram::setUniformf (const std::string& name, float value1, float value2, float value3)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	gl->glUniform3f(location, value1, value2, value3);
}

/** Sets the uniform with the given name. Throws an IllegalArgumentException in case it is not called in between a
* {@link #begin()}/{@link #end()} block.
*
* @param name the name of the uniform
* @param value1 the first value
* @param value2 the second value
* @param value3 the third value
* @param value4 the fourth value */
void ShaderProgram::setUniformf (const std::string& name, float value1, float value2, float value3, float value4)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	gl->glUniform4f(location, value1, value2, value3, value4);
}

void ShaderProgram::setUniform1fv (const std::string& name, const float* values, int offset, int length)
{
	//TODO: need to copy values into an internal buffer like in Java???
	//for now I pass it directly
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	//ensureBufferCapacity(length << 2);
	//floatBuffer.clear();
	//BufferUtils.copy(values, floatBuffer, length, offset);
	gl->glUniform1fv(location, length, values + offset);
}

void ShaderProgram::setUniform2fv (const std::string& name, const float* values, int offset, int length)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	//ensureBufferCapacity(length << 2);
	//floatBuffer.clear();
	//BufferUtils.copy(values, floatBuffer, length, offset);
	gl->glUniform2fv(location, length / 2, values + offset);
}

void ShaderProgram::setUniform3fv (const std::string& name, const float* values, int offset, int length)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	//ensureBufferCapacity(length << 2);
	//floatBuffer.clear();
	//BufferUtils.copy(values, floatBuffer, length, offset);
	gl->glUniform3fv(location, length / 3, values + offset);
}

void ShaderProgram::setUniform4fv (const std::string& name, const float* values, int offset, int length)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	//ensureBufferCapacity(length << 2);
	//floatBuffer.clear();
	//BufferUtils.copy(values, floatBuffer, length, offset);
	gl->glUniform4fv(location, length / 4, values + offset);
}

/** Sets the uniform matrix with the given name. Throws an IllegalArgumentException in case it is not called in between a
* {@link #begin()}/{@link #end()} block.
*
* @param name the name of the uniform
* @param matrix the matrix */
void ShaderProgram::setUniformMatrix (const std::string& name, const Matrix4& matrix)
{
	setUniformMatrix(name, matrix, false);
}

/** Sets the uniform matrix with the given name. Throws an IllegalArgumentException in case it is not called in between a
* {@link #begin()}/{@link #end()} block.
*
* @param name the name of the uniform
* @param matrix the matrix
* @param transpose whether the matrix shouls be transposed */
void ShaderProgram::setUniformMatrix (const std::string& name, const Matrix4& matrix, bool transpose)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	//m_matrix.clear();
	//BufferUtils.copy(matrix.val, m_matrix, matrix.val.length, 0);
	gl->glUniformMatrix4fv(location, 1, transpose, matrix.getValues());
}

/** Sets the uniform matrix with the given name. Throws an IllegalArgumentException in case it is not called in between a
* {@link #begin()}/{@link #end()} block.
*
* @param name the name of the uniform
* @param matrix the matrix */
void ShaderProgram::setUniformMatrix (const std::string& name, const Matrix3& matrix)
{
	setUniformMatrix(name, matrix, false);
}

/** Sets the uniform matrix with the given name. Throws an IllegalArgumentException in case it is not called in between a
* {@link #begin()}/{@link #end()} block.
*
* @param name the name of the uniform
* @param matrix the matrix
* @param transpose whether the uniform matrix should be transposed */
void ShaderProgram::setUniformMatrix (const std::string& name, const Matrix3& matrix, bool transpose)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchUniformLocation(name);
	//float[] vals = matrix.getValues();
	//m_matrix.clear();
	//BufferUtils.copy(vals, m_matrix, vals.length, 0);
	gl->glUniformMatrix3fv(location, 1, transpose, matrix.getValues());
}

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
void ShaderProgram::setVertexAttribute (const std::string& name, int size, int type, bool normalize, int stride, const float* buffer)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchAttributeLocation(name);
	gl->glVertexAttribPointer(location, size, type, normalize, stride, buffer);
}

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
void ShaderProgram::setVertexAttribute (const std::string& name, int size, int type, bool normalize, int stride, int offset)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchAttributeLocation(name);
	if (location == -1) return;
	gl->glVertexAttribPointer(location, size, type, normalize, stride, offset);
}

/** Makes OpenGL ES 2.0 use this vertex and fragment shader pair. When you are done with this shader you have to call
* {@link ShaderProgram#end()}. */
void ShaderProgram::begin ()
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	gl->glUseProgram(m_program);
}

/** Disables this shader. Must be called when one is done with the shader. Don't mix it with dispose, that will release the
* shader resources. */
void ShaderProgram::end ()
{
	GL20* gl = Gdx.gl20;
	gl->glUseProgram(0);
}

/** Disposes all resources associated with this shader. Must be called when the shader is no longer used. */
void ShaderProgram::dispose ()
{
	GL20* gl = Gdx.gl20;
	gl->glUseProgram(0);
	gl->glDeleteShader(m_vertexShaderHandle);
	gl->glDeleteShader(m_fragmentShaderHandle);
	gl->glDeleteProgram(m_program);
	//if (shaders.get(Gdx.app) != null) shaders.get(Gdx.app).remove(this);
	m_shaders.clear();
}

/** Disables the vertex attribute with the given name
*
* @param name the vertex attribute name */
void ShaderProgram::disableVertexAttribute (const std::string& name)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchAttributeLocation(name);
	if (location != -1)
		gl->glDisableVertexAttribArray(location);
}

/** Enables the vertex attribute with the given name
*
* @param name the vertex attribute name */
void ShaderProgram::enableVertexAttribute (const std::string& name)
{
	GL20* gl = Gdx.gl20;
	checkManaged();
	int location = fetchAttributeLocation(name);
	if (location != -1)
		gl->glEnableVertexAttribArray(location);
}

void ShaderProgram::checkManaged ()
{
	if (m_invalidated)
	{
		compileShaders(m_vertexShaderSource, m_fragmentShaderSource);
		m_invalidated = false;
	}
}

void ShaderProgram::addManagedShader(const ShaderProgram& shaderProgram)
{
	m_shaders.push_back(shaderProgram);
}

/** Invalidates all shaders so the next time they are used new handles are generated
* @param app */
void ShaderProgram::invalidateAllShaderPrograms()
{
	if (Gdx.isGL20Available())
	{
		for(std::list<ShaderProgram>::iterator it = m_shaders.begin(); it != m_shaders.end(); it++)
		{
			it->m_invalidated = true;
			it->checkManaged();
		}
	}
}

void ShaderProgram::clearAllShaderPrograms()
{
	m_shaders.clear();
}

/** Sets the given attribute
*
* @param name the name of the attribute
* @param value1 the first value
* @param value2 the second value
* @param value3 the third value
* @param value4 the fourth value */
void ShaderProgram::setAttributef (const std::string& name, float value1, float value2, float value3, float value4)
{
	GL20* gl = Gdx.gl20;
	int location = fetchAttributeLocation(name);
	gl->glVertexAttrib4f(location, value1, value2, value3, value4);
}

void ShaderProgram::fetchUniforms ()
{
	int numUniforms = -1;
	Gdx.gl20->glGetProgramiv(m_program, GL20::GDX_GL_ACTIVE_UNIFORMS, &numUniforms);

	m_uniformNames.resize(numUniforms);

	for (int i = 0; i < numUniforms; i++)
	{
		int size = -1;
		unsigned int type = -1;
		std::string name = Gdx.gl20->glGetActiveUniform(m_program, i, &size, &type);
		int location = Gdx.gl20->glGetUniformLocation(m_program, name);
		m_uniforms[name] = location;
		m_uniformTypes[name] = type;
		m_uniformNames[i] = name;
	}
}

void ShaderProgram::fetchAttributes ()
{
	int numAttributes = -1;
	Gdx.gl20->glGetProgramiv(m_program, GL20::GDX_GL_ACTIVE_ATTRIBUTES, &numAttributes);

	m_attributeNames.resize(numAttributes);

	for (int i = 0; i < numAttributes; i++)
	{
		//params.clear();
		int size = 256;
		unsigned int type = -1;
		std::string name = Gdx.gl20->glGetActiveAttrib(m_program, i, &size, &type);
		int location = Gdx.gl20->glGetAttribLocation(m_program, name);
		m_attributes[name] = location;
		m_attributeTypes[name] = type;
		m_attributeNames[i] = name;
	}
}

/** @param name the name of the attribute
* @return whether the attribute is available in the shader */
bool ShaderProgram::hasAttribute (const std::string& name)
{
	return m_attributes.find(name) != m_attributes.end();
}

/** @param name the name of the attribute
* @return the type of the attribute, one of {@link GL20#GL_FLOAT}, {@link GL20#GL_FLOAT_VEC2} etc. */
int ShaderProgram::getAttributeType (const std::string& name)
{
	ObjectIntMapIterator it = m_attributeTypes.find(name);
	return it != m_attributeTypes.end()? it->second: 0;
}

/** @param name the name of the attribute
* @return the location of the attribute or -1. */
int ShaderProgram::getAttributeLocation (const std::string& name)
{
	ObjectIntMapIterator it = m_attributes.find(name);
	return it != m_attributes.end()? it->second: 0;
}

/** @param name the name of the uniform
* @return whether the uniform is available in the shader */
bool ShaderProgram::hasUniform (const std::string& name)
{
	return m_uniforms.find(name) != m_uniforms.end();
}

/** @param name the name of the uniform
* @return the type of the uniform, one of {@link GL20#GL_FLOAT}, {@link GL20#GL_FLOAT_VEC2} etc. */
int ShaderProgram::getUniformType (const std::string& name)
{
	ObjectIntMapIterator it = m_uniformTypes.find(name);
	return it != m_uniformTypes.end()? it->second: 0;
}

/** @param name the name of the uniform
* @return the location of the uniform or -1. */
int ShaderProgram::getUniformLocation (const std::string& name)
{
	ObjectIntMapIterator it = m_uniforms.find(name);
	return it != m_uniforms.end()? it->second: 0;
}

/** @return the attributes */
const std::vector<std::string>& ShaderProgram::getAttributes()
{
	return m_attributeNames;
}

/** @return the uniforms */
const std::vector<std::string>&  ShaderProgram::getUniforms()
{
	return m_uniformNames;
}