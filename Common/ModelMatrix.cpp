#include "ModelMatrix.hpp"
#include <glm/gtx/quaternion.hpp>

glm::mat4 ModelMatrix::GetModelMatrix() const
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix *= glm::toMat4(rotation);
	modelMatrix = glm::scale(modelMatrix, scale);

	return modelMatrix;
}
