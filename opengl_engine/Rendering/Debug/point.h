#pragma once
#include <Objects/transform.h>
#include <Rendering/Model/mesh.h>
#include <Rendering/material.h>
#include <Utils/Color.h>

//  scale of the cube mesh
const float pointSize = 0.05f;

/** Point
* Contains a cube mesh and a transform that can be setup to be at a specific location.
* 
* For now, this works with a cube mesh that is not scaled with the camera distance so it may be either too big or too small depending on the situation.
* May change that later.
*/
class Point : private Transform
{
public:
	Point();

	void setPointPostition(Vector3 pointPosition);

	void drawPoint(Material& debugMaterial, const Color& drawColor);

private:
	Mesh* cubeMesh{ nullptr };
};

