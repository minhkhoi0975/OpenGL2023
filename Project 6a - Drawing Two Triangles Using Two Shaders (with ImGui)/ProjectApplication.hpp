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
#include "RenderingSettings.h"

// Should be duplicated and modified for each project in this solution.
class ProjectApplication : public Application
{
private:
    RenderingSettings renderingSettings;

private:
    VertexArray vao1, vao2;
    VertexBuffer vbo1, vbo2;
    Shader shader1, shader2;

private:
    void DrawTriangles();
    void DrawImGuiWindows();
    void DrawWindow();

public:
	ProjectApplication(const char* title, int windowWidth, int windowHeight);

	void OnUpdate(const float& deltaTime) override;
    void OnShutdown() override;

public:
    virtual void OnWindowResized(int newWidth, int newHeight) override;
    virtual void OnKeyPressed(int key) override;
};