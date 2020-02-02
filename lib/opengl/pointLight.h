#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
#include "light.h"

class PointLight : public Light
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue, 
				GLfloat aIntensity, GLfloat dIntensity,
				GLfloat xPos, GLfloat yPos, GLfloat zPos,
				GLfloat con, GLfloat lin, GLfloat exp);
	~PointLight();

	void useLight(GLuint ambientIntesityLocation, GLuint ambientColorLocation,
					GLuint diffuseIntensityLocation, GLuint positionLocation,
					GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);

protected:
	glm::vec3 position;
	GLfloat constant, linear, exponent;
};
#endif// POINT_LIGHT_H
