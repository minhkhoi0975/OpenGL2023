#include "ProjectApplication.hpp"
#include <glad/glad.h>

ProjectApplication::ProjectApplication(const char* title, int windowWidth, int windowHeight):Application(title, windowWidth, windowHeight), shader("Shaders/chessboard.vs", "Shaders/chessboard.fs")
{
	// Create a vertex array object.
	glGenVertexArrays(1, &vao);

	// Use this vao.
	glBindVertexArray(vao);

	// Create a vertex buffer object.
	glGenBuffers(1, &vbo);

	// Bind the created vbo to the array buffer.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Set the data of the array buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create an element array buffer object.
	glGenBuffers(1, &ebo);

	// Bind the created ebo to the element array buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// Set the data of the index buffer.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	// Create a shader program.
	Shader shader("Shaders/chessboard.vs", "Shaders/chessboard.fs");
	shader.Use();
}

void ProjectApplication::OnUpdate()
{
	// Clear the render buffer.
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Set the positions.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Set the UV coordinates.
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(unsigned int), GL_UNSIGNED_INT, (void*)0);
}
