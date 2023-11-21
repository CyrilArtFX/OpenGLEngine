#include "object.h"

Object::Object(std::weak_ptr<Material> material_, std::weak_ptr<VertexArray> vertexArray_)
	: material(material_.lock()), vertexArray(vertexArray_.lock()), Transform()
{
}


void Object::draw()
{
	//  we assume that the shader is already in usage, because the renderer that call this function should already have set some uniforms on it

	material->getShader().setMatrix4("model", getModelMatrix().getAsFloatPtr());
	material->getShader().setMatrix4("normalMatrix", getNormalMatrix().getAsFloatPtr());

	material->use();

	vertexArray->setActive();

	if (vertexArray->getNBIndices() == 0)
	{
		glDrawArrays(GL_TRIANGLES, 0, vertexArray->getNBVertices());
	}
	else
	{
		glDrawElements(GL_TRIANGLES, vertexArray->getNBIndices(), GL_UNSIGNED_INT, 0);
	}
}

void Object::deleteObject()
{
}


void Object::setMaterial(std::weak_ptr<Material> newMat)
{
	material = newMat.lock();
}