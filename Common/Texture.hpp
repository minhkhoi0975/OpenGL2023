#pragma once
#include <glad/glad.h>
#include <string>

enum class TextureType
{
	Unknown = 0,
	Diffuse = 1,
	Specular = 2
};

class Texture
{
private:
	unsigned int id = -1;

	int width;
	int height;
	int nrChannels;
	unsigned char* data;

	std::string filePath;
	TextureType textureType;

public:
	Texture(const char* filePath, TextureType textureType = TextureType::Unknown, const int& imageFormat = GL_RGBA);
	~Texture();

	void Use();
	inline std::string GetFilePath() { return filePath; }
	inline TextureType GetTextureType() { return textureType; }
};