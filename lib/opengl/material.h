#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>

class Material
{
public:
	Material();
	Material(GLfloat _specularIntensity, GLfloat _shininess);
	~Material();

	void useMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);
private:
	GLfloat specularIntensity;
	GLfloat shininess;
};

#endif// MATERIAL_H
