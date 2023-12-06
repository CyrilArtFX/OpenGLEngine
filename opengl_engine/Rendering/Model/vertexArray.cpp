#include "vertexArray.h"

VertexArray::VertexArray(const float* vertices, unsigned int nbVertices_, const unsigned int* indices, unsigned int nbIndices_) :
	nbVertices(nbVertices_), nbIndices(nbIndices_)
{
	useEBO = nbIndices > 0;

	//  setup vertex buffer object and vertex array object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); //  bind the VAO before binding the vertex buffer, and before configuring vertex attributes

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, nbVertices * nbDataPerVertex * sizeof(float), vertices, GL_STATIC_DRAW);

	if (useEBO) //  setup EBO if specified
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}


	//  position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, nbDataPerVertex * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//  normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, nbDataPerVertex * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//  texture coordinates attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, nbDataPerVertex * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//  unbind vertex array
	glBindVertexArray(0);
}


VertexArray::VertexArray(std::vector<Vertex> vertices, std::vector<unsigned int> indices) :
	nbVertices(vertices.size()), nbIndices(indices.size()) 
{
	useEBO = indices.size() > 0;

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
