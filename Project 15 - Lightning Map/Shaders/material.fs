#version 330 core
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 textureCoordinates;
in vec3 fragmentPosition;
in vec3 normal;

out vec4 fragmentColor;

uniform Material material;
uniform Light light;

uniform vec3 viewPosition;

void main()
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, textureCoordinates));
	
	vec3 realNormal = normalize(normal);
	vec3 lightDirection = normalize(light.position - fragmentPosition);
	vec3 diffuse = light.diffuse * max(dot(realNormal, lightDirection), 0.0f) * vec3(texture(material.diffuse, textureCoordinates)); 

	vec3 viewDirection = normalize(viewPosition - fragmentPosition);
	vec3 reflectionDirection = reflect(-lightDirection, realNormal);
	vec3 specular = light.specular * (pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess)) * vec3(texture(material.specular, textureCoordinates));

	// Combine the lightning components together.
	vec3 result = ambient + diffuse + specular;
	fragmentColor = vec4(result, 1.0f);
}