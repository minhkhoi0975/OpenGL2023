#include "ProjectApplication.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

ProjectApplication::ProjectApplication(const char* title, int windowWidth, int windowHeight) :
	Application(title, windowWidth, windowHeight),
	vertexArray(),
	texture("textures/sample2.png"),
	shader("Shaders/mvp_shader.vs", "Shaders/mvp_shader.fs"),
	baseColor(0.5f, 0.8f, 0.0f, 1.0f),
	camera(45.0f, (float)windowWidth / windowHeight, 0.1f, 100.0f)
{
	vertexArray.Use();
	vertexBuffer.SetData(vertices, sizeof(vertices));

	shader.Use();

	// Set the MVP matrices.
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate the cube -55.0 degrees around the x-axis.

	// Enable depth testing.
	glEnable(GL_DEPTH_TEST);
}

void ProjectApplication::OnUpdate()
{
	// Clear the render buffer.
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Rotate the cube.
	model = glm::rotate(model, GetDeltaTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

	// Update the camera's position.
	UpdateCameraTransform();

	// Set the positions.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Set the UV coordinates.
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set MVP matrices.
	shader.SetUniformMatrix4("model", model);
	shader.SetUniformMatrix4("view", camera.GetViewMatrix());
	shader.SetUniformMatrix4("projection", camera.GetProjectionMatrix());

	// Set color.
	shader.SetUniformVector4("color", baseColor);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ProjectApplication::UpdateCameraTransform()
{
	// Update position.
	float cameraSpeed = 5.0f;
	camera.SetPosition(camera.GetPosition() + cameraMoveInput.y * camera.GetForwardDirection() * cameraSpeed * GetDeltaTime());
	camera.SetPosition(camera.GetPosition() + cameraMoveInput.x * camera.GetRightDirection() * cameraSpeed * GetDeltaTime());

	// Update rotation.
	if (shouldRotateCamera)
	{
		float cameraRotateSpeed = 1.0f;
		glm::vec3 cameraEulerAngles = glm::eulerAngles(camera.GetRotation());
		cameraEulerAngles.x -= GetCursorDeltaY() * cameraRotateSpeed * GetDeltaTime();
		cameraEulerAngles.y -= GetCursorDeltaX() * cameraRotateSpeed * GetDeltaTime();
		camera.SetRotation(glm::quat(glm::vec3(cameraEulerAngles.x, cameraEulerAngles.y, 0.0f)));
	}
}

void ProjectApplication::OnWindowResized(int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	camera.SetAspectRatio((float)newWidth / newHeight);
}

void ProjectApplication::OnKeyPressed(int key)
{
	switch (key)
	{
	case GLFW_KEY_W:
		cameraMoveInput.y += 1.0f;
		break;
	case GLFW_KEY_S:
		cameraMoveInput.y -= 1.0f;
		break;
	case GLFW_KEY_D:
		cameraMoveInput.x += 1.0f;
		break;
	case GLFW_KEY_A:
		cameraMoveInput.x -= 1.0f;
		break;

	case GLFW_KEY_ESCAPE:
		CloseWindow();
		break;
	}
}

void ProjectApplication::OnKeyReleased(int key)
{
	switch (key)
	{
	case GLFW_KEY_W:
		cameraMoveInput.y -= 1.0f;
		break;
	case GLFW_KEY_S:
		cameraMoveInput.y += 1.0f;
		break;
	case GLFW_KEY_D:
		cameraMoveInput.x -= 1.0f;
		break;
	case GLFW_KEY_A:
		cameraMoveInput.x += 1.0f;
		break;
	}
}

void ProjectApplication::OnMousePressed(int button)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
		shouldRotateCamera = true;
}

void ProjectApplication::OnMouseReleased(int button)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
		shouldRotateCamera = false;
}
