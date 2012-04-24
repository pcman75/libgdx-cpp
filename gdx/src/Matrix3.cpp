#include "StdAfx.h"
#include "Matrix3.h"
#include "GdxRuntimeException.h"
#include "Vector3.h"

const float Matrix3::DEGREE_TO_RAD = (float)M_PI / 180;

Matrix3::Matrix3()
{
	idt();
}

/** Sets this matrix to the identity matrix
* @return this matrix */
Matrix3& Matrix3::idt()
{
	vals[0] = 1;
	vals[1] = 0;
	vals[2] = 0;

	vals[3] = 0;
	vals[4] = 1;
	vals[5] = 0;

	vals[6] = 0;
	vals[7] = 0;
	vals[8] = 1;

	return *this;
}

/** Multiplies this matrix with the other matrix in the order this * m.
* @return this matrix */
Matrix3& Matrix3::mul(const Matrix3& m)
{
	float v00 = vals[0] * m.vals[0] + vals[3] * m.vals[1] + vals[6] * m.vals[2];
	float v01 = vals[0] * m.vals[3] + vals[3] * m.vals[4] + vals[6] * m.vals[5];
	float v02 = vals[0] * m.vals[6] + vals[3] * m.vals[7] + vals[6] * m.vals[8];

	float v10 = vals[1] * m.vals[0] + vals[4] * m.vals[1] + vals[7] * m.vals[2];
	float v11 = vals[1] * m.vals[3] + vals[4] * m.vals[4] + vals[7] * m.vals[5];
	float v12 = vals[1] * m.vals[6] + vals[4] * m.vals[7] + vals[7] * m.vals[8];

	float v20 = vals[2] * m.vals[0] + vals[5] * m.vals[1] + vals[8] * m.vals[2];
	float v21 = vals[2] * m.vals[3] + vals[5] * m.vals[4] + vals[8] * m.vals[5];
	float v22 = vals[2] * m.vals[6] + vals[5] * m.vals[7] + vals[8] * m.vals[8];

	vals[0] = v00;
	vals[1] = v10;
	vals[2] = v20;
	vals[3] = v01;
	vals[4] = v11;
	vals[5] = v21;
	vals[6] = v02;
	vals[7] = v12;
	vals[8] = v22;

	return *this;
}

/** Sets this matrix to a rotation matrix that will rotate any vector in counter clockwise order around the z-axis.
* @param angle the angle in degrees.
* @return this matrix */
Matrix3& Matrix3::setToRotation(float angle)
{
	angle = DEGREE_TO_RAD * angle;
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);

	vals[0] = cosAngle;
	vals[1] = sinAngle;
	vals[2] = 0;

	vals[3] = -sinAngle;
	vals[4] = cosAngle;
	vals[5] = 0;

	vals[6] = 0;
	vals[7] = 0;
	vals[8] = 1;

	return *this;
}

/** Sets this matrix to a translation matrix.
* @param x the translation in x
* @param y the translation in y
* @return this matrix */
Matrix3& Matrix3::setToTranslation(float x, float y)
{
	vals[0] = 1;
	vals[1] = 0;
	vals[2] = 0;

	vals[3] = 0;
	vals[4] = 1;
	vals[5] = 0;

	vals[6] = x;
	vals[7] = y;
	vals[8] = 1;

	return *this;
}

/** Sets this matrix to a scaling matrix
*
* @param scaleX the scale in x
* @param scaleY the scale in y
* @return this matrix */
Matrix3& Matrix3::setToScaling(float scaleX, float scaleY)
{
	vals[0] = scaleX;
	vals[1] = 0;
	vals[2] = 0;

	vals[3] = 0;
	vals[4] = scaleY;
	vals[5] = 0;

	vals[6] = 0;
	vals[7] = 0;
	vals[8] = 1;

	return *this;
}

std::string Matrix3::toString()
{
	std::stringstream ret;
	ret << "[" << vals[0] << "|" << vals[3] << "|" << vals[6] << "]\n" << "[" << vals[1] << "|" << vals[4] << "|" << vals[7] << "]\n" << "["
		<< vals[2] << "|" << vals[5] << "|" << vals[8] << "]";
	return ret.str();
}

/** @return the determinant of this matrix */
float Matrix3::det()
{
	return vals[0] * vals[4] * vals[8] + vals[3] * vals[7] * vals[2] + vals[6] * vals[1] * vals[5] - vals[0] * vals[7]
	* vals[5] - vals[3] * vals[1] * vals[8] - vals[6] * vals[4] * vals[2];
}

/** Inverts this matrix given that the determinant is != 0
* @return this matrix */
Matrix3& Matrix3::inv()
{
	float determinant = det();
	if(determinant == 0) 
		throw GdxRuntimeException("Can't invert a singular matrix");

	float inv_det = 1.0f / determinant;
	float m_tmp[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

	m_tmp[0] = vals[4] * vals[8] - vals[5] * vals[7];
	m_tmp[1] = vals[2] * vals[7] - vals[1] * vals[8];
	m_tmp[2] = vals[1] * vals[5] - vals[2] * vals[4];
	m_tmp[3] = vals[5] * vals[6] - vals[3] * vals[8];
	m_tmp[4] = vals[0] * vals[8] - vals[2] * vals[6];
	m_tmp[5] = vals[2] * vals[3] - vals[0] * vals[5];
	m_tmp[6] = vals[3] * vals[7] - vals[4] * vals[6];
	m_tmp[7] = vals[1] * vals[6] - vals[0] * vals[7];
	m_tmp[8] = vals[0] * vals[4] - vals[1] * vals[3];

	vals[0] = inv_det * m_tmp[0];
	vals[1] = inv_det * m_tmp[1];
	vals[2] = inv_det * m_tmp[2];
	vals[3] = inv_det * m_tmp[3];
	vals[4] = inv_det * m_tmp[4];
	vals[5] = inv_det * m_tmp[5];
	vals[6] = inv_det * m_tmp[6];
	vals[7] = inv_det * m_tmp[7];
	vals[8] = inv_det * m_tmp[8];

	return *this;
}

Matrix3& Matrix3::set(const Matrix3& mat)
{
	vals[0] = mat.vals[0];
	vals[1] = mat.vals[1];
	vals[2] = mat.vals[2];
	vals[3] = mat.vals[3];
	vals[4] = mat.vals[4];
	vals[5] = mat.vals[5];
	vals[6] = mat.vals[6];
	vals[7] = mat.vals[7];
	vals[8] = mat.vals[8];
	return *this;
}

/** Adds a translational component to the matrix in the 3rd column. The other columns are untouched.
* @param vector The translation vector
* @return This matrix for chaining */
Matrix3& Matrix3::trn(const Vector3& vector)
{
	vals[6] += vector.x;
	vals[7] += vector.y;
	return *this;
}

/** Adds a translational component to the matrix in the 3rd column. The other columns are untouched.
* @param x The x-component of the translation vector
* @param y The y-component of the translation vector
* @return This matrix for chaining */
Matrix3& Matrix3::trn(float x, float y)
{
	vals[6] += x;
	vals[7] += y;
	return *this;
}

/** Postmultiplies this matrix by a translation matrix. Postmultiplication is also used by OpenGL ES'
* glTranslate/glRotate/glScale
* @param x
* @param y
* @return this matrix for chaining */
Matrix3& Matrix3::translate(float x, float y)
{
	m_tmp[0] = 1;
	m_tmp[1] = 0;
	m_tmp[2] = 0;

	m_tmp[3] = 0;
	m_tmp[4] = 1;
	m_tmp[5] = 0;

	m_tmp[6] = x;
	m_tmp[7] = y;
	m_tmp[8] = 1;
	mul(vals, m_tmp);
	return *this;
}

/** Postmultiplies this matrix with a (counter-clockwise) rotation matrix. Postmultiplication is also used by OpenGL ES'
* glTranslate/glRotate/glScale
* @param angle the angle in degrees
* @return this matrix for chaining */
Matrix3& Matrix3::rotate(float angle)
{
	if(angle == 0) return *this;
	angle = DEGREE_TO_RAD * angle;
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);

	m_tmp[0] = cosAngle;
	m_tmp[1] = sinAngle;
	m_tmp[2] = 0;

	m_tmp[3] = -sinAngle;
	m_tmp[4] = cosAngle;
	m_tmp[5] = 0;

	m_tmp[6] = 0;
	m_tmp[7] = 0;
	m_tmp[8] = 1;
	mul(vals, m_tmp);
	return *this;
}

/** Postmultiplies this matrix with a scale matrix. Postmultiplication is also used by OpenGL ES' glTranslate/glRotate/glScale.
* @param scaleX
* @param scaleY
* @return this matrix for chaining */
Matrix3& Matrix3::scale(float scaleX, float scaleY)
{
	m_tmp[0] = scaleX;
	m_tmp[1] = 0;
	m_tmp[2] = 0;

	m_tmp[3] = 0;
	m_tmp[4] = scaleY;
	m_tmp[5] = 0;

	m_tmp[6] = 0;
	m_tmp[7] = 0;
	m_tmp[8] = 1;
	mul(vals, m_tmp);
	return *this;
}

const float* const Matrix3::getValues() const
{
	return vals;
}

void Matrix3::mul(float mata[9], float matb[9])
{
	float v00 = mata[0] * matb[0] + mata[3] * matb[1] + mata[6] * matb[2];
	float v01 = mata[0] * matb[3] + mata[3] * matb[4] + mata[6] * matb[5];
	float v02 = mata[0] * matb[6] + mata[3] * matb[7] + mata[6] * matb[8];

	float v10 = mata[1] * matb[0] + mata[4] * matb[1] + mata[7] * matb[2];
	float v11 = mata[1] * matb[3] + mata[4] * matb[4] + mata[7] * matb[5];
	float v12 = mata[1] * matb[6] + mata[4] * matb[7] + mata[7] * matb[8];

	float v20 = mata[2] * matb[0] + mata[5] * matb[1] + mata[8] * matb[2];
	float v21 = mata[2] * matb[3] + mata[5] * matb[4] + mata[8] * matb[5];
	float v22 = mata[2] * matb[6] + mata[5] * matb[7] + mata[8] * matb[8];

	mata[0] = v00;
	mata[1] = v10;
	mata[2] = v20;
	mata[3] = v01;
	mata[4] = v11;
	mata[5] = v21;
	mata[6] = v02;
	mata[7] = v12;
	mata[8] = v22;
}
