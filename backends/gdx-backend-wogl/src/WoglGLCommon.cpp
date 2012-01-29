#include "StdAfx.h"
#include "WoglGLCommon.h"
#include "Utilities.h"
//#include <glew.h>

WoglGLCommon::WoglGLCommon(void)
{
}


WoglGLCommon::~WoglGLCommon(void)
{
}


void WoglGLCommon::glActiveTexture (int texture)
{
	PFNGLACTIVETEXTUREPROC glActiveTextureFunction = (PFNGLACTIVETEXTUREPROC) wglGetProcAddress ("glActiveTexture");
	if(Utilities::CheckFunction(glActiveTextureFunction))
	{
		glActiveTextureFunction(texture);
	}
}

void WoglGLCommon::glBindTexture (int target, int texture)
{
	::glBindTexture(target, texture);
}

void WoglGLCommon::glBlendFunc (int sfactor, int dfactor)
{
	::glBlendFunc(sfactor, dfactor);
}

void WoglGLCommon::glClear (int mask)
{
	::glClear(mask);
}

void WoglGLCommon::glClearColor (float red, float green, float blue, float alpha)
{
	::glClearColor(red, green, blue, alpha);
}

void WoglGLCommon::glClearDepthf (float depth)
{
	//TODO: glClearDepthf it's something else
	::glClearDepth(depth);
}

void WoglGLCommon::glClearStencil (int s)
{
	::glClearStencil(s);
}

void WoglGLCommon::glColorMask (bool red, bool green, bool blue, bool alpha)
{
	::glColorMask(red, green, blue, alpha);
}

void WoglGLCommon::glCompressedTexImage2D (int target, int level, int internalformat, int width, int height, int border,
		int imageSize, void* data)
{
	PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2DFunction = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)::wglGetProcAddress("glCompressedTexImage2D");
	if(Utilities::CheckFunction(glCompressedTexImage2DFunction))
	{
		glCompressedTexImage2DFunction(target, level, internalformat, width, height, border, imageSize, data);
	}
}

void WoglGLCommon::glCompressedTexSubImage2D (int target, int level, int xoffset, int yoffset, int width, int height, int format,
		int imageSize, void* data)
{
	PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2DFunction = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)::wglGetProcAddress("glCompressedTexSubImage2D");
	if(Utilities::CheckFunction(glCompressedTexSubImage2DFunction))
	{
		glCompressedTexSubImage2DFunction(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	}
}

void WoglGLCommon::glCopyTexImage2D (int target, int level, int internalformat, int x, int y, int width, int height, int border)
{
	::glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

void WoglGLCommon::glCopyTexSubImage2D (int target, int level, int xoffset, int yoffset, int x, int y, int width, int height)
{
	::glCopyTexSubImage2D (target, level, xoffset, yoffset, x, y, width, height);
}

void WoglGLCommon::glCullFace (int mode)
{
	::glCullFace (mode);
}

void WoglGLCommon::glDeleteTextures (int n, const unsigned int* textures)
{
	::glDeleteTextures (n, textures);
}

void WoglGLCommon::glDepthFunc (int func)
{
	::glDepthFunc (func);
}

void WoglGLCommon::glDepthMask (bool flag)
{
	::glDepthMask (flag);
}

void WoglGLCommon::glDepthRangef (float zNear, float zFar)
{
	//TODO: glDepthRangef it's something else?
	::glDepthRange(zNear, zFar);
}

void WoglGLCommon::glDisable (int cap)
{
	::glDisable (cap);
}

void WoglGLCommon::glDrawArrays (int mode, int first, int count)
{
	::glDrawArrays (mode, first, count);
}

void WoglGLCommon::glDrawElements (int mode, int count, int type, const void* indices)
{
	::glDrawElements(mode, count, type, indices);
}

void WoglGLCommon::glEnable (int cap)
{
	::glEnable(cap);
}
void WoglGLCommon::glFinish ()
{
	::glFinish();
}

void WoglGLCommon::glFlush ()
{
	::glFlush();
}

void WoglGLCommon::glFrontFace (int mode)
{
	::glFrontFace(mode);
}

void WoglGLCommon::glGenTextures (int n, unsigned int* textures)
{
	::glGenTextures(n, textures);
}

int WoglGLCommon::glGetError ()
{
	return ::glGetError();
}

void WoglGLCommon::glGetIntegerv (int pname, int* params)
{
	::glGetIntegerv(pname, params);
}



std::wstring WoglGLCommon::glGetString (int name)
{
	std::wstring ws = glString2wstring(::glGetString(name));
	return ws;
}

void WoglGLCommon::glHint (int target, int mode)
{
	::glHint(target, mode);
}

void WoglGLCommon::glLineWidth (float width)
{
	::glLineWidth(width);
}

void WoglGLCommon::glPixelStorei (int pname, int param)
{
	::glPixelStorei(pname, param);
}

void WoglGLCommon::glPolygonOffset (float factor, float units)
{
	::glPolygonOffset(factor, units);
}

void WoglGLCommon::glReadPixels (int x, int y, int width, int height, int format, int type, void* pixels)
{
	::glReadPixels(x, y, width, height, format, type, pixels);
}

void WoglGLCommon::glScissor (int x, int y, int width, int height)
{
	::glScissor(x, y, width, height);
}

void WoglGLCommon::glStencilFunc (int func, int ref, int mask)
{
	::glStencilFunc(func, ref, mask);
}

void WoglGLCommon::glStencilMask (int mask)
{
	::glStencilMask(mask);
}

void WoglGLCommon::glStencilOp (int fail, int zfail, int zpass)
{
	::glStencilOp(fail, zfail, zpass);
}

void WoglGLCommon::glTexImage2D (int target, int level, int internalformat, int width, int height, int border, int format, int type, void* pixels)
{
	::glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void WoglGLCommon::glTexParameterf (int target, int pname, float param)
{
	::glTexParameterf(target, pname, param);
}

void WoglGLCommon::glTexSubImage2D (int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, void* pixels)
{
	::glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void WoglGLCommon::glViewport (int x, int y, int width, int height)
{
	::glViewport(x, y, width, height);
}

std::wstring WoglGLCommon::glString2wstring(const unsigned char* glString)
{
	size_t glStringLen = strlen((const char*)glString);
	wchar_t* buf = new wchar_t[glStringLen];
	size_t num_chars = mbstowcs(buf, (const char*)glString, glStringLen);
	std::wstring ws(buf, num_chars);
	delete[] buf;

	return ws;
}

std::string WoglGLCommon::wstring2string(const std::wstring& str)
{
	char* buf = new char[str.length()];
	size_t num_chars = wcstombs(buf, str.c_str(), str.length());
	
	std::string ret(buf, num_chars);
	delete[] buf;

	return ret;
}