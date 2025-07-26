#pragma once
#include "debugRenderBase.h"
#include <Core/transform.h>
#include <Rendering/Model/mesh.h>

//  scale of the cube mesh
const float pointSize = 0.05f;

/** Point
* Contains a cube mesh and a transform that can be setup to be at a specific location.
* 
* For now, this works with a cube mesh that is not scaled with the camera distance so it may be either too big or too small depending on the situation.
* May change that later.
*/
class Point : public DebugRenderBase, private Transform
{
public:
	Point();

	void setPointPostition(Vector3 pointPosition);

	void draw(Material& debugMaterial, const Color& drawColor) override;

private:
	Mesh* cubeMesh{ nullptr };
};

