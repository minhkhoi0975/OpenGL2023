#include <GLFW/glfw3.h>
#include <iostream>

int main(char** argv, int argc)
{
	GLFWwindow* window = nullptr;

	// Initialize GLFW.
	if (!glfwInit())
		std::exit(-1);

	// Create a window.
	window = glfwCreateWindow(640, 480, "Hello World!", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		std::exit(-1);
	}

	// Make the window's context current for OpenGL.
	glfwMakeContextCurrent(window);

	// Loop until the user closes the window.
	while (!glfwWindowShouldClose(window))
	{
		// Clear the render buffer.
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap front and back buffers.
		glfwSwapBuffers(window);

		// Poll and process events.
		glfwPollEvents();
	}

	glfwTerminate();
}