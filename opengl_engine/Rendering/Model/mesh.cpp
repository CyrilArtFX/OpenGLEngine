#include "mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const int matId) : 
	vertexArray(), materialIndex(matId)
{
	vertexArray.LoadVAMesh(vertices, indices);
}

Mesh::Mesh() :
	vertexArray(), materialIndex(0)
{
}

Mesh::~Mesh()
{
}


void Mesh::draw(bool drawAsLines)
{
	//  assume the shader is already in use (the rendering process should have done it)

	vertexArray.setActive();

	GLuint draw_method = drawAsLines ? GL_LINE_STRIP : GL_TRIANGLES;

	if (vertexArray.getUseEBO())
	{
		glDrawElements(draw_method, vertexArray.getNBIndices(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(draw_method, 0, vertexArray.getNBVertices());
	}
}