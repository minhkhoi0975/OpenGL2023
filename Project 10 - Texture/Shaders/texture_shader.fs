#version 330 core
in vec2 textureCoordinateInput;
out vec4 fragmentColor;

uniform sampler2D inputTexture;

void main()
{
    fragmentColor = texture(inputTexture, textureCoordinateInput);
}