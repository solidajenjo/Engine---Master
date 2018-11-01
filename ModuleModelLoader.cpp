#include "GL/glew.h"
#include "ModuleModelLoader.h"
#include "cimport.h"
#include "postprocess.h"
#include "scene.h"
#include "material.h"
#include "mesh.h"
#include "SDL.h"


ModuleModelLoader::ModuleModelLoader()
{
}


ModuleModelLoader::~ModuleModelLoader()
{
}

unsigned int ModuleModelLoader::Load(char * geometryPath)
{
	const aiScene* scene = aiImportFile(geometryPath, 0);
	if (scene == nullptr) {
		LOG("Error importing model");
	}
	else
	{
		for (unsigned i = 0; i < scene->mNumMeshes; ++i)
		{
			GenerateMeshData(scene->mMeshes[i]);
		}
		for (unsigned i = 0; i < scene->mNumMaterials; ++i)
		{
			GenerateMaterialData(scene->mMaterials[i]);
		}
	}
	aiReleaseImport(scene);
	return 0;
}

unsigned int ModuleModelLoader::GenerateMeshData(aiMesh * mesh)
{
	GLuint vbo, vao;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mesh->mNumVertices * 5, NULL, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mesh->mNumVertices * 3, mesh->mVertices, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * mesh->mNumVertices * 3, mesh->mVertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mesh->mNumVertices * 3, sizeof(GLfloat) * mesh->mNumVertices * 3, glMapBufferRange(GL_ARRAY_BUFFER, 3, GL_FLOAT, mesh->mTextureCoords[0]);

	
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		0,                  // attribute 0
		3,                  // number of componentes (3 floats)
		GL_FLOAT,           // data type
		GL_FALSE,           // should be normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)(sizeof(float) * 3 * mesh->mNumVertices)    // 3 float 6 vertices for jump positions
	);

	glDrawArrays(GL_TRIANGLES, 0, mesh->mNumVertices);

	glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	return vbo;
}

unsigned int ModuleModelLoader::GenerateMaterialData(aiMaterial * materials)
{
	return 0;
}
