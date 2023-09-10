#include "ProjectApplication.hpp"
#include <glad/glad.h>

ProjectApplication::ProjectApplication(const char* title, int windowWidth, int windowHeight) :
	Application(title, windowWidth, windowHeight),
	vertexArray(),
	texture("textures/sample2.png"),
	shader("Shaders/texture_shader.vs", "Shaders/texture_shader.fs"),
	baseColor(0.5f, 0.8f, 0.0f, 1.0f)
{
	vertexArray.Use();
	vertexBuffer.SetData(vertices, sizeof(vertices));
	elementBuffer.SetData(indicies, sizeof(indicies));

	shader.Use();
}

void ProjectApplication::OnUpdate(const float& deltaTime)
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

	// Set color.
	shader.SetUniformVector4("color", baseColor);

	glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(unsigned int), GL_UNSIGNED_INT, (void*)0);
}
