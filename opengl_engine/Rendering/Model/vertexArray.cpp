#include "vertexArray.h"

VertexArray::VertexArray(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : 
	nbVertices(vertices.size()),
	nbIndices(indices.size()),
	useEBO(indices.size() > 0)
{
	if (vertices.size() == 0) return;

	//  setup vertex buffer object and vertex array object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); //  bind the VAO before binding the vertex buffer, and before configuring vertex attributes 

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	if (useEBO) //  setup EBO if specified
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	}

	//  position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	//  normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	//  texture coordinates attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	//  unbind vertex array
	glBindVertexArray(0);
}


void VertexArray::setActive()
{
	glBindVertexArray(VAO);
}

void VertexArray::deleteObjects()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}



VertexArray::VertexArray(const VertexArray& other) :
	nbVertices(other.nbVertices), nbIndices(other.nbIndices),
	useEBO(other.useEBO),
	VAO(other.VAO), VBO(other.VBO), EBO(other.EBO)
{
}

VertexArray::VertexArray()
{
}

VertexArray::~VertexArray()
{
	deleteObjects();
}