#include "ElementBuffer.hpp"
#include <glad/glad.h>

ElementBuffer::ElementBuffer()
{
	glGenBuffers(1, &id);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &id);
}

void ElementBuffer::SetData(const void* data, int size)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void ElementBuffer::Use()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBuffer::Unuse()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
