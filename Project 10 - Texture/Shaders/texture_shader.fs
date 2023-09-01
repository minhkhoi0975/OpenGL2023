#version 330 core
in vec2 textureCoordinateInput;
out vec4 fragmentColor;

uniform sampler2D inputTexture;
uniform vec4 color;

void main()
{
    fragmentColor = texture(inputTexture, textureCoordinateInput) * color;
}