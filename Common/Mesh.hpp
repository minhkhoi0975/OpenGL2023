#pragma once

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"

#include "Vertex.hpp"
#include "Texture.hpp"

#include <vector>

class Mesh
{
private:
	VertexArray vao;
	VertexBuffer vbo;
	ElementBuffer ebo;

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indicies;
	std::vector<Texture> textures;

public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies, std::vector<Texture> textures);
};