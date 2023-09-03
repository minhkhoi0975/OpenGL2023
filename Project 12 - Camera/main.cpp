#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ProjectApplication.hpp"
#include "../Common/Shader.hpp"

int main(int argc, char* argv[])
{
    ProjectApplication application("OpenGL", 1080, 1080);
    application.RunLoop();
}