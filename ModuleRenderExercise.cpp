#include "Application.h"

#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"

#include "GL/glew.h"
#include "SDL.h"


ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
	//Model
	xRot = 0;
	yRot = 0;
	zRot = 0;
	xT = 0;
	yT = 0;
	zT = -10;
	xS = 1;
	yS = 1;
	zS = 1;

	//View
	float3 target(0, 0, 0);
	float3 eye(0, 0, 5);
	float3 up(0, 1, 0);
	math::float3 f(target - eye); f.Normalize();
	math::float3 s(f.Cross(up)); s.Normalize();
	math::float3 u(s.Cross(f));
	
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

	float4 v1(-1.0f, -1.0f, 0.0f, 1.0f);
	float4 v2(1.0f, -1.0f, 0.0f, 1.0f);
	float4 v3(0.0f, 1.0f, 0.0f, 1.0f);

    float vertex_buffer_data[] = {
        v1[0], v1[1], v1[2],
		v2[0], v2[1], v2[2],
		v3[0], v3[1], v3[2],
	};

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

update_status ModuleRenderExercise::Update()
{
	xRot += 0.01f;
	yRot += 0.01f;
	zRot += 0.01f;

	math::float4x4 tMat = float4x4::identity;
	tMat[0][3] = xT; tMat[1][3] = yT; tMat[2][3] = zT;

	math::float4x4 rMat = math::Quat::FromEulerXYZ(xRot, yRot, zRot).ToFloat4x4();

	math::float4x4 sMat = float4x4::identity;
	sMat[0][0] *= xS; sMat[1][1] *= yS; sMat[2][2] *= zS;

	model = sMat * tMat * rMat;

	glUniformMatrix4fv(glGetUniformLocation(App->program->program,
		"model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program,
		"view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program,
		"proj"), 1, GL_TRUE, &proj[0][0]);

	glUseProgram(App->program->program);// ->useProgram();
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
            0,                  // attribute 0
            3,                  // number of componentes (3 floats)
            GL_FLOAT,           // data type
            GL_FALSE,           // should be normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );

    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
    if(vbo != 0)
    {
        glDeleteBuffers(1, &vbo);
    }

	return true;
}

