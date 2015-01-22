#include "Components\TransformComponent.h"

TransformComponent::TransformComponent()
{
	scale = glm::vec3 (0.0f,0.0f,0.0f);
	rotate = glm::vec3 (0.0f,0.0f,0.0f);
	translate = glm::vec3 (0.0f,0.0f,0.0f);
}
void TransformComponent::Init()
{
	
	


}
void TransformComponent::Update()
{
	

	
}
void TransformComponent::Rotate(float nx, float ny, float nz)
{
	rotate.x += nx;
	rotate.y += ny;
	rotate.z += nz;
	
	
}
void TransformComponent::Translate(float nx, float ny, float nz)
{
	translate.x += nx;
	translate.y += ny;
	translate.z += nz;
	
	
}
void TransformComponent::Scale(float nx, float ny, float nz)
{
	scale.x += nx;
	scale.y += ny;
	scale.z += nz;
}

void TransformComponent::Reset()
{
	scale = glm::vec3 (0.0f,0.0f,0.0f);
	rotate = glm::vec3 (0.0f,0.0f,0.0f);
	translate = glm::vec3 (0.0f,0.0f,0.0f);
}

