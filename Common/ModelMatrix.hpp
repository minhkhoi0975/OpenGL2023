#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ModelMatrix
{
private:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

public:
	ModelMatrix(glm::vec3 position = glm::vec3(), glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f))
		: position(position), rotation(rotation), scale(scale) {};

	inline glm::vec3 GetPosition() const { return position; }
	inline glm::quat GetRotation() const { return rotation; }
	inline glm::vec3 GetScale() const { return scale; }
	glm::mat4 GetModelMatrix() const;

	inline void SetPosition(const float& x, const float& y, const float& z) { position.x = x; position.y = y; position.z = z; };
	inline void SetPosition(const glm::vec3& newPosition) { position = newPosition; }
	inline void Translate(const glm::vec3& moveVector) { position += moveVector; }
	inline void Translate(const float& x, const float& y, const float& z) { position.x += x; position.y += y; position.z += z; }

	inline void SetRotation(const glm::quat& newRotation) { rotation = newRotation; }
	inline void Rotate(const glm::quat& quat) { rotation = quat * rotation; }

	inline void SetScale(const glm::vec3& newScale) { scale = newScale; }
};