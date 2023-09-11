#version 330 core
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
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
uniform Spotlight spotlight;

uniform vec3 viewPosition;

void main()
{
	vec3 ambient = spotlight.ambient * vec3(texture(material.diffuse, textureCoordinates));
	
	vec3 realNormal = normalize(normal);
	vec3 lightDirection = normalize(spotlight.position - fragmentPosition);
	float diffusePercentage = max(dot(realNormal, lightDirection), 0.0f);
	vec3 diffuse = spotlight.diffuse * diffusePercentage * vec3(texture(material.diffuse, textureCoordinates)); 

	vec3 viewDirection = normalize(viewPosition - fragmentPosition);
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
	vec3 result = ambient + diffuse + specular;
	fragmentColor = vec4(result, 1.0f);
}