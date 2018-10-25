#include "ModuleCamera.h"
#include "GL/glew.h"
#include "SDL.h"
#include "MathGeoLib.h"


ModuleCamera::ModuleCamera()
{
}


ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	//View
	float3 target(0, 0, 0);
	float3 eye(0, 0, 5);
	float3 up(0, 1, 0);
	f = math::float3(target - eye); f.Normalize();
	s = math::float3(f.Cross(up)); s.Normalize();
	u = math::float3(s.Cross(f));

	view[0][0] = s.x; view[0][1] = s.y; view[0][2] = s.z;
	view[1][0] = u.x; view[1][1] = u.y; view[1][2] = u.z;
	view[2][0] = -f.x; view[2][1] = -f.y; view[2][2] = -f.z;
	view[0][3] = -s.Dot(eye); view[1][3] = -u.Dot(eye); view[2][3] = f.Dot(eye);
	view[3][0] = 0; view[3][1] = 0; view[3][2] = 0; view[3][3] = 1;

	//Perspective
	float aspect = SCREEN_WIDTH / SCREEN_HEIGHT;

	Frustum frustum;
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) *aspect);
	proj = frustum.ProjectionMatrix();

	camPos.x = 0;
	camPos.y = 0;
	camPos.z = 5;

	return true;
}

update_status ModuleCamera::Update()
{
	float3 target(camPos.x, camPos.y, camPos.z);
	float3 eye(camPos.x, camPos.y, camPos.z + 5);
	float3 up(0, 1, 0);
	math::float3 f(target - eye); f.Normalize();
	math::float3 s(f.Cross(up)); s.Normalize();
	math::float3 u(s.Cross(f));

	view[0][0] = s.x; view[0][1] = s.y; view[0][2] = s.z;
	view[1][0] = u.x; view[1][1] = u.y; view[1][2] = u.z;
	view[2][0] = -f.x; view[2][1] = -f.y; view[2][2] = -f.z;
	view[0][3] = -s.Dot(eye); view[1][3] = -u.Dot(eye); view[2][3] = f.Dot(eye);
	view[3][0] = 0; view[3][1] = 0; view[3][2] = 0; view[3][3] = 1;
	return UPDATE_CONTINUE;
}

void ModuleCamera::recalcProjection(float hFOV, float zNear, float zFar)
{

}
