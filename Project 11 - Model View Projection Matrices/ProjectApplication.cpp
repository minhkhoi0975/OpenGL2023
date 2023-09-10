#include "ProjectApplication.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

ProjectApplication::ProjectApplication(const char* title, int windowWidth, int windowHeight) :
	Application(title, windowWidth, windowHeight),
	vertexArray(),
	texture("textures/sample2.png"),
	shader("Shaders/mvp_shader.vs", "Shaders/mvp_shader.fs"),
	baseColor(0.5f, 0.8f, 0.0f, 1.0f)
{
	vertexArray.Use();
	vertexBuffer.SetData(vertices, sizeof(vertices));

	shader.Use();

	// Set the MVP matrices.
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate the cube -55.0 degrees around the x-axis.

	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / windowHeight, 0.1f, 100.0f);

	// Enable depth testing.
	glEnable(GL_DEPTH_TEST);
}

void ProjectApplication::OnUpdate(const float& deltaTime)
{
	// Clear the render buffer.
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Rotate the cube.
	model = glm::rotate(model, deltaTime * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

	// Set the positions.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Set the UV coordinates.
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set MVP matrices.
	shader.SetUniformMatrix4("model", model);
	shader.SetUniformMatrix4("view", view);
	shader.SetUniformMatrix4("projection", projection);

	// Set color.
	shader.SetUniformVector4("color", baseColor);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
