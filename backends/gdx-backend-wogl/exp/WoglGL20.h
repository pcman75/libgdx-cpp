/*******************************************************************************
* Copyright 2011 See AUTHORS file.
* 
* Licensed under the Apache License, Version 2.0(the "License");
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

/** Interface wrapping all the methods of OpenGL ES 2.0*/

#pragma once

#include "GL20.h"
#include "WoglGLCommon.h"

//disable  'WoglGL10' : inherits 'WoglGLCommon::WoglGLCommon::glActiveTexture' via dominance
#pragma warning( push )
#pragma warning( disable : 4250 )

class  WoglGL20 : public WoglGLCommon, public GL20 
{
public:
	virtual ~WoglGL20() {};
	virtual void glAttachShader(int program, int shader);
	virtual void glBindAttribLocation(int program, int index, const std::string& name);
	virtual void glBindBuffer(int target, int buffer);
	virtual void glBindFramebuffer(int target, int framebuffer);
	virtual void glBindRenderbuffer(int target, int renderbuffer);
	virtual void glBlendColor(float red, float green, float blue, float alpha);
	virtual void glBlendEquation(int mode);
	virtual void glBlendEquationSeparate(int modeRGB, int modeAlpha);
	virtual void glBlendFuncSeparate(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha);
	virtual void glBufferData(int target, int size, const void* data, int usage);
	virtual void glBufferSubData(int target, int offset, int size, const void* data);
	virtual int glCheckFramebufferStatus(int target);
	virtual void glCompileShader(int shader);
	virtual int glCreateProgram();
	virtual int glCreateShader(int type);
	virtual void glDeleteBuffers(int n, unsigned int* buffers);
	virtual void glDeleteFramebuffers(int n, unsigned int* framebuffers);
	virtual void glDeleteProgram(int program);
	virtual void glDeleteRenderbuffers(int n, unsigned int* renderbuffers);
	virtual void glDeleteShader(int shader);
	virtual void glDetachShader(int program, int shader);
	virtual void glDisableVertexAttribArray(int index);
	virtual void glDrawElements(int mode, int count, int type, int indices);
	virtual void glEnableVertexAttribArray(int index);
	virtual void glFramebufferRenderbuffer(int target, int attachment, int renderbuffertarget, int renderbuffer);
	virtual void glFramebufferTexture2D(int target, int attachment, int textarget, int texture, int level);
	virtual void glGenBuffers(int n, unsigned int* buffers);
	virtual void glGenerateMipmap(int target);
	virtual void glGenFramebuffers(int n, unsigned int* framebuffers);
	virtual void glGenRenderbuffers(int n, unsigned int* renderbuffers);
	virtual std::string glGetActiveAttrib(int program, int index, int* size, unsigned int* type);
	virtual std::string glGetActiveUniform(int program, int index, int* size, unsigned int* type);
	virtual void glGetAttachedShaders(int program, int maxcount, int* count, unsigned int* shaders);
	virtual int glGetAttribLocation(int program, const std::string& name);
	virtual void glGetBooleanv(int pname, bool* params);
	virtual void glGetBufferParameteriv(int target, int pname, int* params);
	virtual void glGetFloatv(int pname, float* params);
	virtual void glGetFramebufferAttachmentParameteriv(int target, int attachment, int pname, int* params);
	virtual void glGetProgramiv(int program, int pname, int* params);
	virtual std::string glGetProgramInfoLog(int program);
	virtual void glGetRenderbufferParameteriv(int target, int pname, int* params);
	virtual void glGetShaderiv(int shader, int pname, int* params);
	virtual std::string glGetShaderInfoLog(int shader);
	virtual void glGetShaderPrecisionFormat(int shadertype, int precisiontype, int* range, int* precision);
	virtual std::string glGetShaderSource(int shader);
	virtual void glGetTexParameterfv(int target, int pname, float* params);
	virtual void glGetTexParameteriv(int target, int pname, int* params);
	virtual void glGetUniformfv(int program, int location, float* params);
	virtual void glGetUniformiv(int program, int location, int* params);
	virtual int glGetUniformLocation(int program, const std::string& name);
	virtual void glGetVertexAttribfv(int index, int pname, float* params);
	virtual void glGetVertexAttribiv(int index, int pname, int* params);
	virtual void glGetVertexAttribPointerv(int index, int pname, void** pointer);
	virtual bool glIsBuffer(int buffer);
	virtual bool glIsEnabled(int cap);
	virtual bool glIsFramebuffer(int framebuffer);
	virtual bool glIsProgram(int program);
	virtual bool glIsRenderbuffer(int renderbuffer);
	virtual bool glIsShader(int shader);
	virtual bool glIsTexture(int texture);
	virtual void glLinkProgram(int program);
	virtual void glReleaseShaderCompiler();
	virtual void glRenderbufferStorage(int target, int internalformat, int width, int height);
	virtual void glSampleCoverage(float value, bool invert);
	virtual void glShaderBinary(int n, const unsigned int* shaders, int binaryformat, const void* binary, int length);
	virtual void glShaderSource(int shader, const std::string& string);
	virtual void glStencilFuncSeparate(int face, int func, int ref, int mask);
	virtual void glStencilMaskSeparate(int face, int mask);
	virtual void glStencilOpSeparate(int face, int fail, int zfail, int zpass);
	virtual void glTexParameterfv(int target, int pname, const float* params);
	virtual void glTexParameteri(int target, int pname, int param);
	virtual void glTexParameteriv(int target, int pname, const int* params);
	virtual void glUniform1f(int location, float x);
	virtual void glUniform1fv(int location, int count, const float* v);
	virtual void glUniform1i(int location, int x);
	virtual void glUniform1iv(int location, int count, const int* v);
	virtual void glUniform2f(int location, float x, float y);
	virtual void glUniform2fv(int location, int count, const float* v);
	virtual void glUniform2i(int location, int x, int y);
	virtual void glUniform2iv(int location, int count, const int* v);
	virtual void glUniform3f(int location, float x, float y, float z);
	virtual void glUniform3fv(int location, int count, const float* v);
	virtual void glUniform3i(int location, int x, int y, int z);
	virtual void glUniform3iv(int location, int count, const int* v);
	virtual void glUniform4f(int location, float x, float y, float z, float w);
	virtual void glUniform4fv(int location, int count, const float* v);
	virtual void glUniform4i(int location, int x, int y, int z, int w);
	virtual void glUniform4iv(int location, int count, const int* v);
	virtual void glUniformMatrix2fv(int location, int count, bool transpose, const float* value);
	virtual void glUniformMatrix3fv(int location, int count, bool transpose, const float* value);
	virtual void glUniformMatrix4fv(int location, int count, bool transpose, const float* value);
	virtual void glUseProgram(int program);
	virtual void glValidateProgram(int program);
	virtual void glVertexAttrib1f(int indx, float x);
	virtual void glVertexAttrib1fv(int indx, const float* values);
	virtual void glVertexAttrib2f(int indx, float x, float y);
	virtual void glVertexAttrib2fv(int indx, const float* values);
	virtual void glVertexAttrib3f(int indx, float x, float y, float z);
	virtual void glVertexAttrib3fv(int indx, const float* values);
	virtual void glVertexAttrib4f(int indx, float x, float y, float z, float w);
	virtual void glVertexAttrib4fv(int indx, const float* values);
	virtual void glVertexAttribPointer(int indx, int size, int type, bool normalized, int stride, const void* ptr);
	virtual void glVertexAttribPointer(int indx, int size, int type, bool normalized, int stride, int ptr);
};

#pragma warning( pop )