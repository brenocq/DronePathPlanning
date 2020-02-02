#include "shader.h"
#include <fstream>
#include <string>

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;

	pointLightCount = 0;
	spotLightCount = 0;
}

Shader::~Shader()
{
	clearShader();
}

void Shader::createFromString(const char* vertexCode, const char* fragmentCode)
{
	compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = readFile(vertexLocation);
	std::string fragmentString = readFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);
}

std::string Shader::readFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if(!fileStream.is_open())
	{
		printf("Failed to read %s! File doesn't exist.\n", fileLocation);
		return "";
	}

	std::string line = "";
	while(!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line+"\n");
	}

	fileStream.close();
	return content;
}

GLuint Shader::getProjectionLocation()
{
	return uniformProjection;	
}

GLuint Shader::getModelLocation()
{
	return uniformModel;
}

GLuint Shader::getViewLocation()
{
	return uniformView;
}
GLuint Shader::getAmbientColorLocation()
{
	return uniformDirectionLight.uniformColor;
}
GLuint Shader::getAmbientIntensityLocation()
{
	return uniformDirectionLight.uniformAmbientIntensity;
}
GLuint Shader::getDiffuseIntensityLocation()
{
	return uniformDirectionLight.uniformDiffuseIntensity;
}
		
GLuint Shader::getDirectionLocation()
{
	return uniformDirectionLight.uniformDirection;
}
GLuint Shader::getSpecularIntensityLocation()
{
	return uniformSpecularIntensity;
}
GLuint Shader::getShininessLocation()
{
	return uniformShininess;
}
GLuint Shader::getEyePositionLocation()
{
	return uniformEyePositon;
}
void Shader::setDirectionalLight(DirectionalLight *dLight)
{
	dLight->useLight(uniformDirectionLight.uniformAmbientIntensity,
						uniformDirectionLight.uniformColor,
						uniformDirectionLight.uniformDiffuseIntensity,
						uniformDirectionLight.uniformDirection);
}

void Shader::setPointLight(PointLight *pLight, unsigned int lightCount)
{
	if(lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

	glUniform1i(uniformPointLightCount, lightCount);

	for(int i=0; i<int(lightCount); i++)
	{
		pLight[i].useLight(uniformPointLight[i].uniformAmbientIntensity,
							uniformPointLight[i].uniformColor,
							uniformPointLight[i].uniformDiffuseIntensity,
							uniformPointLight[i].uniformPosition,
							uniformPointLight[i].uniformConstant,
							uniformPointLight[i].uniformLinear,
							uniformPointLight[i].uniformExponent);
	}
}

void Shader::setSpotLight(SpotLight *sLight, unsigned int lightCount)
{
	if(lightCount > MAX_SPOT_LIGHTS) lightCount = MAX_SPOT_LIGHTS;

	glUniform1i(uniformSpotLightCount, lightCount);

	for(int i=0; i<int(lightCount); i++)
	{
		sLight[i].useLight(uniformSpotLight[i].uniformAmbientIntensity,
							uniformSpotLight[i].uniformColor,
							uniformSpotLight[i].uniformDiffuseIntensity,
							uniformSpotLight[i].uniformPosition,
							uniformSpotLight[i].uniformDirection,
							uniformSpotLight[i].uniformConstant,
							uniformSpotLight[i].uniformLinear,
							uniformSpotLight[i].uniformExponent,
							uniformSpotLight[i].uniformEdge);
	}
}

void Shader::useShader()
{
	glUseProgram(shaderID);
}

void Shader::clearShader()
{
	if(shaderID!=0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if(!shaderID)
	{
		printf("Error creating shader program!");
		return;
	}

	addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER); 

	GLint result = 0;
	GLchar eLog[1024] = {0};

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if(!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);

	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if(!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program '%s'\n", eLog);
		return;
	}
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView= glGetUniformLocation(shaderID, "view");
	uniformDirectionLight.uniformColor = glGetUniformLocation(shaderID, "directionalLight.base.color");
	uniformDirectionLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	uniformDirectionLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
	uniformDirectionLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
	uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
	uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
	uniformEyePositon = glGetUniformLocation(shaderID, "eyePosition");

	uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");
	for(int i=0; i<MAX_POINT_LIGHTS; i++)
	{
		char locBuff[100]={'\0'};

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
		uniformPointLight[i].uniformColor = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
		uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
		uniformPointLight[i].uniformDiffuseIntensity= glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
		uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
		uniformPointLight[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
		uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);
	}

	uniformSpotLightCount = glGetUniformLocation(shaderID, "spotLightCount");
	for(int i=0; i<MAX_SPOT_LIGHTS; i++)
	{
		char locBuff[100]={'\0'};

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.color", i);
		uniformSpotLight[i].uniformColor = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", i);
		uniformSpotLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", i);
		uniformSpotLight[i].uniformDiffuseIntensity= glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
		uniformSpotLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", i);
		uniformSpotLight[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", i);
		uniformSpotLight[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.exponent", i);
		uniformSpotLight[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", i);
		uniformSpotLight[i].uniformDirection= glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
		uniformSpotLight[i].uniformEdge= glGetUniformLocation(shaderID, locBuff);
	}
}

void Shader::addShader(GLuint theProgram, const char*  shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = {0};

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if(!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);	
}
