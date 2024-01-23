#pragma once
#include "vertexArray.h"


class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices = {});
	Mesh();
	Mesh(const Mesh& other);
	Mesh& operator=(const Mesh&) = delete;
	~Mesh();

	void draw(bool drawAsLines = false);
	void deleteObjects();

private:
	VertexArray vertexArray;
};


struct MeshCollection
{
	std::vector<Mesh> collection;
};