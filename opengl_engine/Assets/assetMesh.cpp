#include "assetMesh.h"
#include <Utils/defines.h>
#include <iostream>

Mesh AssetMesh::LoadSingleMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    return Mesh(vertices, indices);
}

Mesh AssetMesh::LoadSingleMesh(std::string filepath)
{
    std::string mesh_path = RESOURCES_PATH + filepath;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(mesh_path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return Mesh();
    }
    //directory = mesh_path.substr(0, mesh_path.find_last_of(’ / ’));

    return processNodeSingle(scene->mRootNode, scene);
}

MeshCollection AssetMesh::LoadMeshCollection(std::string filepath)
{
    std::string meshes_path = RESOURCES_PATH + filepath;

    MeshCollection meshes;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshes_path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return meshes;
    }
    //directory = meshes_path.substr(0, meshes_path.find_last_of(’ / ’));

    processNodeCollection(scene->mRootNode, scene, meshes);

    return meshes;
}


Mesh AssetMesh::processNodeSingle(aiNode* node, const aiScene* scene)
{
    //  process the node first mesh (if it exists)
    if (node->mNumMeshes > 0)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[0]];
        return processMesh(mesh, scene);
    }

    return Mesh();

    //  this part may be changed to get the first mesh it encounters
}

void AssetMesh::processNodeCollection(aiNode* node, const aiScene* scene, MeshCollection& meshCollection)
{
    //  process all the node’s meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshCollection.collection.push_back(processMesh(mesh, scene));
    }
    //  then do the same recursively for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNodeCollection(node->mChildren[i], scene, meshCollection);
    }
}

Mesh AssetMesh::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    //  vertices
    for (int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        //  vertex position
        Vector3 pos;
        pos.x = mesh->mVertices[i].x;
        pos.y = mesh->mVertices[i].y;
        pos.z = mesh->mVertices[i].z;
        vertex.position = pos;

        //  vertex normal
        Vector3 normal;
        normal.x = mesh->mNormals[i].x;
        normal.y = mesh->mNormals[i].y;
        normal.z = mesh->mNormals[i].z;
        vertex.normal = normal;

        //  vertex texture coordinates
        if (mesh->mTextureCoords[0]) //  does the mesh contain texture coordinates?
        {
            Vector2 tex_coords;
            tex_coords.x = mesh->mTextureCoords[0][i].x;
            tex_coords.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = tex_coords;
        }
        else
        {
            vertex.texCoords = Vector2::zero;
        }

        vertices.push_back(vertex);
    }

    //  indices
    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh(vertices, indices);
}
