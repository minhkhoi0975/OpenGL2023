#include "ProjectApplication.hpp"

int main(int argc, char* argv[])
{
    ProjectApplication application("Hello World!", 1080, 1080);
    application.RunLoop();
}