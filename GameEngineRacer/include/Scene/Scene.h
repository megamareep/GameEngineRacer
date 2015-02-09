#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include "GameObjects\GameObject.h"

#include "Camera.h"
#include "ResourceManager.h"
#include "json\json.h"


class Scene
{
private:
	struct SceneJsonData
{
	std::string name;
	std::string sceneShader;
	std::string currentCamera;
	std::string currentLight;
	bool messageHandlers;
	bool menu;
	Json::Value root;
};
	SceneJsonData sceneData;
	std::string filename;
	struct Light
	{
		glm::vec3 position;
		glm::vec3 diffuse;
		glm::vec3 ambient;
		float constant;
		float linear;
		float quadratic;
	};
protected:
	std::vector<Light> lights;
	ResourceManager* rManager;
	int activeCamera;
	std::vector<Camera*> cameras;
	std::vector<GameObject*> gameObjects;
	glm::mat4 model;
	GLuint vertShader, fragShader,programHandle;
public:
	Scene();
	~Scene();
	virtual bool LoadScene(std::string filename); //Loads gameobjects and shaders.
	virtual void InitScene(std::string loadSceneName); //Loads gameobjects and shaders.
	virtual void Update(bool keys[]);//Updates the current scene
	virtual void Render();
	void resize(int w,int h);
	void nextCamera();
	void setLightParams();
	void setUpMatricies();
	void deleteShader();
	void setLights();
	const SceneJsonData& getSceneJsonData(){return sceneData;};
	const std::string& getFileName(){return filename;};
	std::vector<GameObject*> GetGameObjects(){return gameObjects;};
	Camera* GetCamera(){return cameras[activeCamera];};//returns the current camera.
};

#endif // SCENE_H