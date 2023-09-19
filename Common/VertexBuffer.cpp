#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &id);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &id);
}

void VertexBuffer::SetData(const void* data, int size, int usage)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::Use()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unuse()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
