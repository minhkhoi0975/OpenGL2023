#pragma once
#include <glm/glm.hpp>

class Shader
{
private:
	unsigned int id = -1;

public:

	Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
	~Shader();

	unsigned int GetId() const;

	void Use() const;
	void Unuse() const;

	void SetUniformInt(const char* name, const int& value);
	void SetUniformFloat(const char* name, const float& value);
	void SetUniformVector3(const char* name, const glm::vec3& value);
	void SetUniformVector4(const char* name, const glm::vec4& value);
	void SetUniformMatrix3(const char* name, const glm::mat3& value);
	void SetUniformMatrix4(const char* name, const glm::mat4& value);
};