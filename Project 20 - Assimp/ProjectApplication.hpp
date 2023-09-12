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

// Should be duplicated and modified for each project in this solution.
class ProjectApplication : public Application
{
private:
    static const int POINT_LIGHT_COUNT = 4;
    glm::vec3 pointLightPositions[POINT_LIGHT_COUNT] = 
    {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };
    ModelMatrix pointLightModelMatrices[POINT_LIGHT_COUNT];

private:
    Model model;

private:
    Camera camera;
    float cameraYaw = 0.0f, cameraPitch = 0.0f;

    glm::vec2 cameraMoveInput = glm::vec2();
    bool shouldRotateCamera = false;

private:
    Shader cubeShader, lightShader;

private:
    void UpdateNormalMatrices();

private:
    void DrawLights();
    void DrawModel();

public:
	ProjectApplication(const char* title, int windowWidth, int windowHeight);

	void OnUpdate(const float& deltaTime) override;

public:
    void UpdateCameraTransform(const float& deltaTime);

public:
    virtual void OnWindowResized(int newWidth, int newHeight);
    virtual void OnKeyPressed(int key) override;
    virtual void OnKeyReleased(int key) override;
    virtual void OnMousePressed(int button) override;
    virtual void OnMouseReleased(int button) override;
};