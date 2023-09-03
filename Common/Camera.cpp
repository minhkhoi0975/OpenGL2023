#include "Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

void Camera::RecalculateProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClipPlane, farClipPlane);
}

Camera::Camera(float fov, float aspectRatio, float nearClipPlane, float farClipPlane)
	: position(), rotation(1.0f, 0.0f, 0.0f, 0.0f), 
	  fov(fov), aspectRatio(aspectRatio), nearClipPlane(nearClipPlane), farClipPlane(farClipPlane)
{
	RecalculateProjectionMatrix();
}

glm::vec3 Camera::GetForwardDirection() const
{
	// Note: In OpenGL, cameras face backwards in their coordinate system.
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

void Camera::SetFov(float fov)
{
	this->fov = fov;
	RecalculateProjectionMatrix();
}

void Camera::SetAspectRatio(float aspectRatio)
{
	this->aspectRatio = aspectRatio;
	RecalculateProjectionMatrix();
}

void Camera::SetNearClipPlane(float nearClipPlane)
{
	this->nearClipPlane = nearClipPlane;
	RecalculateProjectionMatrix();
}

void Camera::SetFarClipPlane(float farClipPlane)
{
	this->farClipPlane = farClipPlane;
	RecalculateProjectionMatrix();
}

glm::mat4 Camera::GetViewMatrix() const
{
	// Calculate the camera's model matrix.
	glm::mat4 cameraModelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation);

	// Inverse the matrix to get the view matrix.
	return glm::inverse(cameraModelMatrix);
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}
