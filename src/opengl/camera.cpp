#include "camera.h"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <stdio.h>

Camera::Camera()
{}

Camera::Camera(glm::vec3 _position, glm::vec3 _up, GLfloat _yaw, GLfloat _pitch, GLfloat _moveSpeed, GLfloat _turnSpeed)
{
	position = _position;
	worldUp = _up;
	yaw = _yaw;
	pitch = _pitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = _moveSpeed;
	turnSpeed = _turnSpeed;	

	update();
}

Camera::~Camera()
{}

void Camera::update()
{
	front.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
	
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity  = moveSpeed * deltaTime;
	if(keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}	
	if(keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}	
	if(keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}	
	if(keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}	
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	pitch>89.0f?pitch=89.0f:pitch;
	pitch<-89.0f?pitch=-89.0f:pitch;

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

