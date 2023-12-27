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
	VertexArray(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	VertexArray();
	VertexArray(const VertexArray& other);
	VertexArray& operator=(const VertexArray&) = delete;
	~VertexArray();

	void setActive();
	void deleteObjects();

	unsigned int getNBVertices() const { return nbVertices; }
	unsigned int getNBIndices() const { return nbIndices; }

	unsigned int getVAO() const { return VAO; }
	unsigned int getVBO() const { return VBO; }
	unsigned int getEBO() const { return EBO; }

	bool getUseEBO() const { return useEBO; }


private:
	unsigned int nbVertices{ 0 };
	unsigned int nbIndices{ 0 };

	bool useEBO{ false };

	unsigned int VAO{ 0 }; //  OpenGL ID
	unsigned int VBO{ 0 }; //  OpenGL ID
	unsigned int EBO{ 0 }; //  OpenGL ID
};

