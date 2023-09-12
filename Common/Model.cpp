#include "Model.hpp"

#include <iostream>

Model::Model(const char* path)
{
	// Load model from file.
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "Error: Cannot load model from " << path << std::endl;
		return;
	}

	textureDirectory = path;
	textureDirectory = textureDirectory.substr(0, textureDirectory.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	// Process the meshes of the node.
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	// Process the meshes of the child node.
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
		ProcessNode(node->mChildren[i], scene);
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indicies;
	std::vector<Texture> textures;

	// Process the vertices.
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;

		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;

		if (mesh->HasTextureCoords(0))
		{
			vertex.textureCoordinates.x = mesh->mTextureCoords[0][i].x;
			vertex.textureCoordinates.y = mesh->mTextureCoords[0][i].y;
		}
	}

	// Process the indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; ++j)
			indicies.push_back(face.mIndices[j]);
	}

	// Process the textures.
	if (mesh->mMaterialIndex > 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// Add diffuse maps.
		std::vector<Texture> diffuseMaps = LoadTextures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		// Add specular maps.
		std::vector<Texture> specularMaps = LoadTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indicies, textures);
}

std::vector<Texture> Model::LoadTextures(aiMaterial* material, aiTextureType textureType)
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < material->GetTextureCount(textureType); ++i)
	{
		aiString string;
		material->GetTexture(textureType, i, &string);

		std::string textureFilePath = textureDirectory + "/" + string.C_Str();
		const char* textureFilePathCStr = textureFilePath.c_str();
		std::cout << "Loading " << textureFilePath << std::endl;

		//Texture texture(string.C_Str(), GetTextureType(textureType));
		Texture texture(textureFilePathCStr, GetTextureType(textureType));
		textures.push_back(texture);
	}

	return textures;
}

TextureType Model::GetTextureType(aiTextureType assimpTextureType)
{
	switch (assimpTextureType)
	{
	case aiTextureType_DIFFUSE:
		return TextureType::Diffuse;
	case aiTextureType_SPECULAR:
		return TextureType::Specular;
	}

	return TextureType::Unknown;
}
