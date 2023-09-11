#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoordinates;

out vec3 fragmentPosition;
out vec3 normal;
out vec2 textureCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main()
{
	gl_Position = projection * view * model * vec4(aPosition, 1.0f);
	fragmentPosition = vec3(model * vec4(aPosition, 1.0f));
        normal = normalMatrix * aNormal;
	textureCoordinates = aTextureCoordinates;
}