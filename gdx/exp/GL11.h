/*******************************************************************************
* Copyright 2011 See AUTHORS file.
* 
* Licensed under the Apache License, Version 2.0 (the "License") = 0;
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

/** Interface wrapping all OpenGL ES 1.1 methods. This interface inherits all the methods from {@link GL10}. Note that this
* excludes all fixed point methods!
* @author mzechner */
class GL11 : virtual public GL10 
{
public:
	enum
	{
		GDX_GL_OES_VERSION_1_0 = 1,
		GDX_GL_MAX_ELEMENTS_VERTICES = 0x80E8,
		GDX_GL_MAX_ELEMENTS_INDICES = 0x80E9,
		GDX_GL_POLYGON_SMOOTH_HINT = 0x0C53,
		GDX_GL_VERSION_ES_CM_1_0 = 1,
		GDX_GL_VERSION_ES_CL_1_0 = 1,
		GDX_GL_VERSION_ES_CM_1_1 = 1,
		GDX_GL_VERSION_ES_CL_1_1 = 1,
		GDX_GL_CLIP_PLANE0 = 0x3000,
		GDX_GL_CLIP_PLANE1 = 0x3001,
		GDX_GL_CLIP_PLANE2 = 0x3002,
		GDX_GL_CLIP_PLANE3 = 0x3003,
		GDX_GL_CLIP_PLANE4 = 0x3004,
		GDX_GL_CLIP_PLANE5 = 0x3005,
		GDX_GL_CURRENT_COLOR = 0x0B00,
		GDX_GL_CURRENT_NORMAL = 0x0B02,
		GDX_GL_CURRENT_TEXTURE_COORDS = 0x0B03,
		GDX_GL_POINT_SIZE = 0x0B11,
		GDX_GL_POINT_SIZE_MIN = 0x8126,
		GDX_GL_POINT_SIZE_MAX = 0x8127,
		GDX_GL_POINT_FADE_THRESHOLD_SIZE = 0x8128,
		GDX_GL_POINT_DISTANCE_ATTENUATION = 0x8129,
		GDX_GL_LINE_WIDTH = 0x0B21,
		GDX_GL_CULL_FACE_MODE = 0x0B45,
		GDX_GL_FRONT_FACE = 0x0B46,
		GDX_GL_SHADE_MODEL = 0x0B54,
		GDX_GL_DEPTH_RANGE = 0x0B70,
		GDX_GL_DEPTH_WRITEMASK = 0x0B72,
		GDX_GL_DEPTH_CLEAR_VALUE = 0x0B73,
		GDX_GL_DEPTH_FUNC = 0x0B74,
		GDX_GL_STENCIL_CLEAR_VALUE = 0x0B91,
		GDX_GL_STENCIL_FUNC = 0x0B92,
		GDX_GL_STENCIL_VALUE_MASK = 0x0B93,
		GDX_GL_STENCIL_FAIL = 0x0B94,
		GDX_GL_STENCIL_PASS_DEPTH_FAIL = 0x0B95,
		GDX_GL_STENCIL_PASS_DEPTH_PASS = 0x0B96,
		GDX_GL_STENCIL_REF = 0x0B97,
		GDX_GL_STENCIL_WRITEMASK = 0x0B98,
		GDX_GL_MATRIX_MODE = 0x0BA0,
		GDX_GL_VIEWPORT = 0x0BA2,
		GDX_GL_MODELVIEW_STACK_DEPTH = 0x0BA3,
		GDX_GL_PROJECTION_STACK_DEPTH = 0x0BA4,
		GDX_GL_TEXTURE_STACK_DEPTH = 0x0BA5,
		GDX_GL_MODELVIEW_MATRIX = 0x0BA6,
		GDX_GL_PROJECTION_MATRIX = 0x0BA7,
		GDX_GL_TEXTURE_MATRIX = 0x0BA8,
		GDX_GL_ALPHA_TEST_FUNC = 0x0BC1,
		GDX_GL_ALPHA_TEST_REF = 0x0BC2,
		GDX_GL_BLEND_DST = 0x0BE0,
		GDX_GL_BLEND_SRC = 0x0BE1,
		GDX_GL_LOGIC_OP_MODE = 0x0BF0,
		GDX_GL_SCISSOR_BOX = 0x0C10,
		GDX_GL_COLOR_CLEAR_VALUE = 0x0C22,
		GDX_GL_COLOR_WRITEMASK = 0x0C23,
		GDX_GL_MAX_CLIP_PLANES = 0x0D32,
		GDX_GL_POLYGON_OFFSET_UNITS = 0x2A00,
		GDX_GL_POLYGON_OFFSET_FACTOR = 0x8038,
		GDX_GL_TEXTURE_BINDING_2D = 0x8069,
		GDX_GL_VERTEX_ARRAY_SIZE = 0x807A,
		GDX_GL_VERTEX_ARRAY_TYPE = 0x807B,
		GDX_GL_VERTEX_ARRAY_STRIDE = 0x807C,
		GDX_GL_NORMAL_ARRAY_TYPE = 0x807E,
		GDX_GL_NORMAL_ARRAY_STRIDE = 0x807F,
		GDX_GL_COLOR_ARRAY_SIZE = 0x8081,
		GDX_GL_COLOR_ARRAY_TYPE = 0x8082,
		GDX_GL_COLOR_ARRAY_STRIDE = 0x8083,
		GDX_GL_TEXTURE_COORD_ARRAY_SIZE = 0x8088,
		GDX_GL_TEXTURE_COORD_ARRAY_TYPE = 0x8089,
		GDX_GL_TEXTURE_COORD_ARRAY_STRIDE = 0x808A,
		GDX_GL_VERTEX_ARRAY_POINTER = 0x808E,
		GDX_GL_NORMAL_ARRAY_POINTER = 0x808F,
		GDX_GL_COLOR_ARRAY_POINTER = 0x8090,
		GDX_GL_TEXTURE_COORD_ARRAY_POINTER = 0x8092,
		GDX_GL_SAMPLE_BUFFERS = 0x80A8,
		GDX_GL_SAMPLES = 0x80A9,
		GDX_GL_SAMPLE_COVERAGE_VALUE = 0x80AA,
		GDX_GL_SAMPLE_COVERAGE_INVERT = 0x80AB,
		GDX_GL_GENERATE_MIPMAP_HINT = 0x8192,
		GDX_GL_GENERATE_MIPMAP = 0x8191,
		GDX_GL_ACTIVE_TEXTURE = 0x84E0,
		GDX_GL_CLIENT_ACTIVE_TEXTURE = 0x84E1,
		GDX_GL_ARRAY_BUFFER = 0x8892,
		GDX_GL_ELEMENT_ARRAY_BUFFER = 0x8893,
		GDX_GL_ARRAY_BUFFER_BINDING = 0x8894,
		GDX_GL_ELEMENT_ARRAY_BUFFER_BINDING = 0x8895,
		GDX_GL_VERTEX_ARRAY_BUFFER_BINDING = 0x8896,
		GDX_GL_NORMAL_ARRAY_BUFFER_BINDING = 0x8897,
		GDX_GL_COLOR_ARRAY_BUFFER_BINDING = 0x8898,
		GDX_GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING = 0x889A,
		GDX_GL_STATIC_DRAW = 0x88E4,
		GDX_GL_DYNAMIC_DRAW = 0x88E8,
		GDX_GL_BUFFER_SIZE = 0x8764,
		GDX_GL_BUFFER_USAGE = 0x8765,
		GDX_GL_SUBTRACT = 0x84E7,
		GDX_GL_COMBINE = 0x8570,
		GDX_GL_COMBINE_RGB = 0x8571,
		GDX_GL_COMBINE_ALPHA = 0x8572,
		GDX_GL_RGB_SCALE = 0x8573,
		GDX_GL_ADD_SIGNED = 0x8574,
		GDX_GL_INTERPOLATE = 0x8575,
		GDX_GL_CONSTANT = 0x8576,
		GDX_GL_PRIMARY_COLOR = 0x8577,
		GDX_GL_PREVIOUS = 0x8578,
		GDX_GL_OPERAND0_RGB = 0x8590,
		GDX_GL_OPERAND1_RGB = 0x8591,
		GDX_GL_OPERAND2_RGB = 0x8592,
		GDX_GL_OPERAND0_ALPHA = 0x8598,
		GDX_GL_OPERAND1_ALPHA = 0x8599,
		GDX_GL_OPERAND2_ALPHA = 0x859A,
		GDX_GL_ALPHA_SCALE = 0x0D1C,
		GDX_GL_SRC0_RGB = 0x8580,
		GDX_GL_SRC1_RGB = 0x8581,
		GDX_GL_SRC2_RGB = 0x8582,
		GDX_GL_SRC0_ALPHA = 0x8588,
		GDX_GL_SRC1_ALPHA = 0x8589,
		GDX_GL_SRC2_ALPHA = 0x858A,
		GDX_GL_DOT3_RGB = 0x86AE,
		GDX_GL_DOT3_RGBA = 0x86AF,
		GDX_GL_POINT_SIZE_ARRAY_OES = 0x8B9C,
		GDX_GL_POINT_SIZE_ARRAY_TYPE_OES = 0x898A,
		GDX_GL_POINT_SIZE_ARRAY_STRIDE_OES = 0x898B,
		GDX_GL_POINT_SIZE_ARRAY_POINTER_OES = 0x898C,
		GDX_GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES = 0x8B9F,
		GDX_GL_POINT_SPRITE_OES = 0x8861,
		GDX_GL_COORD_REPLACE_OES = 0x8862,
		GDX_GL_OES_point_size_array = 1,
		GDX_GL_OES_point_sprite = 1
	};
	virtual ~GL11() {};
	virtual void glClipPlanef (int plane, const float* equation) = 0;
	virtual void glGetClipPlanef (int pname, float* eqn) = 0;
	virtual void glGetFloatv (int pname, float* params) = 0;
	virtual void glGetLightfv (int light, int pname, float* params) = 0;
	virtual void glGetMaterialfv (int face, int pname, float* params) = 0;
	virtual void glGetTexParameterfv (int target, int pname, float* params) = 0;
	virtual void glPointParameterf (int pname, float param) = 0;
	virtual void glPointParameterfv (int pname, const float* params) = 0;
	virtual void glTexParameterfv (int target, int pname, const float* params) = 0;
	virtual void glBindBuffer (int target, int buffer) = 0;
	virtual void glBufferData (int target, int size, const void* data, int usage) = 0;
	virtual void glBufferSubData (int target, int offset, int size, const void* data) = 0;
	virtual void glColor4ub (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) = 0;
	virtual void glDeleteBuffers (int n, const unsigned int* buffers) = 0;
	virtual void glGetBooleanv (int pname, bool* params) = 0;
	virtual void glGetBufferParameteriv (int target, int pname, int* params) = 0;
	virtual void glGenBuffers (int n, unsigned int* buffers) = 0;
	virtual void glGetPointerv (int pname, void** params) = 0;
	virtual void glGetTexEnviv (int env, int pname, const int* params) = 0;
	virtual void glGetTexParameteriv (int target, int pname, int* params) = 0;
	virtual bool glIsBuffer (int buffer) = 0;
	virtual bool glIsEnabled (int cap) = 0;
	virtual bool glIsTexture (int texture) = 0;
	virtual void glTexEnvi (int target, int pname, int param) = 0;
	virtual void glTexEnviv (int target, int pname, const int* params) = 0;
	virtual void glTexParameteri (int target, int pname, int param) = 0;
	virtual void glTexParameteriv (int target, int pname, const int* params) = 0;
	virtual void glPointSizePointerOES (int type, int stride, const void* pointer) = 0;
	virtual void glVertexPointer (int size, int type, int stride, const void* pointer) = 0;
	virtual void glColorPointer (int size, int type, int stride, const void* pointer) = 0;
	virtual void glNormalPointer (int type, int stride, const void* pointer) = 0;
	virtual void glTexCoordPointer (int size, int type, int stride, const void* pointer) = 0;
	virtual void glDrawElements (int mode, int count, int type, const void* indices) = 0;
};
