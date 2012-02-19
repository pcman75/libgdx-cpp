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
#include "Matrix4.h"
#include "Matrix3.h"
#include "GdxTest.h"

class MatrixJNITest  :
	public GdxTest
{
public:
	GDX_DEFINE_CREATOR(GdxTest);

	MatrixJNITest();
	virtual ~MatrixJNITest();

	virtual void create ();

private:
	void bench ();
	void check(const Vector3& vec, const float* fvec);
	void check(const Vector3& vec, const float* fvec, int numVecs, int stride);
	void check(const Matrix4& mat1, const Matrix4& mat2);
};