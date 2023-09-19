#pragma once

#include <glad/glad.h>

class VertexBuffer
{
private:
	unsigned int id;

public:
	VertexBuffer();
	~VertexBuffer();

	void SetData(const void* data, int size, int usage = GL_STATIC_DRAW);
	void Use();
	void Unuse();
};