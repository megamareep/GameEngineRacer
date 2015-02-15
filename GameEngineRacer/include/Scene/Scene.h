#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include "GameObjects\GameObject.h"

#include "Camera.h"
#include "ResourceManager.h"
#include "json\json.h"
#include <unordered_map>

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
};
	SceneJsonData sceneData;
	std::string filename;
	struct Light
	{
		std::string name;
		glm::vec3 position;
		glm::vec3 diffuse;
		glm::vec3 ambient;
		glm::vec3 specular;
		float constant;
		float linear;
		float quadratic;
	};

	void setLightParams();
	void setUpMatricies();
	std::vector<Light> lights;
	ResourceManager* rManager;
	std::string activeCamera;
	std::unordered_map<std::string, Camera*> cameras;
	std::vector<GameObject*> gameObjects;
	glm::mat4 model;
	GLuint vertShader, fragShader,programHandle;


	
public:
	Scene();
	~Scene();
	bool LoadScene(std::string filename); //Loads gameobjects and shaders.
	void InitScene(std::string loadSceneName); //Loads gameobjects and shaders.
	void Update(bool keys[]);//Updates the current scene
	void Render();
	void resize(int w,int h);
	void nextCamera();

	void deleteShader();
	void setLights();

	const Json::Value Scene::createJson();


	std::vector<Light>& getLights() {return lights;};
	const std::string& getFileName(){return filename;};
	std::vector<GameObject*> GetGameObjects(){return gameObjects;};
	Camera* GetCamera(){return cameras[activeCamera];};//returns the current camera.
};

#endif // SCENE_H