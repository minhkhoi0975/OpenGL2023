#version 330 core
in vec3 fragmentPosition;
in vec3 normal;

out vec4 fragmentColor;

// Ambient properties.
uniform float ambientStrength;
uniform vec3 ambientColor;

// Diffuse properties.
uniform vec3 lightPosition;
uniform vec3 lightColor;

// Specular properties.
uniform vec3 viewPosition;
uniform float specularStrength;
uniform float shininess;

// Object property.
uniform vec3 objectColor;

void main()
{
	// Calculate the ambient.
	vec3 ambient = ambientStrength * ambientColor;

	// Calculate the diffuse.
	vec3 realNormal = normalize(normal);
	vec3 lightDirection = normalize(lightPosition - fragmentPosition);
	vec3 diffuse = max(dot(realNormal, lightDirection), 0.0f) * lightColor;

	// Calculate the specular.
	vec3 viewDirection = normalize(viewPosition - fragmentPosition);
	vec3 reflectionDirection = reflect(-lightDirection, realNormal);
	vec3 specular = specularStrength * pow(max(dot(viewDirection, reflectionDirection), 0.0), shininess) * lightColor;


        // Combine the lightning components together.
        vec3 result = (ambient + diffuse + specular) * objectColor;
	fragmentColor = vec4(result, 1.0f);
}