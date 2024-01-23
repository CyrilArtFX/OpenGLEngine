#pragma once
#include <Objects/transform.h>
#include <Rendering/Model/mesh.h>
#include <Rendering/material.h>
#include <Utils/Color.h>


/** Line
* Contains a line mesh and a transform that can be setup to go from a point A to a point B.
*/
class Line : private Transform
{
public:
	Line();

	void setPoints(Vector3 pointA, Vector3 pointB);

	void drawLine(Material& debugMaterial, const Color& drawColor);

private:
	Mesh* lineMesh{ nullptr };
};

