#pragma once
#include <glad/glad.h>

class Texture
{
private:
	unsigned int id = -1;

	int width;
	int height;
	int nrChannels;
	unsigned char* data;

public:
	Texture(const char* fileName, const int& imageFormat = GL_RGBA);
	~Texture();

	void Use();
};