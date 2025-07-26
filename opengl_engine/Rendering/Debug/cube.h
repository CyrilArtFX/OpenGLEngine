#pragma once
#include "debugRenderBase.h"
#include <Core/transform.h>
#include <Maths/Geometry/box.h>
#include <Rendering/Model/mesh.h>


/** Cube
* Contains a cube mesh, a box information and a transform that can be setup to be at a specific location (no rotation or scale).
*/
class Cube : public DebugRenderBase, private Transform
{
public:
	Cube();

	void setBox(const Box& boxInfos);

	void draw(Material& debugMaterial, const Color& drawColor) override;

private:
	Box box;

	Matrix4 boxModelMatrix{ Matrix4::identity };

	Mesh* cubeMesh{ nullptr };


	void computeBoxModelMatrix();
};

