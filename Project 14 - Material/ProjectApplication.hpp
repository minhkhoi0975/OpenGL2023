#pragma once
#include "../Common/Application.hpp"
#include "../Common/VertexArray.hpp"
#include "../Common/VertexBuffer.hpp"
#include "../Common/ElementBuffer.hpp"
#include "../Common/Shader.hpp"
#include "../Common/Texture.hpp"
#include "../Common/Camera.hpp"
#include "../Common/ModelMatrix.hpp"

// Should be duplicated and modified for each project in this solution.
class ProjectApplication : public Application
{
private:
	VertexArray vertexArray;
	VertexBuffer vertexBuffer;
	Shader cubeShader;
    Shader lightShader;

	// Define the vertices of a cube.
    float vertices[216] =
    {
         // Positions         // Normals
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // The cube's model matrix.
    ModelMatrix cubeModelMatrix = ModelMatrix(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(glm::vec3(0.0f, 50.0f, 0.0f)), glm::vec3(2.0f, 3.0f, 1.0f));

    // The cube's normal matrix.
    glm::mat3 normalMatrix;

    // The light's model matrix.
    ModelMatrix lightModelMatrix = ModelMatrix(glm::vec3(5.0f, 5.0f, 5.0f), glm::quat(glm::vec3(0.0f, 50.0f, 0.0f)));

private:
    Camera camera;
    float cameraYaw = 0.0f, cameraPitch = 0.0f;

    glm::vec2 cameraMoveInput = glm::vec2();
    bool shouldRotateCamera = false;

private:
    void UpdateNormalMatrix();

private:
    void DrawLight();
    void DrawCube();

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