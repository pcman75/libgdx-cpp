#include "stdafx.h"
#include "ImmediateModeRenderer10.h"
#include "Gdx.h"

ImmediateModeRenderer10::ImmediateModeRenderer10()
{
	init(2000);
}
ImmediateModeRenderer10::ImmediateModeRenderer10(int maxVertices)
{
	init(maxVertices);
}

ImmediateModeRenderer10::~ImmediateModeRenderer10()
{
	delete m_positions;
	delete m_colors;
	delete m_normals;
	delete m_texCoords;
}

void ImmediateModeRenderer10::init(int maxVertices)
{
	m_idxPos = 0;
	m_idxCols = 0;
	m_idxNors = 0;
	m_idxTexCoords = 0;

	m_maxVertices = maxVertices;
	if(Gdx.graphics->isGL20Available())
		throw GdxRuntimeException("ImmediateModeRenderer10 can only be used with OpenGL ES 1.0/1.1");

	m_positions = new float[3 * maxVertices];
	m_colors = new float[4 * maxVertices];
	m_normals = new float[3 * maxVertices];
	m_texCoords = new float[2 * maxVertices];
}

void ImmediateModeRenderer10::begin(const Matrix4& projModelView, int primitiveType)
{
	::glMatrixMode(GL_PROJECTION);
	::glLoadMatrixf(projModelView.val);
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	begin(primitiveType);
}

/** Starts a new list of primitives. The primitiveType specifies which primitives to draw. Can be any of GL_TRIANGLES,
* GL_LINES and so on. A maximum of 6000 vertices can be drawn at once.
*
* @param primitiveType the primitive type. */
void ImmediateModeRenderer10::begin(int primitiveType)
{
	m_primitiveType = primitiveType;
	m_numVertices = 0;
	m_idxPos = 0;
	m_idxCols = 0;
	m_idxNors = 0;
	m_idxTexCoords = 0;
	m_hasCols = false;
	m_hasNors = false;
	m_hasTexCoords = false;
}

/** Specifies the color of the current vertex
* @param r the red component
* @param g the green component
* @param b the blue component
* @param a the alpha component */
void ImmediateModeRenderer10::color(float r, float g, float b, float a)
{
	m_colors[m_idxCols] = r;
	m_colors[m_idxCols + 1] = g;
	m_colors[m_idxCols + 2] = b;
	m_colors[m_idxCols + 3] = a;
	m_hasCols = true;
}

/** Specifies the normal of the current vertex
* @param x the x component
* @param y the y component
* @param z the z component */
void ImmediateModeRenderer10::normal(float x, float y, float z)
{
	m_normals[m_idxNors] = x;
	m_normals[m_idxNors + 1] = y;
	m_normals[m_idxNors + 2] = z;
	m_hasNors = true;
}

/** Specifies the texture coordinates of the current vertex
* @param u the u coordinate
* @param v the v coordinate */
void ImmediateModeRenderer10::texCoord(float u, float v)
{
	m_texCoords[m_idxTexCoords] = u;
	m_texCoords[m_idxTexCoords + 1] = v;
	m_hasTexCoords = true;
}

/** Specifies the position of the current vertex and finalizes it. After a call to this method you will effectively define a new
* vertex afterwards.
*
* @param x the x component
* @param y the y component
* @param z the z component */
void ImmediateModeRenderer10::vertex(float x, float y, float z)
{
	m_positions[m_idxPos++] = x;
	m_positions[m_idxPos++] = y;
	m_positions[m_idxPos++] = z;

	if(m_hasCols) m_idxCols += 4;
	if(m_hasNors) m_idxNors += 3;
	if(m_hasTexCoords) m_idxTexCoords += 2;
	m_numVertices++;
}

int ImmediateModeRenderer10::getNumVertices()
{
	return m_numVertices;
}

int ImmediateModeRenderer10::getMaxVertices()
{
	return m_maxVertices;
}

/** Renders the primitives just defined. */
void ImmediateModeRenderer10::end()
{
	if(m_idxPos == 0) 
		return;

	::glEnableClientState(GL_VERTEX_ARRAY);
	::glVertexPointer(3, GL_FLOAT, 0, m_positions);

	if(m_hasCols)
	{
		::glEnableClientState(GL_COLOR_ARRAY);
		::glColorPointer(4, GL_FLOAT, 0, m_colors);
	}

	if(m_hasNors)
	{
		::glEnableClientState(GL_NORMAL_ARRAY);
		::glNormalPointer(GL_FLOAT, 0, m_normals);
	}

	if(m_hasTexCoords)
	{
		//TODO:
		//::glClientActiveTexture(GL_TEXTURE0);
		throw GdxRuntimeException("texture not implemented");
		::glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		::glTexCoordPointer(2, GL_FLOAT, 0, m_texCoords);
	}

	::glDrawArrays(m_primitiveType, 0, m_idxPos / 3);

	if(m_hasCols) ::glDisableClientState(GL_COLOR_ARRAY);
	if(m_hasNors) ::glDisableClientState(GL_NORMAL_ARRAY);
	if(m_hasTexCoords) ::glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void ImmediateModeRenderer10::vertex(const Vector3& point)
{
	vertex(point.x, point.y, point.z);
}
