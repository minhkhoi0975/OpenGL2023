#include "ProjectApplication.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <sstream>

ProjectApplication::ProjectApplication(const char* title, int windowWidth, int windowHeight) :
	Application(title, windowWidth, windowHeight),
	plainTextureShader("Shaders/material.vs", "Shaders/plain_texture.fs"),
	camera(45.0f, (float)windowWidth / windowHeight, 0.1f, 100.0f)
{
	// Initialize ImGui.
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 150");

	ImFont* font = io.Fonts->AddFontFromFileTTF("Fonts/DroidSans.ttf", 32.0f);
	IM_ASSERT(font != nullptr);

	// Set the models.
	models[0] = Model("models/backpack.obj");
	models[1] = Model("models/flyguy.obj");
	models[2] = Model("models/imc_grunt_anti_titan.obj");

	// Set the model matrices.
	UpdateModelMatrices();

	// Set the normal matrices.
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

	if (wireFrameMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Update models' matrices.
	UpdateModelMatrices();
	UpdateNormalMatrices();

	// Update the camera's position.
	UpdateCameraTransform(deltaTime);

	DrawModels();

	DrawImGuiWindows();
}

void ProjectApplication::OnShutdown()
{
	// Shutdown ImGui.
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ProjectApplication::DrawImGuiWindows()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (showDemoWindow)
		ImGui::ShowDemoWindow(&showDemoWindow);

	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::Begin("Settings", nullptr);
	ImGui::Checkbox("Wireframe Mode", &wireFrameMode);

	for (int i = 0; i < MODEL_COUNT; ++i)
	{
		std::string modelLabel = "Model ";
		modelLabel += std::to_string(i);
		ImGui::Text(modelLabel.c_str());

		std::string positionVariableName = "Position##Model ";
		positionVariableName += std::to_string(i);
		ImGui::InputFloat3(positionVariableName.c_str(), &modelPositions[i].x);

		std::string rotationVariableName = "Rotation##Model ";
		rotationVariableName += std::to_string(i);
		ImGui::DragFloat3(rotationVariableName.c_str(), &modelRotations[i].x, 1.0f, -180.0f, 180.0f, "%.3f");
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ProjectApplication::UpdateModelMatrices()
{
	for (int i = 0; i < MODEL_COUNT; ++i)
	{
		// Set position.
		modelMatrices[i].SetPosition(modelPositions[i]);

		// Set rotation.
		glm::quat modelRotationInDegrees = glm::quat(glm::vec3(
			glm::radians(modelRotations[i].x),
			glm::radians(modelRotations[i].y),
			glm::radians(modelRotations[i].z)));

		modelMatrices[i].SetRotation(modelRotationInDegrees);
	}
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
		plainTextureShader.Use();

		plainTextureShader.SetUniformMatrix4("model", modelMatrices[modelIndex].GetModelMatrix());
		plainTextureShader.SetUniformMatrix4("view", camera.GetViewMatrix());
		plainTextureShader.SetUniformMatrix4("projection", camera.GetProjectionMatrix());
		plainTextureShader.SetUniformMatrix3("normalMatrix", normalMatrices[modelIndex]);

		for (int i = 0; i < models[modelIndex].meshes.size(); ++i)
		{
			// TODO: Draw each mesh.
			models[modelIndex].meshes[i].Draw(plainTextureShader);
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
