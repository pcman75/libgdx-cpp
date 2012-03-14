#include "stdafx.h"
#include "ModelLoaderOld.h"
#include "ObjLoader.h"

Mesh* ModelLoaderOld::loadObj(FileHandleStream* in) 
{
	return ObjLoader::loadObj(in);
}

