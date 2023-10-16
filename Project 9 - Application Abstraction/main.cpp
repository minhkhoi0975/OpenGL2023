#include "ProjectApplication.hpp"

int main(char** argv, int argc)
{
    ProjectApplication application("Hello World!", 1080, 1080);
    application.RunLoop();
}