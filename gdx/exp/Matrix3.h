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

/** A 3x3 column major matrix for 2D transforms.
 */
class Matrix3
{
public:
	float vals[9];
private:
	static const float DEGREE_TO_RAD;
	
	float m_tmp[9];

public:
	Matrix3();

	/** Sets this matrix to the identity matrix
	 * @return this matrix */
	Matrix3& idt();;

	/** Multiplies this matrix with the other matrix in the order this * m.
	 * @return this matrix */
	Matrix3& mul(const Matrix3& m);

	/** Sets this matrix to a rotation matrix that will rotate any vector in counter clockwise order around the z-axis.
	 * @param angle the angle in degrees.
	 * @return this matrix */
	Matrix3& setToRotation(float angle);

	/** Sets this matrix to a translation matrix.
	 * @param x the translation in x
	 * @param y the translation in y
	 * @return this matrix */
	Matrix3& setToTranslation(float x, float y);

	/** Sets this matrix to a scaling matrix
	 *
	 * @param scaleX the scale in x
	 * @param scaleY the scale in y
	 * @return this matrix */
	Matrix3& setToScaling(float scaleX, float scaleY);

	std::string toString();

	/** @return the determinant of this matrix */
	float det();

	/** Inverts this matrix given that the determinant is != 0
	 * @return this matrix */
	Matrix3& inv();

	Matrix3& set(const Matrix3& mat);

	/** Adds a translational component to the matrix in the 3rd column. The other columns are untouched.
	 * @param vector The translation vector
	 * @return This matrix for chaining */
	Matrix3& trn(const class Vector3& vector);

	/** Adds a translational component to the matrix in the 3rd column. The other columns are untouched.
	 * @param x The x-component of the translation vector
	 * @param y The y-component of the translation vector
	 * @return This matrix for chaining */
	Matrix3& trn(float x, float y);

	/** Postmultiplies this matrix by a translation matrix. Postmultiplication is also used by OpenGL ES'
	 * glTranslate/glRotate/glScale
	 * @param x
	 * @param y
	 * @return this matrix for chaining */
	Matrix3& translate(float x, float y);

	/** Postmultiplies this matrix with a (counter-clockwise) rotation matrix. Postmultiplication is also used by OpenGL ES'
	 * glTranslate/glRotate/glScale
	 * @param angle the angle in degrees
	 * @return this matrix for chaining */
	Matrix3& rotate(float angle);

	/** Postmultiplies this matrix with a scale matrix. Postmultiplication is also used by OpenGL ES' glTranslate/glRotate/glScale.
	 * @param scaleX
	 * @param scaleY
	 * @return this matrix for chaining */
	Matrix3& scale(float scaleX, float scaleY);

	const float* const getValues() const;

private:
	static void mul(float mata[9], float matb[9]);
};
