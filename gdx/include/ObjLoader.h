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

#include "Mesh.h"

/** Loads Wavefront OBJ files, ignores material files. */
class ObjLoader 
{
public:
	/** Loads a Wavefront OBJ file from the given input stream.
	 * 
	 * @param in the InputStream */
	static Mesh* loadObj (const FileHandle& in);

	/** Loads a Wavefront OBJ file from the given input stream.
	 * 
	 * @param in the InputStream
	 * @param flipV whether to flip the v texture coordinate or not */
	static Mesh* loadObj (const FileHandle& in, bool flipV);

	/** Loads a mesh from the given string in Wavefront OBJ format
	 * 
	 * @param obj The string
	 * @return The Mesh */
	static Mesh* loadObjFromString(const std::string& obj);

	/** Loads a mesh from the given string in Wavefront OBJ format
	 * 
	 * @param obj The string
	 * @param flipV whether to flip the v texture coordinate or not
	 * @return The Mesh */
	static Mesh* loadObjFromString (const std::string& obj, bool flipV);

private:
	static int getIndex(const std::string& index, int size);
};
