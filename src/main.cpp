#include <glm/geometric.hpp>
#include <glm/gtc/quaternion.hpp>
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "parameters.h"

#include "mesh.h"
#include "shader.h"
#include "window.h"
#include "camera.h"
#include "texture.h"
#include "directionalLight.h"
#include "pointLight.h"
#include "spotLight.h"
#include "material.h"
#include "model.h"

using namespace std;

const float toRadians = 3.1415926535f / 180.0f;

Window mainWindow;
Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture floorTexture;

Material shinyMaterial;
Material dullMaterial;

Model droneModel = Model("MQ-27", "rgba");

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];
	
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

// Vertex shader
static const char* vShader = "shaders/shader.vert";

// Fragment shader
static const char* fShader = "shaders/shader.frag";

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, 
						GLfloat* vertices, unsigned int verticesCount, 
						unsigned int vLength, unsigned int normalOffset)
{
	// Find normal vectors
	for(size_t i=0;i<indiceCount;i+=3)
	{
		unsigned int in0 = indices[i]*vLength;
		unsigned int in1 = indices[i+1]*vLength;
		unsigned int in2 = indices[i+2]*vLength;

		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1+1]-vertices[in0+1], vertices[in1+2]-vertices[in0+2]);	
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2+1]-vertices[in0+1], vertices[in2+2]-vertices[in0+2]);	
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0+=normalOffset;
		in1+=normalOffset;
		in2+=normalOffset;

		vertices[in0]+=normal.x;	vertices[in0+1]+=normal.y;	vertices[in0+2]+=normal.z;
		vertices[in1]+=normal.x;	vertices[in1+1]+=normal.y;	vertices[in1+2]+=normal.z;
		vertices[in2]+=normal.x;	vertices[in2+1]+=normal.y;	vertices[in2+2]+=normal.z;
	}
	
	// Normalize normal vectors
	for(size_t i=0;i<verticesCount/vLength;i++)
	{
		unsigned int nOffset = i*vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset+1], vertices[nOffset+2]);
		vec = glm::normalize(vec);
		vertices[nOffset]=vec.x; vertices[nOffset+1]=vec.y; vertices[nOffset+2]=vec.z;
	}
}
void createObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
	//	x		y		z		u		v			nx		ny		nz	
		-1.0f,	-1.0f, 	-0.6f,	0.0f,	0.0f,		0.0f,	0.0f, 	0.0f,
		0.0f, 	-1.0f, 	1.0f,	0.5f,	0.0f,		0.0f,	0.0f, 	0.0f,
		1.0f, 	-1.0f, 	-0.6f,	1.0f,	0.0f,		0.0f,	0.0f, 	0.0f,
		0.0f, 	1.0f, 	0.0f,	0.5f,	1.0f,		0.0f,	0.0f,	0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-50.0f, 0.0f, -50.0f,	0.0f, 0.0f,		0.0f,-1.0f,0.0f,
		50.0f, 0.0f, -50.0f,	50.0f, 0.0f,	0.0f,-1.0f,0.0f,
		-50.0f, 0.0f, 50.0f,	0.0f, 50.0f,	0.0f,-1.0f,0.0f,
		50.0f, 0.0f, 50.0f,		50.0f, 50.0f,	0.0f,-1.0f,0.0f
	};

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh *obj1 = new Mesh();
	obj1->createMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->createMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->createMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);
}

void createShaders()
{
	Shader *shader1 = new Shader();
	shader1->createFromFiles(vShader, fShader);
	shaderList.push_back(shader1);
}

int main() 
{ 
	mainWindow = Window(1366,768);
	mainWindow.initialize();

	createObjects();
	createShaders();
	// Create camera
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	// Create textures
	brickTexture = Texture("textures/brick.png");
	brickTexture.loadTextureA();
	dirtTexture = Texture("textures/dirt.png");
	dirtTexture.loadTextureA();
	floorTexture= Texture("textures/floor.png");
	floorTexture.loadTexture();

	shinyMaterial = Material(1.0f, 32);
	dullMaterial = Material(0.3f, 4);

	// Load models
	droneModel.loadModel();

	// Create lights
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
				   				0.6f, 0.4f, 
								2.0f, -1.0f, -2.0f);

	unsigned int pointLightCount = 0;
	pointLights[0] = PointLight(1.0f, 1.0f, 0.0f,
								0.0f, 0.1f,
								-3.0f, 0.0f, 0.0f,
								0.3f, 0.2f, 0.1f);
	pointLightCount++;
	pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
								0.1f, 0.3f,
								3.0f, 0.0f, 0.0f,
								0.3f, 0.2f, 0.1f);
	//pointLightCount++;
	pointLights[2] = PointLight(0.0f, 0.0f, 1.0f,
								0.1f, 0.3f,
								0.0f, 0.0f, 2.0f,
								0.3f, 0.2f, 0.1f);
	//pointLightCount++;

	unsigned int spotLightCount = 0;
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
								0.0f, 3.0f,
								0.0f, 0.0f, 0.0f,
								0.0f, -1.0f, 0.0f,
								0.3f, 0.2f, 0.1f,
								20.0f);
	spotLightCount++;

	// Define view
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePositon = 0,
		   uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth()/mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while(!mainWindow.getShouldClose())
	{
		// Calculate delta time
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;
		// Get + Handle user input events
		glfwPollEvents();
		camera.keyControl(mainWindow.getKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear window
		glClearColor(0.0f,0.0f,0.0f,1.0f);	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->useShader();
		uniformModel = shaderList[0]->getModelLocation();
		uniformProjection = shaderList[0]->getProjectionLocation();
		uniformView = shaderList[0]->getViewLocation();
		uniformEyePositon = shaderList[0]->getEyePositionLocation();
		uniformSpecularIntensity = shaderList[0]->getSpecularIntensityLocation();
		uniformShininess = shaderList[0]->getShininessLocation();

		spotLights[0].setFlash(camera.getPosition(), camera.getDirection());

		shaderList[0]->setDirectionalLight(&mainLight);
		shaderList[0]->setPointLight(pointLights, pointLightCount);
		shaderList[0]->setSpotLight(spotLights, spotLightCount);

		//mainLight.useLight(uniformAmbientIntensity, uniformAmbientColor,
		//					uniformDiffuseIntensity, uniformDirection);
		
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePositon, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

		//glm::mat4 model(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//////model = glm::rotate(model, currAngle*toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		////model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//brickTexture.useTexture();
		//shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[0]->renderMesh();

		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, 3.0f, -2.5f));
		////model = glm::rotate(model, currAngle*toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		////model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//dirtTexture.useTexture();
		//dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[1]->renderMesh();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		floorTexture.useTexture();
		dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->renderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -5.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		model = glm::rotate(model, 90.0f*toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
		droneModel.renderModel();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
