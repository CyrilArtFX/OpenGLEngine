#pragma once
#include <Objects/transform.h>
#include <Maths/Geometry/box.h>
#include <Rendering/Model/mesh.h>
#include <Rendering/material.h>
#include <Utils/Color.h>


/** Cube
* Contains a cube mesh, a box information and a transform that can be setup to be at a specific location (no rotation or scale).
*/
class Cube : private Transform
{
public:
	Cube();

	void setBox(const Box& boxInfos);

	void drawCube(Material& debugMaterial, const Color& drawColor);

private:
	Box box;

	Matrix4 boxModelMatrix{ Matrix4::identity };

	Mesh* cubeMesh{ nullptr };


	void computeBoxModelMatrix();
};

