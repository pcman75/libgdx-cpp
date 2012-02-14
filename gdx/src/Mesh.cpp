#include "StdAfx.h"
#include "Mesh.h"
#include "VertexBufferObject.h"
#include "IndexBufferObject.h"
#include "VertexArray.h"


bool Mesh::forceVBO = false;
std::list<Mesh*> Mesh::m_meshes;

Mesh::Mesh(bool isStatic,const VertexAttribute& attribute) 
{
	VertexAttributes attributes(&attribute, 1);
	if (Gdx.gl20 != NULL || Gdx.gl11 != NULL || forceVBO) 
	{
		m_vertices = new VertexBufferObject(isStatic, attributes);
		m_indices = new IndexBufferObject(isStatic);
		m_isVertexArray = false;
	} 
	else 
	{
		m_vertices = new VertexArray(attributes);
		m_indices = new IndexBufferObject(isStatic);
		m_isVertexArray = true;
	}

	addManagedMesh(this);
}

Mesh::Mesh(bool isStatic, const VertexAttributes& attributes) 
{
	if (Gdx.gl20 != NULL || Gdx.gl11 != NULL || forceVBO) 
	{
		m_vertices = new VertexBufferObject(isStatic, attributes);
		m_indices = new IndexBufferObject(isStatic);
		m_isVertexArray = false;
	} 
	else 
	{
		m_vertices = new VertexArray(attributes);
		m_indices = new IndexBufferObject(isStatic);
		m_isVertexArray = true;
	}

	addManagedMesh(this);
}

Mesh::Mesh(VertexDataType type, bool isStatic, const VertexAttributes& attributes)
{
	if (type == VertexArrayType && Gdx.graphics->isGL20Available()) 
		type = VertexBufferObjectType;

	if (type == VertexBufferObjectType) 
	{
		m_vertices = new VertexBufferObject(isStatic, attributes);
		m_indices = new IndexBufferObject(isStatic);
		m_isVertexArray = false;
	} 
	else if (type == VertexBufferObjectSubDataType) 
	{
		throw new GdxRuntimeException("TODO: not implemented Vertex Type");
		/*
		vertices = new VertexBufferObjectSubData(isStatic, maxVertices, attributes);
		indices = new IndexBufferObjectSubData(isStatic, maxIndices);
		isVertexArray = false;
		*/
	}
	else 
	{
		m_vertices = new VertexArray(attributes);
		m_indices = new IndexBufferObject(isStatic);
		m_isVertexArray = true;
	}
	addManagedMesh(this);
}

Mesh::~Mesh(void)
{
	dispose();
	if(m_vertices)
	{
		delete m_vertices;
		m_vertices = NULL;
	}
	if(m_indices)
	{
		delete m_indices;
		m_indices = NULL;
	}
}

void Mesh::init()
{
	VertexData* m_vertices = NULL;
	IndexData* m_indices  = NULL;
	m_autoBind = true;
	m_isVertexArray = true;
	m_refCount = 0;
}

/** Creates a new Mesh with the given attributes. This is an expert method with no error checking. Use at your own risk.
* 
* @param type the {@link VertexDataType} to be used, VBO or VA.
* @param isStatic whether this mesh is static or not. Allows for internal optimizations.
* @param maxVertices the maximum number of vertices this mesh can hold
* @param maxIndices the maximum number of indices this mesh can hold
* @param attributes the {@link VertexAttribute}s. Each vertex attribute defines one property of a vertex such as position,
*           normal or texture coordinate */
/*
Mesh (VertexDataType type, bool isStatic, int maxVertices, int maxIndices, VertexAttribute... attributes) {
if (type == VertexDataType.VertexArray && Gdx.graphics.isGL20Available()) type = VertexDataType.VertexBufferObject;

if (type == VertexDataType.VertexBufferObject) {
vertices = new VertexBufferObject(isStatic, maxVertices, attributes);
indices = new IndexBufferObject(isStatic, maxIndices);
isVertexArray = false;
} else if (type == VertexDataType.VertexBufferObjectSubData) {
vertices = new VertexBufferObjectSubData(isStatic, maxVertices, attributes);
indices = new IndexBufferObjectSubData(isStatic, maxIndices);
isVertexArray = false;
} else {
vertices = new VertexArray(maxVertices, attributes);
indices = new IndexBufferObject(maxIndices);
isVertexArray = true;
}
addManagedMesh(Gdx.app, this);
}
*/

void Mesh::setVertices(const float* vertices, int verticesLength) 
{
	m_vertices->setVertices(vertices, verticesLength);
}

void Mesh::setIndices (const short* indices, int count) 
{
	m_indices->setIndices(indices, count);
}

int Mesh::getNumIndices () 
{
	return m_indices->getNumIndices();
}

int Mesh::getNumVertices () 
{
	return m_vertices->getNumVertices();
}

int Mesh::getVertexSize () 
{
	return m_vertices->getAttributes().vertexSize();
}

void Mesh::setAutoBind (bool autoBind) 
{
	m_autoBind = autoBind;
}


void Mesh::bind() 
{
	if (Gdx.graphics->isGL20Available()) 
		throw new GdxRuntimeException("can't use this render method with OpenGL ES 2.0");
	m_vertices->bind();
	if (!m_isVertexArray && m_indices->getNumIndices() > 0) 
		m_indices->bind();
}

void Mesh::unbind () 
{
	if (Gdx.graphics->isGL20Available()) 
		throw new GdxRuntimeException("can't use this render method with OpenGL ES 2.0");
	m_vertices->unbind();
	if (!m_isVertexArray && m_indices->getNumIndices() > 0) 
		m_indices->unbind();
}

/** Binds the underlying {@link VertexBufferObject} and {@link IndexBufferObject} if indices where given. Use this with OpenGL
* ES 2.0 and when auto-bind is disabled.
* 
* @param shader the shader (does not bind the shader) */

void Mesh::bind(ShaderProgram* shader) 
{
	if (!Gdx.graphics->isGL20Available()) 
		throw new GdxRuntimeException("can't use this render method with OpenGL ES 1.x");

	((VertexBufferObject*)m_vertices)->bind(shader);
	if (m_indices->getNumIndices() > 0) 
		m_indices->bind();
}

/** Unbinds the underlying {@link VertexBufferObject} and {@link IndexBufferObject} is indices were given. Use this with OpenGL
* ES 1.x and when auto-bind is disabled.
* 
* @param shader the shader (does not unbind the shader) */

void Mesh::unbind(ShaderProgram* shader) 
{
	if (!Gdx.graphics->isGL20Available()) 
		throw new GdxRuntimeException("can't use this render method with OpenGL ES 1.x");

	((VertexBufferObject*)m_vertices)->unbind(shader);
	if (m_indices->getNumIndices() > 0) 
		m_indices->unbind();
}

void Mesh::render (int primitiveType) 
{
	render(primitiveType, 0, m_indices->getNumIndices() > 0 ? getNumIndices() : getNumVertices());
}

void Mesh::render (int primitiveType, int offset, int count) 
{
	if(Gdx.graphics->isGL20Available()) 
		throw new GdxRuntimeException("can't use this render method with OpenGL ES 2.0");

	if(m_autoBind) 
		bind();

	if (m_isVertexArray) 
	{
		if (m_indices->getNumIndices() > 0)
		{
			short* buffer = m_indices->getBuffer() + offset;
			Gdx.gl10->glDrawElements(primitiveType, count, GL10::GDX_GL_UNSIGNED_SHORT, buffer);
		} 
		else
			Gdx.gl10->glDrawArrays(primitiveType, offset, count);
	}
	else 
	{
		if (m_indices->getNumIndices() > 0)
		{
			Gdx.gl11->glDrawElements(primitiveType, count, GL10::GDX_GL_UNSIGNED_SHORT, (void*)(offset * sizeof(short)));
		}
		else
			Gdx.gl11->glDrawArrays(primitiveType, offset, count);
	}

	if (m_autoBind) 
		unbind();
}

/** <p>
* Renders the mesh using the given primitive type. If indices are set for this mesh then getNumIndices() / #vertices per
* primitive primitives are rendered. If no indices are set then getNumVertices() / #vertices per primitive are rendered.
* </p>
* 
* <p>
* This method will automatically bind each vertex attribute as specified at construction time via {@link VertexAttributes} to
* the respective shader attributes. The binding is based on the alias defined for each VertexAttribute.
* </p>
* 
* <p>
* This method must only be called after the {@link ShaderProgram#begin()} method has been called!
* </p>
* 
* <p>
* This method is intended for use with OpenGL ES 2.0 and will throw an IllegalStateException when OpenGL ES 1.x is used.
* </p>
* 
* @param primitiveType the primitive type */

void Mesh::render (ShaderProgram* shader, int primitiveType) 
{
	render(shader, primitiveType, 0, m_indices->getNumIndices() > 0 ? getNumIndices() : getNumVertices());
}

/** <p>
* Renders the mesh using the given primitive type. offset specifies the offset into either the vertex buffer or the index
* buffer depending on whether indices are defined. count specifies the number of vertices or indices to use thus count /
* #vertices per primitive primitives are rendered.
* </p>
* 
* <p>
* This method will automatically bind each vertex attribute as specified at construction time via {@link VertexAttributes} to
* the respective shader attributes. The binding is based on the alias defined for each VertexAttribute.
* </p>
* 
* <p>
* This method must only be called after the {@link ShaderProgram#begin()} method has been called!
* </p>
* 
* <p>
* This method is intended for use with OpenGL ES 2.0 and will throw an IllegalStateException when OpenGL ES 1.x is used.
* </p>
* 
* @param shader the shader to be used
* @param primitiveType the primitive type
* @param offset the offset into the vertex or index buffer
* @param count number of vertices or indices to use */

void Mesh::render(ShaderProgram* shader, int primitiveType, int offset, int count) 
{
	if (!Gdx.graphics->isGL20Available()) 
		throw new GdxRuntimeException("can't use this render method with OpenGL ES 1.x");

	if (m_autoBind) 
		bind(shader);

	if (m_indices->getNumIndices() > 0)
		Gdx.gl20->glDrawElements(primitiveType, count, GL10::GDX_GL_UNSIGNED_SHORT, offset * 2);
	else
		Gdx.gl20->glDrawArrays(primitiveType, offset, count);

	if (m_autoBind) 
		unbind(shader);
}


void Mesh::dispose ()
{
	//TODO: who increase the refcount???
	//m_refCount--;
	//if (!m_refCount)
	{
		//TODO: costly to remove from a list!
		m_meshes.remove(this);
		m_vertices->dispose();
		m_indices->dispose();
	}
}

bool Mesh::getVertexAttribute (int usage, VertexAttribute& attribute) 
{
	bool found = false;
	VertexAttributes attributes = m_vertices->getAttributes();
	int len = attributes.size();
	for (int i = 0; i < len; i++)
	{
		if (attributes.get(i).usage == usage) 
		{
			attribute = attributes.get(i);
			found = true;
		}
	}
	return found;
}

const VertexAttributes& Mesh::getVertexAttributes () 
{
	return m_vertices->getAttributes();
}


float* Mesh::getVerticesBuffer () 
{
	return m_vertices->getBuffer();
}

/** Calculates the {@link BoundingBox} of the vertices contained in this mesh. In case no vertices are defined yet a
* {@link GdxRuntimeException} is thrown. This method creates a new BoundingBox instance.
* 
* @return the bounding box. */
/*
BoundingBox calculateBoundingBox () 
{
BoundingBox bbox = new BoundingBox();
calculateBoundingBox(bbox);
return bbox;
}*/

/** Calculates the {@link BoundingBox} of the vertices contained in this mesh. In case no vertices are defined yet a
* {@link GdxRuntimeException} is thrown.
* 
* @param bbox the bounding box to store the result in. */
/*
void calculateBoundingBox (BoundingBox bbox) {
final int numVertices = getNumVertices();
if (numVertices == 0) throw new GdxRuntimeException("No vertices defined");

final FloatBuffer verts = vertices.getBuffer();
bbox.inf();
final VertexAttribute posAttrib = getVertexAttribute(Usage.Position);
final int offset = posAttrib.offset / 4;
final int vertexSize = vertices.getAttributes().vertexSize / 4;
int idx = offset;

switch (posAttrib.numComponents) {
case 1:
for (int i = 0; i < numVertices; i++) {
bbox.ext(verts.get(idx), 0, 0);
idx += vertexSize;
}
break;
case 2:
for (int i = 0; i < numVertices; i++) {
bbox.ext(verts.get(idx), verts.get(idx + 1), 0);
idx += vertexSize;
}
break;
case 3:
for (int i = 0; i < numVertices; i++) {
bbox.ext(verts.get(idx), verts.get(idx + 1), verts.get(idx + 2));
idx += vertexSize;
}
break;
}
}
*/

short* Mesh::getIndicesBuffer () 
{
	return m_indices->getBuffer();
}

void Mesh::addManagedMesh(Mesh* mesh) 
{
	m_meshes.push_back(mesh);
}

/** Invalidates all meshes so the next time they are rendered new VBO handles are generated.
* @param app */
void Mesh::invalidateAllMeshes() 
{
	std::list<Mesh*>::iterator current = m_meshes.begin();
	while (current != m_meshes.end())
	{
		VertexBufferObject* vbo = dynamic_cast<VertexBufferObject*>((*current)->m_vertices);
		if(vbo)
			vbo->invalidate();
		(*current)->m_indices->invalidate();
		current++;
	}
}

/** Will clear the managed mesh cache. I wouldn't use this if i was you :) */
void Mesh::clearAllMeshes() 
{
	m_meshes.clear();
}

/*
static String getManagedStatus () {
StringBuilder builder = new StringBuilder();
int i = 0;
builder.append("Managed meshes/app: { ");
for (Application app : meshes.keySet()) {
builder.append(meshes.get(app).size());
builder.append(" ");
}
builder.append("}");
return builder.toString();
}*/

/** Method to scale the positions in the mesh. Normals will be kept as is. This is a potentially slow operation, use with care.
* It will also create a temporary float[] which will be garbage collected.
* 
* @param scaleX scale on x
* @param scaleY scale on y
* @param scaleZ scale on z */
void Mesh::scale (float scaleX, float scaleY, float scaleZ) 
{
	//TODO:
	VertexAttribute posAttr(-1, 0, "");
	getVertexAttribute(VertexAttributes::Position, posAttr);
	int offset = posAttr.offset / 4;
	int numComponents = posAttr.numComponents;
	int numVertices = getNumVertices();
	int vertexSize = getVertexSize() / 4;

	float* vertices = new float[numVertices * vertexSize];
	memcpy(vertices, m_vertices->getBuffer(), sizeof(float) * numVertices * vertexSize);

	int idx = offset;
	switch (numComponents) 
	{
	case 1:
		for (int i = 0; i < numVertices; i++) 
		{
			vertices[idx] *= scaleX;
			idx += vertexSize;
		}
		break;
	case 2:
		for (int i = 0; i < numVertices; i++) 
		{
			vertices[idx] *= scaleX;
			vertices[idx + 1] *= scaleY;
			idx += vertexSize;
		}
		break;
	case 3:
		for (int i = 0; i < numVertices; i++) 
		{
			vertices[idx] *= scaleX;
			vertices[idx + 1] *= scaleY;
			vertices[idx + 2] *= scaleZ;
			idx += vertexSize;
		}
		break;
	}
	setVertices(vertices, numVertices * vertexSize);
	delete [] vertices;
}
