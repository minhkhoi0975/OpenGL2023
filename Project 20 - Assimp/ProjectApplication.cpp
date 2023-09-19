#include "ProjectApplication.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <sstream>

ProjectApplication::ProjectApplication(const char* title, int windowWidth, int windowHeight) :
	Application(title, windowWidth, windowHeight),
	cubeShader("Shaders/material.vs", "Shaders/plain_texture.fs"),
	camera(45.0f, (float)windowWidth / windowHeight, 0.1f, 100.0f)
{
	// Set the models.
	models[0] = Model("models/backpack.obj");
	models[1] = Model("models/flyguy.obj");

	// Set the model matrix.
	modelMatrices[0] = ModelMatrix(glm::vec3(-5.0f, 0.0f, 0.0f));
    modelMatrices[1] = ModelMatrix();

	// Set the normal matrix.
	UpdateNormalMatrices();

	// Set the camera's position.
	camera.SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));

	// Enable depth testing.
	glEnable(GL_DEPTH_TEST);
}

void ProjectApplication::OnUpdate(const float& deltaTime)
{
	// Clear the render buffer.
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Update the normal matrices.
	UpdateNormalMatrices();

	// Update the camera's position.
	UpdateCameraTransform(deltaTime);

	DrawModels();
}

void ProjectApplication::UpdateNormalMatrices()
{
	for (int i = 0; i < MODEL_COUNT; ++i)
	{
		normalMatrices[i] = glm::mat3(transpose(glm::inverse(modelMatrices[i].GetModelMatrix())));
	}
}

void ProjectApplication::DrawModels()
{
	for (int modelIndex = 0; modelIndex < MODEL_COUNT; ++modelIndex)
	{
		cubeShader.Use();

		cubeShader.SetUniformMatrix4("model", modelMatrices[modelIndex].GetModelMatrix());
		cubeShader.SetUniformMatrix4("view", camera.GetViewMatrix());
		cubeShader.SetUniformMatrix4("projection", camera.GetProjectionMatrix());
		cubeShader.SetUniformMatrix3("normalMatrix", normalMatrices[modelIndex]);

		for (int i = 0; i < models[modelIndex].meshes.size(); ++i)
		{
			// TODO: Draw each mesh.
			models[modelIndex].meshes[i].Draw(cubeShader);
		}
	}
}

void ProjectApplication::UpdateCameraTransform(const float& deltaTime)
{
	// Update position.
	float cameraSpeed = 5.0f;
	camera.SetPosition(camera.GetPosition() + cameraMoveInput.y * camera.GetFacingDirection() * cameraSpeed * deltaTime);
	camera.SetPosition(camera.GetPosition() + cameraMoveInput.x * camera.GetRightDirection() * cameraSpeed * deltaTime);

	// Update rotation.
	if (shouldRotateCamera)
	{
		float cameraRotateSpeed = 1.0f;

		// Update the yaw.
		cameraYaw += -GetCursorDeltaX() * cameraRotateSpeed * GetDeltaTime();

		// Update the pitch.
		cameraPitch += -GetCursorDeltaY() * cameraRotateSpeed * GetDeltaTime();

		camera.SetRotation(cameraPitch, cameraYaw, 0.0f);
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
