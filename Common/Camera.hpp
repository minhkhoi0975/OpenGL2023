#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera
{
private:
	glm::vec3 position;
	glm::quat rotation;

private:
	float fov;              // In degrees.
	float aspectRatio;
	float nearClipPlane;
	float farClipPlane;
	glm::mat4 projectionMatrix;

private:
	void RecalculateProjectionMatrix();
	
public:
	Camera(float fov, float aspectRatio, float nearClipPlane, float farClipPlane);

public:
	inline glm::vec3 GetPosition() { return position; }
	inline glm::quat GetRotation() { return rotation; }

	glm::vec3 GetForwardDirection() const;
	glm::vec3 GetRightDirection() const;
	glm::vec3 GetUpDirection() const;

	void SetPosition(glm::vec3 newPosition);
	void SetRotation(float pitch, float yaw, float roll);
	void SetRotation(glm::quat newRotation);

public:
	void SetFov(float fovInDegrees);
	void SetAspectRatio(float aspectRatio);
	void SetNearClipPlane(float nearClipPlane);
	void SetFarClipPlane(float farClipPlane);

public:
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
};