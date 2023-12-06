#pragma once
#include "vertexArray.h"


class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices = {});

	void draw();
	void deleteObjects();

private:
	VertexArray vertexArray;
};