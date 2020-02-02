#version 330

in vec4 vCol;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 colour;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

struct Light
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};
struct DirectionalLight
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform sampler2D theTexture;
uniform Material material;

uniform vec3 eyePosition;

vec4 calcLightByDirection(Light light, vec3 direction)
{
	vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;

	float diffuseFactor = max(dot(normalize(normal), normalize(direction)), 0.0f);
	vec4 diffuseColor = vec4(light.color, 1.0f)*light.diffuseIntensity*diffuseFactor;

	vec4 specularColor = vec4(0,0,0,0);
	if(diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(eyePosition - fragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(normal)));

		float specularFactor = dot(fragToEye, reflectedVertex);
		if(specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0f);
		}
	}

	return (ambientColor + diffuseColor + specularColor);
}

vec4 calcDirectionalLight()
{
	return calcLightByDirection(directionalLight.base, directionalLight.direction);
}

vec4 calcPointLight(PointLight pLight)
{
	vec3 direction = fragPos - pLight.position;
	float distance = length(direction);
	direction = normalize(direction);

	vec4 color = calcLightByDirection(pLight.base, direction);
	float attenuation = pLight.exponent * distance * distance + 
						pLight.linear * distance + 
						pLight.constant;

	return (color/attenuation);
}

vec4 calcSpotLight(SpotLight sLight)
{
	vec3 rayDirection = normalize(fragPos - sLight.base.position);
	float slFactor = dot(rayDirection, sLight.direction);

	if(slFactor > sLight.edge)
	{
		vec4 color = calcPointLight(sLight.base);
		return color * (1.0f- (1.0f-slFactor)*(1.0f/(1.0f-sLight.edge)));
	}
	else
	{
		return vec4(0,0,0,0);
	}
}

vec4 calcPointLights()
{
	vec4 totalColor = vec4(0,0,0,0);
	for(int i=0; i<pointLightCount; i++)
	{
		totalColor += calcPointLight(pointLights[i]);
	}
	return totalColor;
}

vec4 calcSpotLights()
{
	vec4 totalColor = vec4(0,0,0,0);
	for(int i=0; i<spotLightCount; i++)
	{
		totalColor += calcSpotLight(spotLights[i]);
	}
	return totalColor;
}

void main()
{
	vec4 finalColor = calcDirectionalLight();
	finalColor += calcPointLights();
	finalColor += calcSpotLights();
	
	colour = texture(theTexture, texCoord) * finalColor; 
}
