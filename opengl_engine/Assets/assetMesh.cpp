#include "assetMesh.h"

Mesh AssetMesh::LoadSingleMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    Mesh mesh;
    mesh.load(vertices, indices);
    return mesh;
}

Mesh AssetMesh::LoadSingleMesh(std::string filepath)
{
    Mesh mesh;
    return mesh;
}

MeshCollection AssetMesh::LoadMeshCollection(std::string filepath)
{
    MeshCollection meshes;
    return meshes;
}
