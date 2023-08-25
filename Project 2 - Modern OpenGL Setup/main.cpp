#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(char** argv, int argc)
{
	GLFWwindow* window = nullptr;

	// Initialize GLFW.
	if (!glfwInit())
	{
		std::cout << "Error: Cannot initialize GLFW." << std::endl;
		std::exit(-1);
	}

	// Use OpenGL 3.3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window.
	window = glfwCreateWindow(640, 480, "Hello World!", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Error: Cannot create a window." << std::endl;
		glfwTerminate();
		std::exit(-1);
	}

	// Ensure to set this window to be the current context of OpenGL. Otherwise, GLAD can't be initialized.
	glfwMakeContextCurrent(window); 

	// Initialize GLAD.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: Cannot initialize GLAD." << std::endl;
		glfwTerminate();
		std::exit(-1);
	}

	// Define a triangle.
	float vertices[] =
	{
	   -0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	// Create a vertex array object.
	unsigned int vao;
	glGenVertexArrays(1, &vao);

	// Use this vao.
	glBindVertexArray(vao);

	// Create a vertex buffer object.
	unsigned int vbo;
	glGenBuffers(1, &vbo);

	// By the created vbo to the array buffer.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Set the data of the array buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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