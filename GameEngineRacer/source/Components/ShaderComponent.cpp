#include "Components\ShaderComponent.h"



ShaderComponent::ShaderComponent()
{
	rManager = ResourceManager::getInstance();
}
ShaderComponent::~ShaderComponent()
{

}
void ShaderComponent::SetShader(const std::string& shaderName)
{
	// Attach the shaders to the program object

	m_shaderName = shaderName;
}
void ShaderComponent::Render()
{
	/*GLuint loc= gl::GetUniformLocation(programHandle, "frag");
	gl::Uniform1i(loc, false);*/

    //gl::UseProgram( programHandle );

	GLuint loc= gl::GetUniformLocation(rManager->getShaders().at(0)->programhandle, "Kd");
	gl::Uniform3f(loc,1.0f, 1.0f, 1.0f);
	GLuint loc1= gl::GetUniformLocation(rManager->getShaders().at(0)->programhandle, "Ks");
	gl::Uniform3f(loc1,1.f,1.f,1.f);
	GLuint loc2= gl::GetUniformLocation(rManager->getShaders().at(0)->programhandle, "Ka");
	gl::Uniform3f(loc2,0.2f, 0.2f, 0.2f);
	GLuint loc3= gl::GetUniformLocation(rManager->getShaders().at(0)->programhandle, "n");
	gl::Uniform1f(loc3,32.f);
	
}


