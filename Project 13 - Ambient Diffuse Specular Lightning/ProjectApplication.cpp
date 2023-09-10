#include "ProjectApplication.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

ProjectApplication::ProjectApplication(const char* title, int windowWidth, int windowHeight) :
	Application(title, windowWidth, windowHeight),
	vertexArray(),
	cubeShader("Shaders/ambient_diffuse_specular.vs", "Shaders/ambient_diffuse_specular.fs"),
	lightShader("Shaders/light.vs", "Shaders/light.fs"),
	camera(45.0f, (float)windowWidth / windowHeight, 0.1f, 100.0f)
{
	vertexArray.Use();
	vertexBuffer.SetData(vertices, sizeof(vertices));

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

	// Rotate the cube.
	cubeModelMatrix.Rotate(glm::quat(glm::vec3(glm::radians(90.0f * deltaTime), glm::radians(90.0f * deltaTime), 0.0f)));

	// Translate the light.
	glm::vec3 currentLightPosition = lightModelMatrix.GetPosition();
	lightModelMatrix.SetPosition(currentLightPosition.x, 5 + 10 * glm::sin(GetLatestFrameTime()), 5 + 10 * glm::sin(GetLatestFrameTime()));

	// Update the normal matrix.
	UpdateNormalMatrix();

	// Update the camera's position.
	UpdateCameraTransform();

	DrawLight();
	DrawCube();
}

void ProjectApplication::UpdateNormalMatrix()
{
	normalMatrix = glm::mat3(transpose(glm::inverse(cubeModelMatrix.GetModelMatrix())));
}

void ProjectApplication::DrawLight()
{
	lightShader.Use();

	lightShader.SetUniformMatrix4("model", lightModelMatrix.GetModelMatrix());
	lightShader.SetUniformMatrix4("view", camera.GetViewMatrix());
	lightShader.SetUniformMatrix4("projection", camera.GetProjectionMatrix());

	lightShader.SetUniformVector3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	// Set the positions.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Set the normals.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ProjectApplication::DrawCube()
{
	cubeShader.Use();

	// Set MVP matrices.
	cubeShader.SetUniformMatrix4("model", cubeModelMatrix.GetModelMatrix());
	cubeShader.SetUniformMatrix4("view", camera.GetViewMatrix());
	cubeShader.SetUniformMatrix4("projection", camera.GetProjectionMatrix());

	// Set the normal matrix.
	cubeShader.SetUniformMatrix3("normalMatrix", normalMatrix);

	// Set lightning properties.
	cubeShader.SetUniformVector3("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));
	cubeShader.SetUniformFloat("ambientStrength", 0.2f);
	cubeShader.SetUniformVector3("ambientColor", glm::vec3(1.0f, 0.0f, 0.0f));
	cubeShader.SetUniformVector3("lightPosition", lightModelMatrix.GetPosition());
	cubeShader.SetUniformVector3("lightColor", glm::vec3(1.0f, 1.0f, 0.0f));
	cubeShader.SetUniformVector3("viewPosition", camera.GetPosition());
	cubeShader.SetUniformFloat("specularStrength", 0.8f);
	cubeShader.SetUniformFloat("shininess", 128.0f);

	// Set the positions.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Set the normals.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ProjectApplication::UpdateCameraTransform()
{
	// Update position.
	float cameraSpeed = 5.0f;
	camera.SetPosition(camera.GetPosition() + cameraMoveInput.y * camera.GetFacingDirection() * cameraSpeed * GetDeltaTime());
	camera.SetPosition(camera.GetPosition() + cameraMoveInput.x * camera.GetRightDirection() * cameraSpeed * GetDeltaTime());

	// Update rotation.
	if (shouldRotateCamera)
	{
		float cameraRotateSpeed = 1.0f;

		// Update the yaw.
		cameraYaw += -GetCursorDeltaX() * cameraRotateSpeed * GetDeltaTime();

		// Update the pitch.
		cameraPitch += -GetCursorDeltaY() * cameraRotateSpeed * GetDeltaTime();

		camera.SetRotation(cameraPitch, cameraYaw, 0.0f);

		glm::vec3 cameraEulerAngles = glm::eulerAngles(camera.GetRotation());
		std::cout << "Pitch: " << cameraEulerAngles.x << ", Yaw: " << cameraEulerAngles.y << ", Roll: " << cameraEulerAngles.z << std::endl;
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
