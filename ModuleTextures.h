#pragma once
#include<vector>
#include "Module.h"
#include "Globals.h"

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	bool CleanUp();

	unsigned char * Load(const char* path, int &xSize, int &ySize);

};