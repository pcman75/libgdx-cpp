#include "StdAfx.h"
#include "BoundingBox.h"


/** @return the center of the bounding box */
Vector3 BoundingBox::getCenter()
{
	return m_cnt;
}


void BoundingBox::updateCorners()
{
	if(!m_crn_dirty) 
		return;

	m_crn[0].set(m_min.x, m_min.y, m_min.z);
	m_crn[1].set(m_max.x, m_min.y, m_min.z);
	m_crn[2].set(m_max.x, m_max.y, m_min.z);
	m_crn[3].set(m_min.x, m_max.y, m_min.z);
	m_crn[4].set(m_min.x, m_min.y, m_max.z);
	m_crn[5].set(m_max.x, m_min.y, m_max.z);
	m_crn[6].set(m_max.x, m_max.y, m_max.z);
	m_crn[7].set(m_min.x, m_max.y, m_max.z);
	m_crn_dirty = false;
}


/** @return the corners of this bounding box */
const Vector3* const BoundingBox::getCorners()
{
	updateCorners();
	return m_crn;
}

/** @return The dimensions of this bounding box on all three axis */
const Vector3& BoundingBox::getDimensions()
{
	return m_dim;
}

/** @return The minimum vector */
const Vector3& BoundingBox::getMin()
{
	return m_min;
}

/** @return The maximum vector */
const Vector3& BoundingBox::getMax()
{
	return m_max;
}

/** Constructs a new bounding box with the minimum and maximum vector set to zeros.*/
BoundingBox::BoundingBox()
{
	m_crn_dirty = true;
	for(int l_idx = 0; l_idx < 8; l_idx++)
		m_crn[l_idx] = Vector3();
	clr();
}
 

/** Constructs a new bounding box from the given bounding box.
*
* @param bounds The bounding box to copy */
BoundingBox::BoundingBox(const BoundingBox& bounds)
{
	m_crn_dirty = true;
	for(int l_idx = 0; l_idx < 8; l_idx++)
		m_crn[l_idx] = Vector3();
	set(bounds);
}

/** Constructs the new bounding box using the given minimum and maximum vector.
*
* @param minimum The minimum vector
* @param maximum The maximum vector */
BoundingBox::BoundingBox(const Vector3& minimum, const Vector3& maximum)
{
	m_crn_dirty = true;
	for(int l_idx = 0; l_idx < 8; l_idx++)
		m_crn[l_idx] = Vector3();
	set(minimum, maximum);
}

/** Sets the given bounding box.
*
* @param bounds The bounds.
* @return This bounding box for chaining. */
BoundingBox& BoundingBox::set(const BoundingBox& bounds)
{
	m_crn_dirty = true;
	return set(bounds.m_min, bounds.m_max);
}

/** Sets the given minimum and maximum vector.
*
* @param minimum The minimum vector
* @param maximum The maximum vector
* @return This bounding box for chaining. */
BoundingBox& BoundingBox::set(const Vector3& minimum, const Vector3& maximum)
{
	m_min.set(minimum.x < maximum.x ? minimum.x : maximum.x, minimum.y < maximum.y ? minimum.y : maximum.y,
		minimum.z < maximum.z ? minimum.z : maximum.z);
	m_max.set(minimum.x > maximum.x ? minimum.x : maximum.x, minimum.y > maximum.y ? minimum.y : maximum.y,
		minimum.z > maximum.z ? minimum.z : maximum.z);
	m_cnt.set(m_min).add(m_max).mul(0.5f);
	m_dim.set(m_max).sub(m_min);
	m_crn_dirty = true;
	return *this;
}

/** Sets the bounding box minimum and maximum vector from the given points.
*
* @param points The points.
* @return This bounding box for chaining. */
BoundingBox& BoundingBox::set(const Vector3* points, int numPoints)
{
	inf();
	for(int i = 0; i < numPoints; i++)
	{
		ext(points[i]);
	}
	m_crn_dirty = true;
	return *this;
}

/** Sets the bounding box minimum and maximum vector from the given points.
*
* @param points The points.
* @return This bounding box for chaining. */
BoundingBox& BoundingBox::set(std::list<Vector3> points)
{
	inf();
	for(std::list<Vector3>::iterator it=points.begin(); it != points.end(); it++)
		this->ext(*it);
	m_crn_dirty = true;
	return *this;
}

/** Sets the minimum and maximum vector to positive and negative infinity.
*
* @return This bounding box for chaining. */
BoundingBox& BoundingBox::inf()
{
	m_min.set(FLT_MAX, FLT_MAX, FLT_MAX);
	m_max.set(FLT_MIN, FLT_MIN, FLT_MIN);
	m_cnt.set(0, 0, 0);
	m_dim.set(0, 0, 0);
	m_crn_dirty = true;
	return *this;
}

/** Extends the bounding box to incorporate the given {@link Vector3}.
*
* @param point The vector
* @return This bounding box for chaining. */
BoundingBox& BoundingBox::ext(const Vector3& point)
{
	m_crn_dirty = true;
	return set(m_min.set(min(m_min.x, point.x), min(m_min.y, point.y), min(m_min.z, point.z)),
		m_max.set(max(m_max.x, point.x), max(m_max.y, point.y), max(m_max.z, point.z)));
}

/** Sets the minimum and maximum vector to zeros
*
* @return This bounding box for chaining. */
BoundingBox& BoundingBox::clr()
{
	m_crn_dirty = true;
	return set(m_min.set(0, 0, 0), m_max.set(0, 0, 0));
}

/** Returns wheter this bounding box is valid. This means that m_min != m_max and m_min < m_max.
*
* @return True in case the bounding box is valid, false otherwise */
bool BoundingBox::isValid()
{
	return (m_min.x < m_max.x && m_min.y < m_max.y && m_min.z < m_max.z);
}

/** Extends this bounding box by the given bounding box.
*
* @param a_bounds The bounding box
* @return This bounding box for chaining. */
BoundingBox& BoundingBox::ext(BoundingBox& a_bounds)
{
	m_crn_dirty = true;
	return this->set(m_min.set(min(m_min.x, a_bounds.m_min.x), min(m_min.y, a_bounds.m_min.y), min(m_min.z, a_bounds.m_min.z)),
		m_max.set(max(m_max.x, a_bounds.m_max.x), max(m_max.y, a_bounds.m_max.y), max(m_max.z, a_bounds.m_max.z)));
}

/** Multiplies the bounding box by the given matrix. This is achieved by multiplying the 8 corner points and then calculating
* the minimum and maximum vectors from the transformed points.
*
* @param matrix The matrix
* @return This bounding box for chaining. */
BoundingBox& BoundingBox::mul(const class Matrix4& matrix)
{
	updateCorners();
	inf();
	for(int i = 0; i < 8; i++)
	{
		Vector3 l_pnt = m_crn[i];
		l_pnt.mul(matrix);
		m_min.set(min(m_min.x, l_pnt.x), min(m_min.y, l_pnt.y), min(m_min.z, l_pnt.z));
		m_max.set(max(m_max.x, l_pnt.x), max(m_max.y, l_pnt.y), max(m_max.z, l_pnt.z));
	}
	m_crn_dirty = true;
	return this->set(m_min, m_max);
}

/** Returns wheter the given bounding box is contained in this bounding box.
* @param bounds The bounding box
* @return Wheter the given bounding box is contained */
bool BoundingBox::contains(BoundingBox& bounds)
{
	if(!isValid()) return true;
	if(m_min.x > bounds.m_min.x) return false;
	if(m_min.y > bounds.m_min.y) return false;
	if(m_min.z > bounds.m_min.z) return false;
	if(m_max.x < bounds.m_max.x) return false;
	if(m_max.y < bounds.m_max.y) return false;
	if(m_max.z < bounds.m_max.z) return false;
	return true;
}

/** Returns wheter the given vector is contained in this bounding box.
* @param v The vector
* @return Wheter the vector is contained or not. */
bool BoundingBox::contains(const Vector3& v)
{
	if(m_min.x > v.x) return false;
	if(m_max.x < v.x) return false;
	if(m_min.y > v.y) return false;
	if(m_max.y < v.y) return false;
	if(m_min.z > v.z) return false;
	if(m_max.z < v.z) return false;

	return true;
}

std::wstring BoundingBox::toString()
{
	std::wstringstream ret;
	ret << "[" << m_min.toString() << "|" << m_max.toString() << "]";
	return ret.str();
}

/** Extends the bounding box by the given vector.
*
* @param x The x-coordinate
* @param y The y-coordinate
* @param z The z-coordinate
* @return This bounding box for chaining. */
BoundingBox& BoundingBox::ext(float x, float y, float z)
{
	m_crn_dirty = true;
	return this->set(m_min.set(min(m_min.x, x), min(m_min.y, y), min(m_min.z, z)), m_max.set(max(m_max.x, x), max(m_max.y, y), max(m_max.z, z)));
}
