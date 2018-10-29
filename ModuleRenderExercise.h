#pragma once
#include "Module.h"
#include "MathGeoLib.h"

class ModuleTextures;
class ModuleProgram;

class ModuleRenderExercise : public Module
{
public:
    ModuleRenderExercise();
    ~ModuleRenderExercise();

	bool            Init    ();
	update_status   Update  ();
	bool            CleanUp ();

private:
    unsigned vbo        = 0;
	float xRot, yRot, zRot, xT, yT, zT, xS, yS, zS;

	math::float4x4 model;

	unsigned int lennaTex;
	ModuleTextures* textures;
};


