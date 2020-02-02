#include "material.h"
Material::Material()
{
	specularIntensity = 0.0f;
	shininess = 0.0f;
}

Material::Material(GLfloat _specularIntensity, GLfloat _shininess)
{
	specularIntensity = _specularIntensity;
	shininess = _shininess;	
}

Material::~Material()
{

}

void Material::useMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
{
	glUniform1f(specularIntensityLocation, specularIntensity);
	glUniform1f(shininessLocation, shininess);

}
