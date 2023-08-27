#pragma once

class Shader
{
private:
	unsigned int id = -1;

public:

	Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);

	/// <summary>
	/// Returns the ID of the shader.
	/// </summary>
	unsigned int GetId() const;

	/// <summary>
	/// Makes OpenGL uses this shader program.
	/// </summary>
	void Use() const;
};