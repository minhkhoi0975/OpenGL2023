#include "Camera.hpp"

Camera::Camera(glm::vec3 position): position(position), rotation(glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)))
{
}

Camera::Camera(glm::vec3 position, glm::vec3 forwardDirection): position(position), rotation(glm::quatLookAt(-forwardDirection, glm::vec3(0.0f, 1.0f, 0.0f)))
{
}

glm::vec3 Camera::GetForwardDirection() const
{
	return rotation * glm::vec3(0.0f, 0.0f, -1.0f);
}

glm::vec3 Camera::GetRightDirection() const
{
	return rotation * glm::vec3(1.0f, 0.0f, 0.0f);
}

glm::vec3 Camera::GetUpDirection() const
{
	return rotation * glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Camera::SetRotation(float pitch, float yaw, float roll)
{
	rotation = glm::quat(glm::vec3(-pitch, -yaw, -roll));
}

void Camera::SetRotation(glm::quat newRotation)
{
	rotation = newRotation;
}
