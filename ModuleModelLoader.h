#pragma once
#include "Module.h"
#include <vector>

struct aiMesh;
struct aiMaterial;

class ModuleModelLoader :
	public Module
{
public:
	ModuleModelLoader();
	~ModuleModelLoader();

	unsigned int Load(char * geometryPath);
	unsigned int GenerateMeshData(aiMesh* meshes);
	unsigned int GenerateMaterialData(aiMaterial* materials);
	std::vector<unsigned int> meshes;
};

