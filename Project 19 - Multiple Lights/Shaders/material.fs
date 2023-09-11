#version 330 core
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectionalLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct Spotlight
{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 textureCoordinates;
in vec3 fragmentPosition;
in vec3 normal;

out vec4 fragmentColor;

uniform Material material;

uniform DirectionalLight directionalLight;

#define POINT_LIGHT_COUNT 4
uniform PointLight pointLights[POINT_LIGHT_COUNT];

uniform Spotlight spotlight;

uniform vec3 viewPosition;

vec3 CalculateDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 viewDirection);
vec3 CalculatePointLight(PointLight pointLight, vec3 normal, vec3 fragmentPosition, vec3 viewDirection);
vec3 CalculateSpotlight(Spotlight spotlight, vec3 normal, vec3 fragmentPosition, vec3 viewDirection);

void main()
{	
	vec3 result;

	vec3 realNormal = normalize(normal);
	vec3 viewDirection = normalize(viewPosition - fragmentPosition);

	result = CalculateDirectionalLight(directionalLight, realNormal, viewDirection);
	for (int i = 0; i < POINT_LIGHT_COUNT; ++i)
		result += CalculatePointLight(pointLights[i], realNormal, fragmentPosition, viewDirection);
	result += CalculateSpotlight(spotlight, realNormal, fragmentPosition, viewDirection);

	fragmentColor = vec4(result, 1.0f);
}

vec3 CalculateDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 viewDirection)
{
	vec3 ambient = directionalLight.ambient * vec3(texture(material.diffuse, textureCoordinates));
	
	vec3 realNormal = normalize(normal);
	vec3 lightDirection = normalize(-directionalLight.direction);
	float diffusePercentage = max(dot(realNormal, lightDirection), 0.0f);
	vec3 diffuse = directionalLight.diffuse * diffusePercentage * vec3(texture(material.diffuse, textureCoordinates)); 

	vec3 reflectionDirection = reflect(-lightDirection, realNormal);
	float specularPercentage = (pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess));
	vec3 specular = directionalLight.specular * specularPercentage * vec3(texture(material.specular, textureCoordinates));

	// Combine the lightning components together.
	return ambient + diffuse + specular;
}

vec3 CalculatePointLight(PointLight pointLight, vec3 normal, vec3 fragmentPosition, vec3 viewDirection)
{
	vec3 ambient = pointLight.ambient * vec3(texture(material.diffuse, textureCoordinates));
	
	vec3 realNormal = normalize(normal);
	vec3 lightDirection = normalize(pointLight.position - fragmentPosition);
	float diffusePercentage = max(dot(realNormal, lightDirection), 0.0f);
	vec3 diffuse = pointLight.diffuse * diffusePercentage * vec3(texture(material.diffuse, textureCoordinates)); 

	vec3 reflectionDirection = reflect(-lightDirection, realNormal);
	float specularPercentage = (pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess));
	vec3 specular = pointLight.specular * specularPercentage * vec3(texture(material.specular, textureCoordinates));

	// Calculate the distance and attenuation.
	float distance = length(pointLight.position - fragmentPosition);
	float attenuation = 1.0f / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * distance * distance);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	// Combine the lightning components together.
	return ambient + diffuse + specular;
}

vec3 CalculateSpotlight(Spotlight spotlight, vec3 normal, vec3 fragmentPosition, vec3 viewDirection)
{
	vec3 ambient = spotlight.ambient * vec3(texture(material.diffuse, textureCoordinates));
	
	vec3 realNormal = normalize(normal);
	vec3 lightDirection = normalize(spotlight.position - fragmentPosition);
	float diffusePercentage = max(dot(realNormal, lightDirection), 0.0f);
	vec3 diffuse = spotlight.diffuse * diffusePercentage * vec3(texture(material.diffuse, textureCoordinates)); 

	vec3 reflectionDirection = reflect(-lightDirection, realNormal);
	float specularPercentage = (pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess));
	vec3 specular = spotlight.specular * specularPercentage * vec3(texture(material.specular, textureCoordinates));

	// Calculate the attenuation.
	float distance = length(spotlight.position - fragmentPosition);	
	float attenuation = 1.0f / (spotlight.constant + spotlight.linear * distance + spotlight.quadratic * distance * distance);

	diffuse *= attenuation;
	specular *= attenuation;

	// Calculate the intensity (see https://learnopengl.com/Lighting/Light-casters).
	float theta = dot(lightDirection, normalize(-spotlight.direction));
	float epsilon = spotlight.cutOff - spotlight.outerCutOff;
	float intensity = clamp((theta - spotlight.outerCutOff) / epsilon, 0.0f, 1.0f);

	diffuse *= intensity;
	specular *= intensity;

	// Combine the lightning components together.
	return ambient + diffuse + specular;
}