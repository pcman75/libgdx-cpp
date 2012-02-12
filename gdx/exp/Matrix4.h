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
#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "GdxDefines.h"


/** Encapsulates a column major 4 by 4 matrix. You can access the linear array for use with OpenGL via the public
 * {@link Matrix4#val} member. Like the {@link Vector3} class it allows to chain methods by returning a reference to itself.*/

class GdxDllImportExport Matrix4
{
public:
	float val[16];

private:
	float m_tmp[16];
	static Quaternion m_quat;
	static Vector3 m_tmpV;
	static Vector3 m_l_vez;
	static Vector3 m_l_vex;
	static Vector3 m_l_vey;
	static Vector3 m_tmpVec;
	static Matrix4 m_tmpMat;
	static Vector3 m_right;
	static Vector3 m_tmpForward;
	static Vector3 m_tmpUp;

public:

	static const int M00 = 0;// 0;
	static const int M01 = 4;// 1;
	static const int M02 = 8;// 2;
	static const int M03 = 12;// 3;
	static const int M10 = 1;// 4;
	static const int M11 = 5;// 5;
	static const int M12 = 9;// 6;
	static const int M13 = 13;// 7;
	static const int M20 = 2;// 8;
	static const int M21 = 6;// 9;
	static const int M22 = 10;// 10;
	static const int M23 = 14;// 11;
	static const int M30 = 3;// 12;
	static const int M31 = 7;// 13;
	static const int M32 = 11;// 14;
	static const int M33 = 15;// 15;

	/** Constructs an identity matrix */
	Matrix4();

	/** Constructs a matrix from the given matrix
	 *
	 * @param matrix The matrix */
	Matrix4(const Matrix4& matrix);

	/** Constructs a matrix from the given float array. The array must have at least 16 elements
	 * @param values The float array */
	Matrix4(const float values[16]);

	/** Constructs a rotation matrix from the given {@link Quaternion}
	 * @param quaternion The quaternion */
	Matrix4(const class Quaternion& quaternion);

	/** Sets the matrix to the given matrix.
	 *
	 * @param matrix The matrix
	 * @return This matrix for chaining */
	Matrix4& set(const Matrix4& matrix);

	/** Sets the matrix to the given matrix as a float array
	 *
	 * @param values The matrix
	 * @return This matrix for chaining */
	Matrix4& set(const float values[16]);

	/** Sets the matrix to a rotation matrix representing the quaternion.
	 *
	 * @param quaternion The quaternion
	 * @return This matrix for chaining */
	Matrix4& set(const class Quaternion& quaternion);

	/** Sets the four columns of the matrix which correspond to the x-, y- and z-axis of the vector space this matrix creates as
	 * well as the 4th column representing the translation of any point that is multiplied by this matrix.
	 *
	 * @param xAxis The x-axis
	 * @param yAxis The y-axis
	 * @param zAxis The z-axis
	 * @param pos The translation vector */
	void set(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis, const Vector3& pos);

	/** @return a copy of this matrix */
	Matrix4 cpy();

	/** Adds a translational component to the matrix in the 4th column. The other columns are untouched.
	 *
	 * @param vector The translation vector
	 * @return This matrix for chaining */
	Matrix4& trn(const Vector3& vector);

	/** Adds a translational component to the matrix in the 4th column. The other columns are untouched.
	 *
	 * @param x The x-component of the translation vector
	 * @param y The y-component of the translation vector
	 * @param z The z-component of the translation vector
	 * @return This matrix for chaining */
	Matrix4& trn(float x, float y, float z);

	/** @return the backing float array */
	const float* const getValues() const;

	/** Multiplies this matrix with the given matrix, storing the result in this matrix.
	 *
	 * @param matrix The other matrix
	 * @return This matrix for chaining. */
	Matrix4& mul(const Matrix4& matrix);

	/** Transposes the matrix
	 *
	 * @return This matrix for chaining */
	Matrix4& tra();

	/** Sets the matrix to an identity matrix
	 *
	 * @return This matrix for chaining */
	Matrix4& idt();

	/** Inverts the matrix. Throws a RuntimeException in case the matrix is not invertible. Stores the result in this matrix
	 *
	 * @return This matrix for chaining */
	Matrix4& inv();

	/** @return The determinant of this matrix */
	float det();

	/** Sets the matrix to a projection matrix with a nearPlane- and farPlane plane, a field of view in degrees and an aspect ratio.
	 *
	 * @param nearPlane The nearPlane plane
	 * @param farPlane The farPlane plane
	 * @param fov The field of view in degrees
	 * @param aspectRatio The aspect ratio
	 * @return This matrix for chaining */
	Matrix4& setToProjection(float nearPlane, float farPlane, float fov, float aspectRatio);

	/** Sets this matrix to an orthographic projection matrix with the origin at (x,y) extending by width and height. The nearPlane plane
	 * is set to 0, the farPlane plane is set to 1.
	 *
	 * @param x The x-coordinate of the origin
	 * @param y The y-coordinate of the origin
	 * @param width The width
	 * @param height The height
	 * @return This matrix for chaining */
	Matrix4& setToOrtho2D(float x, float y, float width, float height);

	/** Sets this matrix to an orthographic projection matrix with the origin at (x,y) extending by width and height, having a nearPlane
	 * and farPlane plane.
	 *
	 * @param x The x-coordinate of the origin
	 * @param y The y-coordinate of the origin
	 * @param width The width
	 * @param height The height
	 * @param nearPlane The nearPlane plane
	 * @param farPlane The farPlane plane
	 * @return This matrix for chaining */
	Matrix4& setToOrtho2D(float x, float y, float width, float height, float nearPlane, float farPlane);

	/** Sets the matrix to an orthographic projection like glOrtho (http://www.opengl.org/sdk/docs/man/xhtml/glOrtho.xml) following
	 * the OpenGL equivalent
	 *
	 * @param left The left clipping plane
	 * @param right The right clipping plane
	 * @param bottom The bottom clipping plane
	 * @param top The top clipping plane
	 * @param nearPlane The nearPlane clipping plane
	 * @param farPlane The farPlane clipping plane
	 * @return This matrix for chaining */
	Matrix4& setToOrtho(float left, float right, float bottom, float top, float nearPlane, float farPlane);

	/** Sets this matrix to a translation matrix, overwriting it first by an identity matrix and then setting the 4th column to the
	 * translation vector.
	 *
	 * @param vector The translation vector
	 * @return This matrix for chaining */
	Matrix4& setToTranslation(const Vector3& vector);

	/** Sets this matrix to a translation matrix, overwriting it first by an identity matrix and then setting the 4th column to the
	 * translation vector.
	 *
	 * @param x The x-component of the translation vector
	 * @param y The y-component of the translation vector
	 * @param z The z-component of the translation vector
	 * @return This matrix for chaining */
	Matrix4& setToTranslation(float x, float y, float z);

	/** Sets this matrix to a translation and scaling matrix by first overwritting it with an identity and then setting the
	 * translation vector in the 4th column and the scaling vector in the diagonal.
	 *
	 * @param translation The translation vector
	 * @param scaling The scaling vector
	 * @return This matrix for chaining */
	Matrix4& setToTranslationAndScaling(const Vector3& translation, const Vector3& scaling);

	/** Sets this matrix to a translation and scaling matrix by first overwritting it with an identity and then setting the
	 * translation vector in the 4th column and the scaling vector in the diagonal.
	 *
	 * @param translationX The x-component of the translation vector
	 * @param translationY The y-component of the translation vector
	 * @param translationZ The z-component of the translation vector
	 * @param scalingX The x-component of the scaling vector
	 * @param scalingY The x-component of the scaling vector
	 * @param scalingZ The x-component of the scaling vector
	 * @return This matrix for chaining */
	Matrix4& setToTranslationAndScaling(float translationX, float translationY, float translationZ, float scalingX,
	        float scalingY, float scalingZ);

	/** Sets the matrix to a rotation matrix around the given axis.
	 *
	 * @param axis The axis
	 * @param angle The angle in degrees
	 * @return This matrix for chaining */
	Matrix4& setToRotation(const Vector3& axis, float angle);

	/** Sets the matrix to a rotation matrix around the given axis.
	 *
	 * @param axisX The x-component of the axis
	 * @param axisY The y-component of the axis
	 * @param axisZ The z-component of the axis
	 * @param angle The angle in degrees
	 * @return This matrix for chaining */
	Matrix4& setToRotation(float axisX, float axisY, float axisZ, float angle);

	

	/** Sets this matrix to a rotation matrix from the given euler angles.
	 * @param yaw the yaw in degrees
	 * @param pitch the pitch in degress
	 * @param roll the roll in degrees
	 * @return this matrix */
	Matrix4& setFromEulerAngles(float yaw, float pitch, float roll);

	/** Sets this matrix to a scaling matrix
	 *
	 * @param vector The scaling vector
	 * @return This matrix for chaining. */
	Matrix4& setToScaling(const Vector3& vector);

	/** Sets this matrix to a scaling matrix
	 *
	 * @param x The x-component of the scaling vector
	 * @param y The y-component of the scaling vector
	 * @param z The z-component of the scaling vector
	 * @return This matrix for chaining. */
	Matrix4& setToScaling(float x, float y, float z);

	/** Sets the matrix to a look at matrix with a direction and an up vector. Multiply with a translation matrix to get a camera
	 * model view matrix.
	 *
	 * @param direction The direction vector
	 * @param up The up vector
	 * @return This matrix for chaining */
	Matrix4& setToLookAt(const Vector3& direction, const Vector3& up);

	/** Sets this matrix to a look at matrix with the given position, target and up vector.
	 *
	 * @param position the position
	 * @param target the target
	 * @param up the up vector
	 * @return this matrix */
	Matrix4& setToLookAt(const Vector3& position, const Vector3& target, const Vector3& up);

	Matrix4& setToWorld(Vector3 position, Vector3 forward, Vector3 up);

	/** {@inheritDoc} */
	std::wstring toString();

	/** Linearly interpolates between this matrix and the given matrix mixing by alpha
	 * @param matrix the matrix
	 * @param alpha the alpha value in the range [0,1] */
	void lerp(const Matrix4& matrix, float alpha);

	/** Sets this matrix to the given 3x3 matrix. The third column of this matrix is set to (0,0,1,0).
	 * @param mat the matrix */
	Matrix4& set(const Matrix3& mat);

	void scl(const Vector3& scale);

	void getTranslation(Vector3& position);

	void getRotation(Quaternion& rotation);

	/** removes the translational part and transposes the matrix. */
	Matrix4& toNormalMatrix();

	
	/** Multiplies the matrix mata with matrix matb, storing the result in mata. The arrays are assumed to hold 4x4 column major
	 * matrices as you can get from {@link Matrix4#val}. This is the same as {@link Matrix4#mul(Matrix4)}.
	 *
	 * @param mata the first matrix.
	 * @param matb the second matrix. */
	static void mul(float mata[16], const float matb[16]);

	/** Multiplies the vector with the given matrix. The matrix array is assumed to hold a 4x4 column major matrix as you can get
	 * from {@link Matrix4#val}. The vector array is assumed to hold a 3-component vector, with x being the first element, y being
	 * the second and z being the last component. The result is stored in the vector array. This is the same as
	 * {@link Vector3#mul(Matrix4)}.
	 * @param mat the matrix
	 * @param vec the vector. */
	static void mulVec(const float mat[16], float vec[3]);

	/** Multiplies the vectors with the given matrix. The matrix array is assumed to hold a 4x4 column major matrix as you can get
	 * from {@link Matrix4#val}. The vectors array is assumed to hold 3-component vectors. Offset specifies the offset into the
	 * array where the x-component of the first vector is located. The numVecs parameter specifies the number of vectors stored in
	 * the vectors array. The stride parameter specifies the number of floats between subsequent vectors and must be >= 3. This is
	 * the same as {@link Vector3#mul(Matrix4)} applied to multiple vectors.
	 *
	 * @param mat the matrix
	 * @param vecs the vectors
	 * @param offset the offset into the vectors array
	 * @param numVecs the number of vectors
	 * @param stride the stride between vectors in floats */
	static void mulVec(const float mat[16], float* vecs, int offset, int numVecs, int stride);

	/** Multiplies the vector with the given matrix, performing a division by w. The matrix array is assumed to hold a 4x4 column
	 * major matrix as you can get from {@link Matrix4#val}. The vector array is assumed to hold a 3-component vector, with x being
	 * the first element, y being the second and z being the last component. The result is stored in the vector array. This is the
	 * same as {@link Vector3#prj(Matrix4)}.
	 * @param mat the matrix
	 * @param vec the vector. */
	static void prj(const float mat[16], float vec[3]);

	/** Multiplies the vectors with the given matrix, , performing a division by w. The matrix array is assumed to hold a 4x4 column
	 * major matrix as you can get from {@link Matrix4#val}. The vectors array is assumed to hold 3-component vectors. Offset
	 * specifies the offset into the array where the x-component of the first vector is located. The numVecs parameter specifies
	 * the number of vectors stored in the vectors array. The stride parameter specifies the number of floats between subsequent
	 * vectors and must be >= 3. This is the same as {@link Vector3#prj(Matrix4)} applied to multiple vectors.
	 *
	 * @param mat the matrix
	 * @param vecs the vectors
	 * @param offset the offset into the vectors array
	 * @param numVecs the number of vectors
	 * @param stride the stride between vectors in floats */
	static void prj(const float mat[16], float* vecs, int offset, int numVecs, int stride);

	/** Multiplies the vector with the top most 3x3 sub-matrix of the given matrix. The matrix array is assumed to hold a 4x4 column
	 * major matrix as you can get from {@link Matrix4#val}. The vector array is assumed to hold a 3-component vector, with x being
	 * the first element, y being the second and z being the last component. The result is stored in the vector array. This is the
	 * same as {@link Vector3#rot(Matrix4)}.
	 * @param mat the matrix
	 * @param vec the vector. */
	static void rot(const float mat[16], float* vec);

	/** Multiplies the vectors with the top most 3x3 sub-matrix of the given matrix. The matrix array is assumed to hold a 4x4
	 * column major matrix as you can get from {@link Matrix4#val}. The vectors array is assumed to hold 3-component vectors.
	 * Offset specifies the offset into the array where the x-component of the first vector is located. The numVecs parameter
	 * specifies the number of vectors stored in the vectors array. The stride parameter specifies the number of floats between
	 * subsequent vectors and must be >= 3. This is the same as {@link Vector3#rot(Matrix4)} applied to multiple vectors.
	 *
	 * @param mat the matrix
	 * @param vecs the vectors
	 * @param offset the offset into the vectors array
	 * @param numVecs the number of vectors
	 * @param stride the stride between vectors in floats */
	static void rot(const float mat[16], float* vecs, int offset, int numVecs, int stride);
	

	/** Computes the inverse of the given matrix. The matrix array is assumed to hold a 4x4 column major matrix as you can get from
	 * {@link Matrix4#val}.
	 * @param values the matrix values.
	 * @return false in case the inverse could not be calculated, true otherwise. */
	static bool inv(float values[16]);

	/** Computes the determinante of the given matrix. The matrix array is assumed to hold a 4x4 column major matrix as you can get
	 * from {@link Matrix4#val}.
	 * @param values the matrix values.
	 * @return the determinante. */
	static float det(float values[16]);

	/** Postmultiplies this matrix by a translation matrix. Postmultiplication is also used by OpenGL ES'
	 * glTranslate/glRotate/glScale
	 * @param x
	 * @param y
	 * @param z
	 * @return this matrix for chaining */
	Matrix4& translate(float x, float y, float z);

	/** Postmultiplies this matrix with a (counter-clockwise) rotation matrix. Postmultiplication is also used by OpenGL ES'
	 * glTranslate/glRotate/glScale
	 * @param axisX
	 * @param axisY
	 * @param axisZ
	 * @param angle the angle in degrees
	 * @return this matrix for chaining */
	Matrix4& rotate(float axisX, float axisY, float axisZ, float angle);

	/** Postmultiplies this matrix with a scale matrix. Postmultiplication is also used by OpenGL ES' glTranslate/glRotate/glScale.
	 * @param scaleX
	 * @param scaleY
	 * @param scaleZ
	 * @return this matrix for chaining */
	Matrix4& scale(float scaleX, float scaleY, float scaleZ);
};
