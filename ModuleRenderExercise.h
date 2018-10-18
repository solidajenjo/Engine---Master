#pragma once
#include "Module.h"
#include "MathGeoLib.h"

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
	math::float4x4 proj;
	math::float4x4 view;
	math::float4x4 model;
};


