#include "stdafx.h"
#include "ObjLoader.h"
#include "StringTokenizer.h"
#include "StringUtils.h"

using namespace std;

/** Loads a Wavefront OBJ file from the given input stream.
* 
* @param in the InputStream */
Mesh* ObjLoader::loadObj (const FileHandle& in) 
{
	return loadObj(in, false);
}

/** Loads a Wavefront OBJ file from the given input stream.
* 
* @param in the InputStream
* @param flipV whether to flip the v texture coordinate or not */
Mesh* ObjLoader::loadObj(const FileHandle& in, bool flipV) 
{
	std::string objFile;
	in.readString(objFile);
	return loadObjFromString(objFile.c_str(), flipV);
}

/** Loads a mesh from the given string in Wavefront OBJ format
* 
* @param obj The string
* @return The Mesh */
Mesh* ObjLoader::loadObjFromString(const std::string& obj) 
{
	return loadObjFromString(obj, false);
}

/** Loads a mesh from the given string in Wavefront OBJ format
* 
* @param obj The string
* @param flipV whether to flip the v texture coordinate or not
* @return The Mesh */
Mesh* ObjLoader::loadObjFromString (const std::string& obj, bool flipV) 
{
	typedef std::vector<std::string> Strings;
	Strings lines;
	
	StringTokenizer::split(obj, "\n", lines);
	
	float* vertices = new float[lines.size() * 3];
	float* normals = new float[lines.size() * 3];
	float* uv = new float[lines.size() * 3];

	int numVertices = 0;
	int numNormals = 0;
	int numUV = 0;
	int numFaces = 0;

	int* facesVerts = new int[lines.size() * 3];
	memset(facesVerts, 0, lines.size() * 3 * sizeof(int));
	int* facesNormals = new int[lines.size() * 3];
	memset(facesNormals, 0, lines.size() * 3 * sizeof(int));
	int* facesUV = new int[lines.size() * 3];
	memset(facesUV, 0, lines.size() * 3 * sizeof(int));
	int vertexIndex = 0;
	int normalIndex = 0;
	int uvIndex = 0;
	int faceIndex = 0;

	for(Strings::iterator line = lines.begin(); line != lines.end();line++)
	{
		if (StringUtils::startsWith(*line, "v ")) 
		{
			Strings tokens;
			StringTokenizer::split(*line, tokens);
			vertices[vertexIndex] = (float)atof(tokens[1].c_str());
			vertices[vertexIndex + 1] = (float)atof(tokens[2].c_str());
			vertices[vertexIndex + 2] = (float)atof(tokens[3].c_str());
			vertexIndex += 3;
			numVertices++;
			continue;
		}
		if (StringUtils::startsWith(*line, "vn ")) 
		{
			Strings tokens;
			StringTokenizer::split(*line, tokens);
			normals[normalIndex] = (float)atof(tokens[1].c_str());
			normals[normalIndex + 1] = (float)atof(tokens[2].c_str());
			normals[normalIndex + 2] = (float)atof(tokens[3].c_str());
			normalIndex += 3;
			numNormals++;
			continue;
		}

		if (StringUtils::startsWith(*line, "vt")) 
		{
			Strings tokens;
			StringTokenizer::split(*line, tokens);
			uv[uvIndex] = (float)atof(tokens[1].c_str());
			uv[uvIndex + 1] = flipV ? 1 - (float)atof(tokens[2].c_str()): (float)atof(tokens[2].c_str());
			uvIndex += 2;
			numUV++;
			continue;
		}
		if (StringUtils::startsWith(*line, "f ")) 
		{
			Strings tokens;
			StringTokenizer::split(*line, tokens);
			
			Strings parts;
			StringTokenizer::split(tokens[1], "/", parts);
			
			facesVerts[faceIndex] = getIndex(parts[0], numVertices);
			if (parts.size() > 2) 
				facesNormals[faceIndex] = getIndex(parts[2], numNormals);
			if (parts.size() > 1) 
				facesUV[faceIndex] = getIndex(parts[1], numUV);
			faceIndex++;

			StringTokenizer::split(tokens[2], "/", parts);
			facesVerts[faceIndex] = getIndex(parts[0], numVertices);
			if (parts.size() > 2) 
				facesNormals[faceIndex] = getIndex(parts[2], numNormals);
			if (parts.size() > 1) 
				facesUV[faceIndex] = getIndex(parts[1], numUV);
			faceIndex++;

			StringTokenizer::split(tokens[3], "/", parts);
			facesVerts[faceIndex] = getIndex(parts[0], numVertices);
			if (parts.size() > 2) 
				facesNormals[faceIndex] = getIndex(parts[2], numNormals);
			if (parts.size() > 1) 
				facesUV[faceIndex] = getIndex(parts[1], numUV);
			faceIndex++;
			numFaces++;
			continue;
		}
	}

	int vertsLen = (numFaces * 3) * (3 + (numNormals > 0 ? 3 : 0) + (numUV > 0 ? 2 : 0));
	float* verts = new float[vertsLen];

	for (int i = 0, vi = 0; i < numFaces * 3; i++) 
	{
		int vertexIdx = facesVerts[i] * 3;
		verts[vi++] = vertices[vertexIdx];
		verts[vi++] = vertices[vertexIdx + 1];
		verts[vi++] = vertices[vertexIdx + 2];

		if (numNormals > 0)
		{
			int normalIdx = facesNormals[i] * 3;
			verts[vi++] = normals[normalIdx];
			verts[vi++] = normals[normalIdx + 1];
			verts[vi++] = normals[normalIdx + 2];
		}
		if (numUV > 0) 
		{
			int uvIdx = facesUV[i] * 2;
			verts[vi++] = uv[uvIdx];
			verts[vi++] = uv[uvIdx + 1];
		}
	}

	Mesh* mesh = NULL;

	std::vector<VertexAttribute> attributes;
	attributes.push_back(VertexAttribute(VertexAttributes::Position, 3, ShaderProgram::POSITION_ATTRIBUTE));
	if (numNormals > 0) 
		attributes.push_back(VertexAttribute(VertexAttributes::Normal, 3, ShaderProgram::NORMAL_ATTRIBUTE));
	if (numUV > 0) 
	{
		std::string texName = std::string(ShaderProgram::TEXCOORD_ATTRIBUTE) + "0";
		attributes.push_back(VertexAttribute(VertexAttributes::TextureCoordinates, 2, texName.c_str()));
	}

	mesh = new Mesh(true, attributes.data(), attributes.size());
	mesh->setVertices(verts, vertsLen);

	//cleanup
	delete[] vertices;
	delete[] normals;
	delete[] uv;

	delete[] facesVerts;
	delete[] facesNormals;
	delete[] facesUV;

	return mesh;
}


int ObjLoader::getIndex(const std::string& index, int size) 
{
	if (index.length() == 0) 
		return 0;
	int idx = atoi(index.c_str());
	if (idx < 0)
		return size + idx;
	else
		return idx - 1;
}

