#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : vertexArray(vertices, indices)
{
}

void Mesh::draw()
{
	//  assume the shader is already in use (the rendering process should have done it)

	vertexArray.setActive();

	if (vertexArray.getUseEBO())
	{
		glDrawElements(GL_TRIANGLES, vertexArray.getNBIndices(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, vertexArray.getNBVertices());
	}
}

void Mesh::deleteObjects()
{
	vertexArray.deleteObjects();
}