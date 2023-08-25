#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/// <summary>
/// Called when the size of the window is updated.
/// </summary>
/// <param name="window">The window whose size is changed.</param>
/// <param name="width">The new width of the window.</param>
/// <param name="height">The new height of the window.</param>
void OnWindowSizeChanged(GLFWwindow* window, int width, int height);

int main(char** argv, int argc)
{
	const char* vertexShaderSource = 
		"#version 330 core										\n"
		"layout (location = 0) in vec3 aPos;					\n"
		"void main()											\n"
		"{														\n"
		"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\n"
		"}														\0";

	const char* fragmentShaderSource =
		"#version 330 core										\n"
		"out vec4 fragColor;									\n"
		"														\n"
		"void main()											\n"
		"{														\n"
	    "	fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);			\n"
		"}														\n";

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

	// Bind functions to events.
	glfwSetFramebufferSizeCallback(window, OnWindowSizeChanged);

	// Initialize GLAD.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: Cannot initialize GLAD." << std::endl;
		glfwTerminate();
		std::exit(-1);
	}

	// Define 2 triangles.
	float vertices[] =
	{
		// Left triangle.
		-0.5f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,

		 // Right triangle.
		  0.5f,  0.5f, 0.0f,
		  0.0f, -1.0f, 0.0f,
		 0.25f, 0.25f, 0.0f
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

	int  success;
	char infoLog[512];

	// Create a vertex shader.
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
		std::cout << "Error: Cannot compile the vertex shader:\n" << infoLog << std::endl;
	}

	// Create a fragment shader.
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
		std::cout << "Error: Cannot compile the fragment shader:\n" << infoLog << std::endl;
	}

	// Create a shader program.
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
		std::cout << "Error: Cannot create a shader program:\n" << infoLog << std::endl;
	}

	// Use the shader program for rendering.
	glUseProgram(shaderProgram);

	// Loop until the user closes the window.
	while (!glfwWindowShouldClose(window))
	{
		// Clear the render buffer.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the triangle.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Swap front and back buffers.
		glfwSwapBuffers(window);

		// Poll and process events.
		glfwPollEvents();
	}

	glfwTerminate();
}

void OnWindowSizeChanged(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}