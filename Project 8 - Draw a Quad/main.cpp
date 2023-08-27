#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Common/Shader.hpp"

// Called when the size of the window is updated.
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

// Called when there is an action from the keyboard.
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool wireFrameMode = false;

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
	window = glfwCreateWindow(1080, 1080, "Hello World!", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Error: Cannot create a window." << std::endl;
		glfwTerminate();
		std::exit(-1);
	}

	// Ensure to set this window to be the current context of OpenGL. Otherwise, GLAD can't be initialized.
	glfwMakeContextCurrent(window);

	// Bind functions to events.
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetKeyCallback(window, KeyCallback);

	// Initialize GLAD.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: Cannot initialize GLAD." << std::endl;
		glfwTerminate();
		std::exit(-1);
	}

	// Define the vertices of the quad.
	float vertices[] =
	{
		 // Positions       // UV coordinates  
		-0.5f,  0.5f, 0.0f,	0.0f, 1.0f,	       // Top left
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f,	       // Bottom left
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,		   // Top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f		   // Bottom right
	};

	// Define the indicies of the triangles.
	unsigned int indicies[] =
	{
		2, 0, 1, // Top left
		3, 2, 1  // Bottom right
	};

	// Create a vertex array object.
	unsigned int vao;
	glGenVertexArrays(1, &vao);

	// Use this vao.
	glBindVertexArray(vao);

	// Create a vertex buffer object.
	unsigned int vbo;
	glGenBuffers(1, &vbo);

	// Bind the created vbo to the array buffer.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Set the data of the array buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create an element array buffer object.
	unsigned int ebo;
	glGenBuffers(1, &ebo);

	// Bind the created ebo to the element array buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// Set the data of the index buffer.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	// Create a shader program.
	Shader shader("Shaders/chessboard.vs", "Shaders/chessboard.fs");
	shader.Use();

	// Loop until the user closes the window.
	while (!glfwWindowShouldClose(window))
	{
		// Clear the render buffer.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		// Set the positions.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Set the UV coordinates.
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);

		glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(unsigned int), GL_UNSIGNED_INT, (void*)0);

		// Swap front and back buffers.
		glfwSwapBuffers(window);

		// Poll and process events.
		glfwPollEvents();
	}

	glfwTerminate();
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		// Toggle/untoggle wireframe mode.
		if (key == GLFW_KEY_W)
		{
			if (!wireFrameMode)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			wireFrameMode = !wireFrameMode;
		}

		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);
	}
}