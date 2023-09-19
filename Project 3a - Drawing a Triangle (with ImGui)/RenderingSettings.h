#pragma once

#include <glm/glm.hpp>

struct RenderingSettings
{
	// Background settings.
	glm::vec3 backgroundColor = glm::vec3(0.2f, 0.3f, 0.3f);

	// Triangle settings.
	float vertexPositions[9] =
	{
	   -0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	glm::vec3 triangleColor = glm::vec3(1.0f, 0.0f, 0.0f);
	bool wireframeMode = false;
};

