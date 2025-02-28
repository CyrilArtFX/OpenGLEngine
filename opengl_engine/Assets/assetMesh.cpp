#include "assetMesh.h"
#include <Utils/defines.h>
#include <ServiceLocator/locator.h>

LoadMeshData AssetMesh::LoadSingleMesh(const std::string& filepath)
{
    const std::string mesh_path = RESOURCES_PATH + filepath;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(mesh_path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode)
    {
        Locator::getLog().LogMessage_Category("Assimp_Import: " + std::string(importer.GetErrorString()), LogCategory::Error);
        return LoadMeshData{};
    }
    //directory = mesh_path.substr(0, mesh_path.find_last_of(� / �));

    return processNodeSingle(scene->mRootNode, scene);
}

std::vector<LoadMeshData> AssetMesh::LoadMeshCollection(const std::string& filepath)
{
    const std::string meshes_path = RESOURCES_PATH + filepath;

    std::vector<LoadMeshData> meshes_datas;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshes_path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode)
    {
        Locator::getLog().LogMessage_Category("Assimp_Import: " + std::string(importer.GetErrorString()), LogCategory::Error);
        return meshes_datas;
    }
    //directory = meshes_path.substr(0, meshes_path.find_last_of(� / �));

    processNodeCollection(scene->mRootNode, scene, meshes_datas);

    return meshes_datas;
}


LoadMeshData AssetMesh::processNodeSingle(aiNode* node, const aiScene* scene)
{
    //  process the node first mesh (if it exists)
    if (node->mNumMeshes > 0)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[0]];
        return processMesh(mesh, node, scene);
    }

    return LoadMeshData{};

    //  this part may be changed to get the first mesh it encounters
}

void AssetMesh::processNodeCollection(aiNode* node, const aiScene* scene, std::vector<LoadMeshData>& meshCollection)
{
    //  process all the node�s meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshCollection.push_back(processMesh(mesh, node, scene));
    }
    //  then do the same recursively for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNodeCollection(node->mChildren[i], scene, meshCollection);
    }
}

LoadMeshData AssetMesh::processMesh(aiMesh* mesh, aiNode* node, const aiScene* scene)
{
    aiMatrix4x4 node_matrix = retrieveParentTransform(node);
    aiMatrix4x4 node_matrix_normal = node_matrix;
    node_matrix_normal.Inverse();
    node_matrix_normal.Transpose();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    int material = mesh->mMaterialIndex;

    //  vertices
    vertices.reserve(mesh->mNumVertices);
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        //  vertex position
        aiVector3D vertices_transformed = mesh->mVertices[i];
        vertices_transformed *= node_matrix;

        Vector3 pos;
        pos.x = vertices_transformed.x;
        pos.y = vertices_transformed.y;
        pos.z = vertices_transformed.z;
        vertex.position = pos;

        //  vertex normal
        aiVector3D normal_transformed = mesh->mNormals[i];
        normal_transformed *= node_matrix_normal; //  it is supposed to rotate the normal properly if the node has a rotation but I'm not sure it works perfectly

        Vector3 normal;
        normal.x = normal_transformed.x;
        normal.y = normal_transformed.y;
        normal.z = normal_transformed.z;
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
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    return LoadMeshData{ vertices, indices, material };
}

aiMatrix4x4 AssetMesh::retrieveParentTransform(aiNode* node)
{
    aiNode* parent = node->mParent;
    if (parent == nullptr) return node->mTransformation;

    return retrieveParentTransform(node->mParent) * node->mTransformation;
}
