#ifndef __MODULE_EDITOR_H
#define __MODULE_EDITOR_H

#include<list>
#include "Module.h"
#include "Globals.h"

class SubModuleEditor;

class ModuleEditor :
	public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init();

	update_status PreUpdate();

	update_status Update();

	update_status PostUpdate();

	bool CleanUp();

public:

	std::list<SubModuleEditor*> subModules;
};

#endif