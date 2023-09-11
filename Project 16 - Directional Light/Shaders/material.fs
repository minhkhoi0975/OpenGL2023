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

in vec2 textureCoordinates;
in vec3 fragmentPosition;
in vec3 normal;

out vec4 fragmentColor;

uniform Material material;
uniform DirectionalLight directionalLight;

uniform vec3 viewPosition;

void main()
{
	vec3 ambient = directionalLight.ambient * vec3(texture(material.diffuse, textureCoordinates));
	
	vec3 realNormal = normalize(normal);
	vec3 lightDirection = normalize(-directionalLight.direction);
	float diffusePercentage = max(dot(realNormal, lightDirection), 0.0f);
	vec3 diffuse = directionalLight.diffuse * diffusePercentage * vec3(texture(material.diffuse, textureCoordinates)); 

	vec3 viewDirection = normalize(viewPosition - fragmentPosition);
	vec3 reflectionDirection = reflect(-lightDirection, realNormal);
	float specularPercentage = (pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess));
	vec3 specular = directionalLight.specular * specularPercentage * vec3(texture(material.specular, textureCoordinates));

	// Combine the lightning components together.
	vec3 result = ambient + diffuse + specular;
	fragmentColor = vec4(result, 1.0f);
}