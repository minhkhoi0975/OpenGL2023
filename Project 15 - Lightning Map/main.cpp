#include "ProjectApplication.hpp"

int main(int argc, char* argv[])
{
    ProjectApplication application("OpenGL", 1080, 1080);
    application.RunLoop();
}