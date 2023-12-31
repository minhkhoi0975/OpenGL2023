#include "Model.hpp"

#include <iostream>

Model::Model() {}

Model::Model(const char* path)
{
	LoadModel(path);
}

void Model::LoadModel(const char* path)
{
	// Load model from file.
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals /* | aiProcess_FlipUVs*/);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "Error: Cannot load model from " << path << std::endl;
		return;
	}

	textureDirectory = path;
	textureDirectory = textureDirectory.substr(0, textureDirectory.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void Model::Draw(Shader& shader)
{
	for (unsigned int i = 0, ni = meshes.size(); i < ni; ++i)
		meshes[i].Draw(shader);
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

		vertices.push_back(vertex);
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

	std::cout
		<< "Loaded mesh: " << std::endl
		<< "+ Vertices count: " << vertices.size() << std::endl
		<< "+ Indicies count: " << indicies.size() << std::endl
		<< "+ Textures count: " << textures.size() << std::endl;

	return Mesh(vertices, indicies, textures);
}

std::vector<Texture> Model::LoadTextures(aiMaterial* material, aiTextureType textureType)
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < material->GetTextureCount(textureType); ++i)
	{
		aiString string;
		material->GetTexture(textureType, i, &string);

		// Only keep the file name of the texture instead of using the whole path.
		std::string fileName = string.C_Str();
		fileName = fileName.substr(fileName.find_last_of("/\\") + 1);

		std::string textureFilePath = textureDirectory + "/" + fileName;
		const char* textureFilePathCStr = textureFilePath.c_str();

		// Don't load the texture if it has already been loaded.
		bool skip = false;
		for (unsigned int j = 0; j < loadedTextures.size(); ++j)
		{
			if (loadedTextures[j].GetFilePath().compare(textureFilePath) == 0)
			{
				textures.push_back(loadedTextures[j]);
				skip = true;
				break;
			}
		}

		// Texture needs to be loaded from file.
		if (!skip)
		{
			//Texture texture(textureFilePathCStr, GetTextureType(textureType));
			Texture texture;
			texture.Load(textureFilePathCStr, GetTextureType(textureType));
			textures.push_back(texture);
			loadedTextures.push_back(texture);
		}
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
