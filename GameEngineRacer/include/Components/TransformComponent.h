#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H
#define GLM_FORCE_RADIANS

#include "3rdParty\gl_core_4_3.hpp"
#include "glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtc\constants.hpp"
#include "glm\gtc\matrix_transform.hpp"

class TransformComponent
{
private:
	
	glm::vec3 scale;
	glm::vec3 rotate;
	glm::vec3 translate;
	
public:
	TransformComponent();
	void Init();
	void Update();
	void Rotate(float nx, float ny, float nz);
	void Translate(float x, float y, float z);
	void Scale(float nx, float ny, float nz);
	void Reset();


	const glm::vec3& getScale() {return scale;};
	const glm::vec3& getRotate() {return rotate;};
	const glm::vec3& getTranslate() {return translate;};


};
#endif