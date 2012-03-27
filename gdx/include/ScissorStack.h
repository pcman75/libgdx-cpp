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
#include "Rectang.h"
#include "Gdx.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Camera.h"
#include "Matrix4.h"

/** A scissor stack is a stack of {@link Rectang} to be used for clipping via {@link GLCommon#glScissor(int, int, int, int)}.
 * When a new Rectang is pushed onto the stack, it will be merged with the current top of stack. The minimum area of overlap is
 * then set as the real top of the stack.
 * @author mzechner */
class ScissorStack 
{
private:
  static std::vector<Rectang> scissors;
  static Vector3 tmp;
  static Rectang viewport;

	/** Pushes a new scissor {@link Rectang} onto the stack, merging it with the current top of the stack. The minimal area of
	 * overlap between the TOS Rectang and the provided Rectang is pushed onto the stack. This will invoke
	 * {@link GLCommon#glScissor(int, int, int, int)} with the final TOS Rectang. In case no scissor is yet on the stack this
	 * will also enable {@link GL10#GL_SCISSOR_TEST} automatically.
	 * @param scissor the scissor Rectang
	 * @return true if the scissors were pushed. false if the scissor area was zero, in this case the scissors were not pushed and
	 *         no drawing should occur. */
public:
  static bool pushScissors( Rectang scissor);
  
	/** Pops the current scissor Rectang from the stack and sets the new scissor area to the new TOS Rectang. In case no more
	 * Rectangs are on the stack, {@link GL10#GL_SCISSOR_TEST} is disabled. */
	static void popScissors ();
  
	static void fix (Rectang rect);
  
	/** Calculates a scissor Rectang in OpenGL ES window coordinates from a {@link Camera}, a transformation {@link Matrix4} and
	 * an axis aligned {@link Rectang}. The Rectang will get transformed by the camera and transform matrices and is then
	 * projected to screen coordinates. Note that only axis aligned Rectangs will work with this method. If either the Camera or
	 * the Matrix4 have rotational components, the output of this method will not be suitable for
	 * {@link GLCommon#glScissor(int, int, int, int)}.
	 * @param camera the {@link Camera}
	 * @param batchTransform the transformation {@link Matrix4}
	 * @param area the {@link Rectang} to transform to window coordinates
	 * @param scissor the Rectang to store the result in */
	static void calculateScissors ( Camera* camera, Matrix4 batchTransform, Rectang area, Rectang scissor);
  
	/** @return the current viewport in OpenGL ES window coordinates based on the currently applied scissor */
	static Rectang getViewport ();
  
	/** Transforms a point to real window coordinates (as oposed to OpenGL ES window coordinates), where the origin is in the top
	 * left and the the y-axis is pointing downwards
	 * @param camera the {@link Camera}
	 * @param transformMatrix the transformation {@link Matrix4}
	 * @param point the point to be transformed. */
	static void toWindowCoordinates( Camera* camera, Matrix4 transformMatrix, Vector2 point);
};
