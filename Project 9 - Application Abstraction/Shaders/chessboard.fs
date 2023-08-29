#version 330 core
in vec2 textureCoordinateInput;
out vec4 fragmentColor;

uniform vec4 color;

void main()
{
    vec2 chessboardPosition = floor(textureCoordinateInput/0.125f);
    float patternMask = mod(chessboardPosition.x + mod(chessboardPosition.y, 2.0f), 2.0f);

    fragmentColor = patternMask * color;
}