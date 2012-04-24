#include "StdAfx.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "GdxRuntimeException.h"

Quaternion Matrix4::m_quat = Quaternion();
Vector3 Matrix4::m_tmpV = Vector3();
Vector3 Matrix4::m_tmpVec = Vector3();
Matrix4 Matrix4::m_tmpMat = Matrix4();

Vector3 Matrix4::m_l_vez;
Vector3 Matrix4::m_l_vex;
Vector3 Matrix4::m_l_vey;
Vector3 Matrix4::m_right;
Vector3 Matrix4::m_tmpForward;
Vector3 Matrix4::m_tmpUp;

Matrix4::Matrix4()
{
	memset(val, 0, sizeof(float) * 16);
	val[M00] = 1.;
	val[M11] = 1.;
	val[M22] = 1.;
	val[M33] = 1.;
}

/** Constructs a matrix from the given matrix
*
* @param matrix The matrix */
Matrix4::Matrix4(const Matrix4& matrix)
{
	set(matrix);
}

/** Constructs a matrix from the given float array. The array must have at least 16 elements
* @param values The float array */
Matrix4::Matrix4(const float values[16])
{
	set(values);
}

/** Constructs a rotation matrix from the given {@link Quaternion}
* @param quaternion The quaternion */
Matrix4::Matrix4(const class Quaternion& quaternion)
{
	set(quaternion);
}

/** Sets the matrix to the given matrix.
*
* @param matrix The matrix
* @return This matrix for chaining */
Matrix4& Matrix4::set(const Matrix4& matrix)
{
	return set(matrix.val);
}

/** Sets the matrix to the given matrix as a float array
*
* @param values The matrix
* @return This matrix for chaining */
Matrix4& Matrix4::set(const float values[16])
{
	memcpy(val, values, sizeof(float)*16);
	return *this;
}

/** Sets the matrix to a rotation matrix representing the quaternion.
*
* @param quaternion The quaternion
* @return This matrix for chaining */
Matrix4& Matrix4::set(const class Quaternion& quaternion)
{
	// Compute quaternion factors
	float l_xx = quaternion.x * quaternion.x;
	float l_xy = quaternion.x * quaternion.y;
	float l_xz = quaternion.x * quaternion.z;
	float l_xw = quaternion.x * quaternion.w;
	float l_yy = quaternion.y * quaternion.y;
	float l_yz = quaternion.y * quaternion.z;
	float l_yw = quaternion.y * quaternion.w;
	float l_zz = quaternion.z * quaternion.z;
	float l_zw = quaternion.z * quaternion.w;
	// Set matrix from quaternion
	val[M00] = 1 - 2 * (l_yy + l_zz);
	val[M01] = 2 * (l_xy - l_zw);
	val[M02] = 2 * (l_xz + l_yw);
	val[M03] = 0;
	val[M10] = 2 * (l_xy + l_zw);
	val[M11] = 1 - 2 * (l_xx + l_zz);
	val[M12] = 2 * (l_yz - l_xw);
	val[M13] = 0;
	val[M20] = 2 * (l_xz - l_yw);
	val[M21] = 2 * (l_yz + l_xw);
	val[M22] = 1 - 2 * (l_xx + l_yy);
	val[M23] = 0;
	val[M30] = 0;
	val[M31] = 0;
	val[M32] = 0;
	val[M33] = 1;
	return *this;
}

/** Sets the four columns of the matrix which correspond to the x-, y- and z-axis of the vector space this matrix creates as
* well as the 4th column representing the translation of any point that is multiplied by this matrix.
*
* @param xAxis The x-axis
* @param yAxis The y-axis
* @param zAxis The z-axis
* @param pos The translation vector */
void Matrix4::set(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis, const Vector3& pos)
{
	val[M00] = xAxis.x;
	val[M01] = xAxis.y;
	val[M02] = xAxis.z;
	val[M10] = yAxis.x;
	val[M11] = yAxis.y;
	val[M12] = yAxis.z;
	val[M20] = -zAxis.x;
	val[M21] = -zAxis.y;
	val[M22] = -zAxis.z;
	val[M03] = pos.x;
	val[M13] = pos.y;
	val[M23] = pos.z;
	val[M30] = 0;
	val[M31] = 0;
	val[M32] = 0;
	val[M33] = 1;
}

/** @return a copy of this matrix */
Matrix4 Matrix4::cpy()
{
	return *this;
}

/** Adds a translational component to the matrix in the 4th column. The other columns are untouched.
*
* @param vector The translation vector
* @return This matrix for chaining */
Matrix4& Matrix4::trn(const Vector3& vector)
{
	val[M03] += vector.x;
	val[M13] += vector.y;
	val[M23] += vector.z;
	return *this;
}

/** Adds a translational component to the matrix in the 4th column. The other columns are untouched.
*
* @param x The x-component of the translation vector
* @param y The y-component of the translation vector
* @param z The z-component of the translation vector
* @return This matrix for chaining */
Matrix4& Matrix4::trn(float x, float y, float z)
{
	val[M03] += x;
	val[M13] += y;
	val[M23] += z;
	return *this;
}

/** @return the backing float array */
const float* const Matrix4::getValues() const
{
	return val;
}

/** Multiplies this matrix with the given matrix, storing the result in this matrix.
*
* @param matrix The other matrix
* @return This matrix for chaining. */
Matrix4& Matrix4::mul(const Matrix4& matrix)
{
	mul(val, matrix.val);
	return *this;
}

/** Transposes the matrix
*
* @return This matrix for chaining */
Matrix4& Matrix4::tra()
{
	m_tmp[M00] = val[M00];
	m_tmp[M01] = val[M10];
	m_tmp[M02] = val[M20];
	m_tmp[M03] = val[M30];
	m_tmp[M10] = val[M01];
	m_tmp[M11] = val[M11];
	m_tmp[M12] = val[M21];
	m_tmp[M13] = val[M31];
	m_tmp[M20] = val[M02];
	m_tmp[M21] = val[M12];
	m_tmp[M22] = val[M22];
	m_tmp[M23] = val[M32];
	m_tmp[M30] = val[M03];
	m_tmp[M31] = val[M13];
	m_tmp[M32] = val[M23];
	m_tmp[M33] = val[M33];
	return set(m_tmp);
}

/** Sets the matrix to an identity matrix
*
* @return This matrix for chaining */
Matrix4& Matrix4::idt()
{
	val[M00] = 1;
	val[M01] = 0;
	val[M02] = 0;
	val[M03] = 0;
	val[M10] = 0;
	val[M11] = 1;
	val[M12] = 0;
	val[M13] = 0;
	val[M20] = 0;
	val[M21] = 0;
	val[M22] = 1;
	val[M23] = 0;
	val[M30] = 0;
	val[M31] = 0;
	val[M32] = 0;
	val[M33] = 1;
	return *this;
}

/** Inverts the matrix. Throws a RuntimeException in case the matrix is not invertible. Stores the result in this matrix
*
* @return This matrix for chaining */
Matrix4& Matrix4::inv()
{
	if(!inv(val))
		throw GdxRuntimeException("non-invertible matrix");
	return *this;
}

/** @return The determinant of this matrix */
float Matrix4::det()
{
	return det(val);
}

/** Sets the matrix to a projection matrix with a nearPlane- and farPlane plane, a field of view in degrees and an aspect ratio.
*
* @param nearPlane The nearPlane plane
* @param farPlane The farPlane plane
* @param fov The field of view in degrees
* @param aspectRatio The aspect ratio
* @return This matrix for chaining */
Matrix4& Matrix4::setToProjection(float nearPlane, float farPlane, float fov, float aspectRatio)
{
	this->idt();
	float l_fd = (float)(1.0 / tan((fov * (M_PI / 180)) / 2.0));
	float l_a1 = (farPlane + nearPlane) / (nearPlane - farPlane);
	float l_a2 = (2 * farPlane * nearPlane) / (nearPlane - farPlane);
	val[M00] = l_fd / aspectRatio;
	val[M10] = 0;
	val[M20] = 0;
	val[M30] = 0;
	val[M01] = 0;
	val[M11] = l_fd;
	val[M21] = 0;
	val[M31] = 0;
	val[M02] = 0;
	val[M12] = 0;
	val[M22] = l_a1;
	val[M32] = -1;
	val[M03] = 0;
	val[M13] = 0;
	val[M23] = l_a2;
	val[M33] = 0;

	return *this;
}

/** Sets this matrix to an orthographic projection matrix with the origin at (x,y) extending by width and height. The nearPlane plane
* is set to 0, the farPlane plane is set to 1.
*
* @param x The x-coordinate of the origin
* @param y The y-coordinate of the origin
* @param width The width
* @param height The height
* @return This matrix for chaining */
Matrix4& Matrix4::setToOrtho2D(float x, float y, float width, float height)
{
	setToOrtho(x, x + width, y, y + height, 0, 1);
	return *this;
}

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
Matrix4& Matrix4::setToOrtho2D(float x, float y, float width, float height, float nearPlane, float farPlane)
{
	setToOrtho(x, x + width, y, y + height, nearPlane, farPlane);
	return *this;
}

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
Matrix4& Matrix4::setToOrtho(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
	this->idt();
	float x_orth = 2 / (right - left);
	float y_orth = 2 / (top - bottom);
	float z_orth = -2 / (farPlane - nearPlane);

	float tx = -(right + left) / (right - left);
	float ty = -(top + bottom) / (top - bottom);
	float tz = -(farPlane + nearPlane) / (farPlane - nearPlane);

	val[M00] = x_orth;
	val[M10] = 0;
	val[M20] = 0;
	val[M30] = 0;
	val[M01] = 0;
	val[M11] = y_orth;
	val[M21] = 0;
	val[M31] = 0;
	val[M02] = 0;
	val[M12] = 0;
	val[M22] = z_orth;
	val[M32] = 0;
	val[M03] = tx;
	val[M13] = ty;
	val[M23] = tz;
	val[M33] = 1;

	return *this;
}

/** Sets this matrix to a translation matrix, overwriting it first by an identity matrix and then setting the 4th column to the
* translation vector.
*
* @param vector The translation vector
* @return This matrix for chaining */
Matrix4& Matrix4::setToTranslation(const Vector3& vector)
{
	idt();
	val[M03] = vector.x;
	val[M13] = vector.y;
	val[M23] = vector.z;
	return *this;
}

/** Sets this matrix to a translation matrix, overwriting it first by an identity matrix and then setting the 4th column to the
* translation vector.
*
* @param x The x-component of the translation vector
* @param y The y-component of the translation vector
* @param z The z-component of the translation vector
* @return This matrix for chaining */
Matrix4& Matrix4::setToTranslation(float x, float y, float z)
{
	idt();
	val[M03] = x;
	val[M13] = y;
	val[M23] = z;
	return *this;
}

/** Sets this matrix to a translation and scaling matrix by first overwritting it with an identity and then setting the
* translation vector in the 4th column and the scaling vector in the diagonal.
*
* @param translation The translation vector
* @param scaling The scaling vector
* @return This matrix for chaining */
Matrix4& Matrix4::setToTranslationAndScaling(const Vector3& translation, const Vector3& scaling)
{
	idt();
	val[M03] = translation.x;
	val[M13] = translation.y;
	val[M23] = translation.z;
	val[M00] = scaling.x;
	val[M11] = scaling.y;
	val[M22] = scaling.z;
	return *this;
}

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
Matrix4& Matrix4::setToTranslationAndScaling(float translationX, float translationY, float translationZ, float scalingX,
	float scalingY, float scalingZ)
{
	idt();
	val[M03] = translationX;
	val[M13] = translationY;
	val[M23] = translationZ;
	val[M00] = scalingX;
	val[M11] = scalingY;
	val[M22] = scalingZ;
	return *this;
}

/** Sets the matrix to a rotation matrix around the given axis.
*
* @param axis The axis
* @param angle The angle in degrees
* @return This matrix for chaining */
Matrix4& Matrix4::setToRotation(const Vector3& axis, float angle)
{
	idt();
	if(angle == 0) 
		return *this;
	return set(m_quat.set(axis, angle));
}

/** Sets the matrix to a rotation matrix around the given axis.
*
* @param axisX The x-component of the axis
* @param axisY The y-component of the axis
* @param axisZ The z-component of the axis
* @param angle The angle in degrees
* @return This matrix for chaining */
Matrix4& Matrix4::setToRotation(float axisX, float axisY, float axisZ, float angle)
{
	idt();
	if(angle == 0)
		return *this;
	return set(m_quat.set(m_tmpV.set(axisX, axisY, axisZ), angle));
}



/** Sets this matrix to a rotation matrix from the given euler angles.
* @param yaw the yaw in degrees
* @param pitch the pitch in degress
* @param roll the roll in degrees
* @return this matrix */
Matrix4& Matrix4::setFromEulerAngles(float yaw, float pitch, float roll)
{
	idt();
	m_quat.setEulerAngles(yaw, pitch, roll);
	return set(m_quat);
}

/** Sets this matrix to a scaling matrix
*
* @param vector The scaling vector
* @return This matrix for chaining. */
Matrix4& Matrix4::setToScaling(const Vector3& vector)
{
	idt();
	val[M00] = vector.x;
	val[M11] = vector.y;
	val[M22] = vector.z;
	return *this;
}

/** Sets this matrix to a scaling matrix
*
* @param x The x-component of the scaling vector
* @param y The y-component of the scaling vector
* @param z The z-component of the scaling vector
* @return This matrix for chaining. */
Matrix4& Matrix4::setToScaling(float x, float y, float z)
{
	idt();
	val[M00] = x;
	val[M11] = y;
	val[M22] = z;
	return *this;
}

/** Sets the matrix to a look at matrix with a direction and an up vector. Multiply with a translation matrix to get a camera
* model view matrix.
*
* @param direction The direction vector
* @param up The up vector
* @return This matrix for chaining */
Matrix4& Matrix4::setToLookAt(const Vector3& direction, const Vector3& up)
{
	m_l_vez.set(direction).nor();
	m_l_vex.set(direction).nor();
	m_l_vex.crs(up).nor();
	m_l_vey.set(m_l_vex).crs(m_l_vez).nor();
	idt();
	val[M00] = m_l_vex.x;
	val[M01] = m_l_vex.y;
	val[M02] = m_l_vex.z;
	val[M10] = m_l_vey.x;
	val[M11] = m_l_vey.y;
	val[M12] = m_l_vey.z;
	val[M20] = -m_l_vez.x;
	val[M21] = -m_l_vez.y;
	val[M22] = -m_l_vez.z;

	return *this;
}

/** Sets this matrix to a look at matrix with the given position, target and up vector.
*
* @param position the position
* @param target the target
* @param up the up vector
* @return this matrix */
Matrix4& Matrix4::setToLookAt(const Vector3& position, const Vector3& target, const Vector3& up)
{
	m_tmpVec.set(target).sub(position);
	setToLookAt(m_tmpVec, up);
	this->mul(m_tmpMat.setToTranslation(position.tmp().mul(-1)));

	return *this;
}

Matrix4& Matrix4::setToWorld(Vector3 position, Vector3 forward, Vector3 up)
{
	m_tmpForward.set(forward).nor();
	m_right.set(m_tmpForward).crs(up).nor();
	m_tmpUp.set(m_right).crs(m_tmpForward).nor();

	this->set(m_right, m_tmpUp, m_tmpForward, position);
	return *this;
}

/** {@inheritDoc} */
std::string Matrix4::toString()
{
	std::stringstream ret;
	ret << "[" << val[M00] << "|" << val[M01] << "|" << val[M02] << "|" << val[M03] << "]\n" << "[" << val[M10] << "|" << val[M11] << "|"
		<< val[M12] << "|" << val[M13] << "]\n" << "[" << val[M20] << "|" << val[M21] << "|" << val[M22] << "|" << val[M23] << "]\n" << "["
		<< val[M30] << "|" << val[M31] << "|" << val[M32] << "|" << val[M33] << "]\n";
	return ret.str();
}

/** Linearly interpolates between this matrix and the given matrix mixing by alpha
* @param matrix the matrix
* @param alpha the alpha value in the range [0,1] */
void Matrix4::lerp(const Matrix4& matrix, float alpha)
{
	for(int i = 0; i < 16; i++)
		this->val[i] = this->val[i] * (1 - alpha) + matrix.val[i] * alpha;
}

/** Sets this matrix to the given 3x3 matrix. The third column of this matrix is set to (0,0,1,0).
* @param mat the matrix */
Matrix4& Matrix4::set(const Matrix3& mat)
{
	val[0] = mat.vals[0];
	val[1] = mat.vals[1];
	val[2] = mat.vals[2];
	val[3] = 0;
	val[4] = mat.vals[3];
	val[5] = mat.vals[4];
	val[6] = mat.vals[5];
	val[7] = 0;
	val[8] = 0;
	val[9] = 0;
	val[10] = 1;
	val[11] = 0;
	val[12] = mat.vals[6];
	val[13] = mat.vals[7];
	val[14] = 0;
	val[15] = mat.vals[8];
	return *this;
}

void Matrix4::scl(const Vector3& scale)
{
	val[M00] *= scale.x;
	val[M11] *= scale.y;
	val[M22] *= scale.z;
}

void Matrix4::getTranslation(Vector3& position)
{
	position.x = val[M03];
	position.y = val[M13];
	position.z = val[M23];
}

void Matrix4::getRotation(Quaternion& rotation)
{
	rotation.setFromMatrix(*this);
}

/** removes the translational part and transposes the matrix. */
Matrix4& Matrix4::toNormalMatrix()
{
	val[M03] = 0;
	val[M13] = 0;
	val[M23] = 0;
	inv();
	return tra();
}


/** Multiplies the matrix mata with matrix matb, storing the result in mata. The arrays are assumed to hold 4x4 column major
* matrices as you can get from {@link Matrix4#val}. This is the same as {@link Matrix4#mul(Matrix4)}.
*
* @param mata the first matrix.
* @param matb the second matrix. */
void Matrix4::mul(float mata[16], const float matb[16])
{
	float tmp[16];
	tmp[M00] = mata[M00] * matb[M00] + mata[M01] * matb[M10] + mata[M02] * matb[M20] + mata[M03] * matb[M30];
	tmp[M01] = mata[M00] * matb[M01] + mata[M01] * matb[M11] + mata[M02] * matb[M21] + mata[M03] * matb[M31];
	tmp[M02] = mata[M00] * matb[M02] + mata[M01] * matb[M12] + mata[M02] * matb[M22] + mata[M03] * matb[M32];
	tmp[M03] = mata[M00] * matb[M03] + mata[M01] * matb[M13] + mata[M02] * matb[M23] + mata[M03] * matb[M33];
	tmp[M10] = mata[M10] * matb[M00] + mata[M11] * matb[M10] + mata[M12] * matb[M20] + mata[M13] * matb[M30];
	tmp[M11] = mata[M10] * matb[M01] + mata[M11] * matb[M11] + mata[M12] * matb[M21] + mata[M13] * matb[M31];
	tmp[M12] = mata[M10] * matb[M02] + mata[M11] * matb[M12] + mata[M12] * matb[M22] + mata[M13] * matb[M32];
	tmp[M13] = mata[M10] * matb[M03] + mata[M11] * matb[M13] + mata[M12] * matb[M23] + mata[M13] * matb[M33];
	tmp[M20] = mata[M20] * matb[M00] + mata[M21] * matb[M10] + mata[M22] * matb[M20] + mata[M23] * matb[M30];
	tmp[M21] = mata[M20] * matb[M01] + mata[M21] * matb[M11] + mata[M22] * matb[M21] + mata[M23] * matb[M31];
	tmp[M22] = mata[M20] * matb[M02] + mata[M21] * matb[M12] + mata[M22] * matb[M22] + mata[M23] * matb[M32];
	tmp[M23] = mata[M20] * matb[M03] + mata[M21] * matb[M13] + mata[M22] * matb[M23] + mata[M23] * matb[M33];
	tmp[M30] = mata[M30] * matb[M00] + mata[M31] * matb[M10] + mata[M32] * matb[M20] + mata[M33] * matb[M30];
	tmp[M31] = mata[M30] * matb[M01] + mata[M31] * matb[M11] + mata[M32] * matb[M21] + mata[M33] * matb[M31];
	tmp[M32] = mata[M30] * matb[M02] + mata[M31] * matb[M12] + mata[M32] * matb[M22] + mata[M33] * matb[M32];
	tmp[M33] = mata[M30] * matb[M03] + mata[M31] * matb[M13] + mata[M32] * matb[M23] + mata[M33] * matb[M33];
	memcpy(mata, tmp, sizeof(float) *  16);
}

/** Multiplies the vector with the given matrix. The matrix array is assumed to hold a 4x4 column major matrix as you can get
* from {@link Matrix4#val}. The vector array is assumed to hold a 3-component vector, with x being the first element, y being
* the second and z being the last component. The result is stored in the vector array. This is the same as
* {@link Vector3#mul(Matrix4)}.
* @param mat the matrix
* @param vec the vector. */
void Matrix4::mulVec(const float mat[16], float vec[3])
{
	float x = vec[0] * mat[M00] + vec[1] * mat[M01] + vec[2] * mat[M02] + mat[M03];
	float y = vec[0] * mat[M10] + vec[1] * mat[M11] + vec[2] * mat[M12] + mat[M13];
	float z = vec[0] * mat[M20] + vec[1] * mat[M21] + vec[2] * mat[M22] + mat[M23];
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}

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
void Matrix4::mulVec(const float mat[16], float* vecs, int offset, int numVecs, int stride)
{
	float* vecPtr = vecs + offset;
	for(int i = 0; i < numVecs; i++) 
	{
		mulVec(mat, vecPtr);
		vecPtr += stride;
	}
}

/** Multiplies the vector with the given matrix, performing a division by w. The matrix array is assumed to hold a 4x4 column
* major matrix as you can get from {@link Matrix4#val}. The vector array is assumed to hold a 3-component vector, with x being
* the first element, y being the second and z being the last component. The result is stored in the vector array. This is the
* same as {@link Vector3#prj(Matrix4)}.
* @param mat the matrix
* @param vec the vector. */
void Matrix4::prj(const float mat[16], float vec[3])
{
	float inv_w = 1.0f / (vec[0] * mat[M30] + vec[1] * mat[M31] + vec[2] * mat[M32] + mat[M33]);
	float x = (vec[0] * mat[M00] + vec[1] * mat[M01] + vec[2] * mat[M02] + mat[M03]) * inv_w;
	float y = (vec[0] * mat[M10] + vec[1] * mat[M11] + vec[2] * mat[M12] + mat[M13]) * inv_w; 
	float z = (vec[0] * mat[M20] + vec[1] * mat[M21] + vec[2] * mat[M22] + mat[M23]) * inv_w;
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}

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
void Matrix4::prj(const float mat[16], float* vecs, int offset, int numVecs, int stride)
{
	float* vecPtr = vecs + offset;
	for(int i = 0; i < numVecs; i++) 
	{
		prj(mat, vecPtr);
		vecPtr += stride;
	}
}

/** Multiplies the vector with the top most 3x3 sub-matrix of the given matrix. The matrix array is assumed to hold a 4x4 column
* major matrix as you can get from {@link Matrix4#val}. The vector array is assumed to hold a 3-component vector, with x being
* the first element, y being the second and z being the last component. The result is stored in the vector array. This is the
* same as {@link Vector3#rot(Matrix4)}.
* @param mat the matrix
* @param vec the vector. */
void Matrix4::rot(const float mat[16], float* vec)
{
	float x = vec[0] * mat[M00] + vec[1] * mat[M01] + vec[2] * mat[M02];
	float y = vec[0] * mat[M10] + vec[1] * mat[M11] + vec[2] * mat[M12];
	float z = vec[0] * mat[M20] + vec[1] * mat[M21] + vec[2] * mat[M22];
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}

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
void Matrix4::rot(const float mat[16], float* vecs, int offset, int numVecs, int stride)
{
	float* vecPtr = vecs + offset;
	for(int i = 0; i < numVecs; i++) 
	{
		rot(mat, vecPtr);
		vecPtr += stride;
	}
}


/** Computes the inverse of the given matrix. The matrix array is assumed to hold a 4x4 column major matrix as you can get from
* {@link Matrix4#val}.
* @param values the matrix values.
* @return false in case the inverse could not be calculated, true otherwise. */
bool Matrix4::inv(float values[16])
{
	float tmp[16];
	float l_det = det(values);
	if (l_det == 0) 
		return false;

	tmp[M00] = values[M12] * values[M23] * values[M31] - values[M13] * values[M22] * values[M31] + values[M13] * values[M21] * values[M32] - values[M11]
		* values[M23] * values[M32] - values[M12] * values[M21] * values[M33] + values[M11] * values[M22] * values[M33];
	tmp[M01] = values[M03] * values[M22] * values[M31] - values[M02] * values[M23] * values[M31] - values[M03] * values[M21] * values[M32] + values[M01]
		* values[M23] * values[M32] + values[M02] * values[M21] * values[M33] - values[M01] * values[M22] * values[M33];
	tmp[M02] = values[M02] * values[M13] * values[M31] - values[M03] * values[M12] * values[M31] + values[M03] * values[M11] * values[M32] - values[M01]
		* values[M13] * values[M32] - values[M02] * values[M11] * values[M33] + values[M01] * values[M12] * values[M33];
	tmp[M03] = values[M03] * values[M12] * values[M21] - values[M02] * values[M13] * values[M21] - values[M03] * values[M11] * values[M22] + values[M01]
		* values[M13] * values[M22] + values[M02] * values[M11] * values[M23] - values[M01] * values[M12] * values[M23];
	tmp[M10] = values[M13] * values[M22] * values[M30] - values[M12] * values[M23] * values[M30] - values[M13] * values[M20] * values[M32] + values[M10]
		* values[M23] * values[M32] + values[M12] * values[M20] * values[M33] - values[M10] * values[M22] * values[M33];
	tmp[M11] = values[M02] * values[M23] * values[M30] - values[M03] * values[M22] * values[M30] + values[M03] * values[M20] * values[M32] - values[M00]
		* values[M23] * values[M32] - values[M02] * values[M20] * values[M33] + values[M00] * values[M22] * values[M33];
	tmp[M12] = values[M03] * values[M12] * values[M30] - values[M02] * values[M13] * values[M30] - values[M03] * values[M10] * values[M32] + values[M00]
		* values[M13] * values[M32] + values[M02] * values[M10] * values[M33] - values[M00] * values[M12] * values[M33];
	tmp[M13] = values[M02] * values[M13] * values[M20] - values[M03] * values[M12] * values[M20] + values[M03] * values[M10] * values[M22] - values[M00]
		* values[M13] * values[M22] - values[M02] * values[M10] * values[M23] + values[M00] * values[M12] * values[M23];
	tmp[M20] = values[M11] * values[M23] * values[M30] - values[M13] * values[M21] * values[M30] + values[M13] * values[M20] * values[M31] - values[M10]
		* values[M23] * values[M31] - values[M11] * values[M20] * values[M33] + values[M10] * values[M21] * values[M33];
	tmp[M21] = values[M03] * values[M21] * values[M30] - values[M01] * values[M23] * values[M30] - values[M03] * values[M20] * values[M31] + values[M00]
		* values[M23] * values[M31] + values[M01] * values[M20] * values[M33] - values[M00] * values[M21] * values[M33];
	tmp[M22] = values[M01] * values[M13] * values[M30] - values[M03] * values[M11] * values[M30] + values[M03] * values[M10] * values[M31] - values[M00]
		* values[M13] * values[M31] - values[M01] * values[M10] * values[M33] + values[M00] * values[M11] * values[M33];
	tmp[M23] = values[M03] * values[M11] * values[M20] - values[M01] * values[M13] * values[M20] - values[M03] * values[M10] * values[M21] + values[M00]
		* values[M13] * values[M21] + values[M01] * values[M10] * values[M23] - values[M00] * values[M11] * values[M23];
	tmp[M30] = values[M12] * values[M21] * values[M30] - values[M11] * values[M22] * values[M30] - values[M12] * values[M20] * values[M31] + values[M10]
		* values[M22] * values[M31] + values[M11] * values[M20] * values[M32] - values[M10] * values[M21] * values[M32];
	tmp[M31] = values[M01] * values[M22] * values[M30] - values[M02] * values[M21] * values[M30] + values[M02] * values[M20] * values[M31] - values[M00]
		* values[M22] * values[M31] - values[M01] * values[M20] * values[M32] + values[M00] * values[M21] * values[M32];
	tmp[M32] = values[M02] * values[M11] * values[M30] - values[M01] * values[M12] * values[M30] - values[M02] * values[M10] * values[M31] + values[M00]
		* values[M12] * values[M31] + values[M01] * values[M10] * values[M32] - values[M00] * values[M11] * values[M32];
	tmp[M33] = values[M01] * values[M12] * values[M20] - values[M02] * values[M11] * values[M20] + values[M02] * values[M10] * values[M21] - values[M00]
		* values[M12] * values[M21] - values[M01] * values[M10] * values[M22] + values[M00] * values[M11] * values[M22];
	
	float inv_det = 1.0f / l_det;
	values[M00] = tmp[M00] * inv_det;
	values[M01] = tmp[M01] * inv_det;
	values[M02] = tmp[M02] * inv_det;
	values[M03] = tmp[M03] * inv_det;
	values[M10] = tmp[M10] * inv_det;
	values[M11] = tmp[M11] * inv_det;
	values[M12] = tmp[M12] * inv_det;
	values[M13] = tmp[M13] * inv_det;
	values[M20] = tmp[M20] * inv_det;
	values[M21] = tmp[M21] * inv_det;
	values[M22] = tmp[M22] * inv_det;
	values[M23] = tmp[M23] * inv_det;
	values[M30] = tmp[M30] * inv_det;
	values[M31] = tmp[M31] * inv_det;
	values[M32] = tmp[M32] * inv_det;
	values[M33] = tmp[M33] * inv_det;
	return true;
}

/** Computes the determinante of the given matrix. The matrix array is assumed to hold a 4x4 column major matrix as you can get
* from {@link Matrix4#val}.
* @param values the matrix values.
* @return the determinante. */
float Matrix4::det(float values[16])
{
	return values[M30] * values[M21] * values[M12] * values[M03] - values[M20] * values[M31] * values[M12] * values[M03] - values[M30] * values[M11]
		* values[M22] * values[M03] + values[M10] * values[M31] * values[M22] * values[M03] + values[M20] * values[M11] * values[M32] * values[M03] - values[M10]
		* values[M21] * values[M32] * values[M03] - values[M30] * values[M21] * values[M02] * values[M13] + values[M20] * values[M31] * values[M02] * values[M13]
		+ values[M30] * values[M01] * values[M22] * values[M13] - values[M00] * values[M31] * values[M22] * values[M13] - values[M20] * values[M01] * values[M32]
		* values[M13] + values[M00] * values[M21] * values[M32] * values[M13] + values[M30] * values[M11] * values[M02] * values[M23] - values[M10] * values[M31]
		* values[M02] * values[M23] - values[M30] * values[M01] * values[M12] * values[M23] + values[M00] * values[M31] * values[M12] * values[M23] + values[M10]
		* values[M01] * values[M32] * values[M23] - values[M00] * values[M11] * values[M32] * values[M23] - values[M20] * values[M11] * values[M02] * values[M33]
		+ values[M10] * values[M21] * values[M02] * values[M33] + values[M20] * values[M01] * values[M12] * values[M33] - values[M00] * values[M21] * values[M12]
		* values[M33] - values[M10] * values[M01] * values[M22] * values[M33] + values[M00] * values[M11] * values[M22] * values[M33];
}

/** Postmultiplies this matrix by a translation matrix. Postmultiplication is also used by OpenGL ES'
* glTranslate/glRotate/glScale
* @param x
* @param y
* @param z
* @return this matrix for chaining */
Matrix4& Matrix4::translate(float x, float y, float z)
{
	m_tmp[M00] = 1;
	m_tmp[M01] = 0;
	m_tmp[M02] = 0;
	m_tmp[M03] = x;
	m_tmp[M10] = 0;
	m_tmp[M11] = 1;
	m_tmp[M12] = 0;
	m_tmp[M13] = y;
	m_tmp[M20] = 0;
	m_tmp[M21] = 0;
	m_tmp[M22] = 1;
	m_tmp[M23] = z;
	m_tmp[M30] = 0;
	m_tmp[M31] = 0;
	m_tmp[M32] = 0;
	m_tmp[M33] = 1;

	mul(val, m_tmp);
	return *this;
}

/** Postmultiplies this matrix with a (counter-clockwise) rotation matrix. Postmultiplication is also used by OpenGL ES'
* glTranslate/glRotate/glScale
* @param axisX
* @param axisY
* @param axisZ
* @param angle the angle in degrees
* @return this matrix for chaining */
Matrix4& Matrix4::rotate(float axisX, float axisY, float axisZ, float angle)
{
	if(angle == 0) 
		return *this;

	m_quat.set(m_tmpV.set(axisX, axisY, axisZ), angle);
	Quaternion& quaternion = m_quat;
	float l_xx = quaternion.x * quaternion.x;
	float l_xy = quaternion.x * quaternion.y;
	float l_xz = quaternion.x * quaternion.z;
	float l_xw = quaternion.x * quaternion.w;
	float l_yy = quaternion.y * quaternion.y;
	float l_yz = quaternion.y * quaternion.z;
	float l_yw = quaternion.y * quaternion.w;
	float l_zz = quaternion.z * quaternion.z;
	float l_zw = quaternion.z * quaternion.w;
	// Set matrix from quaternion
	m_tmp[M00] = 1 - 2 * (l_yy + l_zz);
	m_tmp[M01] = 2 * (l_xy - l_zw);
	m_tmp[M02] = 2 * (l_xz + l_yw);
	m_tmp[M03] = 0;
	m_tmp[M10] = 2 * (l_xy + l_zw);
	m_tmp[M11] = 1 - 2 * (l_xx + l_zz);
	m_tmp[M12] = 2 * (l_yz - l_xw);
	m_tmp[M13] = 0;
	m_tmp[M20] = 2 * (l_xz - l_yw);
	m_tmp[M21] = 2 * (l_yz + l_xw);
	m_tmp[M22] = 1 - 2 * (l_xx + l_yy);
	m_tmp[M23] = 0;
	m_tmp[M30] = 0;
	m_tmp[M31] = 0;
	m_tmp[M32] = 0;
	m_tmp[M33] = 1;

	mul(val, m_tmp);
	return *this;
}

/** Postmultiplies this matrix with a scale matrix. Postmultiplication is also used by OpenGL ES' glTranslate/glRotate/glScale.
* @param scaleX
* @param scaleY
* @param scaleZ
* @return this matrix for chaining */
Matrix4& Matrix4::scale(float scaleX, float scaleY, float scaleZ)
{
	m_tmp[M00] = scaleX;
	m_tmp[M01] = 0;
	m_tmp[M02] = 0;
	m_tmp[M03] = 0;
	m_tmp[M10] = 0;
	m_tmp[M11] = scaleY;
	m_tmp[M12] = 0;
	m_tmp[M13] = 0;
	m_tmp[M20] = 0;
	m_tmp[M21] = 0;
	m_tmp[M22] = scaleZ;
	m_tmp[M23] = 0;
	m_tmp[M30] = 0;
	m_tmp[M31] = 0;
	m_tmp[M32] = 0;
	m_tmp[M33] = 1;

	mul(val, m_tmp);
	return *this;
}

