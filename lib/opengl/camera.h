#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 _Position, glm::vec3 _up, GLfloat _yaw, GLfloat _pitch, GLfloat _moveSpeed, GLfloat _turnSpeed);
	~Camera();

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	glm::vec3 getPosition(){return position;}
	glm::vec3 getDirection(){return glm::normalize(front);}

	glm::mat4 calculateViewMatrix();

private:
	glm::vec3 position, front, up, right, worldUp;

	GLfloat yaw, pitch;

	GLfloat moveSpeed, turnSpeed;

	void update();
};
#endif// CAMERA_H
