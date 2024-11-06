#pragma once
#include "vertexArray.h"
#include <memory>


class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices = {}, const int matId = 0);
	Mesh();
	Mesh(const Mesh& other) = delete;
	Mesh& operator=(const Mesh&) = delete;
	~Mesh();

	int getMaterialIndex() const { return materialIndex; }

	void draw(bool drawAsLines = false);

private:
	VertexArray vertexArray;
	int materialIndex;
};


struct MeshCollection
{
	std::vector<std::unique_ptr<Mesh>> collection{};

	MeshCollection() {}
	MeshCollection(const MeshCollection&) = delete;
	MeshCollection& operator=(const MeshCollection&) = delete;
};