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


/** A single vertex attribute defined by its {@link Usage}, its number of components and its shader alias. The Usage is needed for
* the fixed function pipeline of OpenGL ES 1.x. Generic attributes are not supported in the fixed function pipeline. The number
* of components defines how many components the attribute has. The alias defines to which shader attribute this attribute should
* bind. The alias is used by a {@link Mesh} when drawing with a {@link ShaderProgram}. The alias can be changed at any time.
*/
class VertexAttribute
{
	friend class VertexAttributes;

	/** the attribute {@link Usage} **/
public:
	// don't change this!
	int usage;
	/** the number of components this attribute has. don't change this! **/
	int numComponents;
	/** the offset of this attribute in bytes. don't change this!**/
	int offset;
	/** the alias for the attribute used in a {@link ShaderProgram} **/
	std::string alias;

	/** Constructs a new VertexAttribute.
	* 
	* @param usage the usage, used for the fixed function pipeline. Generic attributes are not supported in the fixed function
	*           pipeline.
	* @param numComponents the number of components of this attribute, must be between 1 and 4.
	* @param alias the alias used in a shader for this attribute. Can be changed after construction. */
	VertexAttribute (int usage, int numComponents, std::string alias);
	VertexAttribute();
	virtual ~VertexAttribute();
};
