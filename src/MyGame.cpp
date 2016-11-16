#include "MyGame.h"

const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string MODEL_PATH = "/models";

MyGame::MyGame()
{
	
}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{
<<<<<<< HEAD
	/*
	Vertex verts[] = {
		{vec3(-0.5f, -0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(0.0f,3.0f)},
		{vec3(0.5f, -0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(3.0f,3.0f)},
		{vec3(-0.5f,  0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(0.0f,0.0f)},
		{vec3(0.5f, 0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(3.0f,0.0f)},
	};

	int indices[] =
	{
		0,2,1,
		2,3,1
	};

	m_TestObject = new GameObject();
	*/
	string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	string fsPath = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";
	//m_TestObject->loadShaders(vsPath, fsPath);

	//lets load texture
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	//m_TestObject->loadTexture(texturePath);

	//m_TestObject->copyVertexData(verts, 4, indices ,6 );

	string mPath = ASSET_PATH + MODEL_PATH + "/utah-teapot.fbx";
	m_NewObject = shared_ptr<GameObject>(loadModelFromFile(mPath));
	m_NewObject->loadShaders(vsPath, fsPath);

	m_CameraPosition = vec3(0.0f, 0.0f, 100.0f);
	

	

=======
	string modelPath = ASSET_PATH + MODEL_PATH + "/utah-teapot.fbx";
	string vsFilename = ASSET_PATH + SHADER_PATH + "/lightVS.glsl";
	string fsFilename = ASSET_PATH + SHADER_PATH + "/lightFS.glsl";
	m_TestGO=shared_ptr<GameObject>(loadModelFromFile(modelPath));
	m_TestGO->loadShaders(vsFilename, fsFilename);

	m_TestGO->setScale(vec3(0.5f, 0.5f, 0.5f));

	m_CameraPosition = vec3(0.0f, 0.0f, 100.0f);

	/*
	m_Light = shared_ptr<Light>(new Light());
	m_Light->DiffuseColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->Direction = vec3(0.0f, 0.0f, -1.0f);
	m_AmbientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	*/
}

void MyGame::onKeyDown(SDL_Keycode keyCode)
{
	if (keyCode == SDLK_a)
	{
		m_TestGO->rotate(vec3(0.0f, -0.1f, 0.0f));
	}else if (keyCode == SDLK_d)
	{
		m_TestGO->rotate(vec3(0.0f, 0.1f, 0.0f));
	}
	if (keyCode==SDLK_w)
	{
		m_TestGO->rotate(vec3(-0.1f,0.0f,0.0f));
	}
	else if (keyCode==SDLK_s)
	{
		m_TestGO->rotate(vec3(0.1f,0.0f,0.0f));
	}
>>>>>>> refs/remotes/origin/Lab6-Complete
}

void MyGame::destroyScene()
{
<<<<<<< HEAD
	


		m_NewObject->onDestroy();

=======
	m_TestGO->onDestroy();
>>>>>>> refs/remotes/origin/Lab6-Complete
}

void MyGame::update()
{
	GameApplication::update();

<<<<<<< HEAD
	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 100.0f);
	m_ViewMatrix = lookAt(m_CameraPosition, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	//m_ModelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, -0.2f));
	m_NewObject->onUpdate();
=======
	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 1000.0f);
	m_ViewMatrix = lookAt(m_CameraPosition, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	m_TestGO->onUpdate();
>>>>>>> refs/remotes/origin/Lab6-Complete
}

void MyGame::render()
{
	GameApplication::render();
<<<<<<< HEAD
	m_NewObject->onRender(m_ViewMatrix, m_ProjMatrix);
=======
	GLuint currentShader = m_TestGO->getShaderProgram();
	/*
	GLint ambientLightColourLocation = glGetUniformLocation(currentShader, "ambientLightColour");
	glUniform4fv(ambientLightColourLocation, 1, value_ptr(m_AmbientLightColour));

	GLint diffuseLightColourLocation = glGetUniformLocation(currentShader, "diffuseLightColour");
	glUniform4fv(diffuseLightColourLocation, 1, value_ptr(m_Light->DiffuseColour));

	GLint specularLightColourLocation = glGetUniformLocation(currentShader, "specularLightColour");
	glUniform4fv(specularLightColourLocation, 1, value_ptr(m_Light->SpecularColour));

	GLint lightDirectionLocation = glGetUniformLocation(currentShader, "lightDirection");
	glUniform3fv(lightDirectionLocation, 1, value_ptr(m_Light->Direction));

	GLint cameraPositionLocation = glGetUniformLocation(currentShader, "cameraPos");
	glUniform3fv(cameraPositionLocation, 1, value_ptr(m_CameraPosition));
	*/
	m_TestGO->onRender(m_ViewMatrix, m_ProjMatrix);
>>>>>>> refs/remotes/origin/Lab6-Complete
}
