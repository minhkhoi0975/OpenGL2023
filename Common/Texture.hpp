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
public:
	unsigned int id = -1;

	int width = 0;
	int height = 0;
	int nrChannels = 0;
	unsigned char* data = nullptr;

	std::string filePath = "";
	TextureType textureType = TextureType::Unknown;

public:
	virtual ~Texture() = default;
	Texture();
	Texture(const char* filePath, TextureType textureType = TextureType::Unknown);

	void Load(const char* filePath, TextureType textureType = TextureType::Unknown);
	void Use();
	inline std::string GetFilePath() { return filePath; }
	inline TextureType GetTextureType() { return textureType; }
};