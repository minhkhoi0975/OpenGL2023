#pragma once

class VertexBuffer
{
private:
	unsigned int id;

public:
	VertexBuffer();
	~VertexBuffer();

	void SetData(const void* data, int size);
	void Use();
	void Unuse();
};