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
#include "GL11.h"
#include "WoglGL10.h"

//disable  'WoglGL10' : inherits 'WoglGLCommon::WoglGLCommon::glActiveTexture' via dominance
#pragma warning( push )
#pragma warning( disable : 4250 )

/** Interface wrapping all OpenGL ES 1.1 methods. This interface inherits all the methods from {@link GL10}. Note that this
* excludes all fixed point methods!
*/
class WoglGL11 : public WoglGL10, public GL11
{
public:
	virtual ~WoglGL11() {};
	virtual void glClipPlanef (int plane, const float* equation);
	virtual void glGetClipPlanef (int pname, float* eqn);
	virtual void glGetFloatv (int pname, float* params);
	virtual void glGetLightfv (int light, int pname, float* params);
	virtual void glGetMaterialfv (int face, int pname, float* params);
	virtual void glGetTexParameterfv (int target, int pname, float* params);
	virtual void glPointParameterf (int pname, float param);
	virtual void glPointParameterfv (int pname, const float* params);
	virtual void glTexParameterfv (int target, int pname, const float* params);
	virtual void glBindBuffer (int target, int buffer);
	virtual void glBufferData (int target, int size, const void* data, int usage);
	virtual void glBufferSubData (int target, int offset, int size, const void* data);
	virtual void glColor4ub (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	virtual void glDeleteBuffers (int n, const unsigned int* buffers);
	virtual void glGetBooleanv (int pname, bool* params);
	virtual void glGetBufferParameteriv (int target, int pname, int* params);
	virtual void glGenBuffers (int n, unsigned int* buffers);
	virtual void glGetPointerv (int pname, void** params);
	virtual void glGetTexEnviv (int env, int pname, const int* params);
	virtual void glGetTexParameteriv (int target, int pname, int* params);
	virtual bool glIsBuffer (int buffer);
	virtual bool glIsEnabled (int cap);
	virtual bool glIsTexture (int texture);
	virtual void glTexEnvi (int target, int pname, int param);
	virtual void glTexEnviv (int target, int pname, const int* params);
	virtual void glTexParameteri (int target, int pname, int param);
	virtual void glTexParameteriv (int target, int pname, const int* params);
	virtual void glPointSizePointerOES (int type, int stride, const void* pointer);
	virtual void glVertexPointer (int size, int type, int stride, const void* pointer);
	virtual void glColorPointer (int size, int type, int stride, const void* pointer);
	virtual void glNormalPointer (int type, int stride, const void* pointer);
	virtual void glTexCoordPointer (int size, int type, int stride, const void* pointer);
	virtual void glDrawElements (int mode, int count, int type, const void* indices);
};

#pragma warning( pop )