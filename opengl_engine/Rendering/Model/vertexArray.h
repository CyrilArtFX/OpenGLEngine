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
	VertexArray();
	void load(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	void setActive();
	void deleteObjects();

	unsigned int getNBVertices() const { return nbVertices; }
	unsigned int getNBIndices() const { return nbIndices; }

	unsigned int getVAO() const { return VAO; }
	unsigned int getVBO() const { return VBO; }
	unsigned int getEBO() const { return EBO; }

	bool getUseEBO() const { return useEBO; }

	bool isLoaded() const { return loaded; }


private:
	bool loaded = false;

	unsigned int nbVertices = 0;
	unsigned int nbIndices = 0;

	bool useEBO = false;

	unsigned int VAO = 0; //  OpenGL ID
	unsigned int VBO = 0; //  OpenGL ID
	unsigned int EBO = 0; //  OpenGL ID
};

