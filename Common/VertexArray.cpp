#include "VertexArray.hpp"
#include <glad/glad.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

void VertexArray::Use()
{
	glBindVertexArray(id);
}

void VertexArray::Unuse()
{
	glBindVertexArray(0);
}
