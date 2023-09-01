#include "VertexBuffer.hpp"
#include <glad/glad.h>

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &id);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &id);
}

void VertexBuffer::SetData(const void* data, int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Use()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unuse()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
