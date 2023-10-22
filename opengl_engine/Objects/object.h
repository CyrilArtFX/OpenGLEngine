#pragma once

#include <Maths/Matrix4.h>

#include <Rendering/vertexArray.h>
#include <Rendering/shader.h>


struct Material
{
	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	float shininess;
};


class Object
{
public:
	Object(Shader& shaderUsed, const float* vertices, unsigned int nbVertices, const unsigned int* indices = 0, unsigned int nbIndices = 0);

	void draw();
	void deleteObject();

	void setMaterial(Material newMat);

	void setPosition(Vector3 newPos);
	void setScale(Vector3 newScale);
	void setScale(float newUniformScale);

private:
	void computeMatrix();

	Shader& shader;
	VertexArray vertexArray;

	Material material
	{
		Vector3{1.0f, 1.0f, 1.0f},
		Vector3{1.0f, 1.0f, 1.0f},
		Vector3{0.5f, 0.5f, 0.5f},
		32.0f
	};

	Vector3 position{ Vector3::zero };
	Vector3 scale{ Vector3::one };
	Matrix4 modelMatrix{ Matrix4::identity };
	Matrix4 normalMatrix{ Matrix4::identity };
};

