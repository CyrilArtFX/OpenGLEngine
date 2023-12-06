#pragma once

#include <Rendering/Model/vertexArray.h>
#include <Rendering/material.h>

#include "transform.h"


class Object : public Transform
{
public:
	Object(std::weak_ptr<Material> material_, std::weak_ptr<VertexArray> vertexArray_);

	void draw();
	void deleteObject();

	void setMaterial(std::weak_ptr<Material> newMat);

private:
	std::shared_ptr<VertexArray> vertexArray;
	std::shared_ptr<Material> material;
};

