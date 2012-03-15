#pragma once

#include "GLCommon.h"

class WoglGLCommon :
	virtual public GLCommon
{
public:
	WoglGLCommon(void);
	virtual ~WoglGLCommon(void);

	virtual void glActiveTexture (int texture);
	virtual void glBindTexture (int target, int texture);
	virtual void glBlendFunc (int sfactor, int dfactor);
	virtual void glClear (int mask);
	virtual void glClearColor (float red, float green, float blue, float alpha);
	virtual void glClearDepthf (float depth);
	virtual void glClearStencil (int s);
	virtual void glColorMask (bool red, bool green, bool blue, bool alpha);
	virtual void glCompressedTexImage2D (int target, int level, int internalformat, int width, int height, int border, int imageSize, void* data);
	virtual void glCompressedTexSubImage2D (int target, int level, int xoffset, int yoffset, int width, int height, int format, int imageSize, void* data);
	virtual void glCopyTexImage2D (int target, int level, int internalformat, int x, int y, int width, int height, int border);
	virtual void glCopyTexSubImage2D (int target, int level, int xoffset, int yoffset, int x, int y, int width, int height);
	virtual void glCullFace (int mode);
	virtual void glDeleteTextures (int n, const unsigned int* textures);
	virtual void glDepthFunc (int func);
	virtual void glDepthMask (bool flag);
	virtual void glDepthRangef (float zNear, float zFar);
	virtual void glDisable (int cap);
	virtual void glDrawArrays (int mode, int first, int count);
	virtual void glDrawElements (int mode, int count, int type, const void* indices);
	virtual void glEnable (int cap);
	virtual void glFinish ();
	virtual void glFlush ();
	virtual void glFrontFace (int mode);
	virtual void glGenTextures (int n, unsigned int*  textures);
	virtual int glGetError ();
	virtual void glGetIntegerv (int pname, int* params);
	virtual std::string glGetString (int name);
	virtual void glHint (int target, int mode);
	virtual void glLineWidth (float width);
	virtual void glPixelStorei (int pname, int param);
	virtual void glPolygonOffset (float factor, float units);
	virtual void glReadPixels (int x, int y, int width, int height, int format, int type, void* pixels);
	virtual void glScissor (int x, int y, int width, int height);
	virtual void glStencilFunc (int func, int ref, int mask);
	virtual void glStencilMask (int mask);
	virtual void glStencilOp (int fail, int zfail, int zpass);
	virtual void glTexImage2D (int target, int level, int internalformat, int width, int height, int border, int format, int type, void* pixels);
	virtual void glTexParameterf (int target, int pname, float param);
	virtual void glTexSubImage2D (int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, void* pixels);
	virtual void glViewport (int x, int y, int width, int height);

protected:
};

