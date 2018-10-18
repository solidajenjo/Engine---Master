#pragma once
#include "Module.h"
#include "GL/glew.h"

class ModuleProgram :
	public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	bool Init();
	void useProgram();
	bool CleanUp();
	
	GLuint program;
private:

	char* readFile(char* name);
	
};

