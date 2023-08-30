#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ProjectApplication.hpp"
#include "../Common/Shader.hpp"

int main(char** argv, int argc)
{
    ProjectApplication application("Hello World!", 1080, 1080);
    application.RunLoop();
}