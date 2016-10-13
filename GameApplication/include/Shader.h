#ifndef Shader_h
#define Shader_h

#include "Common.h"

enum SHADER_TYPE
{
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

GLuint loadShaderFromFile(std::string& filename, SHADER_TYPE shaderType);
GLuint loadShaderFromMemory(const char * pMem, SHADER_TYPE shaderType);

bool checkForLinkErrors(GLuint program);
bool checkForCompilerErrors(GLuint shaderProgram);

const char * GLTypeToString(GLenum type);
void logShaderInfo(GLuint program);
void logAttributeInfo(GLuint program);
void logUniformInfo(GLuint program);

#endif