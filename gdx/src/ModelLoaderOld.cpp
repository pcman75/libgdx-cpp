#include "stdafx.h"
#include "ModelLoaderOld.h"
#include "ObjLoader.h"

Mesh* ModelLoaderOld::loadObj(const FileHandle& in) 
{
	return ObjLoader::loadObj(in);
}

