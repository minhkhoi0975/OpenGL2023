#pragma once
#include <glm/glm.hpp>

class Shader
{
private:
	unsigned int id = -1;

public:

	Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
	~Shader();

	/// <summary>
	/// Returns the ID of the shader.
	/// </summary>
	unsigned int GetId() const;

	/// <summary>
	/// Makes OpenGL uses this shader program.
	/// </summary>
	void Use() const;

	void SetUniformInt(const char* name, const int& value);
	void SetUniformFloat(const char* name, const float& value);
	void SetUniformVector3(const char* name, const glm::vec3& value);
	void SetUniformVector4(const char* name, const glm::vec4& value);
	void SetUniformMatrix3(const char* name, const glm::mat3& value);
	void SetUniformMatrix4(const char* name, const glm::mat4& value);
};