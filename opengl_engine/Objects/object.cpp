#include "object.h"

Object::Object(Shader& shaderUsed, const float* vertices, unsigned int nbVertices, const unsigned int* indices, unsigned int nbIndices)
	: shader(shaderUsed), vertexArray(vertices, nbVertices, indices, nbIndices)
{
	computeMatrix();
}


void Object::draw()
{
	//  we assume that the shader is already in usage, because the renderer that call this function should already have set some uniforms on it

	shader.setMatrix4("model", modelMatrix.getAsFloatPtr());
	shader.setMatrix4("normalMatrix", normalMatrix.getAsFloatPtr());

	vertexArray.setActive();

	if (vertexArray.getNBIndices() == 0)
	{
		glDrawArrays(GL_TRIANGLES, 0, vertexArray.getNBVertices());
	}
	else
	{
		glDrawElements(GL_TRIANGLES, vertexArray.getNBIndices(), GL_UNSIGNED_INT, 0);
	}
}

void Object::deleteObject()
{
	vertexArray.deleteObjects();
}


void Object::setPosition(Vector3 newPos)
{
	position = newPos;
	computeMatrix();
}

void Object::setScale(Vector3 newScale)
{
	scale = newScale;
	computeMatrix();
}

void Object::setScale(float newUniformScale)
{
	setScale(Vector3{ newUniformScale, newUniformScale, newUniformScale });
}


void Object::computeMatrix()
{
	modelMatrix =
		Matrix4::createScale(scale) *
		Matrix4::createTranslation(position);

	normalMatrix = modelMatrix;
	normalMatrix.invert();
	normalMatrix.transpose();
}
