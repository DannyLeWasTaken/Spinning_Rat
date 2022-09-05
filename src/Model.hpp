//
// Created by Danny Le on 2022-08-29.
//

#ifndef SPINNING_RAT_MODEL_HPP
#define SPINNING_RAT_MODEL_HPP

#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "Mesh.hpp"

class Model {

public:
    Model(const std::string &path);
private:
    std::vector<Texture> TexturesLoaded;
    std::vector<Mesh> Meshes;
    std::string Directory;

    void LoadModel(const std::string &path);
    void Draw(Shader &shader);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};


#endif //SPINNING_RAT_MODEL_HPP
