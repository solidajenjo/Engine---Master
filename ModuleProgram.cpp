#include "ModuleProgram.h"
#include <vector>


ModuleProgram::ModuleProgram()
{
}


ModuleProgram::~ModuleProgram()
{
}

bool ModuleProgram::Init()
{
	LOG("Program Creation");
	program = glCreateProgram();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	char* vSource = readFile("default.vs");
	glShaderSource(vs, 1, &vSource, 0);
	glCompileShader(vs);
	free((void*)vSource);
	GLint isCompiled = 0;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vs, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(vs);
		LOG("Vertex shader compilation error: %s", infoLog);
		return false;
	}
	

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	char* fSource = readFile("default.fs");
	glShaderSource(fs, 1, &fSource, 0);
	glCompileShader(fs);
	free((void*)fSource);
	isCompiled = 0;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fs, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(fs);
		LOG("Fragment shader compilation error: %s", infoLog);
		return false;
	}

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	GLint isLinked = 0;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &isLinked);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(program);
		glDeleteShader(vs);
		glDeleteShader(fs);
		LOG("Program Linking error: %s", infoLog);
		return false;
	}


	glDeleteShader(vs);
	glDeleteShader(fs);
	LOG("Program Created");
	return true;
}

void ModuleProgram::useProgram()
{
	glUseProgram(program);
	
}

bool ModuleProgram::CleanUp()
{
	glDeleteProgram(program);
	return true;
}

char * ModuleProgram::readFile(char * name)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, name, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		rewind(file);
		data = (char*)malloc(size + 1);
		fread(data, 1, size, file);
		data[size] = 0;
		fclose(file);
	}
	return data;
}
