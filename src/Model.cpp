//
// Created by Danny Le on 2022-08-29.
//

#include "Model.hpp"

#include <glad.h>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>
#include <string>
#include <vector>
#include "Mesh.hpp"
#include "stb_image.h"

unsigned int TextureFromFile(const char *path, std::string &directory);

Model::Model(const std::string &path)
{
    LoadModel(path);
}

void Model::Draw(Shader &shader)
{
    for (unsigned int i = 0; i < Meshes.size(); i++)
    {
        Meshes[i].Draw(shader);
    }
}

void Model::LoadModel(const std::string &path)
{
    Assimp::Importer importer;
    const aiScene* Scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
    if (!Scene || Scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
    {
        std::cout << "ERROR:ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    this->Directory = path.substr(0, path.find_last_of('/'));
    ProcessNode(Scene->mRootNode, Scene);
}

void Model::ProcessNode(aiNode* Node, const aiScene* scene)
{
    for (int i = 0; i < Node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[i];
        this->Meshes.push_back( ProcessMesh(mesh, scene) );
    }

    for (unsigned int i = 0; Node->mNumChildren; i++)
    {
        ProcessNode(Node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 position;
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z;
        vertex.Position = position;
        // add normals
        if (mesh->HasNormals())
        {
            glm::vec3 normal;
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;
            vertex.Normal = normal;
        }
        // add textures coordinates
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
        }
        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }
    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[i]);
        }
    }
    // process materials
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_diffuse");
        textures.end();
        diffuseMaps.begin();
        diffuseMaps.end();
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        // check if any textures have been loaded already
        for (unsigned int j = 0; j < TexturesLoaded.size(); j++)
        {
            if (std::strcmp(TexturesLoaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(TexturesLoaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->Directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            TexturesLoaded.push_back(texture);
        }
    }
    return textures;
}

unsigned int TextureFromFile(const char *path, std::string &directory)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}