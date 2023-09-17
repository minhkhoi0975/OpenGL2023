#version 330 core
in vec2 textureCoordinates;
in vec3 fragmentPosition;
in vec3 normal;

out vec4 fragmentColor;

uniform sampler2D diffuse0;

void main()
{	
	fragmentColor = texture(diffuse0, textureCoordinates);
}