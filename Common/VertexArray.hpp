#pragma once

class VertexArray
{
private:
	unsigned int id;

public:
	VertexArray();
	~VertexArray();

	void Use();
	void Unuse();
};