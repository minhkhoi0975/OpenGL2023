#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>



Texture::Texture(const char* filePath, TextureType textureType, const int& imageFormat) :
	filePath(filePath), textureType(textureType)
{
	// The origin of the image is in top left, but the origin of UV is bottom left.
	// Without calling this function, the image is vertically reversed.
	stbi_set_flip_vertically_on_load(true);

	// Load the image.
	data = stbi_load(filePath, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (!data)
	{
		std::cout << "Error: Cannot load the texture file " << filePath << std::endl;
		return;
	}

	// Generate a texture.
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Bind the image to the texture.
	glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free the image.
	stbi_image_free(data);

	std::cout << "Loaded texture from " << filePath << std::endl;
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::Use()
{
	glBindTexture(GL_TEXTURE_2D, id);
}
