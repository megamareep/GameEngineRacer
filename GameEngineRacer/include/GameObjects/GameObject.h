#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "Components\TransformComponent.h"
#include "Components\RenderComponent.h"
#include "Components\ShaderComponent.h"
#include "ResourceManager.h"
#include "Components\AnimationComponent.h"
#include "ResourceManager.h"


//class ResourceManager;
class GameObject
{
protected:
	////////
	
	enum ComponentType {ANIM, UNKN};
	std::string m_name;
	std::string m_type;

	ResourceManager* m_rManager;
	ComponentType m_compType;

	AnimationComponent *m_anim;
	TransformComponent *m_transform;//Pointer to Transform component
	RenderComponent *m_renderer;//Creates the vbo and vao for this object.
	ShaderComponent *m_shader;//Loads in the shaders for this object
public:
	GameObject();
	GameObject(std::string nName);
	~GameObject();
	virtual void init();//Initialises the game objects
	virtual void update(bool keys[]);//Updates the Game objects
	virtual void render();

	void setName(const std::string& nName);
	const std::string& getName()const {return m_name;};

	bool addComponent(std::string nName);

	void setEntityType(const std::string& entityType);
	const std::string& getEntityType()const {return m_type;};

	TransformComponent* getTransformComp(){return m_transform;};
	RenderComponent* getRenderComp(){return m_renderer;};
	ShaderComponent* getShaderComp(){return m_shader;};
	AnimationComponent* getAnimComp(){return m_anim;};
};
#endif