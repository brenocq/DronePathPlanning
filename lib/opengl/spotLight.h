#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "pointLight.h"

class SpotLight : public PointLight
{
public:
	SpotLight();
	SpotLight(GLfloat red, GLfloat green, GLfloat blue, 
				GLfloat aIntensity, GLfloat dIntensity,
				GLfloat xPos, GLfloat yPos, GLfloat zPos,
				GLfloat xDir, GLfloat yDir, GLfloat zDir,
				GLfloat con, GLfloat lin, GLfloat exp,
				GLfloat edg);
	~SpotLight();

	void useLight(GLuint ambientIntesityLocation, GLuint ambientColorLocation,
					GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation,
					GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
					GLuint edgeLocation);

	void setFlash(glm::vec3 pos, glm::vec3 dir);

private:
	glm::vec3 direction;

	GLfloat edge, procEdge;
};
#endif// SPOT_LIGHT_H
