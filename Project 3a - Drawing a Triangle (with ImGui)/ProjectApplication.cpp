#include "ProjectApplication.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ProjectApplication::ProjectApplication(const char* title, int windowWidth, int windowHeight) :
	Application(title, windowWidth, windowHeight), vao(), vbo(), shader("shaders/triangle.vs", "shaders/triangle.fs")
{
	vao.Use();
	vbo.Use();
	vbo.SetData(renderingSettings.vertexPositions, 9 * sizeof(float), GL_DYNAMIC_DRAW);

	shader.Use();

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

	// Enable depth testing.
	glEnable(GL_DEPTH_TEST);
}

void ProjectApplication::OnUpdate(const float& deltaTime)
{
	// Clear the render buffer.
	glClearColor(renderingSettings.backgroundColor.x, renderingSettings.backgroundColor.y, renderingSettings.backgroundColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawTriangle();
	DrawImGuiWindows();
}

void ProjectApplication::OnShutdown()
{
	// Shutdown ImGui.
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ProjectApplication::DrawTriangle()
{
	// Update the vertices' positions.
	vbo.SetData(renderingSettings.vertexPositions, 9 * sizeof(float), GL_DYNAMIC_DRAW);

	// Set wireframe mode.
	glPolygonMode(GL_FRONT_AND_BACK, renderingSettings.wireframeMode ? GL_LINE : GL_FILL);

	// Set the color of the triangle.
	shader.SetUniformVector3("color", renderingSettings.triangleColor);

	// Set the positions of the triangle's vertices.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ProjectApplication::DrawImGuiWindows()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	DrawWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ProjectApplication::DrawWindow()
{
	// Add properties here.

	ImGui::Begin("Properties");
	
	ImGui::ColorEdit3("Background Color", &renderingSettings.backgroundColor.x);

	ImGui::ColorEdit3("Triangle Color", &renderingSettings.triangleColor.x);
	for (int i = 0; i < 3; ++i)
	{
		std::string label = "Vertex " + std::to_string(i);
		ImGui::Text(label.c_str());

		std::string positionLabel = "Position##" + std::to_string(i);
		ImGui::DragFloat3(positionLabel.c_str(), &renderingSettings.vertexPositions[3 * i], 0.1f, -1.0f, 1.0f);
	}

	ImGui::Checkbox("Wireframe Mode", &renderingSettings.wireframeMode);

	ImGui::End();
}

void ProjectApplication::OnWindowResized(int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}

void ProjectApplication::OnKeyPressed(int key)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		CloseWindow();
		break;
	}
}
