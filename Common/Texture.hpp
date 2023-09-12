#pragma once
#include <glad/glad.h>

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

	const char* filePath;
	TextureType textureType;

public:
	Texture(const char* filePath, TextureType textureType = TextureType::Unknown, const int& imageFormat = GL_RGBA);
	~Texture();

	void Use();
};