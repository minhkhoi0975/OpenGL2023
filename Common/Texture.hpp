#pragma once

class Texture
{
private:
	unsigned int id = -1;

	int width;
	int height;
	int nrChannels;
	unsigned char* data;

public:
	Texture(const char* fileName);
	~Texture();

	void Use();
};