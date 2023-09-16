#pragma once

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"

#include "Vertex.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

#include <vector>

class Mesh
{
public:
	unsigned int vao, vbo, ebo;

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indicies;
	std::vector<Texture> textures;

public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies, std::vector<Texture> textures);

public:
	void Draw(Shader& shader);
};