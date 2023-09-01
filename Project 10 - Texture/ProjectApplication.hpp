#pragma once
#include "../Common/Application.hpp"
#include "../Common/VertexArray.hpp"
#include "../Common/VertexBuffer.hpp"
#include "../Common/ElementBuffer.hpp"
#include "../Common/Shader.hpp"
#include "../Common/Texture.hpp"

// Should be duplicated and modified for each project in this solution.
class ProjectApplication : public Application
{
private:
	VertexArray vertexArray;
	VertexBuffer vertexBuffer;
	ElementBuffer elementBuffer;
	Texture texture;
	Shader shader;
	glm::vec4 baseColor;

	// Define the vertices of the quad.
	float vertices[20] =
	{
		// Positions        // UV coordinates  
	   -0.5f,  0.5f, 0.0f,	0.0f, 1.0f,	       // Top left
	   -0.5f, -0.5f, 0.0f,	0.0f, 0.0f,	       // Bottom left
		0.5f,  0.5f, 0.0f,  1.0f, 1.0f,		   // Top right
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f		   // Bottom right
	};

	// Define the indicies of the triangles.
	unsigned int indicies[6] =
	{
		2, 0, 1, // Top left
		3, 2, 1  // Bottom right
	};

public:
	ProjectApplication(const char* title, int windowWidth, int windowHeight);

	void OnUpdate() override;
};