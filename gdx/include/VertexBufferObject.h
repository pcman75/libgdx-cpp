#pragma once
#include "vertexdata.h"
#include "VertexAttributes.h"
#include "ShaderProgram.h"
#include "GdxDefines.h"

class GdxDllImportExport VertexBufferObject
	:	public VertexData
{
private:
	//final static IntBuffer tmpHandle = BufferUtils.newIntBuffer(1);

	VertexAttributes m_attributes;
	int m_numVertices;
	float* m_buffer;
	unsigned int m_bufferHandle;
	bool m_isStatic;
	int m_usage;
	bool m_isDirty;
	bool m_isBound;

public:
	VertexBufferObject(bool isStatic, const VertexAttributes& attributes);
	VertexBufferObject(bool isStatic, const VertexAttribute attributes[], int attributesLength);
	virtual ~VertexBufferObject();

	virtual int getNumVertices();

	/** @return the number of vertices this VertedData can store */
	//virtual int getNumMaxVertices ();

	/** @return the {@link VertexAttributes} as specified during construction. */
	virtual const class VertexAttributes& getAttributes();

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
	virtual float* getBuffer();

	/** Binds this VertexData for rendering via glDrawArrays or glDrawElements. */
	virtual void bind();
	void bind(ShaderProgram* shader);

	/** Unbinds this VertexData. */
	virtual void unbind();
	void unbind(ShaderProgram* shader);

	/** Disposes this VertexData and all its associated OpenGL resources. */
	virtual void dispose();

	/** Invalidates the VertexBufferObject so a new OpenGL buffer handle is created. Use this in case of a context loss. */
	void invalidate();

private:
	void createBufferObject();
	
};

