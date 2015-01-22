#ifndef SHADERCOMPONENT_H
#define SHADERCOMPONENT_H

#include "3rdParty\gl_core_4_3.hpp"
#include "glfw3.h"
#include <fstream>
#include "ResourceManager.h"

class ShaderComponent
{
private:
	ResourceManager* rManager;
	GLuint fragShader;
	GLuint vertShader;
public:
	ShaderComponent();
	~ShaderComponent();
	void SetShader(GLuint fShader, GLuint vShader);
	//GLuint& GetProgramHandle(){return programHandle;};
	void Render();
	
};

#endif
