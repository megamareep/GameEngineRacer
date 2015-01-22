#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS
#include "glm\glm.hpp"
#include "GameObjects\GameObject.h"
#include "glm\gtx\rotate_vector.hpp"
class Camera
{
private:
	float _pitch;
	float _yaw;

	float _fieldOfView;
	float _nearPlane;
	float _farPlane;
	float _aspectRatio;

	glm::vec3 _position;
	glm::vec3 _target;
	glm::vec3 _right;
	glm::vec3 _up;
	glm::vec3 _forward;
	GLuint programHandle;

	glm::mat4 _view;
	glm::mat4 _projection;

public:
	Camera();
	~Camera();

	const glm::vec3& position() const; //position getter method
	void setPosition(const glm::vec3& position); //position setter method

	float fieldOfView() const; //fieldOfView getter method
	void setFieldOfView(float fieldOfView); //fieldOfView setter method

	float aspectRatio() const; //aspectRatio getter method
	void setAspectRatio(float aspectRatio);  //aspectRatio setter method

	float nearPlane() const;  //nearPlane getter method
	float farPlane() const;   //farPlane getter method
	void setNearAndFarPlanes(float nearPlane, float farPlane); //nearPlane and farPLane setter method


	void rotate(const float x, const float y); //Rotate camera
	void pan(const float x, const float y);  //Pan camera
	void zoom(const float z); //Zoom camera

	void lookAt(const glm::vec3& target); //Set up the view matrix

	void update();  //Update the camera

	void init(GLuint& nProgramHandle); //Reset the camera

	glm::mat4 view(); //Get the View matrix

	glm::mat4 projection(); //Get the Projection matrix
};
#endif
