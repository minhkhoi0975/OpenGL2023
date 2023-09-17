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

#define MODEL_COUNT 3

// Should be duplicated and modified for each project in this solution.
class ProjectApplication : public Application
{
private:
    Model models[MODEL_COUNT];
    ModelMatrix modelMatrices[MODEL_COUNT];
    glm::mat3 normalMatrices[MODEL_COUNT];

private:
    Camera camera;
    float cameraYaw = 0.0f, cameraPitch = 0.0f;

    glm::vec2 cameraMoveInput = glm::vec2();
    bool shouldRotateCamera = false;

private:
    Shader cubeShader;

private:
    void UpdateNormalMatrices();

private:
    void DrawModels();

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