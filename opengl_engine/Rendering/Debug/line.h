#pragma once
#include <Objects/transform.h>
#include <Rendering/material.h>
#include <Utils/Color.h>


/** Line
* Creates a custom VAO that is released at the destruction of this object.
*/
class Line : private Transform
{
public:
	Line();
	~Line();
	Line(const Line&) = delete;
	Line& operator=(const Line&) = delete;

	void setPoints(Vector3 pointA, Vector3 pointB);

	void drawLine(Material& debugMaterial, const Color& drawColor);

private:
	unsigned int lineVAO{ 0 };
	unsigned int lineVBO{ 0 };
};

