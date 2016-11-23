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
	//asset paths
	string modelPath = ASSET_PATH + MODEL_PATH + "/Earth.fbx";

	string lightTextureVSPath = ASSET_PATH + SHADER_PATH + "/lightTextureVS.glsl";
	string lightTextureFSPath = ASSET_PATH + SHADER_PATH + "/lightTextureFS.glsl";

	string normalMappingVSPath = ASSET_PATH + SHADER_PATH + "normalMappingVS.glsl";
	string normalMappingFSPath = ASSET_PATH + SHADER_PATH + "normalMappingFS.glsl";

	string paralaxMappingVSPath = ASSET_PATH + SHADER_PATH + "paralaxMappingVS.glsl";
	string paralaxMappingFSPath = ASSET_PATH + SHADER_PATH + "paralaxMappingFS.glsl";

	//earth textures
	string earthDiffTexPath = ASSET_PATH + TEXTURE_PATH + "/earth_diff.png";
	string earthSpecTexPath = ASSET_PATH + TEXTURE_PATH + "/earth_spec.png";
	string earthBumpTexPath = ASSET_PATH + TEXTURE_PATH + "/earth_norm.png";
	string earthHeightTexPath = ASSET_PATH + TEXTURE_PATH + "/earth_height.png";

	string brickDiffTexPath = ASSET_PATH + TEXTURE_PATH + "/bricks_diff.png";
	string brickSpecTexPath = ASSET_PATH + TEXTURE_PATH + "/bricks_spec.png";
	string brickBumpTexPath = ASSET_PATH + TEXTURE_PATH + "/bricks_norm.png";
	string brickHeightTexPath = ASSET_PATH + TEXTURE_PATH + "/bricks_height.png";

	//brickTextures

	//loads model and shaders
	m_TestGO=shared_ptr<GameObject>(loadModelFromFile(modelPath));
	m_TestGO->loadShaders(lightTextureVSPath, lightTextureFSPath);
	m_TestGO->loadDiffuseTexture(earthDiffTexPath);
	m_TestGO->loadSpecularTexture(earthSpecTexPath);
	m_TestGO->loadNormalTexture(earthBumpTexPath);
	m_TestGO->loadHeightMapTexture(earthHeightTexPath);

	m_TestGO->setScale(vec3(1.5f, 1.5f, 1.5f));
	m_CameraPosition = vec3(0.0f, 0.0f, 50.0f);

	//lighting
	m_Light = shared_ptr<Light>(new Light());
	m_Light->DiffuseColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->Direction = vec3(0.0f, 0.0f, -1.0f);
	m_AmbientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	
}

void MyGame::onKeyDown(SDL_Keycode keyCode)
{
	//input for rotation
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

	//input for zooming
	if (keyCode == SDLK_DOWN)
	{
		m_CameraPosition = vec3(m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z + 0.25f);
	}
	else if (keyCode == SDLK_UP)
	{
		m_CameraPosition = vec3(m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z - 0.25f);

	}
}

void MyGame::destroyScene()
{
	m_TestGO->onDestroy();
}

void MyGame::update()
{
	GameApplication::update();

	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 1000.0f);
	m_ViewMatrix = lookAt(m_CameraPosition, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	m_TestGO->onUpdate();
}

void MyGame::render()
{
	GameApplication::render();
	GLuint currentShader = m_TestGO->getShaderProgram();
	
	GLint ambientLightColourLocation = glGetUniformLocation(currentShader, "directionLight.ambientColour");
	glUniform4fv(ambientLightColourLocation, 1, value_ptr(m_AmbientLightColour));

	GLint diffuseLightColourLocation = glGetUniformLocation(currentShader, "directionLight.diffuseColour");
	glUniform4fv(diffuseLightColourLocation, 1, value_ptr(m_Light->DiffuseColour));

	GLint specularLightColourLocation = glGetUniformLocation(currentShader, "directionLight.specularColour");
	glUniform4fv(specularLightColourLocation, 1, value_ptr(m_Light->SpecularColour));

	GLint lightDirectionLocation = glGetUniformLocation(currentShader, "directionLight.direction");
	glUniform3fv(lightDirectionLocation, 1, value_ptr(m_Light->Direction));

	GLint cameraPositionLocation = glGetUniformLocation(currentShader, "cameraPos");
	glUniform3fv(cameraPositionLocation, 1, value_ptr(m_CameraPosition));
	
	m_TestGO->onRender(m_ViewMatrix, m_ProjMatrix);
}
