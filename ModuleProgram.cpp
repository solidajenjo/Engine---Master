#include "ModuleProgram.h"
#include <vector>


ModuleProgram::ModuleProgram(char * vsName, char * fsName)
{
	this->vsName = vsName;
	this->fsName = fsName;
}


ModuleProgram::~ModuleProgram()
{
}

bool ModuleProgram::Init()
{
	LOG("Shader Program Creation");
	program = glCreateProgram();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	char* vSource = readFile(vsName);
	glShaderSource(vs, 1, &vSource, 0);
	glCompileShader(vs);
	free((void*)vSource);
	GLint isCompiled = 0;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);
		GLchar* infoLog = (GLchar*) malloc(sizeof(char) * (maxLength + 1));
		glGetShaderInfoLog(vs, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(vs);
		LOG("Vertex shader compilation error: %s", infoLog);
		free(infoLog);
		return false;
	}
	

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	char* fSource = readFile(fsName);
	glShaderSource(fs, 1, &fSource, 0);
	glCompileShader(fs);
	free((void*)fSource);
	isCompiled = 0;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);
		GLchar* infoLog = (GLchar*)malloc(sizeof(char) * (maxLength + 1));
		glGetShaderInfoLog(fs, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(fs);
		LOG("Fragment shader compilation error: %s", infoLog);
		free(infoLog);
		return false;
	}

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	GLint isLinked = 0;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		GLchar* infoLog = (GLchar*)malloc(sizeof(char) * (maxLength + 1));
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(program);
		glDeleteShader(vs);
		glDeleteShader(fs);
		LOG("Program Linking error: %s", infoLog);
		free(infoLog);
		return false;
	}


	glDeleteShader(vs);
	glDeleteShader(fs);
	LOG("Shader Program Created");
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
