#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies, std::vector<Texture> textures)
	: vertices(vertices), indicies(indicies), textures(textures)
{
	vao = VertexArray();
	vbo = VertexBuffer();
	ebo = ElementBuffer();

	vbo.SetData(&vertices[0], vertices.size() * sizeof(Vertex));
	ebo.SetData(&indicies[0], indicies.size() * sizeof(unsigned int));
}
