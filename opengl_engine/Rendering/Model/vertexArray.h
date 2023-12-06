#pragma once

#include <Maths/vector2.h>
#include <Maths/vector3.h>

#include <glad/glad.h>
#include <vector>


struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 texCoords;
};


class VertexArray
{
public:
	/**
	* Give vertices with 3 spatial coordinates, 3 normal coordinates and 2 textures coordinates per vertex.
	*/
	VertexArray(const float* vertices, unsigned int nbVertices_, const unsigned int* indices = 0, unsigned int nbIndices_ = 0);
	/**
	* Simplified version of the constructor using vectors and the Vertex struct.
	*/
	VertexArray(std::vector<Vertex> vertices, std::vector<unsigned int> indices = {});

	void setActive();
	void deleteObjects();

	unsigned int getNBVertices() const { return nbVertices; }
	unsigned int getNBIndices() const { return nbIndices; }

	unsigned int getVAO() const { return VAO; }
	unsigned int getVBO() const { return VBO; }
	unsigned int getEBO() const { return EBO; }

	bool getUseEBO() const { return useEBO; }


private:
	const unsigned int nbDataPerVertex = 8;

	unsigned int nbVertices;
	unsigned int nbIndices;

	bool useEBO;

	unsigned int VAO = 0; //  OpenGL ID
	unsigned int VBO = 0; //  OpenGL ID
	unsigned int EBO = 0; //  OpenGL ID
};

