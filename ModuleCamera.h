#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"

class ModuleCamera :
	public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status Update();

	void recalcProjection(float hFOV, float zNear, float zFar);

	math::float3 camPos;

	math::float4x4 proj;
	math::float4x4 view;

	math::float3 f;
	math::float3 s;
	math::float3 u;
};

