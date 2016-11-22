#ifndef _MyGame_H
#define _MyGame_H

#include "GameApplication.h"

class MyGame:public GameApplication
{
public:
	MyGame();
	~MyGame();

	void render();
	void update();
	void initScene();
	void destroyScene();

	void onKeyDown(SDL_Keycode keyCode);
private:
	//matrices
	mat4 m_ViewMatrix;
	mat4 m_ProjMatrix;

<<<<<<< HEAD
	vec3 m_CameraPosition;

	//GLuint m_Texture;
	GLuint m_ClampSampler;

	GameObject * m_TestObject;
	shared_ptr<GameObject> m_NewObject;
=======
	shared_ptr<GameObject> m_TestGO;
	shared_ptr<Light> m_Light;
	vec4 m_AmbientLightColour;

	vec3 m_CameraPosition;
>>>>>>> refs/remotes/origin/Lab6-Complete
};
#endif
