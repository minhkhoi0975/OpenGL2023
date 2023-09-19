#pragma once
#include "../Common/Application.hpp"
#include "../Common/VertexArray.hpp"
#include "../Common/VertexBuffer.hpp"
#include "../Common/ElementBuffer.hpp"
#include "../Common/Shader.hpp"
#include "../Common/Texture.hpp"
#include "../Common/Camera.hpp"
#include "../Common/ModelMatrix.hpp"
#include "../Common/Model.hpp"
#include "../Common/DirectionalLight.hpp"

#define MODEL_COUNT 3

// Should be duplicated and modified for each project in this solution.
class ProjectApplication : public Application
{
// ImGui's properties.
private:
    bool showDemoWindow = true;
    float value1 = 0;
    float value2 = 0;
    int currentOperation = 0;
    int result = 0;

private:
    void DrawImGuiWindows();
    void DrawMenuBar();
    void DrawCalculatorWindow();

public:
	ProjectApplication(const char* title, int windowWidth, int windowHeight);

	void OnUpdate(const float& deltaTime) override;
    void OnShutdown() override;

public:
    void UpdateCameraTransform(const float& deltaTime);

public:
    virtual void OnWindowResized(int newWidth, int newHeight) override;
    virtual void OnKeyPressed(int key) override;
};