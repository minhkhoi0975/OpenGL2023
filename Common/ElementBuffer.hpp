#pragma once

class ElementBuffer
{
private:
	unsigned int id;

public:
	ElementBuffer();
	~ElementBuffer();

	void SetData(const void* data, int size);
	void Use();
	void Unuse();
};