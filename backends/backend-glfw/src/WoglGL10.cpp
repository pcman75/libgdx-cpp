#include "StdAfx.h"
#include "WoglGL10.h"
#include "Utilities.h"


WoglGL10::WoglGL10()
{
}

WoglGL10::~WoglGL10()
{
}




void WoglGL10::glAlphaFunc (int func, float ref)
{
	::glAlphaFunc(func, ref);
}


void WoglGL10::glClientActiveTexture (int texture)
{
	PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTextureFunction = (PFNGLCLIENTACTIVETEXTUREPROC) wglGetProcAddress ("glClientActiveTexture");
	if(Utilities::CheckFunction(glClientActiveTextureFunction))
	{
		glClientActiveTextureFunction(texture);
	}
}

void WoglGL10::glColor4f (float red, float green, float blue, float alpha)
{
	::glColor4f(red, green, blue, alpha);
}

void WoglGL10::glColorPointer (int size, int type, int stride,  void* pointer)
{
	::glColorPointer(size, type, stride,  pointer);
}

void WoglGL10::glDeleteTextures (int n, const unsigned int* textures, int offset)
{
	//TODO: review the offset stuff
	::glDeleteTextures(n, textures + offset);
}

void WoglGL10::glDisableClientState (int array)
{
	::glDisableClientState (array);
}

void WoglGL10::glEnableClientState (int array)
{
	::glEnableClientState (array);
}

void WoglGL10::glFogf (int pname, float param)
{
	::glFogf (pname, param);
}

void WoglGL10::glFogfv (int pname, float* params, int offset)
{
	::glFogfv(pname, params + offset);
}

void WoglGL10::glFogfv (int pname, float* params)
{
	::glFogfv(pname, params);
}

void WoglGL10::glFrustumf (float left, float right, float bottom, float top, float zNear, float zFar)
{
	//TODO: same as glFrustumf?
	::glFrustum(left, right, bottom, top, zNear, zFar);
}

void WoglGL10::glGenTextures (int n, unsigned int* textures, int offset)
{
	//TODO:
	::glGenTextures(n, textures + offset);
}

void WoglGL10::glGetIntegerv (int pname, int* params, int offset)
{
	//TODO:
	::glGetIntegerv(pname, params + offset);
}
void WoglGL10::glLightModelf (int pname, float param)
{
	::glLightModelf(pname, param);
}

void WoglGL10::glLightModelfv (int pname, float* params, int offset)
{
	//TODO:
	::glLightModelfv(pname, params + offset);
}

void WoglGL10::glLightModelfv (int pname, float* params)
{
	::glLightModelfv(pname, params);
}

void WoglGL10::glLightf (int light, int pname, float param)
{
	::glLightf(light, pname, param);
}
void WoglGL10::glLightfv (int light, int pname, float* params, int offset)
{
	::glLightfv(light, pname, params + offset);
}

void WoglGL10::glLightfv (int light, int pname, float* params)
{
	::glLightfv(light, pname, params);
}

void WoglGL10::glLoadIdentity ()
{
	::glLoadIdentity ();
}

void WoglGL10::glLoadMatrixf (float* m, int offset)
{
	::glLoadMatrixf(m + offset);
}

void WoglGL10::glLoadMatrixf (float* m)
{
	::glLoadMatrixf(m);
}

void WoglGL10::glLogicOp (int opcode)
{
	::glLogicOp(opcode);
}

void WoglGL10::glMaterialf (int face, int pname, float param)
{
	::glMaterialf (face, pname, param);
}

void WoglGL10::glMaterialfv (int face, int pname, float* params, int offset)
{
	::glMaterialfv(face, pname, params + offset);
}

void WoglGL10::glMaterialfv (int face, int pname, float* params)
{
	::glMaterialfv(face, pname, params);
}

void WoglGL10::glMatrixMode (int mode)
{
	::glMatrixMode(mode);
}

void WoglGL10::glMultMatrixf (float* m, int offset)
{
	::glMultMatrixf(m + offset);
}

void WoglGL10::glMultMatrixf (float* m)
{
	::glMultMatrixf(m);
}

void WoglGL10::glMultiTexCoord4f (int target, float s, float t, float r, float q)
{
	PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4fFunction = (PFNGLMULTITEXCOORD4FPROC) wglGetProcAddress ("glMultiTexCoord4f");
	if(Utilities::CheckFunction(glMultiTexCoord4fFunction))
	{
		glMultiTexCoord4fFunction(target, s, t, r, q);
	}
}

void WoglGL10::glNormal3f (float nx, float ny, float nz)
{
	::glNormal3f(nx, ny, nz);
}

void WoglGL10::glNormalPointer (int type, int stride, void* pointer)
{
	::glNormalPointer(type, stride, pointer);
}

void WoglGL10::glOrthof (float left, float right, float bottom, float top, float zNear, float zFar)
{
	//TODO:
	::glOrtho(left, right, bottom, top, zNear, zFar);
}

void WoglGL10::glPointSize (float size)
{
	::glPointSize(size);
}

void WoglGL10::glPopMatrix ()
{
	::glPopMatrix();
}

void WoglGL10::glPushMatrix ()
{
	::glPushMatrix();
}

void WoglGL10::glRotatef (float angle, float x, float y, float z)
{
	::glRotatef(angle, x, y, z);
}

void WoglGL10::glSampleCoverage (float value, bool invert)
{
	PFNGLSAMPLECOVERAGEARBPROC glSampleCoverageFunction = (PFNGLSAMPLECOVERAGEARBPROC) wglGetProcAddress ("glSampleCoverage");
	if(Utilities::CheckFunction(glSampleCoverageFunction))
	{
		glSampleCoverageFunction(value, invert);
	}
}

void WoglGL10::glScalef (float x, float y, float z)
{
	::glScalef(x, y, z);
}

void WoglGL10::glShadeModel (int mode)
{
	::glShadeModel(mode);
}

void WoglGL10::glTexCoordPointer (int size, int type, int stride,  void* pointer)
{
	::glTexCoordPointer(size, type, stride, pointer);
}

void WoglGL10::glTexEnvf (int target, int pname, float param)
{
	::glTexEnvf(target, pname, param);
}

void WoglGL10::glTexEnvfv (int target, int pname, float* params, int offset)
{
	::glTexEnvfv(target, pname, params + offset);
}

void WoglGL10::glTexEnvfv (int target, int pname, float* params)
{
	::glTexEnvfv(target, pname, params);
}

void WoglGL10::glTranslatef (float x, float y, float z)
{
	::glTranslatef(x, y, z);
}

void WoglGL10::glVertexPointer (int size, int type, int stride,  void* pointer)
{
	::glVertexPointer(size, type, stride, pointer);
}

void WoglGL10::glPolygonMode (int face, int mode)
{
	::glPolygonMode(face, mode);
}