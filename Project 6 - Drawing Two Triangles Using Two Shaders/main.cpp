#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/// <summary>
/// Called when the size of the window is updated.
/// </summary>
/// <param name="window">The window whose size is changed.</param>
/// <param name="width">The new width of the window.</param>
/// <param name="height">The new height of the window.</param>
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

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

	const char* fragmentShaderSource2 =
		"#version 330 core										\n"
		"out vec4 fragColor;									\n"
		"														\n"
		"void main()											\n"
		"{														\n"
		"	fragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);			\n"
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
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	// Initialize GLAD.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: Cannot initialize GLAD." << std::endl;
		glfwTerminate();
		std::exit(-1);
	}

	// Define 2 triangles. 
	// The order of the vertices must be counter-clockwise so that the face is visible.
	float vertices[] =
	{
		// Top left triangle.
		-0.5f,  0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.0f,  0.0f, 0.0f,

		 // Bottom right triangle.
		 0.0f, -0.5f, 0.0f,
		 0.0f,  0.0f, 0.0f,
		 0.5f,  0.0f, 0.0f
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices, GL_STATIC_DRAW);

	// Create the second verrtex buffer object.
	unsigned int vbo2;
	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices + 9, GL_STATIC_DRAW);

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

	// Create the first fragment shader.
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
		std::cout << "Error: Cannot compile the fragment shader:\n" << infoLog << std::endl;
	}

	// Create the second fragment shader.
	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, nullptr);
	glCompileShader(fragmentShader2);

	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader2, sizeof(infoLog), nullptr, infoLog);
		std::cout << "Error: Cannot compile the fragment shader:\n" << infoLog << std::endl;
	}

	// Create the first shader program.
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

	// Create the second shader program.
	unsigned int shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram2, sizeof(infoLog), nullptr, infoLog);
		std::cout << "Error: Cannot create a shader program:\n" << infoLog << std::endl;
	}

	// Delete the shaders.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader2);

	// Loop until the user closes the window.
	while (!glfwWindowShouldClose(window))
	{
		// Clear the render buffer.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the first triangle using the first shader program.
		glUseProgram(shaderProgram);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Draw the second triangle using the second shader program.
		glUseProgram(shaderProgram2);
		glBindBuffer(GL_ARRAY_BUFFER, vbo2);
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

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}