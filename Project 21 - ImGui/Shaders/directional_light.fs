#version 330 core
struct Material
{
	sampler2D diffuse0;
	sampler2D specular0;
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

vec3 CalculateDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 viewDirection);

void main()
{	
	vec3 result;

	vec3 realNormal = normalize(normal);
	vec3 viewDirection = normalize(viewPosition - fragmentPosition);

	result = CalculateDirectionalLight(directionalLight, realNormal, viewDirection);

	fragmentColor = vec4(result, 1.0f);
}

vec3 CalculateDirectionalLight(DirectionalLight directionalLight, vec3 normal, vec3 viewDirection)
{
	vec3 ambient = directionalLight.ambient * vec3(texture(material.diffuse0, textureCoordinates));
	
	vec3 lightDirection = normalize(-directionalLight.direction);
	float diffusePercentage = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuse = directionalLight.diffuse * diffusePercentage * vec3(texture(material.diffuse0, textureCoordinates)); 

	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specularPercentage = (pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess));
	vec3 specular = directionalLight.specular * specularPercentage * vec3(texture(material.specular0, textureCoordinates));

	// Combine the lightning components together.
	return ambient + diffuse + specular;
}