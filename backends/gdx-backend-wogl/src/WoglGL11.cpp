#include "stdafx.h"
#include "WoglGL11.h"
#include "Utilities.h"
#include "GdxRuntimeException.h"

void WoglGL11::glClipPlanef(int plane, const float* equation)
{
	double eq = *equation;
	::glClipPlane(plane, &eq);
}

void WoglGL11::glGetClipPlanef(int pname, float* equation)
{
	double eq = *equation;
	::glGetClipPlane(pname, &eq);
	*equation =(float)eq;
}

void WoglGL11::glGetFloatv(int pname, float* params)
{
	::glGetFloatv(pname, params);
}

void WoglGL11::glGetLightfv(int light, int pname, float* params)
{
	::glGetLightfv(light, pname, params);
}

void WoglGL11::glGetMaterialfv(int face, int pname, float* params)
{
	::glGetMaterialfv(face, pname, params);
}

void WoglGL11::glGetTexParameterfv(int target, int pname, float* params)
{
	::glGetTexParameterfv(target, pname, params);
}

void WoglGL11::glPointParameterf(int pname, float param)
{
	PFNGLPOINTPARAMETERFPROC glPointParameterfFunction = (PFNGLPOINTPARAMETERFPROC) wglGetProcAddress ("glPointParameterf");
	if(Utilities::CheckFunction(glPointParameterfFunction))
	{
		glPointParameterfFunction(pname, param);
	}
}

void WoglGL11::glPointParameterfv(int pname,const float* params)
{
	PFNGLPOINTPARAMETERFVPROC glPointParameterfvFunction = (PFNGLPOINTPARAMETERFVPROC) wglGetProcAddress ("glPointParameterfv");
	if(Utilities::CheckFunction(glPointParameterfvFunction))
	{
		glPointParameterfvFunction(pname, params);
	}
}

void WoglGL11::glTexParameterfv(int target,int pname,const float* params)
{
	::glTexParameterfv(target, pname, params);
}

void WoglGL11::glBindBuffer(int target,int buffer)
{
	PFNGLBINDBUFFERPROC glBindBufferFunction = (PFNGLBINDBUFFERPROC) wglGetProcAddress ("glBindBuffer");
	if(Utilities::CheckFunction(glBindBufferFunction))
	{
		glBindBufferFunction(target,buffer);
	}
}

void WoglGL11::glBufferData(int target,int size,const void* data,int usage)
{
	PFNGLBUFFERDATAPROC glBufferDataFunction = (PFNGLBUFFERDATAPROC) wglGetProcAddress ("glBufferData");
	if(Utilities::CheckFunction(glBufferDataFunction))
	{
		glBufferDataFunction(target, size, data, usage);
	}
}

void WoglGL11::glBufferSubData(int target,int offset,int size,const void* data)
{
	PFNGLBUFFERSUBDATAPROC glBufferSubDataFunction = (PFNGLBUFFERSUBDATAPROC) wglGetProcAddress ("glBufferSubData");
	if(Utilities::CheckFunction(glBufferSubDataFunction))
	{
		glBufferSubDataFunction(target, offset, size, data);
	}
}

void WoglGL11::glColor4ub(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha)
{
	::glColor4ub(red, green, blue, alpha);
}

void WoglGL11::glDeleteBuffers(int n,const unsigned int* buffers)
{
	PFNGLDELETEBUFFERSPROC glDeleteBuffersFunction = (PFNGLDELETEBUFFERSPROC) wglGetProcAddress ("glDeleteBuffers");
	if(Utilities::CheckFunction(glDeleteBuffersFunction))
	{
		glDeleteBuffersFunction(n, buffers);
	}
}

void WoglGL11::glGetBooleanv(int pname, bool* params)
{
	::glGetBooleanv(pname, (unsigned char*)params);
}

void WoglGL11::glGetBufferParameteriv(int target,int pname, int* params)
{
	PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameterivFunction = (PFNGLGETBUFFERPARAMETERIVPROC) wglGetProcAddress ("glGetBufferParameteriv");
	if(Utilities::CheckFunction(glGetBufferParameterivFunction))
	{
		glGetBufferParameterivFunction(target, pname, params);
	}
}

void WoglGL11::glGenBuffers(int n, unsigned int* buffers)
{
	PFNGLGENBUFFERSPROC glGenBuffersFunction = (PFNGLGENBUFFERSPROC) wglGetProcAddress ("glGenBuffers");
	if(Utilities::CheckFunction(glGenBuffersFunction))
	{
		glGenBuffersFunction(n, buffers);
	}
}

void WoglGL11::glGetPointerv(int pname, void** params)
{
	::glGetPointerv(pname, params);
}

void WoglGL11::glGetTexEnviv(int env,int pname,const int* params)
{
	::glGetTexEnviv(env, pname,(GLint*) params);
}

void WoglGL11::glGetTexParameteriv(int target,int pname, int* params)
{
	::glGetTexParameteriv(target, pname, params);
}

bool WoglGL11::glIsBuffer(int buffer)
{
	bool ret = false;
	PFNGLISBUFFERPROC glIsBufferFunction = (PFNGLISBUFFERPROC) wglGetProcAddress ("glIsBuffer");
	if(Utilities::CheckFunction(glIsBufferFunction))
	{
		ret = glIsBufferFunction(buffer) != 0;
	}
	return ret;
}

bool WoglGL11::glIsEnabled(int cap)
{
	return ::glIsEnabled(cap) != 0;
}

bool WoglGL11::glIsTexture(int texture)
{
	return ::glIsTexture(texture) != 0;
}

void WoglGL11::glTexEnvi(int target,int pname,int param)
{
	::glTexEnvi(target, pname, param);
}

void WoglGL11::glTexEnviv(int target,int pname,const int* params)
{
	::glTexEnviv(target, pname, params);
}

void WoglGL11::glTexParameteri(int target,int pname,int param)
{
	::glTexParameteri(target, pname, param);
}

void WoglGL11::glTexParameteriv(int target,int pname,const int* params)
{
	::glTexParameteriv(target, pname, params);
}

void WoglGL11::glPointSizePointerOES(int type,int stride, const void* pointer)
{
	throw new GdxRuntimeException("not implemented");
}

void WoglGL11::glVertexPointer(int size,int type,int stride, const void* pointer)
{
	::glVertexPointer(size, type, stride, pointer);
}

void WoglGL11::glColorPointer(int size,int type,int stride, const void* pointer)
{
	::glColorPointer(size, type, stride, pointer);
}
void WoglGL11::glNormalPointer(int type, int stride, const void* pointer)
{
	::glNormalPointer(type, stride, pointer);
}
void WoglGL11::glTexCoordPointer(int size, int type, int stride, const void* pointer)
{
	::glTexCoordPointer(size, type, stride, pointer);
}
void WoglGL11::glDrawElements(int mode, int count, int type, const void* indices)
{
	::glDrawElements(mode, count, type, indices);
}



