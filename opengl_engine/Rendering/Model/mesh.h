#pragma once
#include "vertexArray.h"


class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices = {}, int matId  = 0);
	Mesh();
	Mesh(const Mesh& other);
	Mesh& operator=(const Mesh&) = delete;
	~Mesh();

	int getMaterialIndex() { return materialIndex; }

	void draw(bool drawAsLines = false);
	void deleteObjects();

private:
	VertexArray vertexArray;
	int materialIndex;
};


struct MeshCollection
{
	std::vector<Mesh> collection;
};