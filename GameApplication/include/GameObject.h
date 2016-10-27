#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Common.h";
#include "Texture.h";
#include "Shader.h";
#include "Vertex.h";

class GameObject
{
public:
	GameObject();
	~GameObject();
	void onUpdate();
	void onRender(mat4& view, mat4& projection);
	void onInit();
	void onDestroy();
	void loadTexture(const string& filename);
	void loadShaders(const string& vsFilename, const string& fsFilename);
	void copyVertexData(Vertex* pVertex, int numberOfVertices);



private:
	GLuint m_VBO;
	GLuint m_VAO;
	GLuint m_ShaderProgram;
	GLuint m_Texture;
	GLuint m_ClampSampler;
	mat4 m_ModelMatrix;

	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;
	mat4 m_TranslationMatrix;
	mat4 m_ScaleMatrix;
	mat4 m_RotationMatrix;
	int m_NumberOfVerts;



};




#endif // !_GAMEOBJECT_H

