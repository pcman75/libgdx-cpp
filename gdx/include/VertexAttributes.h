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


#include "VertexAttribute.h"
#include "GdxRuntimeException.h"

/** Instances of this class specify the vertex attributes of a mesh. VertexAttributes are used by {@link Mesh} instances to define
 * its vertex structure. Vertex attributes have an order. The order is specified by the order they are added to this class.
 */
class VertexAttributes
{
public:

	//TODO: move this to VertexAttribute class
	/** The usage of a vertex attribute.*/
	enum Usage 
	{
		Position = 0,
		Color = 1,
		ColorPacked = 5,
		Normal = 2,
		TextureCoordinates = 3,
		Generic = 4
	};

	/** Constructor, sets the vertex attributes in a specific order */
	VertexAttributes(const VertexAttribute* attributes, int attributesLength);

	void checkValidity ();

	/** @return the number of attributes */
	int size();

	/** @param index the index
	 * @return the VertexAttribute at the given index */
	const VertexAttribute& get(int index);

	std::string toString ();
	int vertexSize() const;

private:
	int calculateOffsets ();

private:
	/** the attributes in the order they were specified **/
	VertexAttribute* m_attributes;
	int m_attributesLength;

	/** the size of a single vertex in bytes **/
	int m_vertexSize;
};
