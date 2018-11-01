#pragma once

#include<list>
#include<vector>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleProgram;
class ModuleEditor;
class ModuleCamera;
class ModuleModelLoader;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
    ModuleRenderExercise* exercise = nullptr;
	ModuleProgram* program = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleModelLoader* modelLoader = nullptr;

	std::vector<float> fpsLog = std::vector<float>(50);
	std::vector<float> msLog = std::vector<float>(50);
	int fpsLogIterator = 0;

	ImGuiTextBuffer consoleBuffer;
	bool imGuiStarted = false;

private:

	std::list<Module*> modules;

};

extern Application* App;
