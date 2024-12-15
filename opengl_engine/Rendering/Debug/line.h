#pragma once
#include <Maths/Vector3.h>
#include <Utils/Color.h>

class VertexArray;
class Material;

/** Line
* Creates a custom VAO that is released at the destruction of this object.
*/
class Line
{
public:
	Line();
	~Line();
	Line(const Line&) = delete;
	Line& operator=(const Line&) = delete;

	void setPoints(Vector3 pointA, Vector3 pointB);

	void drawLine(Material& debugMaterial, const Color& drawColor);

private:
	VertexArray& lineVA;

	Vector3 originPos{ Vector3::zero };
	Vector3 pointOffset{ Vector3::zero };
};

