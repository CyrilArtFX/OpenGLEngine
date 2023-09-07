#pragma once

#include <glad/glad.h>

class VertexArray
{
public:
	unsigned int VAO; //  OpenGL ID
	unsigned int VBO; //  OpenGL ID
	unsigned int EBO; //  OpenGL ID


	/*Give vertices with 3 spatial coordinates and 2 textures coordinates per vertex.
	*/
	VertexArray(const float* vertices, unsigned int nbVertices_, const unsigned int* indices = 0, unsigned int nbIndices_ = 0);

	void setActive();
	void deleteObjects();

	unsigned int getNBVertices() { return nbVertices; }
	unsigned int getNBIndices() { return nbIndices; }


private:
	unsigned int nbVertices;
	unsigned int nbIndices;
};

