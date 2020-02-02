#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

class Mesh
{
public:
	Mesh();
	~Mesh();
	void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void renderMesh();
	void clearMesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};
#endif// MESH_H
