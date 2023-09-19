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
	Application(title, windowWidth, windowHeight)
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

	// Enable depth testing.
	glEnable(GL_DEPTH_TEST);
}

void ProjectApplication::OnUpdate(const float& deltaTime)
{
	// Clear the render buffer.
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	DrawMenuBar();
	DrawCalculatorWindow();

	// Add control's properties here.

	ImGui::Begin("Hello World!", nullptr);
	ImGui::Checkbox("Show Demo Window", &showDemoWindow);

	// Add controls here.

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ProjectApplication::DrawMenuBar()
{
	const ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui::SetWindowPos(viewport->Pos);
	ImGui::SetWindowSize(ImVec2(viewport->Size.x, 10.0f));
	ImGui::Begin("Sample Menu Bar");

	ImGui::End();
}

void ProjectApplication::DrawCalculatorWindow()
{
	ImGui::Begin("Sample Calculator");
	ImGui::InputFloat("Value 1", &value1);
	ImGui::InputFloat("Value 2", &value2);
	ImGui::RadioButton("Add", &currentOperation, 0); ImGui::SameLine();
	ImGui::RadioButton("Subtract", &currentOperation, 1); ImGui::SameLine();
	ImGui::RadioButton("Multiply", &currentOperation, 2); ImGui::SameLine();
	ImGui::RadioButton("Division", &currentOperation, 3);

	std::string result = "Result: ";
	if (currentOperation == 0)
		result += std::to_string(value1 + value2);
	else if (currentOperation == 1)
		result += std::to_string(value1 - value2);
	else if (currentOperation == 2)
		result += std::to_string(value1 * value2);
	else
		result += std::to_string(value1 / value2);

	ImGui::Text(result.c_str());

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
