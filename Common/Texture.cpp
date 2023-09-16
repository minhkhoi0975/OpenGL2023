#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Texture::Texture() {}

Texture::Texture(const char* filePath, TextureType textureType)
{
	Load(filePath, textureType);
}

void Texture::Load(const char* filePath, TextureType textureType)
{
	this->filePath = filePath;
	this->textureType = textureType;

	// The origin of the image is in top left, but the origin of UV is bottom left.
	// Without calling this function, the image is vertically reversed.
	stbi_set_flip_vertically_on_load(true);

	// Load the image.
	data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "Error: Cannot load the texture file " << filePath << std::endl;
		stbi_image_free(data);
		return;
	}

	GLenum imageFormat = GL_RED;
	if (nrChannels == 1)
		imageFormat = GL_RED;
	else if (nrChannels == 3)
		imageFormat = GL_RGB;
	else if (nrChannels == 4)
		imageFormat = GL_RGBA;

	// Generate a texture.
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Free the image.
	stbi_image_free(data);

	std::cout << "Loaded texture from " << filePath << std::endl;
}

void Texture::Use()
{
	glBindTexture(GL_TEXTURE_2D, id);
}
