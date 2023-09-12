#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies, std::vector<Texture> textures)
	: vertices(vertices), indicies(indicies), textures(textures), vao()
{
	vao.Use();

	vbo.Use();
	vbo.SetData(&vertices[0], vertices.size() * sizeof(Vertex));

	ebo.Use();
	ebo.SetData(&indicies[0], indicies.size() * sizeof(unsigned int));

	/*
	// Set the positions.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// Set the normals.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	// Set the texture coordinates.
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
	*/

	vao.Unuse();
}
