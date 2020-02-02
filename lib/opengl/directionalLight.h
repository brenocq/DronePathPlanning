#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H
#include "light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
			GLfloat xDir, GLfloat yDir, GLfloat zDir);
	~DirectionalLight();

	void useLight(GLfloat ambientIntesityLocation, GLfloat ambientColorLocation,
					GLfloat diffuseIntensityLocation, GLfloat directionLocation);

private:
	glm::vec3 direction;
};
#endif// DIRECTIONAL_LIGHT_H
