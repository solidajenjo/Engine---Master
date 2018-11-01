#pragma once
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "ModuleEditor.h"
#include "ModuleCamera.h"
#include "ModuleModelLoader.h"

using namespace std;

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	modules.push_back(window = new ModuleWindow());
	modules.push_back(camera = new ModuleCamera());
	modules.push_back(editor = new ModuleEditor());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(input = new ModuleInput());
    modules.push_back(exercise = new ModuleRenderExercise());
	modules.push_back(program = new ModuleProgram("default.vs", "default.fs"));
	modules.push_back(camera = new ModuleCamera());
	modules.push_back(modelLoader = new ModuleModelLoader());

}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	float startTime = SDL_GetTicks();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	float frameTime = SDL_GetTicks() - startTime;
	float fps = 1000 / frameTime;

	if (fpsLogIterator == fpsLog.size())
		fpsLogIterator = 0;

	msLog[fpsLogIterator] = frameTime;
	fpsLog[fpsLogIterator++] = fps;
	
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}
