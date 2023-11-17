#pragma once

#include <Maths/Vector3.h>
#include <Maths/Quaternion.h>
#include <Maths/Matrix4.h>

#include <Rendering/vertexArray.h>
#include <Rendering/material.h>



class Object
{
public:
	Object(std::weak_ptr<Material> material_, std::weak_ptr<VertexArray> vertexArray_);

	void draw();
	void deleteObject();

	void setMaterial(std::weak_ptr<Material> newMat);

	void setPosition(Vector3 newPos);
	void setScale(Vector3 newScale);
	void setScale(float newUniformScale);
	void setRotation(Quaternion newRotation);
	void incrementRotation(Quaternion increment);

	Vector3 getPosition() { return position; }
	Vector3 getScale() { return scale; }
	Quaternion getRotation() { return rotation; }

	Vector3 getForward();
	Vector3 getUp();
	Vector3 getRight();

private:
	void computeMatrix();

	std::shared_ptr<VertexArray> vertexArray;
	std::shared_ptr<Material> material;

	Vector3 position{ Vector3::zero };
	Vector3 scale{ Vector3::one };
	Quaternion rotation{ Quaternion::identity };
	Matrix4 modelMatrix{ Matrix4::identity };
	Matrix4 normalMatrix{ Matrix4::identity };
};

