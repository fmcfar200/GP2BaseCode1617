#include "GameObject.h";

GameObject::GameObject()
{
	m_Position = vec3(0,0,0);
	m_Rotation = vec3(0, 0, 0);
	m_Scale = vec3(1.0f, 1.0f, 1.0f);
	m_TranslationMatrix = mat4(1.0f);
	m_ScaleMatrix = mat4(1.0f);
	m_RotationMatrix = mat4(1.0f);
	m_NumberOfVerts = 0;
}

GameObject::~GameObject()
{
}

void GameObject::onUpdate()
{
	m_RotationMatrix = eulerAngleYXZ(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	m_ScaleMatrix = scale(m_Scale);
	m_TranslationMatrix = translate(m_Position);
	m_ModelMatrix = m_RotationMatrix * m_ScaleMatrix * m_TranslationMatrix;
}

void GameObject::onRender(mat4 & view, mat4 & projection)
{
	glUseProgram(m_ShaderProgram);
	glBindVertexArray(m_VAO);

	GLint MVPLocation = glGetUniformLocation(m_ShaderProgram, "MVP");
	if (MVPLocation != -1)
	{
		mat4 MVP = projection*view*m_ModelMatrix;
		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
	}
	glBindSampler(0, m_ClampSampler);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	GLint textureLocation = glGetUniformLocation(m_ShaderProgram, "diffuseSampler");
	if (textureLocation != -1)
	{
		glUniform1i(textureLocation, 0);
	}

	glDrawArrays(GL_TRIANGLES, 0, m_NumberOfVerts);
}



void GameObject::onInit()
{
}

void GameObject::onDestroy()
{
	glDeleteSamplers(1, &m_ClampSampler);
	glDeleteTextures(1, &m_Texture);
	glDeleteProgram(m_ShaderProgram);
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void GameObject::loadTexture(const string & filename)
{
	m_Texture = loadTextureFromFile(filename);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void GameObject::loadShaders(const string & vsFilename, const string & fsFilename)
{
	GLuint vertexShaderProgram = 0;

	GLuint fragmentShaderProgram = 0;

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);
}

void GameObject::copyVertexData(Vertex * pVertex, int numberOfVertices)
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(Vertex), m_NumberOfVerts, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, position)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, textureCoords)));
}






