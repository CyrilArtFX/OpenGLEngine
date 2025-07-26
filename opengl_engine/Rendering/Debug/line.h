#pragma once
#include "debugRenderBase.h"
#include <Maths/Vector3.h>

class VertexArray;

/** Line
* Transform a line vertex array to draw a line between two points
*/
class Line : public DebugRenderBase
{
public:
	Line();
	~Line();
	Line(const Line&) = delete;
	Line& operator=(const Line&) = delete;

	void setPoints(Vector3 pointA, Vector3 pointB);

	void draw(Material& debugMaterial, const Color& drawColor) override;

private:
	VertexArray& lineVA;

	Vector3 originPos{ Vector3::zero };
	Vector3 pointOffset{ Vector3::zero };
};

