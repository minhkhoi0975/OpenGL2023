#version 330 core
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
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

in vec2 textureCoordinates;
in vec3 fragmentPosition;
in vec3 normal;

out vec4 fragmentColor;

uniform Material material;
uniform PointLight pointLight;

uniform vec3 viewPosition;

void main()
{
	vec3 ambient = pointLight.ambient * vec3(texture(material.diffuse, textureCoordinates));
	
	vec3 realNormal = normalize(normal);
	vec3 lightDirection = normalize(pointLight.position - fragmentPosition);
	float diffusePercentage = max(dot(realNormal, lightDirection), 0.0f);
	vec3 diffuse = pointLight.diffuse * diffusePercentage * vec3(texture(material.diffuse, textureCoordinates)); 

	vec3 viewDirection = normalize(viewPosition - fragmentPosition);
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
	vec3 result = ambient + diffuse + specular;
	fragmentColor = vec4(result, 1.0f);
}