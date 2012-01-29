#include "stdafx.h"
#include "WoglGL20.h"

void WoglGL20::glAttachShader(int program, int shader)
{
	::glAttachShader(program, shader);
}

void WoglGL20::glBindAttribLocation(int program, int index, const std::wstring& name)
{
	::glBindAttribLocation(program, index, wstring2string(name.c_str()).c_str());
}

void WoglGL20::glBindBuffer(int target, int buffer)
{
	::glBindBuffer(target, buffer);
}

void WoglGL20::glBindFramebuffer(int target, int framebuffer)
{
	::glBindFramebuffer(target, framebuffer);
}

void WoglGL20::glBindRenderbuffer(int target, int renderbuffer)
{
	::glBindRenderbuffer(target, renderbuffer);
}

void WoglGL20::glBlendColor(float red, float green, float blue, float alpha)
{
	::glBlendColor(red, green, blue, alpha);
}

void WoglGL20::glBlendEquation(int mode)
{
	::glBlendEquation(mode);
}

void WoglGL20::glBlendEquationSeparate(int modeRGB, int modeAlpha)
{
	::glBlendEquationSeparate(modeRGB, modeAlpha);
}

void WoglGL20::glBlendFuncSeparate(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha)
{
	::glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void WoglGL20::glBufferData(int target, int size, const void* data, int usage)
{
	::glBufferData(target, size, data, usage);
}

void WoglGL20::glBufferSubData(int target, int offset, int size, const void* data)
{
	::glBufferSubData(target, offset, size, data);
}

int WoglGL20::glCheckFramebufferStatus(int target)
{
	return ::glCheckFramebufferStatus(target);
}

void WoglGL20::glCompileShader(int shader)
{
	::glCompileShader(shader);
}

int WoglGL20::glCreateProgram()
{
	return ::glCreateProgram();
}

int WoglGL20::glCreateShader(int type)
{
	return ::glCreateShader(type);
}

void WoglGL20::glDeleteBuffers(int n, unsigned int* buffers)
{
	::glDeleteBuffers(n, buffers);
}

void WoglGL20::glDeleteFramebuffers(int n, unsigned int* framebuffers)
{
	::glDeleteFramebuffers(n, framebuffers);
}

void WoglGL20::glDeleteProgram(int program)
{
	::glDeleteProgram(program);
}

void WoglGL20::glDeleteRenderbuffers(int n, unsigned int* renderbuffers)
{
	::glDeleteRenderbuffers(n, renderbuffers);
}

void WoglGL20::glDeleteShader(int shader)
{
	::glDeleteShader(shader);
}

void WoglGL20::glDetachShader(int program, int shader)
{
	::glDetachShader(program, shader);
}

void WoglGL20::glDisableVertexAttribArray(int index)
{
	::glDisableVertexAttribArray(index);
}

void WoglGL20::glDrawElements(int mode, int count, int type, int indices)
{
	::glDrawElements(mode, count, type, &indices);
}

void WoglGL20::glEnableVertexAttribArray(int index)
{
	::glEnableVertexAttribArray(index);
}

void WoglGL20::glFramebufferRenderbuffer(int target, int attachment, int renderbuffertarget, int renderbuffer)
{
	::glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void WoglGL20::glFramebufferTexture2D(int target, int attachment, int textarget, int texture, int level)
{
	::glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void WoglGL20::glGenBuffers(int n, unsigned int* buffers)
{
	::glGenBuffers(n, buffers);
}

void WoglGL20::glGenerateMipmap(int target)
{
	::glGenerateMipmap(target);
}

void WoglGL20::glGenFramebuffers(int n, unsigned int* framebuffers)
{
	::glGenFramebuffers(n, framebuffers);
}

void WoglGL20::glGenRenderbuffers(int n, unsigned int* renderbuffers)
{
	::glGenRenderbuffers(n, renderbuffers);
}

std::wstring WoglGL20::glGetActiveAttrib(int program, int index, int* size, unsigned int* type)
{
	std::wstring ret;
	GLint len;
	::glGetProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &len);
	if(len)
	{
		GLchar* buffer = new GLchar[len];
		::glGetActiveAttrib(program, index, len, NULL, size, type, buffer);
		ret = glString2wstring((unsigned char*)buffer);
		delete buffer;
	}
	return ret;
}

std::wstring WoglGL20::glGetActiveUniform(int program, int index, int* size, unsigned int* type)
{
	std::wstring ret;
	GLint len;
	::glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &len);
	if(len)
	{
		GLchar* buffer = new GLchar[len];
		::glGetActiveUniform(program, index, len, NULL, size, type, buffer);
		ret = glString2wstring((unsigned char*)buffer);
		delete buffer;
	}
	return ret;
}

void WoglGL20::glGetAttachedShaders(int program, int maxcount, int* count, unsigned int* shaders)
{
	::glGetAttachedShaders(program, maxcount, (GLsizei*) count, shaders);
}

int WoglGL20::glGetAttribLocation(int program, const std::wstring& name)
{
	return ::glGetAttribLocation(program, wstring2string(name).c_str());
}

void WoglGL20::glGetBooleanv(int pname, bool* params)
{
	::glGetBooleanv(pname, (unsigned char*)params);
}

void WoglGL20::glGetBufferParameteriv(int target, int pname, int* params)
{
	::glGetBufferParameteriv(target, pname, params);
}

void WoglGL20::glGetFloatv(int pname, float* params)
{
	::glGetFloatv(pname, params);
}

void WoglGL20::glGetFramebufferAttachmentParameteriv(int target, int attachment, int pname, int* params)
{
	::glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}

void WoglGL20::glGetProgramiv(int program, int pname, int* params)
{
	::glGetProgramiv(program, pname, params);
}

std::wstring WoglGL20::glGetProgramInfoLog(int program)
{

	std::wstring ret;
	GLint len;
	::glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
	if(len)
	{
		GLchar* buffer = new GLchar[len];
		::glGetProgramInfoLog(program, len, NULL, buffer);
		ret = glString2wstring((unsigned char*)buffer);
		delete buffer;
	}
	return ret;
}

void WoglGL20::glGetRenderbufferParameteriv(int target, int pname, int* params)
{
	::glGetRenderbufferParameteriv(target, pname, params);
}

void WoglGL20::glGetShaderiv(int shader, int pname, int* params)
{
	::glGetShaderiv(shader, pname, params);
}

std::wstring WoglGL20::glGetShaderInfoLog(int shader)
{
	std::wstring ret;
	GLint len;
	::glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if(len)
	{
		GLchar* buffer = new GLchar[len];
		::glGetShaderInfoLog(shader, len, NULL, buffer);
		ret = glString2wstring((unsigned char*)buffer);
		delete buffer;
	}
	return ret;
}

void WoglGL20::glGetShaderPrecisionFormat(int shadertype, int precisiontype, int* range, int* precision)
{
	::glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
}

std::wstring WoglGL20::glGetShaderSource(int shader)
{
	std::wstring ret;
	GLint len;
	::glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &len);
	if(len)
	{
		GLchar* buffer = new GLchar[len];
		::glGetShaderSource(shader, len, NULL, buffer);
		ret = glString2wstring((unsigned char*)buffer);
		delete buffer;
	}
	return ret;
}

void WoglGL20::glGetTexParameterfv(int target, int pname, float* params)
{
	::glGetTexParameterfv(target, pname, params);
}

void WoglGL20::glGetTexParameteriv(int target, int pname, int* params)
{
	::glGetTexParameteriv(target, pname, params);
}

void WoglGL20::glGetUniformfv(int program, int location, float* params)
{
	::glGetUniformfv(program, location, params);
}

void WoglGL20::glGetUniformiv(int program, int location, int* params)
{
	::glGetUniformiv(program, location, params);
}

int WoglGL20::glGetUniformLocation(int program, const std::wstring& name)
{
	return ::glGetUniformLocation(program, wstring2string(name).c_str());
}

void WoglGL20::glGetVertexAttribfv(int index, int pname, float* params)
{
	::glGetVertexAttribfv(index, pname, params);
}

void WoglGL20::glGetVertexAttribiv(int index, int pname, int* params)
{
	::glGetVertexAttribiv(index, pname, params);
}

void WoglGL20::glGetVertexAttribPointerv(int index, int pname, void** pointer)
{
	::glGetVertexAttribPointerv(index, pname, pointer);
}

bool WoglGL20::glIsBuffer(int buffer)
{
	return ::glIsBuffer(buffer) != 0;
}

bool WoglGL20::glIsEnabled(int cap)
{
	return ::glIsEnabled(cap) != 0;
}

bool WoglGL20::glIsFramebuffer(int framebuffer)
{
	return ::glIsFramebuffer(framebuffer) != 0;
}

bool WoglGL20::glIsProgram(int program)
{
	return ::glIsProgram(program) != 0;
}

bool WoglGL20::glIsRenderbuffer(int renderbuffer)
{
	return ::glIsRenderbuffer(renderbuffer) != 0;
}

bool WoglGL20::glIsShader(int shader)
{
	return ::glIsShader(shader) != 0;
}

bool WoglGL20::glIsTexture(int texture)
{
	return ::glIsTexture(texture) != 0;
}

void WoglGL20::glLinkProgram(int program)
{
	::glLinkProgram(program);
}

void WoglGL20::glReleaseShaderCompiler()
{
	::glReleaseShaderCompiler();
}

void WoglGL20::glRenderbufferStorage(int target, int internalformat, int width, int height)
{
	::glRenderbufferStorage(target, internalformat, width, height);
}

void WoglGL20::glSampleCoverage(float value, bool invert)
{
	::glSampleCoverage(value, invert);
}

void WoglGL20::glShaderBinary(int n, const unsigned int* shaders, int binaryformat, const void* binary, int length)
{
	::glShaderBinary(n, shaders, binaryformat, binary, length);
}

void WoglGL20::glShaderSource(int shader, const std::wstring& string)
{
	GLint length = string.size();
	const GLchar* sources[1] = { wstring2string(string).c_str() };

	::glShaderSource(shader, 1, &sources[0], &length);
}

void WoglGL20::glStencilFuncSeparate(int face, int func, int ref, int mask)
{
	::glStencilFuncSeparate(face, func, ref, mask);
}

void WoglGL20::glStencilMaskSeparate(int face, int mask)
{
	::glStencilMaskSeparate(face, mask);
}

void WoglGL20::glStencilOpSeparate(int face, int fail, int zfail, int zpass)
{
	::glStencilOpSeparate(face, fail, zfail, zpass);
}

void WoglGL20::glTexParameterfv(int target, int pname, const float* params)
{
	::glTexParameterfv(target, pname, params);
}

void WoglGL20::glTexParameteri(int target, int pname, int param)
{
	::glTexParameteri(target, pname, param);
}

void WoglGL20::glTexParameteriv(int target, int pname, const int* params)
{
	::glTexParameteriv(target, pname, params);
}

void WoglGL20::glUniform1f(int location, float x)
{
	::glUniform1f(location, x);
}

void WoglGL20::glUniform1fv(int location, int count, const float* v)
{
	::glUniform1fv(location, count, v);
}

void WoglGL20::glUniform1i(int location, int x)
{
	::glUniform1i(location, x);
}

void WoglGL20::glUniform1iv(int location, int count, const int* v)
{
	::glUniform1iv(location, count, v);
}

void WoglGL20::glUniform2f(int location, float x, float y)
{
	::glUniform2f(location, x, y);
}

void WoglGL20::glUniform2fv(int location, int count, const float* v)
{
	::glUniform2fv(location, count, v);
}

void WoglGL20::glUniform2i(int location, int x, int y)
{
	::glUniform2i(location, x, y);
}

void WoglGL20::glUniform2iv(int location, int count, const int* v)
{
	::glUniform2iv(location, count, v);
}

void WoglGL20::glUniform3f(int location, float x, float y, float z)
{
	::glUniform3f(location, x, y, z);
}

void WoglGL20::glUniform3fv(int location, int count, const float* v)
{
	::glUniform3fv(location, count, v);
}

void WoglGL20::glUniform3i(int location, int x, int y, int z)
{
	::glUniform3i(location, x, y, z);
}

void WoglGL20::glUniform3iv(int location, int count, const int* v)
{
	::glUniform3iv(location, count, v);
}

void WoglGL20::glUniform4f(int location, float x, float y, float z, float w)
{
	::glUniform4f(location, x, y, z, w);
}

void WoglGL20::glUniform4fv(int location, int count, const float* v)
{
	::glUniform4fv(location, count, v);
}

void WoglGL20::glUniform4i(int location, int x, int y, int z, int w)
{
	::glUniform4i(location, x, y, z, w);
}

void WoglGL20::glUniform4iv(int location, int count, const int* v)
{
	::glUniform4iv(location, count, v);
}

void WoglGL20::glUniformMatrix2fv(int location, int count, bool transpose, const float* value)
{
	::glUniformMatrix2fv(location, count, transpose, value);
}

void WoglGL20::glUniformMatrix3fv(int location, int count, bool transpose, const float* value)
{
	::glUniformMatrix3fv(location, count, transpose, value);
}

void WoglGL20::glUniformMatrix4fv(int location, int count, bool transpose, const float* value)
{
	::glUniformMatrix4fv(location, count, transpose, value);
}

void WoglGL20::glUseProgram(int program)
{
	::glUseProgram(program);
}

void WoglGL20::glValidateProgram(int program)
{
	::glValidateProgram(program);
}

void WoglGL20::glVertexAttrib1f(int indx, float x)
{
	::glVertexAttrib1f(indx, x);
}

void WoglGL20::glVertexAttrib1fv(int indx, const float* values)
{
	::glVertexAttrib1fv(indx, values);
}

void WoglGL20::glVertexAttrib2f(int indx, float x, float y)
{
	::glVertexAttrib2f(indx, x, y);
}

void WoglGL20::glVertexAttrib2fv(int indx, const float* values)
{
	::glVertexAttrib2fv(indx, values);
}

void WoglGL20::glVertexAttrib3f(int indx, float x, float y, float z)
{
	::glVertexAttrib3f(indx, x, y, z);
}

void WoglGL20::glVertexAttrib3fv(int indx, const float* values)
{
	::glVertexAttrib3fv(indx, values);
}

void WoglGL20::glVertexAttrib4f(int indx, float x, float y, float z, float w)
{
	::glVertexAttrib4f(indx, x, y, z, w);
}

void WoglGL20::glVertexAttrib4fv(int indx, const float* values)
{
	::glVertexAttrib4fv(indx, values);
}

void WoglGL20::glVertexAttribPointer(int indx, int size, int type, bool normalized, int stride, const void* ptr)
{
	::glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
}

void WoglGL20::glVertexAttribPointer(int indx, int size, int type, bool normalized, int stride, int ptr)
{
	::glVertexAttribPointer(indx, size, type, normalized, stride, (GLvoid*) ptr);
}
//
//void WoglGL20::glActiveTexture(int texture)
//{
//	::glActiveTexture(texture);
//}
//void WoglGL20::glBindTexture(int target, int texture)
//{
//	::glBindTexture(target, texture);
//}
//void WoglGL20::glBlendFunc(int sfactor, int dfactor)
//{
//	::glBlendFunc(sfactor, dfactor);
//}
//void WoglGL20::glClear(int mask)
//{
//	::glClear(mask);
//}
//void WoglGL20::glClearColor(float red, float green, float blue, float alpha)
//{
//	::glClearColor(red, green, blue, alpha);
//}
//void WoglGL20::glClearDepthf(float depth)
//{
//	::glClearDepthf(depth);
//}
//void WoglGL20::glClearStencil(int s)
//{
//	::glClearStencil(s);
//}
//void WoglGL20::glColorMask(bool red, bool green, bool blue, bool alpha)
//{
//	::glColorMask(red, green, blue, alpha);
//}
//void WoglGL20::glCompressedTexImage2D(int target, int level, int internalformat, int width, int height, int border, int imageSize, const unsigned char* data)
//{
//	::glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
//}
//void WoglGL20::glCompressedTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int imageSize, const unsigned char* data)
//{
//	::glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
//}
//void WoglGL20::glCopyTexImage2D(int target, int level, int internalformat, int x, int y, int width, int height, int border)
//{
//	::glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
//}
//void WoglGL20::glCopyTexSubImage2D(int target, int level, int xoffset, int yoffset, int x, int y, int width, int height)
//{
//	::glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
//}
//void WoglGL20::glCullFace(int mode)
//{
//	::glCullFace(mode);
//}
//void WoglGL20::glDeleteTextures(int n, int* textures)
//{
//	::glDeleteTextures(n, textures);
//}
//void WoglGL20::glDepthFunc(int func)
//{
//	::glDepthFunc(func);
//}
//void WoglGL20::glDepthMask(bool flag)
//{
//	::glDepthMask(flag);
//}
//void WoglGL20::glDepthRangef(float zNear, float zFar)
//{
//	::glDepthRangef(zNear, zFar);
//}
//void WoglGL20::glDisable(int cap)
//{
//	::glDisable(cap);
//}
//void WoglGL20::glDrawArrays(int mode, int first, int count)
//{
//	::glDrawArrays(mode, first, count);
//}
//void WoglGL20::glDrawElements(int mode, int count, int type, void* indices)
//{
//	::glDrawElements(mode, count, type, indices);
//}
//void WoglGL20::glEnable(int cap)
//{
//	::glEnable(cap);
//}
//void WoglGL20::glFinish()
//{
//	::glFinish();
//}
//void WoglGL20::glFlush()
//{
//	::glFlush();
//}
//
//void WoglGL20::glFrontFace(int mode)
//{
//	::glFrontFace(mode);
//}
//void WoglGL20::glGenTextures(int n, int* textures)
//{
//	::glGenTextures(n, textures);
//}
//int WoglGL20::glGetError()
//{
//	return ::glGetError();
//}
//void WoglGL20::glGetIntegerv(int pname, const int* params)
//{
//	::glGetIntegerv(pname, params);
//}
//std::wstring WoglGL20::glGetString(int name)
//{
//	const GLubyte* str = ::glGetString(name);
//	return std::wstring((char*)str);
//}
//void WoglGL20::glHint(int target, int mode)
//{
//	::glHint(target, mode);
//}
//void WoglGL20::glLineWidth(float width)
//{
//	::glLineWidth(width);
//}
//void WoglGL20::glPixelStorei(int pname, int param)
//{
//	::glPixelStorei(pname, param);
//}
//void WoglGL20::glPolygonOffset(float factor, float units)
//{
//	::glPolygonOffset(factor, units);
//}
//void WoglGL20::glReadPixels(int x, int y, int width, int height, int format, int type, const void* pixels)
//{
//	::glReadPixels(x, y, width, height, format, type, (GLvoid*) pixels);
//}
//void WoglGL20::glScissor(int x, int y, int width, int height)
//{
//	::glScissor(x, y, width, height);
//}
//void WoglGL20::glStencilFunc(int func, int ref, int mask)
//{
//	::glStencilFunc(func, ref, mask);
//}
//void WoglGL20::glStencilMask(int mask)
//{
//	::glStencilMask(mask);
//}
//void WoglGL20::glStencilOp(int fail, int zfail, int zpass)
//{
//	::glStencilOp(fail, zfail, zpass);
//}
//void WoglGL20::glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type, const unsigned char* pixels)
//{
//	::glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
//}
//void WoglGL20::glTexParameterf(int target, int pname, float param)
//{
//	::glTexParameterf(target, pname, param);
//}
//void WoglGL20::glTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, const unsigned char* pixels)
//{
//	::glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
//}
//void WoglGL20::glViewport(int x, int y, int width, int height)
//{
//	::glViewport(x, y, width, height);
//}
