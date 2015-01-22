#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H


#include <iostream>
#include "ShaderComponent.h"
#include "3rdParty\gl_core_4_3.hpp"
#include "glfw3.h"
#include "3rdParty\Texture.h"
#include "ResourceManager.h"

#include <vector>
class ResourceManager;
class RenderComponent
{
private:
	GLuint positionBufferHandle;
	GLuint normalBufferHandle;
	GLuint uvBufferHandle;
	ResourceManager* rManger;
	GLuint vboHandles[2];
	GLuint vaoHandle;
	GLsizei indicesCount;
	Texture* texture;
public:
	RenderComponent();
	void init(std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals, 
		std::vector<GLfloat>& uvData, Texture* nTexture);
	void update();
};
#endif