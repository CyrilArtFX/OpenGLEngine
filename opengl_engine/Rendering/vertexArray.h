#pragma once

#include <glad/glad.h>

class VertexArray
{
public:
	/*
		* Give vertices with 3 spatial coordinates, 3 normal coordinates and 2 textures coordinates per vertex.
	*/
	VertexArray(const float* vertices, unsigned int nbVertices_, const unsigned int* indices = 0, unsigned int nbIndices_ = 0);
	VertexArray() = default;

	void setActive();
	void deleteObjects();

	unsigned int getNBVertices() { return nbVertices; }
	unsigned int getNBIndices() { return nbIndices; }

	unsigned int getVAO() { return VAO; }
	unsigned int getVBO() { return VBO; }
	unsigned int getEBO() { return EBO; }


private:
	unsigned int nbVertices;
	unsigned int nbIndices;

	unsigned int VAO; //  OpenGL ID
	unsigned int VBO; //  OpenGL ID
	unsigned int EBO; //  OpenGL ID
};

