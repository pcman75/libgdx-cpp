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
#include "indexdata.h"
#include "GL11.h"
#include "Gdx.h"

#include "GdxRuntimeException.h"

/** <p>
* In IndexBufferObject wraps OpenGL's index buffer functionality to be used in conjunction with VBOs. This class can be
* seamlessly used with OpenGL ES 1.x and 2.0.
* </p>
* 
* <p>
* Uses indirect Buffers on Android 1.5/1.6 to fix GC invocation due to leaking PlatformAddress instances.
* </p>
* 
* <p>
* You can also use this to store indices for vertex arrays. Do not call {@link #bind()} or {@link #unbind()} in this case but
* rather use {@link #getBuffer()} to use the m_buffer directly with glDrawElements. You must also create the IndexBufferObject with
* the second constructor and specify isDirect as true as glDrawElements in conjunction with vertex arrays needs direct buffers.
* </p>
* 
* <p>
* VertexBufferObjects must be disposed via the {@link #dispose()} method when no longer needed
* </p>
*/

class GdxDllImportExport IndexBufferObject : public IndexData 
{
private:
	short* m_buffer;
	int m_numIndices;
	unsigned int m_bufferHandle;
	bool m_isDirect;
	bool m_isDirty;
	bool m_isBound;
	int m_usage;

public:
	/** Creates a new IndexBufferObject.
	* 
	* @param isStatic whether the index m_buffer is static
	* @param maxIndices the maximum number of indices this m_buffer can hold */
	IndexBufferObject(bool isStatic, int numIndices); 

	/** Creates a new IndexBufferObject to be used with vertex arrays.
	* 
	* @param maxIndices the maximum number of indices this m_buffer can hold */
	IndexBufferObject (int numIndices);

	virtual ~IndexBufferObject(void);

	/** @return the number of indices currently stored in this m_buffer */
	int getNumIndices ();

	/** @return the maximum number of indices this IndexBufferObject can store. 
	public int getNumMaxIndices () {
	return m_buffer.capacity();
	}
	*/

	/** <p>
	* Sets the indices of this IndexBufferObject, discarding the old indices. The count must equal the number of indices to be
	* copied to this IndexBufferObject.
	* </p>
	* 
	* <p>
	* This can be called in between calls to {@link #bind()} and {@link #unbind()}. The index data will be updated instantly.
	* </p>
	* 
	* @param indices the vertex data
	* @param offset the offset to start copying the data from
	* @param count the number of shorts to copy */
	void setIndices (const short* indices, int offset, int count);

	/** <p>
	* Returns the underlying ShortBuffer. If you modify the m_buffer contents they wil be uploaded on the call to {@link #bind()}.
	* If you need immediate uploading use {@link #setIndices(short[], int, int)}.
	* </p>
	* 
	* @return the underlying short buffer. */
	short* getBuffer ();

	/** Binds this IndexBufferObject for rendering with glDrawElements. */
	void bind ();

	/** Unbinds this IndexBufferObject. */
	void unbind ();

	/** Invalidates the IndexBufferObject so a new OpenGL m_buffer handle is created. Use this in case of a context loss. */
	void invalidate ();

	/** Disposes this IndexBufferObject and all its associated OpenGL resources. */
	void dispose ();

private:
	IndexBufferObject(IndexBufferObject const&);
    void operator=(IndexBufferObject const&);
	void init(int numIndices);
	int createBufferObject ();
};
