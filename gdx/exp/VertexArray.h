#pragma once
#include "vertexdata.h"
#include "VertexAttributes.h"

class VertexArray :
	public VertexData
{
private:
	VertexAttributes m_attributes;
	float* m_buffer;
	bool m_isBound;
	int m_numVertices;

public:
	VertexArray(const VertexAttributes& attributes);
	virtual ~VertexArray(void);

	/** @return the number of vertices this VertexData stores */
	virtual int getNumVertices ();

	/** @return the number of vertices this VertedData can store */
	//virtual int getNumMaxVertices ();

	/** @return the {@link VertexAttributes} as specified during construction. */
	virtual const class VertexAttributes& getAttributes ();

	/** <p>
	 * Sets the vertices of this VertexData, discarding the old vertex data. The count must equal the number of floats per vertex
	 * times the number of vertices to be copied to this VertexData. The order of the vertex attributes must be the same as
	 * specified at construction time via {@link VertexAttributes}.
	 * </p>
	 * 
	 * <p>
	 * This can be called in between calls to {@link #bind()} and {@link #unbind()}. The vertex data will be updated instantly.
	 * </p>
	 * 
	 * @param vertices the vertex data
	 * @param offset the offset to start copying the data from
	 * @param count the number of floats to copy */
	virtual void setVertices(const float* vertices, int count);

	/** <p>
	 * Returns the underlying FloatBuffer. If you modify the buffer contents they will be uploaded on the next call to
	 * {@link #bind()}. If you need immediate uploading use {@link #setVertices(float[], int, int)};
	 * </p>
	 * 
	 * @return the underlying FloatBuffer holding the vertex data. */
	virtual float* getBuffer ();

	/** Binds this VertexData for rendering via glDrawArrays or glDrawElements. */
	virtual void bind ();

	/** Unbinds this VertexData. */
	virtual void unbind ();

	/** Disposes this VertexData and all its associated OpenGL resources. */
	virtual void dispose ();
};

