#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies, std::vector<Texture> textures)
	: vertices(vertices), indicies(indicies), textures(textures)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), &indicies[0], GL_STATIC_DRAW);

	// Set the positions.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// Set the normals.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	// Set the texture coordinates.
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

	glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader)
{
	unsigned int diffuseIndex = 0;
	unsigned int specularIndex = 0;

	for (int i = 0; i < textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string variableName = "material";
		TextureType textureType = textures[i].GetTextureType();

		if (textureType == TextureType::Diffuse)
			variableName += ".diffuse" + std::to_string(diffuseIndex++);   // material.diffuse[index]
		else if (textureType == TextureType::Specular)
			variableName += ".specular" + std::to_string(specularIndex++); // material.specular[index]
		else // Skip unknown textures.
			continue;

		shader.SetUniformInt(variableName.c_str(), i);

		textures[i].Use();
	}

	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}