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

#include "GL10.h"
#include "WoglGLCommon.h"

//disable  'WoglGL10' : inherits 'WoglGLCommon::WoglGLCommon::glActiveTexture' via dominance
#pragma warning( push )
#pragma warning( disable : 4250 )

/** Interface wrapping all standard OpenGL ES 1.0 methods. Note that this excludes and fixed point OpenGL ES 1.0 methods!*/
class WoglGL10 : public WoglGLCommon, virtual public GL10
{
public:
	WoglGL10();
	virtual ~WoglGL10();

	virtual void glAlphaFunc(int func, float ref);
	virtual void glClientActiveTexture (int texture);
	virtual void glColor4f (float red, float green, float blue, float alpha);
	virtual void glColorPointer (int size, int type, int stride,  void* pointer);
	virtual void glDeleteTextures (int n, const unsigned int* textures, int offset);
	virtual void glDisableClientState (int array);
	virtual void glEnableClientState (int array);
	virtual void glFogf (int pname, float param);
	virtual void glFogfv (int pname, float* params, int offset);
	virtual void glFogfv (int pname, float* params);
	virtual void glFrustumf (float left, float right, float bottom, float top, float zNear, float zFar);
	virtual void glGenTextures (int n, unsigned int* textures, int offset);
	virtual void glGetIntegerv (int pname, int* params, int offset);
	virtual void glLightModelf (int pname, float param);
	virtual void glLightModelfv (int pname, float* params, int offset);
	virtual void glLightModelfv (int pname, float* params);
	virtual void glLightf (int light, int pname, float param);
	virtual void glLightfv (int light, int pname, float* params, int offset);
	virtual void glLightfv (int light, int pname, float* params);
	virtual void glLoadIdentity ();
	virtual void glLoadMatrixf (float* m, int offset);
	virtual void glLoadMatrixf (float* m);
	virtual void glLogicOp (int opcode);
	virtual void glMaterialf (int face, int pname, float param);
	virtual void glMaterialfv (int face, int pname, float* params, int offset);
	virtual void glMaterialfv (int face, int pname, float* params);
	virtual void glMatrixMode (int mode);
	virtual void glMultMatrixf (float* m, int offset);
	virtual void glMultMatrixf (float* m);
	virtual void glMultiTexCoord4f (int target, float s, float t, float r, float q);
	virtual void glNormal3f (float nx, float ny, float nz);
	virtual void glNormalPointer (int type, int stride,  void* pointer);
	virtual void glOrthof (float left, float right, float bottom, float top, float zNear, float zFar);
	virtual void glPointSize (float size);
	virtual void glPopMatrix ();
	virtual void glPushMatrix ();
	virtual void glRotatef (float angle, float x, float y, float z);
	virtual void glSampleCoverage (float value, bool invert);
	virtual void glScalef (float x, float y, float z);
	virtual void glShadeModel (int mode);
	virtual void glTexCoordPointer (int size, int type, int stride,  void* pointer);
	virtual void glTexEnvf (int target, int pname, float param);
	virtual void glTexEnvfv (int target, int pname, float* params, int offset);
	virtual void glTexEnvfv (int target, int pname, float* params);
	virtual void glTranslatef (float x, float y, float z);
	virtual void glVertexPointer (int size, int type, int stride,  void* pointer);
	virtual void glPolygonMode (int face, int mode);

protected:
	std::wstring glString2wstring(const unsigned char* glString);
};

#pragma warning( pop )