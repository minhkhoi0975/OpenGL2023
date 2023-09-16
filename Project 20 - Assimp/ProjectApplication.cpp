#include "ProjectApplication.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <sstream>

ProjectApplication::ProjectApplication(const char* title, int windowWidth, int windowHeight) :
	Application(title, windowWidth, windowHeight),
	cubeShader("Shaders/material.vs", "Shaders/material.fs"),
	lightShader("Shaders/light.vs", "Shaders/light.fs"),
	camera(45.0f, (float)windowWidth / windowHeight, 0.1f, 100.0f),
	model("models/backpack.obj")
{
	// Set up the initial model matrices of the lights.
	for (int i = 0; i < POINT_LIGHT_COUNT; ++i)
		pointLightModelMatrices[i] = ModelMatrix(pointLightPositions[i]);

	// Set the model matrix.
	modelMatrix = ModelMatrix();

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
	UpdateNormalMatrix();

	// Update the camera's position.
	UpdateCameraTransform(deltaTime);

	DrawModel();
}

void ProjectApplication::UpdateNormalMatrix()
{
	normalMatrix = glm::mat3(transpose(glm::inverse(modelMatrix.GetModelMatrix())));
}

void ProjectApplication::DrawModel()
{
	cubeShader.Use();

	cubeShader.SetUniformMatrix4("model", modelMatrix.GetModelMatrix());
	cubeShader.SetUniformMatrix4("view", camera.GetViewMatrix());
	cubeShader.SetUniformMatrix4("projection", camera.GetProjectionMatrix());
	cubeShader.SetUniformMatrix3("normalMatrix", normalMatrix);

	// Set lightning properties.
	cubeShader.SetUniformVector3("viewPosition", camera.GetPosition());

	// Directional light.
	cubeShader.SetUniformVector3("directionalLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	cubeShader.SetUniformVector3("directionalLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	cubeShader.SetUniformVector3("directionalLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	cubeShader.SetUniformVector3("directionalLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

	// Point light 1.
	cubeShader.SetUniformVector3("pointLights[0].position", pointLightPositions[0]);
	cubeShader.SetUniformVector3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	cubeShader.SetUniformVector3("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	cubeShader.SetUniformVector3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	cubeShader.SetUniformFloat("pointLights[0].constant", 1.0f);
	cubeShader.SetUniformFloat("pointLights[0].linear", 0.09f);
	cubeShader.SetUniformFloat("pointLights[0].quadratic", 0.032f);

	// Point light 2.
	cubeShader.SetUniformVector3("pointLights[1].position", pointLightPositions[1]);
	cubeShader.SetUniformVector3("pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	cubeShader.SetUniformVector3("pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	cubeShader.SetUniformVector3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	cubeShader.SetUniformFloat("pointLights[1].constant", 1.0f);
	cubeShader.SetUniformFloat("pointLights[1].linear", 0.09f);
	cubeShader.SetUniformFloat("pointLights[1].quadratic", 0.032f);

	// Point light 3.
	cubeShader.SetUniformVector3("pointLights[2].position", pointLightPositions[2]);
	cubeShader.SetUniformVector3("pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	cubeShader.SetUniformVector3("pointLights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	cubeShader.SetUniformVector3("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	cubeShader.SetUniformFloat("pointLights[2].constant", 1.0f);
	cubeShader.SetUniformFloat("pointLights[2].linear", 0.09f);
	cubeShader.SetUniformFloat("pointLights[2].quadratic", 0.032f);

	// Point light 4.
	cubeShader.SetUniformVector3("pointLights[3].position", pointLightPositions[3]);
	cubeShader.SetUniformVector3("pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	cubeShader.SetUniformVector3("pointLights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	cubeShader.SetUniformVector3("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	cubeShader.SetUniformFloat("pointLights[3].constant", 1.0f);
	cubeShader.SetUniformFloat("pointLights[3].linear", 0.09f);
	cubeShader.SetUniformFloat("pointLights[3].quadratic", 0.032f);

	// Spot light.
	cubeShader.SetUniformVector3("spotlight.position", camera.GetPosition());
	cubeShader.SetUniformVector3("spotlight.direction", camera.GetFacingDirection());
	cubeShader.SetUniformFloat("spotlight.cutOff", glm::cos(glm::radians(12.5f)));
	cubeShader.SetUniformFloat("spotlight.outerCutOff", glm::cos(glm::radians(17.5f)));
	cubeShader.SetUniformFloat("spotlight.constant", 1.0f);
	cubeShader.SetUniformFloat("spotlight.linear", 0.09f);
	cubeShader.SetUniformFloat("spotlight.quadratic", 0.032f);
	cubeShader.SetUniformVector3("spotlight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	cubeShader.SetUniformVector3("spotlight.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	cubeShader.SetUniformVector3("spotlight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	for (int i = 0; i < model.meshes.size(); ++i)
	{
		// TODO: Draw each mesh.
		model.meshes[i].Draw(cubeShader);
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
