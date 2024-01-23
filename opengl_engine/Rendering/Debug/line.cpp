#include "line.h"
#include <Assets/assetManager.h>

Line::Line()
{
	lineMesh = &AssetManager::GetSingleMesh("debug_line");
}

void Line::setPoints(Vector3 pointA, Vector3 pointB)
{
	//  position to point A
	setPosition(pointA);

	//  scale to the distance between point A and point B
	Vector3 a_to_b = pointB - pointA;
	setScale(a_to_b.length());

	//  orient toward point B
	a_to_b.normalize();
	Vector3 rotation_axis = Vector3::cross(Vector3::unitX, a_to_b);
	float rotation_angle = Maths::acos(Vector3::dot(Vector3::unitX, a_to_b));
	setRotation(Quaternion{ rotation_axis, rotation_angle });
}

void Line::drawLine(Material& debugMaterial, const Color& drawColor)
{
	debugMaterial.getShader().setMatrix4("model", getModelMatrix().getAsFloatPtr());
	debugMaterial.getShader().setVec3("color", drawColor);
	
	lineMesh->draw(true);
}