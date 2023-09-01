#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera
{
private:
	glm::vec3 position;
	glm::quat rotation;
	
public:
	Camera(glm::vec3 position);
	Camera(glm::vec3 position, glm::vec3 forwardDirection);

	glm::vec3 GetForwardDirection() const;
	glm::vec3 GetRightDirection() const;
	glm::vec3 GetUpDirection() const;

	void SetPosition(glm::vec3 newPosition);
	void SetRotation(float pitch, float yaw, float roll);
	void SetRotation(glm::quat newRotation);
};