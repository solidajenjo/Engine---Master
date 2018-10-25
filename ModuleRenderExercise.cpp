#include "Application.h"

#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
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
	math::float4x4 identity = float4x4::identity;
	glUniformMatrix4fv(glGetUniformLocation(App->program->program,
		"model"), 1, GL_TRUE, &identity[0][0]);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&(GLfloat)App->camera->view[0][0]);
	glLineWidth(0.5f);

	glBegin(GL_LINES);

	float d = 200.0f;

	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();
	
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
		"view"), 1, GL_TRUE, &App->camera->view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(App->program->program,
		"proj"), 1, GL_TRUE, &App->camera->proj[0][0]);

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

