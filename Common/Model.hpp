#pragma once

#include "Mesh.hpp"
#include "Texture.hpp"

#include <vector>
#include <cstring>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	std::vector<Mesh> meshes;
	std::string textureDirectory;

private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadTextures(aiMaterial* material, aiTextureType textureType);
	TextureType GetTextureType(aiTextureType assimpTextureType);

public:
	Model(const char* path);
};